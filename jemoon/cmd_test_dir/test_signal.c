#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 사용자 정의 구조체
typedef struct s_data
{
    char *str;
} t_data;

// 신호 처리 함수
void handle_signal(int signum, siginfo_t *info, void *context)
{
    t_data *data = (t_data *)context;

    if (signum == SIGINT)
	{
        printf("Signal %d caught! Cleaning up...\n", signum);
        free(data->str); // 동적 메모리 해제
        printf("Memory freed. Exiting program.\n");
        exit(0);
    }
}

int main()
{
    struct sigaction sa;
    t_data data;

    // 동적 메모리 할당
    data.str = malloc(11);
    if (!data.str)
	{
        perror("malloc failed");
        return 1;
    }
    data.str[10] = '\0';

    // sigaction 설정
    sa.sa_flags = SA_SIGINFO; // siginfo_t를 사용하기 위한 플래그 설정
    sa.sa_sigaction = handle_signal;
    sigemptyset(&sa.sa_mask);

    // SIGINT 신호 처리기 등록
    if (sigaction(SIGINT, &sa, NULL) == -1)
	{
        perror("sigaction failed");
        free(data.str);
        return 1;
    }

    // 메인 루프
    int i = 0;
    while (1)
	{
        printf("Running [%d]...\n", i++);
        sleep(1);
    }

    return 0;
}
