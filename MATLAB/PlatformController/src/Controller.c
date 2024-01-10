#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include "../include/MATLAB/c_coder_ert_shrlib_rtw/c_coder_types.h"
#include "../include/MATLAB/c_coder_ert_shrlib_rtw/rtwtypes.h"
#include "../include/MATLAB/c_coder_ert_shrlib_rtw/c_coder.h"

#include <stddef.h>
#include <unistd.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#define DEFAULT_BUFLEN 24

typedef void (*Dll_Step)(RT_MODEL_c_coder_T* const, real_T, real_T, real_T, real_T, real_T, real_T, uint8_T[25]);
typedef void (*Dll_Initialize)(RT_MODEL_c_coder_T* const, real_T, real_T, real_T, real_T, real_T, real_T);


static RT_MODEL_c_coder_T c_coder_M_;
static RT_MODEL_c_coder_T* const c_coder_MPtr = &c_coder_M_;
static B_c_coder_T c_coder_B;
static DW_c_coder_T c_coder_DW;
static X_c_coder_T c_coder_X;

static real_T c_coder_U_Inport0;
static real_T c_coder_U_Inport1;
static real_T c_coder_U_Inport2;
static real_T c_coder_U_Inport3;
static real_T c_coder_U_Inport4;
static real_T c_coder_U_Inport5;

