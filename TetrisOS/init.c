#include <string.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void show_help() {
    printf("Available commands:\n");
    printf("  vitetris  - play tetris\n");
    printf("  help      - show this message\n");
    printf("  reboot    - reboot the system\n");
    printf("  shutdown  - shutdown the system\n");
}

int main() {
    char input[100];
    
    show_help();

    while (1) {
        printf("> ");
        fflush(stdout);
        
        if (fgets(input, sizeof(input), stdin) == NULL) {
            continue;
        }
        
        // Strip trailing newline
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "shutdown") == 0) {
            sync();
            reboot(RB_POWER_OFF);
        } else if (strcmp(input, "reboot") == 0) {
            sync();
            reboot(RB_AUTOBOOT);
        } else if (strcmp(input, "vitetris") == 0) {
            if (fork() == 0) {
                char *args[] = {"/bin/vitetris", NULL};
                execv("/bin/vitetris", args);
            }
            wait(NULL);
        } else if (strcmp(input, "help") == 0) {
            show_help();
        } else if (strcmp(input, "") != 0) {
            printf("Command not found: %s\n", input);
        }
    }
    return 0;
}
