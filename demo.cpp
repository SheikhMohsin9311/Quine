#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

int main() {
    const char* s =
"#include <iostream>\n"
"#include <cstdio>\n"
"#include <fstream>\n"
"using namespace std;\n\n"
"int main() {\n"
"    const char* s =\n"
"%c%s%c;\n"
"    char buffer[10000];\n"
"    snprintf(buffer, sizeof(buffer), s, 34, s, 34);\n"
"\n"
"    for (int i = 1; i <= 10; i++) {\n"
"        char filename[20];\n"
"        snprintf(filename, sizeof(filename), \"demo%d.cpp\", i);\n"
"        ofstream out(filename);\n"
"        out << buffer;\n"
"        out.close();\n"
"    }\n"
"    return 0;\n"
"}\n";

    char buffer[10000];
    snprintf(buffer, sizeof(buffer), s, 34, s, 34);

    for (int i = 1; i <= 10; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "demo%d.cpp", i);
        ofstream out(filename);
        out << buffer;
        out.close();
    }

    return 0;
}
