#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    if(argc < 1){
        printf("usage: sleep numberOfTicks\n");
        exit(1);
    }
    int numOfTics = atoi(argv[1]);
    sleep(numOfTics);
    exit(0);
}