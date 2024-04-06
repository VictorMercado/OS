#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>

#define string std::string
#define cout std::cout
#define fstream std::fstream
#define endl std::endl
#define to_string std::to_string

void downloadFile(string url, string filename) {
  pid_t pid;
  int exit_status;

  if((pid=fork())<0) {
    perror("fork error");
    exit(1);
  } else if(pid == 0) {
    printf("Child Process Id: %d\n", getpid());
    printf("Child Process UID: %d\n", getuid());
    printf("Child Process GID: %d\n", getgid());
    printf("Parent Process Id: %d\n", getppid());
    printf("Parent Process UID: %d\n", geteuid());
    printf("Parent Process GID: %d\n", getegid());
    execlp("curl", "curl", "-o", filename.c_str(), url.c_str(), (char *)0);
  } else {
    pid = wait(&exit_status);
    printf("Finshed downloading %s\n", filename.c_str());
  }
}

int main() {
  // "https://api.open-meteo.com/v1/forecast?latitude=34.039&longitude=-117.66&temperature_unit=fahrenheit&forecast_days=1&current=temperature_2m&timezone=America%2FLos_Angeles"
  // https://api.open-meteo.com/v1/forecast?current weather=True &latitude=52.520000 & longitude=13.410000
  //  file1.json
  fstream file;
  file.open("locations.txt", fstream::in);
  int i = 1;
  while(!file.eof()) {
    string url = "https://api.open-meteo.com/v1/forecast?current=temperature_2m";
    // string filename;
    string latitude = "&latitude=";
    string longitude = "&longitude=";
    string lat;
    string lon;
    file >> lat >> lon;
    latitude += lat;
    longitude += lon;
    cout << latitude << " " << longitude << endl;
    downloadFile(url + latitude + longitude, "file" + to_string(i) + ".json");
    i++;
  }
  // downloadFile("https://api.open-meteo.com/v1/forecast?latitude=34.039&longitude=-117.66&", "file1.json");
}