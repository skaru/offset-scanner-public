#include "Module.h"

Module::Module(DWORD id, char *moduleName) {
    MODULEENTRY32 mod = getModule(id, moduleName);
    name = moduleName;
    base = mod.modBaseAddr;
    size = mod.modBaseSize;
    end = 0 + size;
}


MODULEENTRY32 Module::getModule(DWORD dwProcID, char * moduleName)
{
    MODULEENTRY32 modEntry = { 0 };

    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, dwProcID);

    if (hSnapshot != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 curr = { 0 };

        curr.dwSize = sizeof(MODULEENTRY32);
        void* watchme;
        if (Module32First(hSnapshot, &curr))
        {
            do
            {
                if (!strcmp(curr.szModule, moduleName))
                {
                    modEntry = curr;
                    break;
                }
                void* watchme = (void*)curr.modBaseAddr;
                int nome = 1 + 1;
            } while (Module32Next(hSnapshot, &curr));
        }
        CloseHandle(hSnapshot);
    }

    return modEntry;
}