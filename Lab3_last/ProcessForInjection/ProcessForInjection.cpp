#include <iostream>
#include <Windows.h>

int main()
{
    DWORD pid = GetCurrentProcessId();
    std::string someStr = "alenaivanova";
    std::cout << "Your pid is " << pid << '\n';
    while (true) 
    {
        std::cout << "Your string is " << someStr << '\n';
        getchar();
    }
}
