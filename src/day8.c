#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool fileOpener(int argc, char *argv[], FILE **file);

int max(int *arr, int size);

int simulate(FILE *file, int *visible_score, int *rating_score);

int sum(int *arr, int size);

void update_visible(int *grid, int *visible, int *rating, int step, int jump,
                    int s, int j);

int main(int argc, char *argv[]) {
  FILE *file = NULL;
  if (!fileOpener(argc, argv, &file)) {
    return 1;
  }
  int visible = 0;
  int rating = 0;
  if (simulate(file, &visible, &rating)) {
    printf("The file is invalid\n");
  } else {
    printf("%d\n%d\n", visible, rating);
  }
  fclose(file); // Close the file after use
  return 0;
}

bool fileOpener(int argc, char *argv[], FILE **file) {
  if (argc == 1) {
    printf("No file has been provided\n");
    return false;
  }

  *file = fopen(argv[1], "r");
  if (*file == NULL) {
    perror("Error opening file");
    return false;
  }

  return true;
}

int max(const int *arr, int size) {
  int max_ = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > max_) {
      max_ = arr[i];
    }
  }
  return max_;
}

int simulate(FILE *file, int *visible_score, int *rating_score) {
  char c;
  int width = 0;
  int current_width = 0;
  int height = 1;
  while ((c = fgetc(file)) != EOF) {
    if (c == '\n') {
      height++;
      if (width && current_width != width) {
        return 1;
      } else {
        width = current_width;
        current_width = 0;
      }
    } else {
      current_width++;
    }
  }
  if (current_width == 0) {
    height -= 1;
  } else if (current_width != width) {
    return 1;
  }

  int *grid = malloc(sizeof(int) * width * height);
  int *visible = calloc(width * height, sizeof(int));
  int *rating = calloc(width * height, sizeof(int));

  if (grid == NULL || visible == NULL || rating == NULL) {
    perror("Memory allocation failed");
    return 1;
  }

  fseek(file, 0, SEEK_SET);
  int *grid_ptr = grid;
  while ((c = fgetc(file)) != EOF) {
    if (c != '\n') {
      *grid_ptr = c - '0';
      grid_ptr++;
    }
  }
  for (int i = 0; i < width * height; i++) {
    rating[i]++;
  }
  update_visible(grid, visible, rating, 1, width, width, height);
  update_visible(&grid[width - 1], &visible[width - 1], &rating[width - 1], -1,
                 width, width, height);
  update_visible(grid, visible, rating, height, 1, height, width);
  update_visible(&grid[width * height - width],
                 &visible[width * height - width],
                 &rating[width * height - width], -height, 1, height, width);
  *visible_score = sum(visible, width * height);
  *rating_score = max(rating, width * height);

  // Free allocated memory
  free(grid);
  free(visible);
  free(rating);

  return 0;
}

int sum(const int *arr, int size) {
  int sum_ = 0;
  for (int i = 0; i < size; i++) {
    sum_ += arr[i];
  }
  return sum_;
}

void update_visible(int *grid, int *visible, int *rating, int step, int jump,
                    int s, int j) {
  for (int _ = 0; _ < j; _++) {
    int *pre_grid = grid;
    int *pre_visible = visible;
    int *pre_rating = rating;
    int max_tree_height = -1;
    for (int __ = 0; __ < s; __++) {
      if (*grid > max_tree_height) {
        max_tree_height = *grid;
        *visible = 1;
      }
      int tree_height = *grid;
      int *temp = grid;
      int score = 0;
      while (grid != pre_grid) {
        score += 1;
        grid -= step;
        if (*grid >= tree_height) {
          break;
        }
      }
      *rating = *rating * score;
      grid = temp;
      grid += step;
      visible += step;
      rating += step;
    }

    grid = pre_grid + jump;
    visible = pre_visible + jump;
    rating = pre_rating + jump;
  }
}
