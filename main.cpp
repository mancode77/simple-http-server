#include "beriw-lib/http_server.h"
#include <iostream>

void helloHandler(const std::map<std::string, std::string>& params, std::string& response) {
    // Bangun respons JSON
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
