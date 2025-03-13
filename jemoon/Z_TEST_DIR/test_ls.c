#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    if (fork() == 0) {
        // 첫 번째 자식 프로세스: `ls > z`
        int fd = open("z", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(fd, STDOUT_FILENO);
        close(fd);
        execlp("ls", "ls", NULL);
        perror("execlp ls");
        exit(1);
    }
    
//   wait(NULL); // 첫 번째 자식 종료 대기

    if (fork() == 0) {
        // 두 번째 자식 프로세스: `cat < z`
        int fd = open("z", O_RDONLY);
        dup2(fd, STDIN_FILENO);
        close(fd);
        execlp("cat", "cat", NULL);
        perror("execlp cat");
        exit(1);
    }

    wait(NULL); // 두 번째 자식 종료 대기
    return 0;
}
