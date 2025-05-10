#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void receive_messages(SOCKET client_socket) {
    char buffer[512];
    while (true) {
        int result = recv(client_socket, buffer, sizeof(buffer), 0);
        if (result <= 0) {
            cout << "Roz³¹czono z serwerem.\n";
            return;
        }
        cout << string(buffer, result) << endl;
    }
}

int main() {
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);

    string nick;

    cout << "Podaj nick: ";
    cin >> nick;

    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);

    // Zmieniono inet_addr() na inet_pton()
    if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) != 1) {
        cout << "Blad konwersji adresu IP.\n";
        return 1;
    }

    if (connect(client_socket, (sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
        cout << "Nie udalo sie polaczyc z serwerem.\n";
        return 1;
    }

    cout << "Polaczono z serwerem. Mozesz wysylac wiadomosci.\n";

    thread receive_thread(receive_messages, client_socket);
    receive_thread.detach();

    string message;
    while (true) {
        getline(cin, message);
        message = nick + ": " + message;

        send(client_socket, message.c_str(), message.size(), 0);
    }

    closesocket(client_socket);
    WSACleanup();
    return 0;
}
