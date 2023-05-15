#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

char cwd[1000];

void callChdir(char* add) {
    int x = chdir(add);
    if (x == -1) {
        printf("Error in changing directory to %s\n", add);
    } else {
        strcpy(cwd, add);
    }
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("getcwd() error\n");
    }
}

int main(int argc, const char* arg[]) {
    const char* token = arg[0];
    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        printf("getcwd() error\n");
        return 1;
    }
    char stri[105];
    strcpy(stri, arg[1]);

    if (token == NULL) {
        printf("Argument missing, Try 'mkdir --help' for more information. \n");
    } else {
        if (strcmp(token, "--help") == 0) {
            printf("Help prompt for mkdir \n");
        } else if (strcmp(token, "-v") == 0) {
            char* vari = strtok(stri, " ");
            if (strcmp(vari, "mkdir") == 0) {
                vari = strtok(NULL, " ");
                if (strcmp(vari, "-v") == 0) {
                    vari = strtok(NULL, " ");
                }
            }
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                printf("getcwd() error\n");
                return 1;
            }
            while (vari != NULL) {
                struct stat s = {0};
                char temp[1000];
                if (getcwd(temp, sizeof(temp)) == NULL) {
                    printf("getcwd() error\n");
                    return 1;
                }
                strcat(temp, "/");
                strcat(temp, vari);

                printf("%s\n", temp);
                int x = mkdir(temp, 0777);
                if (x == -1) {
                    printf("Cannot create '%s' directory, it already exists\n", vari);
                    vari = strtok(NULL, " ");
                } else {
                    printf("Directory '%s' created\n", vari);
                    vari = strtok(NULL, " ");
                }
            }
        } else {
            char* vari = strtok(stri, " ");
            if (strcmp(vari, "mkdir") == 0) {
                vari = strtok(NULL, " ");
            }
            if (getcwd(cwd, sizeof(cwd)) == NULL) {
                printf("getcwd() error\n");
                return 1;
            }
            while (vari != NULL) {
                struct stat s = {0};
                char temp[1000];
                if (getcwd(temp, sizeof(temp)) == NULL) {
                    printf("getcwd() error\n");
                    return 1;
                }
                strcat(temp, "/");
                strcat(temp, vari);

                int x = mkdir(temp, 0777);
                if (x == -1) {
                    printf("Cannot create directory, it already exists\n");
                }
                vari = strtok(NULL, " ");
            }
        }
    }
}