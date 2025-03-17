#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *home = getenv("HOME");
    char *pwd = getenv("PWD");

    if (home)
        printf("HOME: %s\n", home);
    if (pwd)
        printf("PWD: %s\n", pwd);

    return 0;
}
