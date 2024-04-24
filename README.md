# Advent-Of-Code-2022

This repository serves as my progress tracker in learning the C programming language through participating in Advent of Code challenges. Each day's solution is implemented either in C or Python and stored in the `./src` folder with the file naming convention `dayXX.c` or `dayXX.py`, respectively, where `XX` represents the day number.

## Structure

- **`/src`**: Contains the source code for each day's challenge solution.
- **`.gitignore`**: Specifies intentionally untracked files that Git should ignore. This file helps keep the repository clean and focused.
- **`LICENSE.md`**: A file specifying the license under which the code in this repository is distributed. Licensing ensures that others know how they can use your code.

## Usage

1. Clone this repository to your local machine:

    ```bash
    git clone https://github.com/yourusername/advent-of-code-learning.git
    ```

2. Navigate to the cloned directory:

    ```bash
    cd advent-of-code-learning
    ```

3. To run a specific day's solution, compile the corresponding C file (if applicable) and execute the compiled binary or run the Python script:

    ```bash
    # For C solutions
    gcc ./src/dayXX.c -o dayXX
    ./dayXX

    # For Python solutions
    python3 ./src/dayXX.py
    ```

4. Input files, if required, can be provided directly in the code or fetched programmatically from the Advent of Code website.

## Advent of Code

Advent of Code is an annual event featuring a series of programming puzzles released daily in December. It's a great platform to enhance programming skills and explore different languages and problem-solving techniques. Check out [Advent of Code](https://adventofcode.com/) for more information.
