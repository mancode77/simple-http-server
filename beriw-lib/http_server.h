#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <functional>
#include <map>
#include <string>

using HandlerFunction = std::function<void(const std::map<std::string, std::string>&, std::string&)>;

class HTTPServer {
public:
    HTTPServer();

    void addRoute(const std::string& route, HandlerFunction handler);
    void start(int port);

private:
    std::map<std::string, HandlerFunction> routes;
    void handleRequest(const std::string& request, std::string& response);
};

#endif