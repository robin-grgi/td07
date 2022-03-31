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
            exit(0);
        }
    }
    else{
        printf("Signal capturé : SIGSEGV\n");
    }
}

int main(){
    signal(SIGINT, on_sig);
    signal(SIGSEGV, on_sig);
    
    /* while (1){} */
    unsigned int remainingTime = sleep(5);
    printf("Temps restant : %u\n", remainingTime);
    return 0;
}
