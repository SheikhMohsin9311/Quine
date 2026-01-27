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
    
    # Content to print
    content = f"{prefix}{branch}{node}"
    
    # Print to console with color
    print(f"{prefix}{branch}\033[92m{node}\033[0m")
    
    # Write to file without color if file handle provided
    if file:
        file.write(content + "\n")
    
    # Update prefix for children
    new_prefix = prefix + ("    " if is_last else "│   ")
    
    if node in tree:
        children = tree[node]
        count = len(children)
        for i, child in enumerate(children):
            print_tree(tree, child, new_prefix, i == count - 1, file)

def main():
    print("\n\033[1m🧬 Digital Organism Genealogy 🧬\033[0m\n")
    
    # Assuming SEED is always the root and named "SEED"
    root = "SEED"
    tree = parse_dot("genealogy.dot")
    
    if root not in tree and not tree:
        print("No genealogy data found (or tree is empty).")
        return

    output_filename = "genealogy_tree.txt"
    with open(output_filename, "w") as f:
        f.write("Digital Organism Genealogy\n\n")
        
        # Special case for the root to avoid visual clutter of the first branch
        print(f"\033[91m{root}\033[0m") # Red for root
        f.write(f"{root}\n")
        
        if root in tree:
            children = tree[root]
            for i, child in enumerate(children):
                print_tree(tree, child, "", i == len(children) - 1, f)

    print(f"\nExample tree saved to {output_filename}")

if __name__ == "__main__":
    main()
