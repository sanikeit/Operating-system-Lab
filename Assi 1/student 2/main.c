#include <unistd.h>
#include <stdio.h>
#include <string.h>

void displayOptions() {
    printf("\nEnter an option from below: \n");
    printf("1.) Web Browser\n");
    printf("2.) List file directory contents\n");
    printf("3.) Calculator\n");
    printf("4.) LibreOffice\n");
    printf("5.) Exit\n");
}

void run(const char* input) {
    char prog[100] = "/usr/bin/";
    strcat(prog, input);

    pid_t pid;
    int status;

    if ((pid = fork()) == 0) {
        // child
        char* args[] = {prog, NULL};
        execvp(args[0], args);
    }
}

int main(int argc, char* argv[]) {
    char c;
    int choice, dummy;
    do {
        displayOptions();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                run("brave-browser");
                break;
            case 2:
                run("ls");
                break;
            case 3:
                run("gnome-calculator");
                break;
            case 4:
                run("libreoffice");
                break;
            default:
                return 0;
        }
        printf("Continue (Y/N)?\n\n");
        scanf("%d", &dummy);
        scanf("%c", &c);
    } while (c == 'y' || c == 'Y');
}
