#include "http_server.h"
#include <iostream>
#include <sstream>
#include <regex>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <mutex>

HTTPServer::HTTPServer() {}

void HTTPServer::addRoute(const std::string& route, HandlerFunction handler) {
    routes[route] = handler;
}

void HTTPServer::start(int port) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Membuat deskriptor file socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Mengikat socket ke localhost:port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Mendengarkan koneksi masuk
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Server listening on port " << port << std::endl << std::endl;

    // Vector untuk menyimpan thread-thread
    std::vector<std::thread> threads;
    std::mutex mutex; // Mutex untuk keamanan thread

    while (true) {
        // Menerima koneksi masuk
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // Membuat thread baru untuk menangani permintaan
        threads.emplace_back([this, new_socket, &mutex]() {
            char buffer[1024] = {0};

            // Membaca permintaan
            ssize_t bytes_read = read(new_socket, buffer, sizeof(buffer) - 1);
            if (bytes_read == -1) {
                perror("read failed");
                close(new_socket);
                return;
            }
            buffer[bytes_read] = '\0'; // Mengakhiri buffer dengan null

            std::string request(buffer);

            // Menyiapkan respons
            std::string response;
            {
                std::lock_guard<std::mutex> lock(mutex); // Mengunci mutex
                this->handleRequest(request, response); // Memanggil fungsi handleRequest
            }

            // Mengirim respons
            send(new_socket, response.c_str(), response.length(), 0);

            // Menutup socket
            close(new_socket);
        });
    }

    // Bergabung dengan semua thread (seharusnya tidak pernah mencapai sini)
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void HTTPServer::handleRequest(const std::string& request, std::string& response) {
    std::istringstream iss(request);
    std::string method, path, protocol;
    iss >> method >> path >> protocol;

    bool routeMatched = false;
    for (const auto& pair : routes) {
        std::regex routeRegex(pair.first);
        if (std::regex_match(path, routeRegex)) {
            std::map<std::string, std::string> params; // Penampung untuk parsing parameter
            pair.second(params, response); // Memanggil handler dengan parameter dan respons

            // Menentukan kode status
            std::string statusCode = (response.substr(9, 3) == "200") ? "200 OK" : "404 Not Found";

            // Mencetak log dengan metode permintaan dan path
            std::cout << "Request: " << method << " " << path << std::endl;
            std::cout << "Status Code: " << statusCode << std::endl;
            std::cout << std::endl;

            routeMatched = true;
            return;
        }
    }

    if (!routeMatched) {
        // Log bahwa tidak ditemukan
        std::cout << "Request: " << method << " " << path << std::endl;
        std::cout << "Status Code: 404 Not Found" << std::endl;
        std::cout << std::endl;

        response = "HTTP/1.1 404 Not Found\r\n\r\n";
    }
}