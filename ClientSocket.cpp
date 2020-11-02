#include <iostream>
#include <winsock.h>
using namespace std;

struct sockaddr_in soket;

int main(int argc, char* args[])
{
    (void)argc;
    (void)args;
    WSADATA w; // Windows environment variable to get socket to work
    if (WSAStartup(MAKEWORD(2, 2), &w) >= 0) // MAKEWORD is a macro to initialized the environment variable
    {
        cout << "Windows env var is initialized!" << endl;
    }
    else
    {
        cout << "Windows env var was not initialized" << endl;
        WSACleanup();
    }

    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // AF_INET is address family of Internet protocols, using socket stream, Internet prototocol is TCP
    if (client < 0)
    {
        cout << "Socket was not successful !" << endl;
    }
    else
    {
        cout << "socket is successful" << endl;
    }

    soket.sin_family = AF_INET;
    soket.sin_port = htons(9877);
    soket.sin_addr.s_addr = inet_addr("127.0.0.1"); // this is by defaul the local host address
    memset(&(soket.sin_zero), 0, 8);
    // connect the socket address to the server
    if (connect(client, (sockaddr*)&soket, sizeof(sockaddr)) < 0)
    {
        cout << "Socket failed to connect!" << endl;
        WSACleanup();
    }
    else
    {
        cout << "Socket has been connected!" << endl;
    }


    return 0;
}