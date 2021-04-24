# Laporan Penjelasan Soal Shift Modul 2

## Anggota
- Mohammad Faderik Izzul Haq (05111940000023)
- Jonathan Timothy Siregar (05111940000120)
- Abiya Sabitta Ragadani (05111940000166)

## SOAL 1
## SOAL 2
## SOAL 3
Pada soal ini kita diminta membuat program yang berupa daemon proses.
### Kendala yang dihadapi
Pada pengerjaan soal ini, kami sempat mengalami kendala karena command wget tidak bisa berjalan dengan exec. Kami sempat stuck karena tidak mengetahui error nya terletak dimana. Namun setelah kami coba run program yang sama di komputer lain, ternyata program bisa berjalan. Jadi kami simpulkan komputer pertama yang kami gunakan (Ubuntu 16.04) terdapat masalah yang sampai saat ini belum kami ketahui. Selain itu pada masa pengerjaan soal shift kami belum banyak tahu tentang argumen program dan kill program dari dalam program. Sehingga kami belum sempat selesai mengerjakan sampai ke sub soal D dan E. Selain itu kami sempat melakukan kesalahan pada penempatan lokasi exit() sehingga proses berjalan sangat banyak dan membuat komputer hang.

### Sub Soal A

### Sub Soal B
Pada sub soal B diminta untuk mengisi direktori yang sudah dibuat dengan 10 gambar yang didownload dari https://picsum.photos/, dimana setiap gambar akan didownload setiap 5 detik. Setiap gambar yang didownload akan diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss] dan gambar tersebut berbentuk persegi dengan ukuran (n%1000) + 50 pixel dimana n adalah detik Epoch Unix. Untuk itu dapat melanjutkan proses milik poin A, dengan else dan memanggil fungsi wait () untuk memasstikan pembuatan folder telah selesai

```cpp
while ((wait(&stsA)) > 0);
char curFolder[200];
strcpy(curFolder, nmFolder);
chdir(curFolder);
```

Jika pembuatan direktori telah selesai, pindah ke direktori tersebut dengan fungsi chdir(), jika telah masuk ke direktori tersebut,lakukan perulangan sebanyak 10 kali yang setiap iterasinya melakukan hal berikut. Pertama persiapkan variabel untuk memberi nama file dengan cara yang sama dengan sub soal A. Lalu download file dengan command wget dengan perintah fork() dan exec() dan beri nama file dengan variabel yang telah dibuat sebelumnya. Setelah proses download dilakukan, tunggu selama 5 detik dengan fungsi sleep(5)

```cpp
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
    char *argv[] = {"wget", "-qO", nmFile, linkDL, NULL};
    execv("/bin/wget", argv);
    exit(0);
  }

  lop++;
  sleep(5);
}
```

### Sub Soal C
### Sub Soal D
### Sub Soal E
