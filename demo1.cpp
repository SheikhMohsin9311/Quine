#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

int main() {
    const char* s =
"#include <iostream>
#include <cstdio>
#include <fstream>
using namespace std;

int main() {
    const char* s =
%c%s%c;
    char buffer[10000];
    snprintf(buffer, sizeof(buffer), s, 34, s, 34);
    ofstream out("demo1.cpp");
    out << buffer;
    out.close();
    return 0;
}
";
    char buffer[10000];
    snprintf(buffer, sizeof(buffer), s, 34, s, 34);
    ofstream out("demo1.cpp");
    out << buffer;
    out.close();
    return 0;
}
