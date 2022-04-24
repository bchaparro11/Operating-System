#include<stdio.h>
#include<stdlib.h>
#define a 98
#define b 12
#define p 1373
#define M 1300

int fhash(int sourceid){
    return ((((a*sourceid)+b)%p)%M);
}

int main(){
    printf("%d\n",fhash(478));
    return 0;
}