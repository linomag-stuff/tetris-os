#include <string.h>
#include <sys/reboot.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    char input[100];
    
    while (1) {
        if (read(0, input, sizeof(input)) <= 0) {
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
        }
    }
    return 0;
}
