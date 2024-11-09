#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    char *args[argc + 1];
    for(int i = 1; i < argc; i++)
        args[i-1] = argv[i];
    char buf;
    char ln[1024];
    int index = 0;
    while(read(0, &buf, 1) > 0){
        ln[index++] = buf;
        if(ln[index-1] == '\n'){
            ln[index-1] = 0;
            args[argc - 1] = ln;
            args[argc] = "\n";
            if(fork() == 0)
                exec(args[0], args);
            else
                wait(0);
            index = 0;
        }
    }
    exit(0);
}