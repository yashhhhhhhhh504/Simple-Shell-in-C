#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
int date(int argc, const char *args[]) {
    const char *token = args[1];
    if (token == NULL) {
        time_t t;
        time(&t);
        if (t == -1) {
            perror("time");
            return 1;
        }
        else {
            printf("%s", ctime(&t));
            return 0;
        }
    }
    else if (strcmp(token, "-u") == 0) {
        time_t t = time(NULL);
        struct tm *gm = gmtime(&t);
        if (gm == NULL) {
            perror("gmtime");
            return 1;
        }
        else {
            printf("UTC TIME: %s", asctime(gm));
            return 0;
        }
    }
    else if (strcmp(token, "--help") == 0) {
        printf("Usage: date [OPTION]...\n");
        printf("Display the current time in the given FORMAT, or set the system date.\n");
        return 0;
    }
    else {
        printf("date: invalid option -- '%s'\n", token);
        printf("Try 'date --help' for more information.\n");
        return 1;
    }
}
int main(int argc, const char *argv[]) {
    date(argc, argv);
    return 0;
}
