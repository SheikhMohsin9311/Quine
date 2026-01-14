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

    for (int i = 1; i <= 10; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "demo%d.cpp", i);
        ofstream out(filename);
        out << buffer;
        out.close();
    }
    return 0;
}
";
    char buffer[10000];
    snprintf(buffer, sizeof(buffer), s, 34, s, 34);

    for (int i = 1; i <= 10; i++) {
        char filename[20];
        snprintf(filename, sizeof(filename), "demo0.cpp", i);
        ofstream out(filename);
        out << buffer;
        out.close();
    }
    return 0;
}
