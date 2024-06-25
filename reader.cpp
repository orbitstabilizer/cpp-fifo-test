// reader.cpp
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <chrono>
#include <sys/stat.h>

struct Message {
    int data[100];
    std::chrono::high_resolution_clock::time_point timestamp;
};

int main() {
    const char *pipe_name = "/tmp/test_pipe";
    mkfifo(pipe_name, 0666);

    int fd = open(pipe_name, O_RDONLY);
    if (fd == -1) { return 1; }

    const int num_messages = 1000000;
    Message message;
    std::chrono::duration<double, std::micro> latency(0);

    for (int i = 0; i < num_messages; ++i) {
        if (read(fd, &message, sizeof(message)) == -1) {
            close(fd);
            return 1;
        }

        auto receive_time = std::chrono::high_resolution_clock::now();
        latency += receive_time - message.timestamp;
    }
    std::cout << "message.data: " << message.data[0] << std::endl;

    double avg_latency = latency.count() / num_messages;
    std::cout << "avg. latency for "<< num_messages<< " message(s): " << avg_latency << " us" << std::endl;

    close(fd);
    return 0;
}
