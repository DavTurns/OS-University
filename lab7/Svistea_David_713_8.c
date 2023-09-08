#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>
#include <string.h>

int main() {
    int p12[2]; // pipe 1 to 2
    int p13[2]; // pipe 1 to 3
    int p24[2]; // pipe 2 to 4
    int p34[2]; // pipe 3 to 4
    char buffer[31];

    char a, b, a_lower;
    int i, pid1, pid2, pid3, status;
    if (pipe(p12) == -1 || pipe(p13) == -1 || pipe(p24) == -1 || pipe(p34) == -1) {
        perror("pipe error");
        exit(1);
    }


    if ((pid1 = fork()) == -1) {
        printf("fork fehlgeschlagen");
        exit(1);
    }

    if (pid1 == 0) {
        //prozess 2

        //close unused pipes

        close(p12[1]);
        close(p24[0]);
        close(p13[1]);
        close(p13[0]);
        close(p34[0]);
        close(p34[1]);

        char alphabet[] = "abcdefghijklmnopqrstuvwxyz";

        while ((read(p12[0], &a, 1)) == 1) {
            a_lower = tolower(a);
            //ermittle ob a_lower ein buchstabe ist;
            for (i = 0; i < 26; i++) {
                if (a_lower == alphabet[i]) {
                    a_lower = '0';
                    break;
                }
            }
            write(p24[1], &a_lower, 1);
        }

        close(p12[0]);
        close(p24[1]);
        exit(0);
    }

    if ((pid2 = fork()) == -1) {
        printf("fork fehlgeschlagen");
        exit(1);
    }

    if (pid2 == 0) {
        //prozess 3
        char nums[] = "0123456789";
        close(p13[1]);
        close(p34[0]);
        close(p12[1]);
        close(p12[0]);
        close(p24[0]);
        close(p24[1]);

        while (read(p13[0], &a, 1) == 1) {
            char a_changed = a;
            for (i = 0; i < 10; i++) {
                if (a == nums[i]) {
                    a_changed = '9';
                    break;
                }
            }
            write(p34[1], &a_changed, 1);
        }
        close(p34[1]);
        exit(0);
    }

    if ((pid3 = fork()) == -1) {
        printf("fork fehlgeschlagen");
        exit(1);
    }
    if (pid3 == 0) {
        //prozess 4

        close(p12[1]);
        close(p12[0]);
        close(p24[1]);
        close(p34[1]);
        close(p13[0]);
        close(p13[1]);
        char outbuffer[1024];

        i = 0;
        while ((read(p24[0], &a, 1)) == 1) {
            outbuffer[i] = a;
            i++;
        }

        close(p24[1]);
        while ((read(p34[0], &a, 1)) == 1) {
            outbuffer[i] = a;
            i++;
        }
        printf("%.*s", i, outbuffer);

        close(p34[1]);
        exit(0);

    }

//prozess 1

//closing unused pipes
    close(p24[0]);
    close(p34[0]);
    close(p24[1]);
    close(p34[1]);
    close(p12[0]);
    close(p13[0]);

    int linecount = 0;
    while (1) {
        char line[100];
        printf("Enter a line (maximum 30 characters): ");
        fgets(line, sizeof(line), stdin);
        if (line[0] == '0') {
            break;
        }
        
        // Check if the line length exceeds the maximum allowed
        if (strlen(line) > 31) {
            printf("Line too long! Please enter a line with a maximum of %d characters.\n", 30);
            continue;
        }
        if (linecount % 2) {
            write(p12[1], line, strlen(line));
        } else {
            write(p13[1], line, strlen(line));
        }
        linecount++;
    }

    close(p12[1]);
    close(p13[1]);
    while (wait(&status) != -1);

    exit(0);
    return 0;
}
