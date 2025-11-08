import os
from pathlib import Path

paths = [
    Path("D:/CNotes/canvas"), 
    Path("D:/CNotes/canvas/Tools"), 
    Path("D:/CNotes/canvas/UI"), 
    Path("D:/CNotes/notebook")
]

print("\n")
for i in range(len(paths)):
    current_path = paths[i]
    
    if not current_path.exists():
        print(f"Warning: Path not found: {current_path}")
        continue

    for item in current_path.iterdir():
        if item.is_file() and item.name.endswith(".c"):
            filename = os.path.join(current_path,item.name)
            print(f"{filename}")

