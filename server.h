// pseudo-minimal TCP client

#include <vector>
#include <string>
#include <cstring>

#include <winsock2.h>

void send_data(const std::vector<float>& speeds)
{
    static bool initialized = false;
    static int sock;
    
    if (!initialized) {

        WSADATA wsa;
        WSAStartup(MAKEWORD(2,2), &wsa);

        sock = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_port = htons(5000);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        connect(sock, (sockaddr*)&server, sizeof(server));
        initialized = true;
    }

    // stringe çevir (newline ile ayır)
    std::string msg;
    for (float v : speeds) {
        msg += std::to_string(v) + " ";
    }
    msg += "\n";

    send(sock, msg.c_str(), msg.size(), 0);
}