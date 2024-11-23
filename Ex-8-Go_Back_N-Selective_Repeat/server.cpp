#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>

#define PORT 8080
#define ll long long int

using namespace std;

void transmission(int client_socket, ll tf, ll N) {
    ll tt = 0;
    ll i = 1;

    while (i <= tf) {
        int z = 0;
        
        // Send frames in the current window
        for (int k = i; k < i + N && k <= tf; k++) {
            string msg = "Sending Frame " + to_string(k);
            send(client_socket, msg.c_str(), msg.size(), 0);
            cout << msg << endl;
            tt++;
            usleep(500000); // slight delay
        }

        // Check acknowledgments for the frames in the window
        for (int k = i; k < i + N && k <= tf; k++) {
            char buffer[1024] = {0};
            
            // Set a timeout of 8 seconds for acknowledgment
            fd_set readfds;
            struct timeval tv;
            FD_ZERO(&readfds);
            FD_SET(client_socket, &readfds);
            tv.tv_sec = 8;  // 8 seconds timeout
            tv.tv_usec = 0;

            int activity = select(client_socket + 1, &readfds, NULL, NULL, &tv);

            if (activity > 0) {
                int valread = read(client_socket, buffer, 1024);
                if (valread > 0 && strcmp(buffer, "ACK") == 0) {
                    cout << "Acknowledgment received for Frame " << k << endl;
                    z++;
                } else {
                    cout << "Timeout or NACK! Frame Number " << k << " Not Received" << endl;
                    cout << "Retransmitting Window..." << endl;
                    break;
                }
            } else {
                cout << "Timeout! Frame Number " << k << " Not Received" << endl;
                cout << "Retransmitting Window..." << endl;
                break;
            }
        }

        i = i + z;  // Move forward by the number of acknowledged frames
        cout << "\n";
    }
    cout << "Total frames sent and resent: " << tt << endl;
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    cout << "Waiting for client connection..." << endl;
    if ((client_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    cout << "Client connected." << endl;

    // Ask for total frames and window size from the client
    ll tf, N;
    char buffer[1024] = {0};

    cout << "Requesting frame count and window size from client..." << endl;
    send(client_socket, "SEND_FRAME_AND_WINDOW_SIZE", 26, 0);
    read(client_socket, buffer, 1024);
    sscanf(buffer, "%lld %lld", &tf, &N);
    cout << "Total Frames: " << tf << ", Window Size: " << N << endl;

    // Start transmission of frames
    transmission(client_socket, tf, N);

    close(client_socket);
    close(server_fd);

    return 0;
}

