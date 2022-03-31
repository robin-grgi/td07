#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void on_sig(int code){
    if(code == SIGUSR1){
        printf("Youngest process captured SIGUSR1\n");
    }
    else if(code == SIGUSR2){
        printf("Eldest process captured SIGUSR2\n");
    }
}

int main() {
    int eldestPID, youngestPID;
    
    struct sigaction sigactEldest, sigactYoungest;
    sigset_t sigmaskEldest, sigmaskYoungest;

    sigemptyset(&sigmaskEldest);
    sigaddset(&sigmaskEldest, SIGUSR2);
    sigemptyset(&sigmaskYoungest);
    sigaddset(&sigmaskYoungest, SIGUSR1);

    sigactEldest.sa_handler = on_sig;
    sigactYoungest.sa_handler = on_sig;

    sigactEldest.sa_mask = sigmaskEldest;
    sigaction(SIGUSR2, &sigactEldest, NULL);
    sigactYoungest.sa_mask = sigmaskYoungest;
    sigaction(SIGUSR1, &sigactYoungest, NULL);

    switch (eldestPID = fork()) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);
        case 0:
            switch (youngestPID = fork()){
                case -1:
                    perror("fork");
                    exit(EXIT_FAILURE);
                case 0:
                    printf("youngest child\n");
                    sleep(5);
                    kill(eldestPID, SIGUSR2);
                    exit(0);
                default:
                    printf("eldest child\n");
                    sleep(5);
                    exit(0);
                    break;
            }
            break;
        default:
            printf("parent\n");
            sleep(5);
            kill(youngestPID, SIGUSR1);
            wait(NULL);
            wait(NULL);
            printf("children done, exit program\n");
            break;
    }
    return 0;
}
