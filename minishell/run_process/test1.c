/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jahong <jahong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:30:09 by jahong            #+#    #+#             */
/*   Updated: 2025/03/19 14:35:51 by jahong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

void sigquit_handler(int signum) {
    const char *msg = "Quit (core dumped)\n";
    write(STDERR_FILENO, msg, 18);  // ✅ stderr에 직접 출력

    raise(SIGQUIT);  // ✅ Core Dump 발생
}

void sigchld_handler(int signum) {
    int status;
    waitpid(-1, &status, WNOHANG);  // ✅ 자식 프로세스 종료 감지

    // ✅ readline 강제 출력 및 갱신
    printf("\n");  // ✅ 개행 추가
    rl_replace_line("", 0);  // ✅ 현재 입력 라인 삭제
    rl_redisplay();  // ✅ 프롬프트 갱신
}

// int main() {
//     pid_t pid;

//     // ✅ 부모에서 SIGQUIT을 무시
//     signal(SIGQUIT, SIG_IGN);
//     signal(SIGCHLD, sigchld_handler);  // ✅ 자식 종료 시 readline 갱신

//     pid = fork();
//     if (pid < 0) {
//         perror("fork 실패");
//         exit(1);
//     }
//     else if (pid == 0) {  // ✅ 자식 프로세스
//         signal(SIGQUIT, sigquit_handler);  // ✅ SIGQUIT 핸들러 설정

//         printf("자식 프로세스 실행 중 (PID: %d)\n", getpid());
//         fflush(stdout);  // ✅ 즉시 출력 보장

//         while (1) {
//             sleep(1);  // ✅ 무한 루프 대기 (sleep 계열을 안 쓰려면 다른 블로킹 대기 활용)
//         }
//     }
//     else {  // ✅ 부모 프로세스 (readline() 실행)
//         printf("부모 프로세스 (PID: %d)에서 SIGQUIT 무시 중...\n", getpid());
//         fflush(stdout);  // ✅ 즉시 출력 보장

//         while (1) {
//             char *input = readline(">> ");  // ✅ readline() 실행
//             if (input) {
//                 printf("입력된 값: %s\n", input);
//                 free(input);
//             }
//         }
//     }

//     return 0;
// }