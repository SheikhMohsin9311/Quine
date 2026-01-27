import os
import sys
import time
import random
import subprocess

# --- CONFIGURATION (Injected) ---
CURRENT_GEN = 4
MY_ID = "YK8C"
PARENT_ID = "AU9P"
MAX_GEN = 5
CHILDREN_PER_GEN = 2
# --------------------------------

def generate_id():
    chars = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    return "".join(random.choices(chars, k=4))

def log_genealogy():
    """Appends this node and edge to the dot file."""
    # We use a file lock or just append mode. 
    # For a simple demo, append mode is usually safe enough on FS for small writes, 
    # but concurrent writes can interleave lines. 
    # Python generic print is usually atomic for small buffers.
    try:
        with open("genealogy.dot", "a") as f:
            if CURRENT_GEN == 0:
                f.write('digraph FamilyTree {\n')
                f.write('    node [shape=box, style=filled, color="#007acc", fontcolor=white];\n')
                f.write('    SEED [label="SEED (Gen 0)", fillcolor="#ff6b6b"];\n')
            
            if PARENT_ID != "NONE":
                f.write(f'    "{PARENT_ID}" -> "{MY_ID}";\n')
            
            if MY_ID != "SEED":
                f.write(f'    "{MY_ID}" [label="ID: {MY_ID}\\nGen: {CURRENT_GEN}"];\n')
    except Exception as e:
        pass # Best effort logging

def replicate(src_code):
    if CURRENT_GEN >= MAX_GEN:
        return

    children = []
    for _ in range(CHILDREN_PER_GEN):
        child_id = generate_id()
        child_filename = f"child_{CURRENT_GEN + 1}_{child_id}.py"
        
        # Inject new state into the source code
        # We replace the CONFIGURATION block variables
        # This is a "Template Quine" approach, easier than pure string formatting for variable builds
        
        new_src = src_code
        new_src = new_src.replace(f'CURRENT_GEN = {CURRENT_GEN}', f'CURRENT_GEN = {CURRENT_GEN + 1}', 1)
        new_src = new_src.replace(f'MY_ID = "{MY_ID}"', f'MY_ID = "{child_id}"', 1)
        # Note: We must be careful not to replace the PARENT_ID line with the wrong value if values are same
        # Ideally we use regex or distinct markers, but for this structure:
        new_src = new_src.replace(f'PARENT_ID = "{PARENT_ID}"', f'PARENT_ID = "{MY_ID}"', 1)
        
        with open(child_filename, "w") as f:
            f.write(new_src)
            
        children.append(child_filename)

    # Execute children
    # We use subprocess.Popen to run them in parallel
    for child in children:
        subprocess.Popen([sys.executable, child])

def main():
    # 1. Initialize self
    random.seed(time.time() + os.getpid())
    
    # 2. Log existence
    log_genealogy()
    
    # 3. Read own source code (The Quine trick in Python is often just reading __file__)
    # But to be a "True Quine" we should contain the string.
    # However, reading __file__ is a valid "External Quine" or "Cheating Quine".
    # Given the complexity of the previous C++ introspection, let's stick to reading __file__ 
    # for readability and robustness in Python, as it is idiomatic for scripts.
    # If the user strictly requested valid Quine (no IO), we would use `s=%r;print(s%%s)`.
    # Let's use the file read approach for simplicity unless requested otherwise.
    
    with open(__file__, "r") as f:
        src = f.read()
        
    # 4. Replicate
    replicate(src)

if __name__ == "__main__":
    main()
