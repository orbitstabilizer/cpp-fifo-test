// writer.cpp
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <chrono>
#include <sys/stat.h>
#include <cstring>
#include <algorithm>

struct Message {
    int data[100];
    std::chrono::high_resolution_clock::time_point timestamp;
};

int main() {
    const char *pipe_name = "/tmp/test_pipe";
    mkfifo(pipe_name, 0666);

    int fd = open(pipe_name, O_WRONLY);
    if (fd == -1) { return 1; }

    const int num_messages = 1000000;
    Message message;
    std::fill(message.data, message.data + 100, 31);

    for (int i = 0; i < num_messages; ++i) {
        message.timestamp = std::chrono::high_resolution_clock::now();
        if (write(fd, &message, sizeof(message)) == -1) {
            close(fd);
            return 1;
        }
    }

    close(fd);
    return 0;
}
