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
"    ofstream out(\"demo1.cpp\");\n"
"    out << buffer;\n"
"    out.close();\n"
"    return 0;\n"
"}\n";

    char buffer[10000];
    snprintf(buffer, sizeof(buffer), s, 34, s, 34);

    ofstream out("demo1.cpp");
    out << buffer;
    out.close();

    return 0;
}
