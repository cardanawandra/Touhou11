import os
import json
import sys

def build_vfs_tree(root_path):
    contents = []
    for item in sorted(os.listdir(root_path)):
        full_path = os.path.join(root_path, item)
        if os.path.isdir(full_path):
            dir_contents = build_vfs_tree(full_path)
            if dir_contents:
                contents.append({
                    "type": "directory",
                    "name": item,
                    "contents": dir_contents
                })
        else:
            contents.append({
                "type": "file",
                "name": item,
                "external-contents": full_path
            })
    return contents

def main():
    if len(sys.argv) < 2:
        print("Usage: python3 GenerateVfs.py <path_to_directory>")
        sys.exit(1)
        
    # The VFS root must be an absolute path to match your -I flags
    target_path = os.path.abspath(sys.argv[1])
    
    vfs = {
        "version": 0,
        "case-sensitive": "false", # This disables case-sensitivity for this entire tree
        "roots": [
            {
                "type": "directory",
                "name": target_path,
                "contents": build_vfs_tree(target_path)
            }
        ]
    }
    
    with open("vfs-overlay.json", "w") as f:
        json.dump(vfs, f, indent=2)
        
    print(f"Generated vfs-overlay.json mapping for {target_path}")

if __name__ == "__main__":
    main()
