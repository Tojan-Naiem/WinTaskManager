#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <tlhelp32.h>
void listProcesses() {

    PROCESSENTRY32 pe32;
    HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE) {
        printf("Error: Unable to create process snapshot!\n");
        return;
    }

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (!Process32First(hProcessSnap, &pe32)) {
        printf("Error: Unable to retrieve process information!\n");
        CloseHandle(hProcessSnap);
        return;
    }

    printf("Processes running on the system:\n");
    do {
        printf("PID: %d, Process Name: %s\n", pe32.th32ProcessID, pe32.szExeFile);
    } while (Process32Next(hProcessSnap, &pe32));

    CloseHandle(hProcessSnap);
}

void killProcess(DWORD pid) {
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);

    if (hProcess == NULL) {
        printf("Error: Unable to open process.\n");
        return;
    }

    if (TerminateProcess(hProcess, 0) == 0) {
        printf("Error: Unable to terminate process.\n");
    } else {
        printf("Process terminated successfully.\n");
    }

    CloseHandle(hProcess);
}

int main()
{
    DWORD pid;
    while(1){
        printf("Simple task manager \n");
        printf("1. List running processes\n");
        printf("2. Kill a process \n");
        printf("Enter your choice \n");
        int choice;
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            listProcesses();
            break;
        case 2:{
    printf("Enter the PID of the process to kill: ");
                scanf("%lu", &pid);
                killProcess(pid);break;
        }
        case 3:exit(0);
        default :printf("Invalid choice.\n");

        }

    }

    printf("Hello world!\n");
    return 0;
}
