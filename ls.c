#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
int main(int argc, const char *argv[]) {
    const char *token = argv[1];
    if (token == NULL) {
        struct dirent **dir;
        int n = scandir(".", &dir, NULL, alphasort);
        if (n == -1) {
            printf("Error while scanning directory\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            char *name = dir[i]->d_name;
            if (name[0] != '.') {
                printf("%s ", name);
                free(dir[i]);
            }
        }
        free(dir);
        printf("\n");
    } else if (strcmp(token, "-R") == 0) {
        struct dirent *dir;
        DIR *d = opendir(".");
        if (d == NULL) {
            printf("Error opening directory\n");
            return 1;
        }
        while ((dir = readdir(d)) != NULL) {
            printf("%s ", dir->d_name);
        }
        printf("\n");
        closedir(d);
    } else if (strcmp(token, "-a") == 0) {
        struct dirent **dir;
        int n = scandir(".", &dir, NULL, alphasort);
        if (n == -1) {
            printf("Error while scanning directory\n");
            return 1;
        }
        for (int i = 0; i < n; i++) {
            char *name = dir[i]->d_name;
            printf("%s ", name);
            free(dir[i]);
        }
        free(dir);
        printf("\n");
    } else {
        printf("Command not supported\n");
        return 1;
    }

    return 0;
}
