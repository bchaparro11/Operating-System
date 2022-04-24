#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
    //char *binaryPath = "gcc";
    //char *args[] = {"gcc", "test2.c","-o","test2", NULL};
    //execv(binaryPath, args);
    //execlp("clear","clear",NULL);
    //execlp("gcc","gcc","test2.c","-o","test2",NULL);
    execlp("./test2","./test2",NULL);
    printf("Aquí llegó!!\n");
    //char *args2[] = {"./test2", NULL};
    //execv(args2[0], args2);
    return 0;
}