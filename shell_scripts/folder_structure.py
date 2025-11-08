import os

path = "D:/CNotes"

def folder_structure(path: str, unrelated_dir :str, depth: int = 1 ):
    try:
        for entity in os.listdir(path):
            if entity in [".git", f"{ unrelated_dir }"]:
                print(".git or related file, not useful to know")
                continue

            print("-" * depth + f"{entity}")

            subpath = os.path.join(path, entity)
            if os.path.isdir(subpath):
                folder_structure(subpath, unrelated_dir ,depth + 1)
    except PermissionError:
        print("-" * depth + "[Permission Denied]")

print("-----FOLDER STRUCTURE-----")
folder_structure(path, "src")
print("-----FOLDER STRUCTURE END-----")

