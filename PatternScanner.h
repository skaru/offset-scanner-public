#pragma once
#define INRANGE(x,a,b)  (x >= a && x <= b)
#define getBits(x)      (INRANGE(x,'0','9') ? (x - '0') : ((x&(~0x20)) - 'A' + 0xa))
#define getByte(x)      (getBits(x[0]) << 4 | getBits(x[1]))

#include <Windows.h>
#include <TlHelp32.h>
#include "Module.h"
#include "_Process.h"

class PatternScanner
{
public:
    DWORD getOffset(_Process, char *, char*, DWORD, DWORD, char options = 0);
    enum {
        NORMAL = 0x0,
        READ = 0x1,
        SUBTRACT = 0x2,
    };

private:
    bool compareBytes(char*, char*);
    void *scan(char*, size_t, char*);
    void *scanEx(HANDLE, DWORD, DWORD, char*, DWORD, DWORD, char);
};