// args: OPEN_PORT PLATFORM_IP PLATFORM_PORT MOCK
// MOCK is a boolean, if false, program does not connect to STEWART PLATFORM
int main(int argc, char **argv) {

    if(argc != 5) {
        printf("Wrong number of arguments");
        return 0;
    }

    // int OPEN_PORT = atoi(argv[1]);
    char *OPEN_PORT = argv[1];
    char *PLATFORM_IP = argv[2];
    char *PLATFORM_PORT = argv[3];
    bool MOCK = (strcmp(argv[4], "true") == 0);


    // Printing the variables
    printf("OPEN_PORT: %d\n", OPEN_PORT);
    printf("PLATFORM_IP: %s\n", PLATFORM_IP);
    printf("PLATFORM_PORT: %d\n", PLATFORM_PORT);
    printf("MOCK: %s\n", MOCK ? "true" : "false");

    RT_MODEL_c_coder_T* const c_coder_M = c_coder_MPtr;
    c_coder_M->blockIO = &c_coder_B;
    c_coder_M->dwork = &c_coder_DW;
    c_coder_M->contStates = &c_coder_X;

    HINSTANCE dllHandle = LoadLibrary("./c_coder_win64.dll");

    if (dllHandle != NULL) {
        Dll_Step step = (Dll_Step)GetProcAddress(dllHandle, "wrapper_c_coder_step");
        Dll_Initialize initialize = (Dll_Initialize)GetProcAddress(dllHandle, "wrapper_c_coder_initialize");


        if (initialize != NULL && step != NULL) {
            uint8_T output[25];
            initialize(c_coder_M, c_coder_U_Inport0, c_coder_U_Inport1, c_coder_U_Inport2, c_coder_U_Inport3, c_coder_U_Inport4, c_coder_U_Inport5);
            

            //// Initializing Winsock
            int iResult;
            WSADATA wsaData;
            iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (iResult != 0) {
                printf("WSAStartup failed: %d\n", iResult);
                return 1;
            }
            
            //// Creating a Socket for the Server
            struct addrinfo *result = NULL, hints;

            ZeroMemory(&hints, sizeof (hints));
            hints.ai_family = AF_INET;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_protocol = IPPROTO_TCP;
            hints.ai_flags = AI_PASSIVE;

            // Resolve the local address and port to be used by the server
            iResult = getaddrinfo(NULL, OPEN_PORT, &hints, &result); //port number associated with the server that the client will connect to
            if (iResult != 0) {
                printf("getaddrinfo failed: %d\n", iResult);
                WSACleanup();
                return 1;
            }

            SOCKET ListenSocket = INVALID_SOCKET;
            ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
            if (ListenSocket == INVALID_SOCKET) {
                printf("Error at socket(): %d\n", WSAGetLastError());
                freeaddrinfo(result);
                WSACleanup();
                return 1;
            }

            //// To bind a socket
            // Setup the TCP listening socket
            iResult = bind( ListenSocket, result->ai_addr, (int)result->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                printf("bind failed with error: %d\n", WSAGetLastError());
                freeaddrinfo(result);
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            freeaddrinfo(result);

            //// Listening on a Socket
            if ( listen( ListenSocket, SOMAXCONN ) == SOCKET_ERROR ) {
                printf( "Listen failed with error: %d\n", WSAGetLastError() );
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            //// Accepting a Connection
            SOCKET ClientSocket;
            ClientSocket = INVALID_SOCKET;

            // Accept a client socket
            ClientSocket = accept(ListenSocket, NULL, NULL);
            if (ClientSocket == INVALID_SOCKET) {
                printf("accept failed: %d\n", WSAGetLastError());
                closesocket(ListenSocket);
                WSACleanup();
                return 1;
            }

            ////////////////////////////////////
            //// Creating a socket for the client
            struct addrinfo *resultc = NULL, *ptrc = NULL, hintsc;

            ZeroMemory( &hintsc, sizeof(hintsc) );
            hintsc.ai_family   = AF_INET;
            hintsc.ai_socktype = SOCK_STREAM;
            hintsc.ai_protocol = IPPROTO_TCP;

            // Resolve the server address and port
            int iResultc;
            iResultc = getaddrinfo(PLATFORM_IP, PLATFORM_PORT, &hintsc, &resultc);
            if (iResultc != 0) {
                printf("getaddrinfo failed: %d\n", iResultc);
                WSACleanup();
                return 1;
            }

            SOCKET ConnectSocket = INVALID_SOCKET;
            // Attempt to connect to the first address returned by the call to getaddrinfo
            ptrc = resultc;

            // Create a SOCKET for connecting to server
            ConnectSocket = socket(ptrc->ai_family, ptrc->ai_socktype, ptrc->ai_protocol);
            if (ConnectSocket == INVALID_SOCKET) {
                printf("Error at socket(): %d\n", WSAGetLastError());
                freeaddrinfo(resultc);
                WSACleanup();
                return 1;
            }

            //// Connecting to a Socket
            // Connect to server.
            iResultc = connect( ConnectSocket, ptrc->ai_addr, (int)ptrc->ai_addrlen);
            if (iResultc == SOCKET_ERROR) {
                closesocket(ConnectSocket);
                ConnectSocket = INVALID_SOCKET;
            }
            freeaddrinfo(resultc);

            if (ConnectSocket == INVALID_SOCKET) {
                printf("Unable to connect to server!\n");
                WSACleanup();
                return 1;
            }

            //// Receiving and Sending Data on the Server
            char recvbuf[DEFAULT_BUFLEN];
            int iResults;
            int recvbuflen = DEFAULT_BUFLEN;

            float simValues[6];
            // Receive until the peer shuts down the connection

            do {

                iResults = recv(ClientSocket, recvbuf, recvbuflen, 0);
                if (iResults > 0) {
                    printf("Bytes received: %d\n", iResults);


                    memcpy(simValues, recvbuf, sizeof(simValues));


                    // LOOP DO SIMULINK
                    step(c_coder_M, simValues[0], simValues[1], simValues[2], simValues[3], simValues[4], simValues[5], output);
                    
                    printf("Values of my_out1: ");
                    for (int i = 0; i < 25; ++i) {
                        printf("%u ", output[i]);  // Assuming uint8_T is unsigned char
                    }

                    iResults = send(ConnectSocket, recvbuf, recvbuflen, 0);
                    if (iResults == SOCKET_ERROR) {
                        printf("send failed: %d\n", WSAGetLastError());
                        closesocket(ConnectSocket);
                        WSACleanup();
                        return 1;
                    }
                    printf("Bytes sent: %d\n", iResults);


                } else if (iResults == 0)
                    printf("Connection closing...\n");
                else {
                    printf("recv failed: %d\n", WSAGetLastError());
                    closesocket(ClientSocket);
                    WSACleanup();
                    return 1;
                }

            } while (iResults > 0);


            //// Disconnecting the Server
            // shutdown the send half of the connection since no more data will be sent
            iResult = shutdown(ClientSocket, SD_SEND);
            if (iResult == SOCKET_ERROR) {
                printf("shutdown failed: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }

            // shutdown the send half of the connection since no more data will be sent
            iResult = shutdown(ConnectSocket, SD_SEND);
            if (iResult == SOCKET_ERROR) {
                printf("shutdown failed: %d\n", WSAGetLastError());
                closesocket(ConnectSocket);
                WSACleanup();
                return 1;
            }

            // cleanup
            closesocket(ClientSocket);
            closesocket(ConnectSocket);
            WSACleanup();

            return 0;

        }
        else {
            printf("Error: Function not found in DLL.\n");
        }
        FreeLibrary(dllHandle);
    }
    else {
        printf("Error: DLL not found or failed to load.\n");
    }
    return 0;
}
