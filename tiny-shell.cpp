#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <signal.h>
#include <conio.h>
#include <iostream>
#include <cstdio>
#include <dirent.h>
#include <iostream>
#include <string>

char command_buf[500];

char key;
STARTUPINFO si[100];
PROCESS_INFORMATION  pi[100];
int n, background_mode = 1;
void menu(){
	printf("							MY-SHELL\n");
	printf("________________________________________________________________________________________________________________________\n \n");
	printf("help: Show menu\n");
}
void kill_all(){
    for (int i = 1;i <= n; i++){
        TerminateProcess(pi[i].hProcess, 1);CloseHandle(pi[i].hProcess);CloseHandle(pi[i].hThread);
    }
    printf("All process killed ... \n");
    n = 0;
}
void kill(int id){
    for (int i = 1;i <= n; i++){
        if (id == pi[i].dwProcessId){
            TerminateProcess(pi[i].hProcess, 1);CloseHandle(pi[i].hProcess);CloseHandle(pi[i].hThread);
            for (int j = i; j < n; j++) pi[j] = pi[j + 1], si[j] = si[j + 1];
            n--;
            break;
        }
    }
}

void child(){
    ++n;
    ZeroMemory(&si[n], sizeof(si[n]));
    si[n].cb = sizeof(si[n]);
    CreateProcess("child.exe",NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si[n],&pi[n]);
    if (background_mode == 1) return;
    WaitForSingleObject(pi[n].hProcess,10000);
}
void list(){
    for (int i = 1;i <= n; i++)
        printf("%d %p %s\n", pi[i].dwProcessId, pi[i].hProcess, si[i].wShowWindow);
}
void calc(){
    ++n;
    ZeroMemory(&si[n], sizeof(si[n]));
    si[n].cb = sizeof(si[n]);
    CreateProcess("C:\\Windows\\System32\\calc.exe",NULL,NULL,NULL,FALSE,CREATE_NEW_CONSOLE,NULL,NULL,&si[n],&pi[n]);
    if (background_mode == 1) return;
    WaitForSingleObject(pi[n].hProcess,10000);
}
void exit_process(){
    printf("Sending signal to kill all child processes ...\n");
    kill_all();

}
void sigint(int a){   
    printf("Killing foreground process ... \n");
    for (int i = 1;i <= n; i++){
        TerminateProcess(pi[i].hProcess, 1);CloseHandle(pi[i].hProcess);CloseHandle(pi[i].hThread);
    }
    n = 0;
}

void help() {
    // Display all commands
    printf("For more information on a specific command, type HELP command: name\n");
    printf("kill -1    Kill all running processes\n");
    printf("kill 'ID'   Kill a running process with id \n");
    printf("date    Displays or sets the date\n");
    printf("calc    Open system calculator\n");
    printf("list    Displays list of commands\n");
    printf("Dir Get the list of files in directory\n");
	printf("help    ");
    printf("child  Open child process\n");
    
}


void open(){
}

void dir(){
}




int main(){
    menu();
	while(1) 
	{
		printf("Keyword:  ");
        //if (!fgets(command_buf, 128, stdin)) break;
        scanf("%s", &command_buf);
		if(!strcmp(command_buf, "ipconfig")) { system("ipconfig"); }
		else if(!strcmp(command_buf, "date")) { system("date"); }
		else if(!strcmp(command_buf, "exit") || !strcmp(command_buf, "quit") || !strcmp(command_buf, "e") || !strcmp(command_buf, "q")) {
            exit_process();
            return 0;
        }
		else if(!strcmp(command_buf, "child")) {
            child();
        }
        else if(!strcmp(command_buf, "calc")) {
            calc();
        }
        else if (!strcmp(command_buf, "kill")){
            int id;
            scanf("%d", &id);
            if (id == -1) kill_all();
            else kill(id);
        }
        else if (!strcmp(command_buf, "background")){
            scanf("%s", command_buf);
            if (!strcmp(command_buf, "on")) background_mode = 1;
            if (!strcmp(command_buf, "off")) background_mode = 0;
        }
        else if (!strcmp(command_buf, "list")){
            list();
        }
        else if (!strcmp(command_buf, "help")){
        	help();
		}
		else if (!strcmp(command_buf, "open")){
		
			
		}
		else {printf("404 Error not Found !!!");
		}
	}
}
