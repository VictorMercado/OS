#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void downloadFilesInParallel(vector<string> urls, vector<string> filenames) {
  int exit_status;
  for (int i = 0; i<urls.size(); i++) {
    pid_t pid = fork();
    if(pid < 0) {
      perror("fork error");
      exit(1);
    } else if(pid == 0) {
      printf("Child Process Id: %d\n", getpid());
      printf("Child Process UID: %d\n", getuid());
      printf("Child Process GID: %d\n", getgid());
      printf("Parent Process Id: %d\n", getppid());
      printf("Parent Process UID: %d\n", geteuid());
      printf("Parent Process GID: %d\n", getegid());
      execlp("curl", "curl", "-o", filenames[i].c_str(), urls[i].c_str(), (char *)0);
      perror("execlp");
      exit(EXIT_FAILURE);
    } 
  }
  for (int i = 0; i<urls.size(); i++) {
    pid_t pid = wait(&exit_status);
    printf("Finshed downloading %s\n", filenames[i].c_str());
    
    if (WIFEXITED(exit_status)) {
        printf("Child process exited with status %d\n", WEXITSTATUS(exit_status));
    } else {
        printf("Child process terminated abnormally\n");
    }
  }
}

int main() {
  // "https://api.open-meteo.com/v1/forecast?latitude=34.039&longitude=-117.66&temperature_unit=fahrenheit&forecast_days=1&current=temperature_2m&timezone=America%2FLos_Angeles"
  // https://api.open-meteo.com/v1/forecast?current weather=True &latitude=52.520000 & longitude=13.410000
  //  file1.json
  fstream file;
  file.open("locations.txt", fstream::in);
  int i = 1;
  string URL = "https://api.open-meteo.com/v1/forecast?current=temperature_2m";
  vector<string> urls;
  vector<string> fileNames;
  while(!file.eof()) {
    // string filename;
    string latitude = "&latitude=";
    string longitude = "&longitude=";
    string lat;
    string lon;
    file >> lat >> lon;
    latitude += lat;
    longitude += lon;
    cout << latitude << " " << longitude << endl;
    urls.push_back(URL + latitude + longitude);
    fileNames.push_back("file" + to_string(i) + ".json");
    i++;
  }
  downloadFilesInParallel(urls, fileNames);
  // downloadFile("https://api.open-meteo.com/v1/forecast?latitude=34.039&longitude=-117.66&", "file1.json");
}