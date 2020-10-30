
#include <iostream>
#include <winsock.h>
using namespace std;

struct sockaddr_in sket;

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
    }

    int skt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // AF_INET is address family of Internet protocols, using socket stream, Internet prototocol is TCP
    if (skt < 0)
    {
        cout << "Socket was not successful !" << endl;
    }
    else
    {
        cout << "socket is successful" << endl;
    }
    
    sket.sin_family = AF_INET;
    sket.sin_port = htons(9877);
    sket.sin_addr.s_addr = INADDR_ANY; // this is by defaul the local host address
    memset(&(sket.sin_zero),0, 8);

    // binding the socket address
    if (bind(skt, (sockaddr*)&sket, sizeof(sockaddr)) < 0)
    {
        cout << "Socket failed to bind!" << endl;
    }
    else
    {
        cout << "Socket has been binded!" << endl;
    }

    if (listen(skt, 5) < 0)
    {
        cout << "Failed to to listen!" << endl;
        exit(1);
    }
    else
    {
        cout << "The server is curently listenning!" << endl;
    }

    fd_set readSocket, writeSocket, troublingSocket;
    int maxFD = skt;
    struct timeval timeout;
    timeout.tv_sec = 5;
    while (true)
    {
        FD_ZERO(&readSocket);
        FD_ZERO(&troublingSocket);
        FD_ZERO(&writeSocket);

        FD_SET(skt, &readSocket);
        FD_SET(skt, &troublingSocket);
        int ready = select(maxFD + 1, &readSocket, &writeSocket, &troublingSocket, &timeout);
        if( ready< 0)
        {
            cout << "The server failed" << endl;
        }
        else if (ready == 0)
        {
            cout << "There is no one connecting!" << endl;
        }
        else
        {
            cout << "We have currently " << ready << " connections ready on the server!" << endl;
        }
        
    }
    return 0;
}
