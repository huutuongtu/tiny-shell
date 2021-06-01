#include <iostream>
#include <windows.h>

using std::cout;
using std::cin;
using std::endl;

std::string commandBuf;
STARTUPINFO si[100];
PROCESS_INFORMATION  pi[100];
int n, backgroundMode = 1;

void menu() {
    cout << "             =  =                   =========================            =========================" << endl;
    cout << "             =       =                          =                                    =" << endl;
    cout << "             =           =                      =                                    =" << endl;
    cout << "             =              =                   =                                    =" << endl;
    cout << "             =                =                 =                                    =" << endl;
    cout << "             =                 =                =                                    =" << endl;
    cout << "             =                =                 =                                    =" << endl;
    cout << "             =              =                   =                                    =" << endl;
    cout << "             =           =                      =                                    =" << endl;
    cout << "             =       =                          =                                    =" << endl;
    cout << "             =  =                               =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << "             =                                  =                                    =" << endl;
    cout << endl << endl << endl;
    cout << "                                      Welcome to our Shell!" << endl;
    cout << "help: Show menu" << endl;
}

void setBackground() {
  cout << "Turn background mode on or off" << endl;
  cin >> commandBuf;
  if (!commandBuf.compare("on")) {
    backgroundMode = 1;
    cout << "Background mode turned on" << endl;
  }
  else if (!commandBuf.compare("off")) {
    backgroundMode = 0;
    cout << "Background mode turned off" << endl;
  }
  else if (!commandBuf.compare("display")) {
    if (backgroundMode == 1) {
      cout << "Current background mode settings: on" << endl;
    }
    else {
      cout << "Current background mode settings: off" << endl;
    }
  }
}

void killAll() {
  for (int i = 0; i < n; i++) {
    TerminateProcess(pi[i].hProcess, 1);
    CloseHandle(pi[i].hProcess);
    CloseHandle(pi[i].hThread);
  }
  cout << "All processes killed..." << endl;
  n = 0;
}

void killId(int id) {
  int i;
  for (i = 0; i < n; i++) {
    if (id == pi[i].dwProcessId) {
      TerminateProcess(pi[i].hProcess, 1);
      CloseHandle(pi[i].hProcess);
      CloseHandle(pi[i].hThread);
      cout << "Process " << id << " killed" << endl;

      for (int j = i; j < n - 1; j++) {
        pi[j] = pi[j + 1];
        si[j] = si[j + 1];
      }
      break;
    }
  }
  if (i == n) {
    cout << "Process with id " << id << " not found!" << endl;
  }
  else {
    n--;
  }
}

void kill() {
  int id;
  cout << "Enter process id to kill process, or -1 to kill all processes" << endl;
  cin >> id;
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
    cout << pi[i].dwProcessId << " "
              << pi[i].hProcess << " "
              << si[i].wShowWindow << endl;
  }
}

void open() {
  std::string fileName;
  cout << "Please enter the file path name: ";
  cin >> fileName;
  system(fileName.c_str());
}

void dir() {
  std::string path;
  cout << "Please enter the directory: ";
  cin >> path;
  system(("dir " + path).c_str());
}

void exit() {
  cout << "Sending signal to kill all child processes..." << endl;
  killAll();
}

void help() {
  cout << "For more information on a specific command, type HELP command: name" << endl;
  cout << "kill -1     Kill all running processes" << endl;
  cout << "kill 'ID'   Kill a running process with id " << endl;
  cout << "child       Open child process" << endl;
  cout << "calc        Open system calculator" << endl;
  cout << "list        Displays list of commands" << endl;
  cout << "open        Open a file" << endl;
  cout << "dir         Get the list of files and subdirectories in directory" << endl;
  cout << "exit        Exit shell" << endl;
  cout << "date        Displays or sets the date" << endl;
  cout << "help        Display list of all commands" << endl;
  cout << "ipconfig    Displays all current TCP/IP network configuration values" << endl;
  cout << "bg          Display and change background mode settings" << endl;
  cout << "clear       Clear console" << endl;
}


int main() {
  menu();
  while(1) {
    cout << "Keyword:  ";
    cin >> commandBuf;

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
      cout << "Console cleared!" << endl;
    }
    else {
      cout << "404 Error not Found !!!" << endl;
    }
  }
}
