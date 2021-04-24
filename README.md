# Laporan Penjelasan Soal Shift Modul 2

## Anggota

- Mohammad Faderik Izzul Haq (05111940000023)
- Jonathan Timothy Siregar (05111940000120)
- Abiya Sabitta Ragadani (05111940000166)

## SOAL 1

## SOAL 2

## SOAL 3

Pada soal ini kita diminta membuat program yang berupa daemon proses yang akan mendownload file dari link tertentu berdasarkan waktu proses tersebut berjalan.

### Kendala yang dihadapi

Pada pengerjaan soal ini, kami sempat mengalami kendala karena command wget tidak bisa berjalan dari exec. Kami sempat stuck karena tidak mengetahui error nya terletak dimana. Namun setelah kami coba run program yang sama di komputer lain, ternyata program bisa berjalan. Jadi kami simpulkan komputer pertama yang kami gunakan (Ubuntu 16.04) terdapat masalah yang sampai saat ini belum kami ketahui. Selain itu pada masa pengerjaan soal shift kami belum banyak tahu tentang argumen program dan kill program dari dalam program. Sehingga kami belum sempat selesai mengerjakan sampai ke sub soal D dan E.

### Sub Soal A

Pada soal A kita diminta membuat direktori setiap 40 detik dengan nama direktori merupakan waktu saat ini dengan format sesuai timestamp [YYYY-mm-dd_HH:ii:ss].

```cpp
int main(){
while (1)
    {
      // program utama
    }
    sleep(40);
}

```

Program soal A ini secara keseluruhan berada dalam while daemon seperti kode diatas.

```cpp
  time_t ta = time(NULL);
  struct tm tms = *localtime(&ta);
  sprintf(nmFolder,
          "%02d-%02d-%d_%02d:%02d:%02d",
          tms.tm_mday,
          tms.tm_mon + 1,
          tms.tm_year + 1900,
          tms.tm_hour,
          tms.tm_min,
          tms.tm_sec);
  pid_t pidA;
  pidA = fork();
  int stsA;
  chdir("/home/boi");

  if (pidA < 0)
    exit(EXIT_FAILURE);
  if (pidA == 0)
  {
    char *argv[] = {"mkdir", nmFolder, NULL};
    execv("/bin/mkdir", argv);
  }
```

Program diatas merupakan child proses untuk membuat folder dengan nama direktori dari string yang digenerate dari waktu saat ini.

### Sub Soal B

### Sub Soal C

### Sub Soal D

        // Print only the process IDs of syslogd:
        // ps -C syslogd -o pid
        // -r, --no-run-if-empty
        // If the standard input does not  contain  any  non‐
        // blanks,  do  not  run  the command.

### Sub Soal E
