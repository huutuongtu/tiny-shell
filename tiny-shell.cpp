#include <iostream>
#include <windows.h>


std::string commandBuf;
STARTUPINFO si[100];
PROCESS_INFORMATION  pi[100];
int n, backgroundMode = 1;

void menu() {
    std::cout << "             =  =                   =========================            =========================" << std::endl;
    std::cout << "             =       =                          =                                    =" << std::endl;
    std::cout << "             =           =                      =                                    =" << std::endl;
    std::cout << "             =              =                   =                                    =" << std::endl;
    std::cout << "             =                =                 =                                    =" << std::endl;
    std::cout << "             =                 =                =                                    =" << std::endl;
    std::cout << "             =                =                 =                                    =" << std::endl;
    std::cout << "             =              =                   =                                    =" << std::endl;
    std::cout << "             =           =                      =                                    =" << std::endl;
    std::cout << "             =       =                          =                                    =" << std::endl;
    std::cout << "             =  =                               =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << "             =                                  =                                    =" << std::endl;
    std::cout << std::endl << std::endl << std::endl;
    std::cout << "                                      Welcome to our Shell!" << std::endl;
    std::cout << "help: Show menu" << std::endl;
}

void setBackground() {
  std::cout << "Turn background mode on or off" << std::endl;
  std::cin >> commandBuf;
  if (!commandBuf.compare("on")) {
    backgroundMode = 1;
    std::cout << "Background mode turned on" << std::endl;
  }
  else if (!commandBuf.compare("off")) {
    backgroundMode = 0;
    std::cout << "Background mode turned off" << std::endl;
  }
  else if (!commandBuf.compare("display")) {
    if (backgroundMode == 1) {
      std::cout << "Current background mode settings: on" << std::endl;
    }
    else {
      std::cout << "Current background mode settings: off" << std::endl;
    }
  }
}

void killAll() {
  for (int i = 0; i < n; i++) {
    TerminateProcess(pi[i].hProcess, 1);
    CloseHandle(pi[i].hProcess);
    CloseHandle(pi[i].hThread);
  }
  std::cout << "All processes killed..." << std::endl;
  n = 0;
}

void killId(int id) {
  int i;
  for (i = 0; i < n; i++) {
    if (id == pi[i].dwProcessId) {
      TerminateProcess(pi[i].hProcess, 1);
      CloseHandle(pi[i].hProcess);
      CloseHandle(pi[i].hThread);
      std::cout << "Process " << id << " killed" << std::endl;

      for (int j = i; j < n - 1; j++) {
        pi[j] = pi[j + 1];
        si[j] = si[j + 1];
      }
      break;
    }
  }
  if (i == n) {
    std::cout << "Process with id " << id << " not found!" << std::endl;
  }
  else {
    n--;
  }
}

void kill() {
  int id;
  std::cout << "Enter process id to kill process, or -1 to kill all processes" << std::endl;
  std::cin >> id;
  if (id == -1) {
    killAll();
  }
  else {
    killId(id);
  }
  
}

void child() {
  ZeroMemory(&si[n], sizeof(si[n]));
  si[n].cb = sizeof(si[n]);
  CreateProcess("child.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[n], &pi[n]);
  n++;
  if (backgroundMode == 1) {
    return;
  }
  WaitForSingleObject(pi[n].hProcess, INFINITE);
}

void calc() {
  system("C:\\Windows\\System32\\calc.exe");
}

void list() {
  for (int i = 0; i < n; i++) {
    std::cout << pi[i].dwProcessId << " "
              << pi[i].hProcess << " "
              << si[i].wShowWindow << std::endl;
  }
}

void open() {
  std::string fileName;
  std::cout << "Please enter the file path name: ";
  std::cin >> fileName;
  system(fileName.c_str());
}

void dir() {
  std::string path;
  std::cout << "Please enter the directory: ";
  std::cin >> path;
  system(("dir " + path).c_str());
}

void exit() {
  std::cout << "Sending signal to kill all child processes..." << std::endl;
  killAll();
}

void help() {
  std::cout << "For more information on a specific command, type HELP command: name" << std::endl;
  std::cout << "kill -1     Kill all running processes" << std::endl;
  std::cout << "kill 'ID'   Kill a running process with id " << std::endl;
  std::cout << "child       Open child process" << std::endl;
  std::cout << "calc        Open system calculator" << std::endl;
  std::cout << "list        Displays list of commands" << std::endl;
  std::cout << "open        Open a file" << std::endl;
  std::cout << "dir         Get the list of files and subdirectories in directory" << std::endl;
  std::cout << "exit        Exit shell" << std::endl;
  std::cout << "date        Displays or sets the date" << std::endl;
  std::cout << "help        Display list of all commands" << std::endl;
  std::cout << "ipconfig    Displays all current TCP/IP network configuration values" << std::endl;
  std::cout << "bg          Display and change background mode settings" << std::endl;
  std::cout << "clear       Clear console" << std::endl;
}


int main() {
  menu();
  while(1) {
    std::cout << "Keyword:  ";
    std::cin >> commandBuf;

    if (!commandBuf.compare("kill")) {
      kill();
    }
    else if (!commandBuf.compare("child")) {
      child();
    }
    else if (!commandBuf.compare("calc")) {
      calc();
    }
    else if (!commandBuf.compare("list")) {
      list();
    }
    else if (!commandBuf.compare("open")) {
      open();
    }
    else if (!commandBuf.compare("dir")) {
      dir();
    }
    else if (!commandBuf.compare("exit") || !commandBuf.compare("e")) {
      exit();
      return 0;
    }
    else if (!commandBuf.compare("date")) {
      system("date");
    }
    else if (!commandBuf.compare("help")) {
      help();
    }
    else if (!commandBuf.compare("ipconfig")) {
      system("ipconfig");
    }
    else if (!commandBuf.compare("bg")) {
      setBackground();
    }
    else if (!commandBuf.compare("clear")) {
      system("cls");
      std::cout << "Console cleared!" << std::endl;
    }
    else {
      std::cout << "404 Error not Found !!!" << std::endl;
    }
  }
}
