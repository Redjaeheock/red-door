/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jemoon <jemoon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 21:50:14 by jemoon            #+#    #+#             */
/*   Updated: 2025/01/19 22:00:46 by jemoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *cwd;

    // 반복문 실행
    for (int i = 0; i < 3; i++) {
        // PWD 환경 변수에서 현재 작업 디렉토리 가져오기
        cwd = getenv("PWD");
        if (cwd == NULL) {
            perror("getenv error");
            return 1;
        }

        // 현재 디렉토리 출력
        printf("Current working directory (from PWD): %s\n", cwd);

        // 디렉토리 변경
        if (i == 0) {
            chdir("/tmp");  // 첫 번째 반복에서 /tmp로 변경
            setenv("PWD", "/tmp", 1);  // PWD 환경 변수도 변경
        } else if (i == 1) {
            chdir("/home");  // 두 번째 반복에서 /home으로 변경
            setenv("PWD", "/home", 1);  // PWD 환경 변수도 변경
        }
    }

    return 0;
}
