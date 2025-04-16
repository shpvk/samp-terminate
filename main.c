#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <psapi.h>
#include <winuser.h>

void kill_process_by_name(char* name_str)
{
    HANDLE h_snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(h_snapshot == INVALID_HANDLE_VALUE)
    {
        printf("Snapshot value error\n");
        return;
    }
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);

    
    BOOL is_founded = FALSE;
    if(Process32First(h_snapshot, &pe32))
    {
        do
        {
            if (strcmp(pe32.szExeFile, name_str) == 0)
            {
                is_founded = TRUE;
                HANDLE h_terminate_process = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID);
                if(h_terminate_process == NULL)
                {
                    printf("You do not have access to end this process\n");
                    return;
                }
                if(TerminateProcess(h_terminate_process, 0) == FALSE)
                {
                    printf("TERMINATE ERROR");
                    break;
                }
                CloseHandle(h_terminate_process);
                break;
            
            };
        } while (Process32Next(h_snapshot, &pe32));
    }
    CloseHandle(h_snapshot);
    if(!is_founded)
    {
        printf("Process not found\n");
        return;
    }
}

int main()
{
    kill_process_by_name("gta_sa.exe");
    return 0;
}