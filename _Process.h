#pragma once
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>

class _Process {
public:
    DWORD id;
    HANDLE handle;
    char *name;
    _Process(char*);
    void close();

private:
    DWORD FindProcess(const char*);
};

