#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <wait.h>
#include <dirent.h>
#include <time.h>
#include <string.h>

void Pindah(char *base, char *tujuan);
void Pindah2(char *file, char *folder);
void makeDir();
void jalan();
void apusfolder(char* base);
void apusfolder2(char* tujuan);
void zip();
void foto();
void musik();
void film();


int main() {
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/home/abit/Desktop/Modul2/Praktikum/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  bool check = false;

  while (1) {
	char waktu[100];
	time_t now =time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);
	strftime(waktu, sizeof(waktu), "%d-%m__%H-%M", &tstruct);
	if(strcmp("09-04__16-22",waktu) == 0){
		jalan();
		apusfolder("/home/abit/Desktop/Modul2/Praktikum");}
	else if(strcmp("09-04__22-22", waktu) == 0)zip();
    
	sleep(1);
  }
}

void musik(){
 pid_t child;
 int flag;
 child = fork();
 if(child < 0) exit(EXIT_FAILURE);
 if(child == 0){
	pid_t child_2;
	int flag2;
	child_2 = fork();
	if(child_2 < 0) exit(EXIT_FAILURE);
	if(child_2 == 0){
		char *argument[] = {"wget", "-bq","--no-check-certificate", "https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download", "-O", "Musik_for_Stevany.zip", NULL};
		execv("/bin/wget", argument);}
	else{
		while((wait(&flag2))>0);
		sleep(30);
		char *argument2[] = {"unzip", "/home/abit/Desktop/Modul2/Praktikum/Musik_for_Stevany.zip", NULL};
 		execv("/bin/unzip",argument2);}
 }
 else{
 while((wait(&flag)) > 0);
 Pindah("MUSIK","Musyik");}
}

void film(){
 pid_t child;
 int flag;
 child = fork();
 if(child < 0) exit(EXIT_FAILURE);
 if(child == 0){
	pid_t child_2;
	int flag2;
	child_2 = fork();
	if(child_2 < 0) exit(EXIT_FAILURE);
	if(child_2 == 0){
		char *argument[] = {"wget", "-bq", "--no-check-certificate", "https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download", "-O", "Film_for_Stevany.zip", NULL};
		execv("/bin/wget", argument);}
	else{
		while((wait(&flag2))>0);
		sleep(30);
		char *argument2[] = {"unzip", "/home/abit/Desktop/Modul2/Praktikum/Film_for_Stevany.zip", NULL};
 		execv("/bin/unzip",argument2);}
 }
 else{
 while((wait(&flag)) > 0);
 Pindah("FILM","Fylm");}
}


void foto(){
 pid_t child;
 int flag;
 child = fork();
 if(child < 0) exit(EXIT_FAILURE);
 if(child == 0){
	pid_t child_2;
	int flag2;
	child_2 = fork();
	if(child_2 < 0) exit(EXIT_FAILURE);
	if(child_2 == 0){
		char *argument[] = {"wget", "-bq", "--no-check-certificate", "https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download", "-O", "Foto_for_Stevany.zip", NULL};
		execv("/bin/wget", argument);}
	else{
		while((wait(&flag2))>0);
		sleep(30);
		char *argument2[] = {"unzip", "/home/abit/Desktop/Modul2/Praktikum/Foto_for_Stevany.zip", NULL};
 		execv("/bin/unzip",argument2);}
 }
 else{
 while((wait(&flag)) > 0);
 Pindah("FOTO","Pyoto");}
}


void Pindah(char *base, char*tujuan){
 struct dirent *p;
 char pt[1000];
 DIR *dir = opendir(base);

 if(!dir) return;
 while((p = readdir(dir)) != NULL){
 	if(strcmp(p->d_name, ".") != 0 && strcmp(p->d_name, "..") != 0){
		strcpy(pt, base);
		strcat(pt, "/");
		strcat(pt, p->d_name);
		Pindah2(pt, tujuan);}
 }
 closedir(dir);
}

void Pindah2(char *file, char *folder){
 pid_t child;
 child = fork();
 int flag;
 if(child < 0) exit(EXIT_FAILURE);
 if(child == 0){
	char *arg[]={"mv", file, folder, NULL};
	execv("/bin/mv", arg);}
 else{
 while((wait(&flag)) > 0);}
}

void makeDir(){
 pid_t child;
 child = fork();
 if(child < 0) exit(EXIT_FAILURE);
 if(child == 0){
 	pid_t child_2;
	child_2 = fork();
	if(child_2 < 0) exit(EXIT_FAILURE);
	if(child_2 == 0){
		char *arg[]={"mkdir", "-p", "/home/abit/Desktop/Modul2/Praktikum/Musyik", NULL};
		execv("/bin/mkdir", arg);}
	else{
		char *arg2[]={"mkdir", "-p", "/home/abit/Desktop/Modul2/Praktikum/Fylm", NULL};
		execv("/bin/mkdir", arg2);}
 }
 else{
	char *arg3[]={"mkdir", "-p", "/home/abit/Desktop/Modul2/Praktikum/Pyoto", NULL};
	execv("/bin/mkdir", arg3);}
}


void jalan(){
 pid_t child;
 child = fork();
 int flag;
 if(child<0) exit(EXIT_FAILURE);
 if(child == 0){
 	pid_t child_2;
	child_2 = fork();
	int flag2;

	if(child_2 <0) exit(EXIT_FAILURE);
	if(child_2 == 0){
		pid_t child_3;
		child_3 = fork();
		int flag3;
		if(child_3 <0)exit(EXIT_FAILURE);
		if(child_3 ==0) makeDir();
		else{
		while((wait(&flag3)) > 0);
		foto();
		_exit(1);}
	}
	else{
		while((wait(&flag2)) > 0);
		film();
		_exit(1);}
 }
 else{
	while((wait(&flag)) > 0);
	musik();
 }
}

void zip(){
 char *arg[]={"zip","-mr","Lopyu_Stevany.zip","Pyoto","Fylm","Musyik",NULL};
 execv("/bin/zip",arg);
}

void apusfolder(char* base){
	char path[1000];
	struct dirent *dp;
	DIR *dir = opendir(base);
	
	if(!dir) return;
	while((dp=readdir(dir)) != NULL){
		if(strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") !=0){
			strcpy(path, base);
			strcat(path, "/");
			strcat(path, dp->d_name);
			if(strcmp(dp->d_name, "FILM") == 0 || strcmp(dp->d_name, "FOTO") == 0 || strcmp(dp->d_name, "MUSIK") == 0){
			apusfolder2(path);}
		}
	}
}

void apusfolder2(char* tujuan){
	pid_t child;
	child = fork();
	int flag;
	if(child < 0)exit(EXIT_FAILURE);
	if(child == 0){
		char *arg[]={"rm", "-rf", tujuan, NULL};
		execv("/bin/rm",arg);
	}
	else{
		while((wait(&flag)) > 0);
	}
}
