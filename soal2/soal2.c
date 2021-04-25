#include <sys/stat.h> 
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <fcntl.h>



char from[100] = "/home/jogar/Documents/praktikum2/pets.zip";
char to[100] = "/home/jogar/Documents/praktikum2/petshop";

void remDir (char *NF) {

    pid_t child_id;

    int status;
    char source[150];
    sprintf(source, "%s/%s", to, NF);

    char *argv[] = {"rm", "-f", source, NULL};

    child_id = fork();
    if (child_id == 0)
        execv("/bin/rm", argv);
    else //parent
        (wait(&status) > 0);
}


void keterangan (char *dp, char *age, char *finName) {
    char detil[150];
    char print[200];

    sprintf(detil, "name\t: %s\numur\t: %s\n\n", finName, age);
    sprintf(print, "%s/keterangan.txt", dp);
    FILE *fptrout = fopen(print, "a");
    fputs(detil, fptrout);
    fclose(fptrout);
}


void createDir(char *NF) {
    char temp[150]; 
    char *token1, *token2;
    char *ptrtok1, *ptrtok2;
    char *strptr = NF;

    strcpy(temp, NF);


    while (1) {
        char petName[100];
        char afName[150];
	char befName[150];

        token1 = strtok_r(strptr, "_", &ptrtok1);
        if (!token1) break;

        token2 = strtok_r(token1, ";", &ptrtok2);
        if (!token2) break;

        sprintf(petName, "%s/%s", to, token2);
        char *argv1[] = {"mkdir", "-p", petName, NULL};


    	pid_t child_id2;
   	int status;
    	child_id2 = fork();
    	if (child_id2 == 0)
          execv("/bin/mkdir", argv1);
        else
        ((wait(&status)) > 0);

        token1 = NULL;

        token2 = strtok_r(token1, ";", &ptrtok2);
        if (!token2) break;

        sprintf(befName, "%s/%s", to, temp);
        sprintf(afName, "%s/%s.jpg", petName, token2);

        char *argv2[] = {"cp", befName, afName, NULL};


    	pid_t child_id1;
    	child_id1 = fork();
    	if (child_id1 == 0)
          execv("/bin/cp", argv2);
        else
        ((wait(&status)) > 0);

        token1 = NULL;

        char finName[60];
        strcpy(finName, token2);

        token2 = strtok_r(token1, ";", &ptrtok2);
        if (!token2) break;

	char *ages;
	char *ptok2 = token2;

	for (int i = 0; i < strlen(ptok2); i++) {
        	if (ptok2[i + 1] == '\0') ptok2;
        	if (ptok2[i + 1] == 'j' && ptok2[i + 2] == 'p' && ptok2[i + 3] == 'g') {
            		ptok2[i] = '\0';
            		ptok2;
        	}
	}

        keterangan (petName, ptok2, finName);
        token1 = NULL;

        strptr = NULL;
	}
}
	

void checker() {
    char src[1000];
    struct dirent *ep;
    DIR *dp = opendir(to);
    if (!dp) return;

//  ep = readdir(dp);

    while ((ep = readdir(dp)) != NULL) {
        if (!strcmp(ep->d_name, ".") == 0 && !strcmp(ep->d_name, "..") == 0) {
            char NF[50];
            strcpy(NF, ep->d_name);

            createDir(NF);
            remDir(ep->d_name);
        }
    }
}


int unzipper () {
  pid_t child_id;
    int status;

  child_id = fork();

   if (child_id < 0) {
   exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
   }

  if (child_id == 0) {
    // this is child


//    char *argv[] = {"mkdir", to, NULL};
//    execv("/bin/mkdir", argv);
    	char *argv[] = {"unzip", from , "-x", "*/*", "-d", to, NULL};
    	execv("/usr/bin/unzip", argv);
	exit(EXIT_SUCCESS);
	}
    while ((wait(&status)) > 0);

}



int main() {
    int status;

    pid_t child_id;

    child_id = fork();

    if (child_id < 0) {
       exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }


    if (child_id == 0) {
    // this is child

        char *argv[] = {"mkdir", "-p", to, NULL};
        execv("/bin/mkdir", argv);
    } else {
      // this is parent

        while ((wait(&status)) > 0);

        unzipper();
        checker();
    }
}

