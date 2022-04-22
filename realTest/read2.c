#include<stdio.h>
#include<stdlib.h>
struct row{
    /*
    mpost = My position
    npost = Next position
    */
    int mpos,npos,sourceid,dstid,hod;
    float mean;
};

struct hashrow{
    int img;
};

int main(){

    FILE *fsave;
    fsave=fopen("data.bin","r+b");
    if(fsave==NULL){
        printf("Hubo un error en el opening");
        exit(0);
    }
    struct row r1;
    printf("A continuación empieza la lectura:\n");

    //Vuelve el puntero fsave a la primera posición del file data.bin
    //rewind(fsave);
    while(1){
        fread(&r1,sizeof(struct row),1,fsave);
        if(feof(fsave)){
            printf("Terminó lectura de data.bin!\n");
            break;
        }
        
        printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t \t%ld \n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        r1.hod,r1.mean,ftell(fsave));
    }
    //Siguiente línea es para comprobar cuántos bytes tiene cada struct row
    printf("El peso del struct es igual a: %ld\n",sizeof(struct row));
    printf("El puntero terminó en la posición: %ld\n",ftell(fsave));
    return 0;
}