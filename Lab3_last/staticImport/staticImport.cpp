#include <iostream>
#include <Windows.h>

extern "C" __declspec(dllimport) bool __stdcall replaceString(DWORD pid, std::string replaceableString, std::string substituteString);

int main()
{
    std::string replaceableString, substituteString;
    std::cout << "Input replaceable and substitute string\n";
    std::cin >> replaceableString >> substituteString;
    DWORD pid = GetCurrentProcessId();
    std::string someStr = "alenaivanova";
    if (replaceString(pid, replaceableString, substituteString)) 
    {
        std::cout << "All is right\n";
        std::cout << "New string is " << someStr << '\n';
    }
    else
    {
        std::cout << "I have a bad news";
    }
}
