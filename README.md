# Quinie: A Self-Replicating Digital Organism 🐍

![Python](https://img.shields.io/badge/Language-Python-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Concept](https://img.shields.io/badge/Concept-Quine%20%26%20Recursion-purple)

> "To understand recursion, one must first understand recursion."

**Quinie** is a digital organism written in Python. It possesses the ability to reproduce, passing its own source code to its offspring while enforcing genetic constraints (generation limits) and tracking its own lineage.

This project visualizes the "Tree of Life" of a computer process.

**Note**: The original C++ version is archived in `cpp_version/`.

## 🌟 Features

-   **Self-Replication**: Reads its own source code and creates executable clones.
-   **Genealogy Tracking**: Every instance knows its "Parent ID" and logs the relationship to a distributed graph database (`genealogy.dot`).
-   **Safety Constraints**: Implements a "Hayflick Limit" (Max Generations) to prevent infinite loops.
-   **Visualization**: Includes both a Terminal (ASCII) and Web (HTML) visualizer.

## 🚀 Getting Started

### Prerequisites

-   Python 3.x

### Running the Simulation

```bash
make run
```

This will:
1.  Clean up previous runs.
2.  Execute the seed `quinie.py`.
3.  Wait for the colony to expand.
4.  Display the **ASCII Family Tree** in the terminal.
5.  Generate `genealogy.dot` for web viewing.

### Visualizing the Tree 🌳

**Option 1: Terminal**
The `make run` command automatically prints the tree at the end.

**Option 2: Web Browser**
Open `viewer.html` in your browser to see an interactive graph (requires `genealogy.dot` to be updated).

**Option 3: Text File**
The tree structure is also saved to `genealogy_tree.txt` for your records.

## 🧠 The Code

The core mechanic relies on Python's introspection:

```python
with open(__file__, "r") as f:
    src = f.read()
# Inject new state
new_src = src.replace("CURRENT_GEN = 0", "CURRENT_GEN = 1")
# Write to new file and execute
```

## 📜 License

This project is open source. Feel free to modify the DNA of this organism.
