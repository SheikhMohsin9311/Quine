# Quinie: A Self-Replicating Digital Organism 🧬

![C++](https://img.shields.io/badge/Language-C++17-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Concept](https://img.shields.io/badge/Concept-Quine%20%26%20Recursion-purple)

> "To understand recursion, one must first understand recursion."

**Quinie** is not just a program; it is a digital organism. It possesses the ability to reproduce, passing its own source code to its offspring while enforcing genetic constraints (generation limits) and tracking its own lineage.

Using the concept of a **Quine** (a program that outputs its own source code), this project visualizes the "Tree of Life" of a computer program process.

## 🌟 Features

-   **Self-Replication**: Uses robust string formatting to reconstruct its own source code dynamically.
-   **Genealogy Tracking**: Every instance knows its "Parent ID" and logs the relationship to a distributed graph database (a `.dot` file).
-   **Safety Constraints**: Implements a "Hayflick Limit" (Max Generations) to prevent infinite loops and fork bombs.
-   **Visualization**: Generates a graph that can be rendered into a beautiful family tree.

## 🛠️ How It Works

### The Engine
The project uses a meta-programming approach to ensure perfect replication:
1.  **`template.cpp`**: The blueprint of the organism. It contains the logic for survival, reproduction, and logging.
2.  **`generator.py`**: The "Ribosome". It reads the template, properly escapes it into a C-string representation, and injects it back into the seed `quinie.cpp`.
3.  **`quinie.cpp`**: The Seed. The first alive instance.

When `quinie` runs:
1.  **Mitosis**: It reproduces by creating 2 child source files.
2.  **Inheritance**: It passes the *escaped* source string to the children so they can continue the cycle.
3.  **Logging**: All instances append their nodes and edges to `genealogy.dot`.
4.  **Execution**: Children are compiled and run in parallel/sequence.

## 🚀 Getting Started

### Prerequisites

-   Linux/Unix Environment
-   `g++` (GCC Compiler)
-   `graphviz` (for visualization)
-   `python3` (for building the seed)

### Running the Simulation

```bash
# Build the system and run the simulation
python3 generator.py && make run
```

This will:
1.  Generate the perfect seed `quinie.cpp`.
2.  Compile the seed.
3.  Execute the seed, spawning the colony as background processes.
4.  Wait 10 seconds for the colony to settle.
5.  Finalize `genealogy.dot`.

### Visualizing the Tree 🌳

If you have Graphviz installed:

```bash
dot -Tpng genealogy.dot -o tree.png
```

Open `tree.png` to see the full evolutionary tree of your program!

## 🧠 The Code (Simplified)

The core mechanic relies on a "Quine String" and an escape function:

```cpp
string escape_source(const char* s) {
    // Escapes special characters to keep the cycle going
    // ...
}

int main() {
    const char* s = "..."; // The DNA
    fprintf(fp, s, ..., escape_source(s).c_str(), 34);
}
```

## 📜 License

This project is open source. Feel free to modify the DNA of this organism.
