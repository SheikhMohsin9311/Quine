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
    srand(time(0) + getpid());
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
    // Variable injection placeholders
    int current_gen = 0;
    string my_id = "SEED";
    string parent_id = "NONE";
    
    const int MAX_GEN = 5;
    const int CHILDREN_PER_GEN = 2;

    // The self-reference string
    const char* s = 
"#include <iostream>\n"
"#include <fstream>\n"
"#include <string>\n"
"#include <vector>\n"
"#include <cstdio>\n"
"#include <cstdlib>\n"
"#include <ctime>\n"
"#include <unistd.h>\n"
"\n"
"using namespace std;\n"
"\n"
"string generate_id() {\n"
"    srand(time(0) + getpid());\n"
"    const char input[] = \"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ\";\n"
"    string id = \"\";\n"
"    for(int i=0; i<4; ++i) {\n"
"        id += input[rand() % (sizeof(input) - 1)];\n"
"    }\n"
"    return id;\n"
"}\n"
"\n"
"string escape_source(const char* s) {\n"
"    string res;\n"
"    for (int i = 0; s[i]; ++i) {\n"
"        if (s[i] == '\\n') {\n"
"            res += \"\\\\n\\\"\\n\\\"\";\n"
"        } else if (s[i] == '\\\"') {\n"
"            res += \"\\\\\\\"\";\n"
"        } else if (s[i] == '\\\\') {\n"
"            res += \"\\\\\\\\\";\n"
"        } else {\n"
"            res += s[i];\n"
"        }\n"
"    }\n"
"    return res;\n"
"}\n"
"\n"
"int main() {\n"
"    // Variable injection placeholders\n"
"    int current_gen = %d;\n"
"    string my_id = \"%s\";\n"
"    string parent_id = \"%s\";\n"
"    \n"
"    const int MAX_GEN = 5;\n"
"    const int CHILDREN_PER_GEN = 2;\n"
"\n"
"    // The self-reference string\n"
"    const char* s = \n"
"%c%s%c;\n"
"\n"
"    if (current_gen >= MAX_GEN) {\n"
"        return 0;\n"
"    }\n"
"\n"
"    ofstream graph(\"genealogy.dot\", ios::app);\n"
"    if (graph.is_open()) {\n"
"        if (current_gen == 0) {\n"
"            graph << \"digraph FamilyTree {\\n\";\n"
"            graph << \"    node [shape=box, style=filled, color=\\\"#007acc\\\", fontcolor=white];\\n\";\n"
"            graph << \"    SEED [label=\\\"SEED (Gen 0)\\\", fillcolor=\\\"#ff6b6b\\\"];\\n\";\n"
"        }\n"
"        if (parent_id != \"NONE\") {\n"
"             graph << \"    \\\"\" << parent_id << \"\\\" -> \\\"\" << my_id << \"\\\";\\n\";\n"
"        }\n"
"        if (my_id != \"SEED\") {\n"
"             graph << \"    \\\"\" << my_id << \"\\\" [label=\\\"ID: \" << my_id << \"\\\\nGen: \" << current_gen << \"\\\"];\\n\";\n"
"        }\n"
"        graph.close();\n"
"    }\n"
"\n"
"    for (int i = 0; i < CHILDREN_PER_GEN; ++i) {\n"
"        string child_id = generate_id();\n"
"        string filename = \"child_\" + to_string(current_gen + 1) + \"_\" + child_id + \".cpp\";\n"
"        \n"
"        FILE* fp = fopen(filename.c_str(), \"w\");\n"
"        if (fp) {\n"
"            // Write the source code.\n"
"            // We use escape_source(s) for the %s valid C-string placeholder.\n"
"            fprintf(fp, s, current_gen + 1, child_id.c_str(), my_id.c_str(), 34, escape_source(s).c_str(), 34);\n"
"            fclose(fp);\n"
"            \n"
"            // Compile and run\n"
"            string cmd = \"g++ \" + filename + \" -o \" + filename + \".out && ./\" + filename + \".out &\";\n"
"            system(cmd.c_str());\n"
"        }\n"
"    }\n"
"    return 0;\n"
"}\n"
"\n";

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
