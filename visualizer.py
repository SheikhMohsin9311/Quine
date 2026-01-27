import re
import sys

def parse_dot(filename):
    """
    Parses a simple DOT file to extract parent-child relationships.
    Returns a dict: {parent: [children]}
    """
    tree = {}
    
    try:
        with open(filename, 'r') as f:
            lines = f.readlines()
            
        for line in lines:
            # Look for "Parent" -> "Child"; pattern
            match = re.search(r'"([^"]+)"\s*->\s*"([^"]+)"', line)
            if match:
                parent, child = match.groups()
                if parent not in tree:
                    tree[parent] = []
                tree[parent].append(child)
                
    except FileNotFoundError:
        print(f"Error: {filename} not found.")
        return {}
        
    return tree

def print_tree(tree, node, prefix="", is_last=True, file=None):
    """
    Recursively prints the tree in ASCII format.
    """
    # Define symbols
    branch = "└── " if is_last else "├── "
    
def print_tree(tree, node, prefix="", is_last=True, file=None, use_color=False):
    """
    Recursively prints the tree in ASCII format.
    """
    # Define symbols
    branch = "└── " if is_last else "├── "
    
    # Content creation
    if use_color:
        node_str = f"\033[92m{node}\033[0m"
    else:
        node_str = node
        
    content = f"{prefix}{branch}{node_str}"
    
    # Write to file if provided
    if file:
        file.write(content + "\n")
    else:
        # Default to stdout (which usually wants color)
        # Note: We ignore the file=None case used for stdout in previous version
        # and just print.
        print(content)
    
    # Update prefix for children
    new_prefix = prefix + ("    " if is_last else "│   ")
    
    if node in tree:
        children = tree[node]
        count = len(children)
        for i, child in enumerate(children):
            print_tree(tree, child, new_prefix, i == count - 1, file, use_color)

def main():
    print("\n\033[1m🧬 Digital Organism Genealogy 🧬\033[0m\n")
    
    root = "SEED"
    tree = parse_dot("genealogy.dot")
    
    if root not in tree and not tree:
        print("No genealogy data found (or tree is empty).")
        return

    # 1. Print to functionality (Stdout) - Color
    print(f"\033[91m{root}\033[0m")
    if root in tree:
        children = tree[root]
        for i, child in enumerate(children):
            print_tree(tree, child, "", i == len(children) - 1, file=None, use_color=True)
    print("\n")

    # 2. Save Plain Text (Clean)
    plain_filename = "genealogy_tree.txt"
    with open(plain_filename, "w") as f:
        f.write("Digital Organism Genealogy (Plain)\n\n")
        f.write(f"{root}\n")
        if root in tree:
            children = tree[root]
            for i, child in enumerate(children):
                print_tree(tree, child, "", i == len(children) - 1, file=f, use_color=False)

    # 3. Save Colored Text (ANSI)
    colored_filename = "genealogy_tree.ansi"
    with open(colored_filename, "w") as f:
        f.write("Digital Organism Genealogy (Colored)\n\n")
        f.write(f"\033[91m{root}\033[0m\n")
        if root in tree:
            children = tree[root]
            for i, child in enumerate(children):
                print_tree(tree, child, "", i == len(children) - 1, file=f, use_color=True)

    print(f"Saved plain tree to {plain_filename}")
    print(f"Saved colored tree to {colored_filename}")

if __name__ == "__main__":
    main()
