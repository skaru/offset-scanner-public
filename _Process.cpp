#include "_Process.h"


_Process::_Process(char *name) {
    this->name = name;
    while (!(id = FindProcess(this->name))) {
        std::cout << this->name << " not found" << std::endl;
        Sleep(2000);
    }
    handle = OpenProcess(PROCESS_QUERY_INFORMATION, false, id);
}

void _Process::close() {
    CloseHandle(handle);
}

DWORD _Process::FindProcess(const char *name) {
    PROCESSENTRY32 __ProcessEntry;
    __ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) return 0;
    if (!Process32First(hSnapshot, &__ProcessEntry)) {
        CloseHandle(hSnapshot);
        return 0;
    }
    do {
        if (!_strcmpi(__ProcessEntry.szExeFile, name))
        {
            CloseHandle(hSnapshot);
            return __ProcessEntry.th32ProcessID;
        }
    } while (Process32Next(hSnapshot, &__ProcessEntry));
    CloseHandle(hSnapshot);
    return 0;
}