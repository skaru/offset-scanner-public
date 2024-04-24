#include "PatternScanner.h"
#include <vector>

bool PatternScanner::compareBytes(char *bytes, char *pattern) {
    // TODO:: add check for bytes < end maybe
    for(;*pattern;*pattern == '?' ? pattern += 2 : pattern += 3, ++bytes) {
        if (*pattern == '?')
            continue;
        if (*bytes != (char)getByte(pattern))
            return false;
    }

    return true;
}

void *PatternScanner::scan(char* base, size_t size, char* pattern) {
    for (unsigned int offset = 0; offset < size; offset++) {
        if (compareBytes(base + offset, pattern)) {
            return (void*)(base + offset);
        }
    }

    return nullptr;
}

void *PatternScanner::scanEx(HANDLE hProc, DWORD begin, DWORD end, char* pattern, DWORD patternOffset, DWORD addressOffset, char options) {
    SIZE_T bytesRead;
    uintptr_t currentChunk = begin;

    while (currentChunk < end) {
        char buffer[4096];

        ReadProcessMemory(hProc, (void*)currentChunk, &buffer, sizeof(buffer), &bytesRead);    
        if (bytesRead == 0) {
            return nullptr;
        }

        void *internalAddress = scan((char*)&buffer, bytesRead, pattern);

        if (internalAddress != nullptr) {
            DWORD offset = currentChunk + (DWORD)internalAddress - (DWORD)&buffer + patternOffset;

            if (options & this->READ) 
                ReadProcessMemory(hProc, (void*)offset, &offset, 4, &bytesRead);

            if (options & this->SUBTRACT)
                offset = offset - begin;

            return (void*)(offset + addressOffset);
        }
        else {
            currentChunk = currentChunk + bytesRead;
        }
    }

    return nullptr;
}

DWORD PatternScanner::getOffset(_Process process, char *moduleName, char *pattern, DWORD patternOffset, DWORD addressOffset, char options) {
    Module mod(process.id ,moduleName);
    //return (DWORD)this->scanEx(process.handle, mod.base, mod.end, pattern, patternOffset, addressOffset, options);
    return 0;
}
