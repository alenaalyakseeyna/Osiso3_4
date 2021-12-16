#include <iostream>
#include <Windows.h>

typedef  bool __cdecl TReplaceString(DWORD pid, std::string replaceableString, std::string substituteString);

int main()
{
    HMODULE library = LoadLibrary(L"replaceString1.dll");
    if (library)
    {
        TReplaceString *replaceString = (TReplaceString *)GetProcAddress(library, "replaceString");
        if (replaceString != NULL)
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
        else 
        {
            std::cout << "ooooooppppppsssss";
        }
        FreeLibrary(library);
    }
    else
    {
        std::cout << "ooooooppppppssss";
    }


}
