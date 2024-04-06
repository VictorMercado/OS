#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <map>
#include <fstream>
#include <filesystem>
using namespace std;

#define Command_Map map<string, string> 


void loadCommandsFromFolder(Command_Map &CommandMap, string folderPath) {
  try {
    for (const auto & entry : filesystem::directory_iterator(folderPath))
    {
      string command = entry.path().filename().string();
      string commandPath = entry.path().string();
      CommandMap[command] = commandPath;
    }
  }
  catch (const exception& e) {
    cout << e.what() << endl;
  }
}

void printCommands(Command_Map &CommandMap) {
  for (auto const& x : CommandMap)
  {
    cout << "Command: " << x.first  // string (key)
         << "  -  Path: " << x.second // string's value 
         << endl ;
  }
}

int main(void)
{
  string userInput;
  Command_Map CommandMap;
  string folderPath = "/usr/bin";
  string folderPath2 = "/bin";
  string commandPath;
  int error = errno;
  
  while(userInput != "exit") {
    loadCommandsFromFolder(CommandMap, folderPath);
    loadCommandsFromFolder(CommandMap, folderPath2);
    cout << "Enter a command or help for options and exit to quit: ";
    cin >> userInput;
    
    if( userInput == "help") {
      printCommands(CommandMap);
    }
    else if( userInput == "exit") {
      cout << "Exiting..." << endl;
      break;
    } else {
      commandPath = CommandMap[userInput];
      cout << "Command is located here: " << commandPath << endl;

      pid_t pid = fork();
      int exit_status;
      if(pid < 0) {
        perror("fork error");
        exit(1);
      } else if(pid == 0) {
        int status = execlp(userInput.c_str(), userInput.c_str(), (char *)0);
        if(status == -1) {
          perror("execlp");
          // exit(EXIT_FAILURE);
        }
      } else {
        pid = wait(&exit_status);
        printf("\nProcess id is: %d and is finished\n\n", getpid());
      }
    }
  }

  return 0;
}