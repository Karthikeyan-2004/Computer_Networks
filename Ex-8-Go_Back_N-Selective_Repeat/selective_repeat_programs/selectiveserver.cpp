#include <bits/stdc++.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <ctime>
#include <chrono>
#include <thread>

#define PORT 8080
#define ll long long int

using namespace std;

void sendFrame(int client_socket, ll frameNumber) {
    string msg = "Sending Frame " + to_string(frameNumber);
    send(client_socket, msg.c_str(), msg.size(), 0);
    cout << msg << endl;
}

void selectiveRepeatTransmission(int client_socket, ll tf, ll N) {
    ll tt = 0;
    unordered_map<ll, bool> ackMap;  // Track acknowledgments for each frame
    ll i = 1;

    while (i <= tf) {
        for (ll k = i; k < i + N && k <= tf; ++k) {
            if (!ackMap[k]) {  // Send only if not acknowledged
                sendFrame(client_socket, k);
                tt++;
                usleep(500000); // slight delay between frames
            }
        }

        // Checking acknowledgments for frames in the window
        for (ll k = i; k < i + N && k <= tf; ++k) {
            if (ackMap[k]) continue;  // Skip already acknowledged frames

            char buffer[1024] = {0};
            fd_set readfds;
            struct timeval tv;
            FD_ZERO(&readfds);
            FD_SET(client_socket, &readfds);
            tv.tv_sec = 8;  // Timeout for selective repeat ARQ
            tv.tv_usec = 0;

            int activity = select(client_socket + 1, &readfds, NULL, NULL, &tv);

            if (activity > 0) {
                int valread = read(client_socket, buffer, 1024);
                if (valread > 0 && strcmp(buffer, "ACK") == 0) {
                    cout << "Acknowledgment received for Frame " << k << endl;
                    ackMap[k] = true;
                } else {
                    cout << "NACK received or no acknowledgment for Frame " << k << endl;
                }
            } else {
                cout << "Timeout! No acknowledgment for Frame " << k << endl;
            }
        }

        // Move window to the next unacknowledged frame
        while (i <= tf && ackMap[i]) {
            i++;
        }

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
        perror("Socket creation failed");
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

    // Start transmission using selective repeat
    selectiveRepeatTransmission(client_socket, tf, N);

    close(client_socket);
    close(server_fd);

    return 0;
}

