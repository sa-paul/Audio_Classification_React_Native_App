#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8080
#define MAX_BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[MAX_BUFFER_SIZE] = {0};
    FILE *audio_file;
    long audio_file_size;

    // Opening audio file
    audio_file = fopen("audio.wav", "rb");
    if (audio_file == NULL) {
        perror("Error opening audio file");
        exit(EXIT_FAILURE);
    }

    // Get the file size
    fseek(audio_file, 0, SEEK_END);
    audio_file_size = ftell(audio_file);
    fseek(audio_file, 0, SEEK_SET);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    // if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
    //     perror("setsockopt");
    //     exit(EXIT_FAILURE);
    // }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Sending audio file
    while (!feof(audio_file)) {
        int bytes_read = fread(buffer, 1, sizeof(buffer), audio_file);
        if (bytes_read < 0) {
            perror("Error reading from audio file");
            exit(EXIT_FAILURE);
        }
        send(new_socket, buffer, bytes_read, 0);
    }

    printf("Audio file sent successfully\n");
    fclose(audio_file);
    close(server_fd);
    return 0;
}
