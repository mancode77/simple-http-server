# Simple HTTP Server in C++

Implementasi sederhana dari HTTP server menggunakan C++ untuk menangani permintaan HTTP dasar dan routing menggunakan thread dan soket.

## Deskripsi

HTTP Server ini dirancang untuk mendengarkan permintaan HTTP pada port tertentu, menangani rute yang ditentukan pengguna, dan memberikan respons sesuai dengan handler yang terdaftar.

### Fitur Utama

- Menangani permintaan HTTP GET untuk rute yang ditentukan.
- Mendukung penanganan multi-threading untuk melayani beberapa klien secara bersamaan.
- Menggunakan mutex untuk memastikan keselamatan akses ke sumber daya bersama.

## Persyaratan

Sebelum menggunakan server ini, pastikan Anda memiliki hal berikut:
- Compiler C++ (yang mendukung C++11 atau versi lebih baru)
- Header yang diperlukan (`iostream`, `sstream`, `regex`, `sys/socket.h`, `arpa/inet.h`, `unistd.h`, `thread`, `vector`, `mutex`)

## Instalasi dan Penggunaan

### Langkah 1: Clone Repositori

Clone repositori ini ke mesin lokal Anda:

```bash
git clone https://github.com/mancode77/simple-http-server.git
cd http-server-cpp
```

#### Contoh penggunaan Rute dan Handler

Anda dapat menambahkan rute kustom dan fungsi handler ke server. Edit file `main.cpp` untuk menambahkan rute baru dan mendefinisikan handler yang sesuai.

Contoh menambahkan rute `/hello` dengan handler `helloHandler`:

```cpp
#include "http_server.h"
#include <iostream>

void helloHandler(const std::map<std::string, std::string>& params, std::string& response) {
    response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n";
    response += "{ \"message\": \"Hello, World!\" }";
}

int main() {
    HTTPServer server;

    // Tambahkan rute dan handler
    server.addRoute("/hello", helloHandler);

    // Mulai server pada port 8080
    server.start(8080);

    return 0;
}
```
### Langkah 2: Kompilasi Server dan Menjalankan Server

Kompilasi server menggunakan compiler C++:

```bash
# Untuk Linux dan Mac
chmod +x script.sh

./run_linux_or_mac.sh

#Untuk Windows
runner_windows.bat
```

Secara default, server akan mendengarkan pada port 8080. Anda dapat mengubah port di dalam fungsi `main` pada file sumber Anda.

### Langkah 3: Mengakses Server

Buka browser web atau gunakan `curl` untuk mengakses server:

```bash
curl http://localhost:8080/hello
```

Ini akan mengirimkan permintaan GET ke endpoint `/hello` pada server.


## Kontribusi

Kontribusi dipersilakan! Jika Anda menemukan masalah atau memiliki saran untuk perbaikan, silakan buka isu atau kirimkan pull request.

## Lisensi

Proyek ini dilisensikan di bawah Lisensi MIT.

Dokumentasi ini sekarang lebih terstruktur dan membantu pengguna untuk memahami langkah-langkah instalasi, penggunaan, serta cara menambahkan rute dan handler baru ke server HTTP berbasis C++ ini. Pastikan untuk mengganti bagian yang sesuai dengan detail proyek Anda sendiri sebelum menggunakan atau mendistribusikan.
