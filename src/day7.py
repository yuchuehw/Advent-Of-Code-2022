import sys
from collections import namedtuple

UPPER_LIMIT = 100000
DISK_SPACE = 70000000
DISK_NEED = 30000000

File = namedtuple("File", "type name parent children")


def simulate(s: str):
    def calculate_size(folder: File, d: dict):
        for child in [_ for _ in folder.children if id(_) not in d]:
            calculate_size(child, d)
        d[id(folder)] = ("Folder", sum([d[id(_)][1] for _ in folder.children]))

    folder_tree = File("Folder", "", None, [])
    base = File("Folder", "/", folder_tree, [])
    folder_tree.children.append(base)
    ref = folder_tree
    size_dict = {}

    for i, line in enumerate(s.split("\n")):
        if line.startswith("$ cd .."):
            ref = ref.parent
            if ref is None:
                print("can not go up from /")
                print(f"{i+1}|{line}")
                exit()
        elif line.startswith("$ cd "):
            new_dir = line.replace("$ cd ", "")
            for child in ref.children:
                if child.type == "Folder" and child.name == new_dir:
                    ref = child
                    break
            else:
                print("folder not found")
                print(f"{i+1}|{line}")
                exit()
        elif line == "$ ls":
            pass
        elif not line.startswith("$") and line.startswith("dir "):
            child_folder = File("Folder", line[4:], ref, [])
            ref.children.append(child_folder)
        elif not line.startswith("$"):
            size, name = line.split(" ")
            child_file = File("File", name, None, None)
            size_dict[id(child_file)] = ("File", int(size))
            ref.children.append(child_file)
    calculate_size(folder_tree, size_dict)

    print(sum([j for i, j in size_dict.values() if i == "Folder" and j < UPPER_LIMIT]))

    min_to_del = DISK_NEED - (DISK_SPACE - size_dict[id(folder_tree)][1])
    print(min([j for i, j in size_dict.values() if i == "Folder" and j > min_to_del]))


with open(sys.argv[1] if len(sys.argv) > 1 else "input.txt", "r", encoding="utf8") as f:
    simulate(f.read())
