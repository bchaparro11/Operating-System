#include<stdio.h>
#include<stdlib.h>

struct st{
    int a,b;
};

int main(){
    FILE *fileout;
    fileout = fopen("out.bin","r+b");
    if(fileout==NULL){
        printf("Hubo un error en el opening del FILEOUT!");
        exit(1);
    }
    fseek(fileout,8,SEEK_SET);
    struct st st1={8,9};
    //while(1){
        printf("PUNTERO READ: %ld\n",ftell(fileout));
        fwrite(&st1,sizeof(struct st),1,fileout);
        //if(feof(fileout)){
        //    printf("Se llegó al final!\n");
        //    break;
        //}
        //printf("n1: %d\tn2: %d\n", st1.a, st1.b);
        printf("PUNTERO READ: %ld\n",ftell(fileout));
    //}
    fseek(fileout,-8,SEEK_END);
    printf("<<<PUNTERO READ: %ld\n",ftell(fileout));
    fread(&st1,sizeof(struct st),1,fileout);
    printf("PUNTERO READ: %ld\n",ftell(fileout));
    printf("n1: %d\tn2: %d\n", st1.a, st1.b);
    fread(&st1,sizeof(struct st),1,fileout);
    printf("PUNTERO READ: %ld\n",ftell(fileout));
    printf("n1: %d\tn2: %d\n", st1.a, st1.b);
    /*
    for(int i =1;i<3;i++){
        printf("PUNTERO READ: %ld\n",ftell(fileout));
        fread(&st1,sizeof(struct st),1,fileout);
        printf("n1: %d\tn2: %d\n", st1.a, st1.b);
        printf("PUNTERO READ: %ld\n",ftell(fileout));
    }
    */

    fclose(fileout);
    return 0;
}