#include <iostream>
#include <winsock2.h>
#include <thread>
#include <vector>
#include <map>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

mutex chat_mutex;
map<SOCKET, string> clients;

void handle_client(SOCKET client_socket) {
    char buffer[512];
    while (true) {
        int result = recv(client_socket, buffer, sizeof(buffer), 0);
        if (result <= 0) {
            lock_guard<mutex> lock(chat_mutex);
            clients.erase(client_socket);
            closesocket(client_socket);
            return;
        }
        string message(buffer, result);

        lock_guard<mutex> lock(chat_mutex);
        for (const auto& client : clients) {
            if (client.first != client_socket) {
                send(client.first, message.c_str(), message.size(), 0);
            }
        }
    }
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(1234);

    bind(server_socket, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, SOMAXCONN);

    cout << "Serwer czatu uruchomiony na porcie 1234\n";

    while (true) {
        SOCKET client_socket = accept(server_socket, nullptr, nullptr);

        lock_guard<mutex> lock(chat_mutex);
        clients[client_socket] = "Klient";

        thread(handle_client, client_socket).detach();
    }

    WSACleanup();
    return 0;
}
