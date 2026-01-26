#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

string generate_id() {
    // srand moved to main
    const char input[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string id = "";
    for(int i=0; i<4; ++i) {
        id += input[rand() % (sizeof(input) - 1)];
    }
    return id;
}

string escape_source(const char* s) {
    string res;
    for (int i = 0; s[i]; ++i) {
        if (s[i] == '\n') {
            res += "\\n\"\n\"";
        } else if (s[i] == '\"') {
            res += "\\\"";
        } else if (s[i] == '\\') {
            res += "\\\\";
        } else {
            res += s[i];
        }
    }
    return res;
}

int main() {
    srand(time(0) + getpid());
    
    // Variable injection placeholders
    int current_gen = %d;
    string my_id = "%s";
    string parent_id = "%s";
    
    const int MAX_GEN = 5;
    const int CHILDREN_PER_GEN = 2;

    // The self-reference string
    const char* s = 
%c%s%c;

    if (current_gen >= MAX_GEN) {
        return 0;
    }

    ofstream graph("genealogy.dot", ios::app);
    if (graph.is_open()) {
        if (current_gen == 0) {
            graph << "digraph FamilyTree {\n";
            graph << "    node [shape=box, style=filled, color=\"#007acc\", fontcolor=white];\n";
            graph << "    SEED [label=\"SEED (Gen 0)\", fillcolor=\"#ff6b6b\"];\n";
        }
        if (parent_id != "NONE") {
             graph << "    \"" << parent_id << "\" -> \"" << my_id << "\";\n";
        }
        if (my_id != "SEED") {
             graph << "    \"" << my_id << "\" [label=\"ID: " << my_id << "\\nGen: " << current_gen << "\"];\n";
        }
        graph.close();
    }

    for (int i = 0; i < CHILDREN_PER_GEN; ++i) {
        string child_id = generate_id();
        string filename = "child_" + to_string(current_gen + 1) + "_" + child_id + ".cpp";
        
        FILE* fp = fopen(filename.c_str(), "w");
        if (fp) {
            // Write the source code.
            // We use escape_source(s) for the %s valid C-string placeholder.
            fprintf(fp, s, current_gen + 1, child_id.c_str(), my_id.c_str(), 34, escape_source(s).c_str(), 34);
            fclose(fp);
            
            // Compile and run
            string cmd = "g++ " + filename + " -o " + filename + ".out && ./" + filename + ".out &";
            system(cmd.c_str());
        }
    }
    return 0;
}
