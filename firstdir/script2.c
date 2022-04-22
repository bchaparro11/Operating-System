//Para hacer el fread y fwrite
#include <stdio.h>
#include <stdlib.h>
  
struct test{
    int a,b;
};

int main()
{
    int n;
    struct test test1;
    FILE *file;
    file = fopen("testb.bin","rb");
    if(file==NULL){
        printf("Hubo un error en el opening del file!");
        exit(0);
    }
    for(n=1;n<5;++n){
        fread(&test1,sizeof(struct test),1,file);
        printf("n1: %d\tn2: %d\n", test1.a, test1.b);
        //test1.a=n;
        //test1.b=n+1;
        //fwrite(&test1,sizeof(struct test),1,file);
    }

    return 0;
}