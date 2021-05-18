#include <iostream>
#include <windows.h>


std::string command_buf;
STARTUPINFO si[100];
PROCESS_INFORMATION  pi[100];
int n, background_mode = 1;

void menu() {
  std::cout << "                        MY-SHELL" << std::endl;
  std::cout << "________________________________________________________\n" << std::endl;
  std::cout << "help: Show menu" << std::endl;
}

void kill_all() {
  for (int i = 1; i <= n; i++) {
    TerminateProcess(pi[i].hProcess, 1);
    CloseHandle(pi[i].hProcess);
    CloseHandle(pi[i].hThread);
  }
  std::cout << "All processes killed..." << std::endl;
  n = 0;
}

void kill_id(int id) {
  for (int i = 1; i <= n; i++) {
    if (id == pi[i].dwProcessId) {
      TerminateProcess(pi[i].hProcess, 1);
      CloseHandle(pi[i].hProcess);
      CloseHandle(pi[i].hThread);

      for (int j = i; j < n; j++) {
        pi[j] = pi[j + 1];
        si[j] = si[j + 1];
      }
      n--;
      break;
    }
  }
}

void kill() {
  int id;
  std::cout << "Enter process id to kill process, or -1 to kill all processes\n";
  std::cin >> id;
  if (id == -1) {
    kill_all();
  }
  else {
    kill_id(id);
  }
  
}

void child() {
  n++;
  ZeroMemory(&si[n], sizeof(si[n]));
  si[n].cb = sizeof(si[n]);
  CreateProcess("child.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[n], &pi[n]);
  if (background_mode == 1) {
    return;
  }
  WaitForSingleObject(pi[n].hProcess, 10000);
}

void calc() {
  n++;
  ZeroMemory(&si[n], sizeof(si[n]));
  si[n].cb = sizeof(si[n]);
  CreateProcess("C:\\Windows\\System32\\calc.exe", NULL, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si[n], &pi[n]);
  if (background_mode == 1) {
    return;
  }
  WaitForSingleObject(pi[n].hProcess, 10000);
}

void list() {
  for (int i = 1; i <= n; i++) {
    std::cout << pi[i].dwProcessId << " "
              << pi[i].hProcess << " "
              << si[i].wShowWindow << std::endl;
  }
}

void open() {
  std::string file_name;
  std::cout << "Please enter the file path name: ";
  std::cin >> file_name;
  std::string openString = "start " + file_name;
  system(openString.c_str());
}

void dir() {
  std::string path;
  std::cout << "Please enter the directory: ";
  std::cin >> path;
  std::string openString = "dir " + path;
  system(openString.c_str());
}

void exit() {
  std::cout << "Sending signal to kill all child processes..." << std::endl;
  kill_all();
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
  std::cout << "help        Display all commands" << std::endl;
}


int main() {
  menu();
  while(1) {
    std::cout << "Keyword:  ";
    std::cin >> command_buf;

    if (!command_buf.compare("kill")) {
      kill();
    }
    else if (!command_buf.compare("child")) {
      child();
    }
    else if (!command_buf.compare("calc")) {
      calc();
    }
    else if (!command_buf.compare("list")) {
      list();
    }
    else if (!command_buf.compare("open")) {
      open();
    }
    else if (!command_buf.compare("dir")) {
      dir();
    }
    else if (!command_buf.compare("exit") || !command_buf.compare("e")) {
      exit();
      return 0;
    }
    else if (!command_buf.compare("date")) {
      system("date");
    }
    else if (!command_buf.compare("help")) {
      help();
    }
    else if (!command_buf.compare("ipconfig")) {
      system("ipconfig");
    }
    else if (!command_buf.compare("background")) {
      std::cin >> command_buf;
      if (!command_buf.compare("on")) {
        background_mode = 1;
      }
      if (!command_buf.compare("off")) {
        background_mode = 0;
      }
    }
    else {
      std::cout << "404 Error not Found !!!" << std::endl;
    }
  }
}
