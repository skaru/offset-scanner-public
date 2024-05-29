# offset-scanner
This program can be used to find memory offsets in external memory.
```C++
DWORD PatternScanner::getOffset(process, *moduleName, *pattern, patternOffset, addressOffset, options)
```
- process: The name of the process
- *moduleName: Which module needs to be searched
- *pattern: The pattern
- patternOffset: specifies the index the offset starts at in the pattern
- addressOffset: Specifies the offset for a struct/class data memeber
- options: Should the offset be deferenced and/or should a relative address be returned

Let's say you have process.exe containing module.dll and the memory looks like this:
```
48 8B EC 48 83 EC 20 48 8B 05 50 F0 0E 00 48 BB 32 A2 DF 2D 99 2B 00 00 48 3B C3
75 74 48 83 65 18 00 48 8D 4D 18 FF 15 EA 33 0E 00 48 8B 45 18 48 89 45 10 FF 15
```
Let’s say we are trying to find the pointer 0x50f00e00. If the rest of the memory remains the same the pattern would be:

48 8B EC 48 83 EC 20 48 8B 05 ?? ?? ?? ?? 48 BB 32 A2 DF 2D

The code would look like this:
```C++
_Process hProcess("process.exe");
DWORD PatternScanner::getOffset(hProcess, "module.dll", "48 8B EC 48 83 EC 20 48 8B 05 ?? ?? ?? ?? 48 BB 32 A2 DF 2D", 9, 0, 0)
```
