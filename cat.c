#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
char cwd[1000];
void callGetcwd() {
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("getcwd() error\n");
    }
}
int main(int argc, char const *arg[]) {
    const char *token = arg[1];
    char stri[105];
    strcpy(stri, arg[2]);
    if (strcmp(token, "-n") == 0) {
        char *vari = strtok(stri, " ");
        if (strcmp(vari, "cat") == 0) {
            vari = strtok(NULL, " ");
            if (strcmp(vari, "-n") == 0) {
                vari = strtok(NULL, " ");
            }
        }
        struct stat st = {0}; // initialize status of file
        int line = 1;
        callGetcwd();
        strcat(cwd, "/");
        strcat(cwd, vari);
        if (stat(cwd, &st) == -1) {
            printf("File does not exist\n");
        }
        FILE *file = fopen(cwd, "r");
        printf("%s\n", cwd);
        if (file != NULL) {
            char output[150];
            while (fgets(output, sizeof(output), file) != NULL) {
                printf("%d ", line);
                line += 1;
                fputs(output, stdout);
            }
        }
        if (file == NULL) {
            printf("Error in opening file\n");
        }
    } else if (strcmp(token, "-E") == 0) {
        struct stat st = {0}; // initialize status of file
        char *vari = strtok(stri, " ");
        if (strcmp(vari, "cat") == 0) {
            vari = strtok(NULL, " ");
            if (strcmp(vari, "-E") == 0) {
                vari = strtok(NULL, " ");
            }
        }
        callGetcwd();
        strcat(cwd, "/");
        strcat(cwd, vari);
        if (stat(cwd, &st) == -1) {
            printf("File does not exist\n");
        }
        FILE *file = fopen(cwd, "r");
        if (file != NULL) {
            char output[150];
            while (fgets(output, sizeof(output), file) != NULL) {
                strcat(output, "$");
                fputs(output, stdout);
            }
        }
        if (file == NULL) {
            printf("Error in opening file\n");
        }
    } else if (strcmp(token, "--help") == 0) {
        printf("Help in cat Command\n");
    } else {
        printf("Command not supported\n");
    }
    return 0;
}
