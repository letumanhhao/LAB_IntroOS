#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define MAX_MESSAGE_LENGTH 256  // Độ dài tối đa của một thông điệp

int main() {
    int fd;
    char *pipe_path = "/tmp/my_pipe";
    char buffer[MAX_MESSAGE_LENGTH];

    // Tạo pipe nếu chưa có
    mkfifo(pipe_path, 0666);

    // Mở pipe để ghi
    fd = open(pipe_path, O_WRONLY);
    if (fd == -1) {
        perror("Lỗi mở pipe");
        exit(1);
    }

    while (1) {
        printf("Nhập thông điệp (gõ 'exit' để thoát): ");
        fgets(buffer, MAX_MESSAGE_LENGTH, stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Xóa ký tự xuống dòng

        // Nếu nhập 'exit' thì thoát
        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        // Ghi thông điệp vào pipe
        write(fd, buffer, strlen(buffer) + 1);  // Ghi cả ký tự null kết thúc
        printf("Producer gửi: %s\n", buffer);
    }

    close(fd);
    return 0;
}
