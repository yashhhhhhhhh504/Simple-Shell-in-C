#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
int main(int argc, char const* arg[]) {
    const char* token = arg[0];
    char stri[105];
    strcpy(stri, arg[1]);
    if (token == NULL) {
        printf("missing operand\n");
    }
    else if (strcmp(token, "-f") == 0) {      
        // Flag which never raises an error even if the file is not present
        char* vari = strtok(stri, " ");
        if (strcmp(vari, "rm") == 0) {
            vari = strtok(NULL, " ");
            if (strcmp(vari, "-f") == 0) {
                vari = strtok(NULL, " ");
            }
        }

        while (vari != NULL) {
            remove(vari);
            vari = strtok(NULL, " ");
        }
    }
    else if (strcmp(token, "-i") == 0) {     
        // Asks the user before every removal
        char* vari = strtok(stri, " ");
        if (strcmp(vari, "rm") == 0) {
            vari = strtok(NULL, " ");
            if (strcmp(vari, "-i") == 0) {
                vari = strtok(NULL, " ");
            }
        }
        while (vari != NULL) {
            printf("Remove file %s? Enter 'y' for yes\n", vari);
            char input;
            scanf("%c%*c", &input);  // Read a single character

            if (input == 'y') {
                remove(vari);
            }
            else {
                return 0;
            }
            vari = strtok(NULL, " ");
        }
    }
    else {
        // Default behavior: remove files without confirmation
        char* vari = strtok(stri, " ");
        if (strcmp(vari, "rm") == 0) {
            vari = strtok(NULL, " ");
        }
        while (vari != NULL) {
            int x = remove(vari);
            if (x != 0) {
                printf("File %s does not exist.\n", vari);
            }
            vari = strtok(NULL, " ");
        }
    }
    return 0;
}
