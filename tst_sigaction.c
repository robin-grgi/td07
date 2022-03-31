#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void on_sig(int code){
    static int cptSIGINT = 0;
    if(code == SIGINT){
        printf("Signal capturé : SIGINT\n");
        cptSIGINT++;
        if(cptSIGINT == 5){
            printf("5 SIGINT captured, exiting program\n");
        }
    }
    else{
        printf("Signal capturé : SIGSEGV\n");
    }

}


int main(){
    struct sigaction act;
    sigset_t msk_int, msk_segv;

    sigemptyset(&msk_int);
    sigaddset(&msk_int, SIGINT);
    sigemptyset(&msk_segv);
    sigaddset(&msk_segv, SIGSEGV);

    act.sa_handler = on_sig;

    act.sa_mask = msk_int;
    sigaction(SIGINT, &act, NULL);
    act.sa_mask = msk_segv;
    sigaction(SIGSEGV, &act, NULL);

    /*while (1){}*/
    unsigned int remainingTime = sleep(5);
    printf("Temps restant : %u\n", remainingTime);
    return 0;
}


