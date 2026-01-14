#include <iostream>
#include <cstdio>
using namespace std;

int main() {
    const char* s =
"#include <iostream>\n"
"using namespace std;\n\n"
"int main() {\n"
"    const char* s =\n"
"%c%s%c;\n"
"    printf(s, 34, s, 34);\n"
"    return 0;\n"
"}\n";
    printf(s, 34, s, 34);
    fork();
    return 0;
}
