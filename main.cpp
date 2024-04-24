#include <Windows.h>
#include "_Process.h"
#include "PatternScanner.h"
#include <iostream>

int main() {
    _Process p("x");
    PatternScanner scanner;

    Module engine(p.id, "x");
    while (1) {
        int clientState;
        unsigned char begin[0x1000];
        void* offset = engine.base;
        char* test = (char*)engine.base;
        ReadProcessMemory(p.handle, test, begin, 1000, NULL);
        Sleep(500);
    }

    p.close();
	return  0;
}