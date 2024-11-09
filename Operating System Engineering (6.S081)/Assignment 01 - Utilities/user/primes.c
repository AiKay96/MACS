#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void recursion(int oldp[]){
    close(oldp[1]);
    char buf[1];
    int n = read(oldp[0], buf, sizeof(buf));

    if(n <= 0)
        exit(0);
    
    int prime = buf[0] - 'A';
    printf("prime %d\n", prime);
    int p[2];
    pipe(p);

    if(fork() == 0){
        close(oldp[0]);
        recursion(p);
        exit(0);
    } else {
        close(p[0]);
        while(1){
            n = read(oldp[0], buf, sizeof(buf));
            if(n <= 0){
                close(p[1]);
                close(oldp[0]);
                break;
            } 
            int curr = buf[0] - 'A';
            if(curr % prime != 0)
                write(p[1], buf, 1);
        }
        wait(0);
    }
}

int main(int argc, char *argv[]){
    int p[2];
    pipe(p);
    if(fork() == 0){
        recursion(p);
        exit(0);
    }else{
        close(p[0]);
        for(int i = 2; i <= 35; i++){
            char curr = 'A' + i;
            write(p[1], &curr, 1);
        }
        close(p[1]);
        wait(0);
    }
    exit(0);
}