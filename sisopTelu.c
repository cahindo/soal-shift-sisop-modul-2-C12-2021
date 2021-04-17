#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

void main(){
  pid_t pid, sid;
  pid = fork();

  if (pid < 0)
    exit(EXIT_FAILURE);
  if (pid > 0)
    exit(EXIT_SUCCESS);

  umask(0);

  sid = setsid();
  if (sid < 0) 
    exit(EXIT_FAILURE);

  if ((chdir("/")) < 0)
    exit(EXIT_FAILURE);

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  char nmFolder[200];

  while (1){
    pid_t pid3;
    pid3 = fork();
    if (pid3 == 0){
      pid_t pidA;

      // ! SUBSOAL A
      time_t ta = time(NULL);
      struct tm tms = *localtime(&ta);
      sprintf(nmFolder, 
              "/home/boi/%02d-%02d-%d_%02d:%02d:%02d", 
              tms.tm_mday, 
              tms.tm_mon + 1, 
              tms.tm_year + 1900, 
              tms.tm_hour,
              tms.tm_min, 
              tms.tm_sec);

      pidA = fork();
      int stsA;

      if (pidA < 0)
        exit(EXIT_FAILURE);
      if (pidA == 0){
        char *argv[] = {"mkdir", nmFolder, NULL};
        execv("/bin/mkdir", argv);
      } else {
      // ! SUBSOAL B
        while ((wait(&stsA)) > 0);
        char curFolder[200];
        strcpy(curFolder, nmFolder);
        chdir(curFolder);

        int lop = 0;
        while (lop < 10) {
          int epoch = time(NULL);
          char linkDL[200];
          sprintf(linkDL, "https://picsum.photos/50");

          char nmFile[200];
          time_t tb = time(NULL);
          struct tm tms = *localtime(&tb);
          sprintf(nmFile, "%d-%02d-%02d_%02d:%02d:%02d.jpg", 
                  tms.tm_year + 1900, 
                  tms.tm_mon + 1, 
                  tms.tm_mday, 
                  tms.tm_hour,
                  tms.tm_min, 
                  tms.tm_sec);
          
          pid_t pidB;
          pidB = fork();

          if (pidB == 0) {
            // char newLink[255];
            // sprintf(newLink, "wget -qO %s %s", nmFile, linkDL);
            // system(newLink);
            char *argv[] = {"wget", "-qO", nmFile, linkDL, NULL};
            execv("/bin/wget", argv);
            exit(0);
          }

          lop++;
          sleep(5);
        }
        exit(0);
      }
    }
    sleep(40);
  }
  exit(0);
}