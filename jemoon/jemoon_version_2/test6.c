#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_pipeline(char **commands[], int num_cmds) {
    int pipe_fd[2];
    int prev_fd = -1;

    for (int i = 0; i < num_cmds; i++) {
        pipe(pipe_fd); // 파이프 생성
        pid_t pid = fork();

        if (pid == 0) { // 자식 프로세스
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO); // 이전 파이프 읽기 끝을 STDIN으로
                close(prev_fd);
            }
            if (i < num_cmds - 1) {
                dup2(pipe_fd[1], STDOUT_FILENO); // 현재 파이프 쓰기 끝을 STDOUT으로
            }
            close(pipe_fd[0]);
            close(pipe_fd[1]);

            execvp(commands[i][0], commands[i]);
            perror("execvp failed");
            exit(1);
        } else { // 부모 프로세스
            close(pipe_fd[1]); // 현재 파이프 쓰기 끝 닫기
            if (prev_fd != -1) close(prev_fd); // 이전 파이프 읽기 끝 닫기
            prev_fd = pipe_fd[0]; // 현재 파이프 읽기 끝 저장
        }
    }

    // 모든 자식 프로세스 종료 대기
    while (wait(NULL) > 0);
}

int main() {
    char *cmd1[] = {"cat", NULL};
    char *cmd2[] = {"cat", NULL};
    char *cmd3[] = {"ls", "-l", NULL};
    char **commands[] = {cmd1, cmd2, cmd3,};

    execute_pipeline(commands, 3);
    return(0);
}
