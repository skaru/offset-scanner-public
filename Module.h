#pragma once
#include <Windows.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include "_Process.h"

class Module
{
public:
    Module(DWORD, char*);
    char * name;
    void* base;
    DWORD end;
    DWORD size;

private:
    MODULEENTRY32 getModule(DWORD, char*);
};


