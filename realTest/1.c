#include<stdio.h>
#include<stdlib.h>

struct row{
    /*
    mpost = My position
    npost = Next position
    */
    int mpos,npos;
    short int sourceid,dstid,hod;
    float mean;
};

int main(){
    //printf("El tamaño es: %ld\n: ",sizeof(struct row));
    //El siguiente puntero es para sacar todos los datos del .csv
    FILE *ftake;
    ftake = fopen("csvfinal.csv","r");
    if(ftake==NULL){
        printf("Hubo un error con el opening del csv.csv\n");
        exit(0);
    }

    /*
    El siguiente puntero se va a utilizar para guardar cada row sacado
    del .csv en un archivo binario llamado data.bin. Los datos de cada
    row se almacenan en un struct y se guardan de manera binaria
    */
    FILE *fsave;
    fsave = fopen("data.bin","w+b");
    if(fsave==NULL){
        printf("Hubo un error con el opening del all.bin\n");
        exit(0);
    }
    
    //Declarando el struct e inicializando el primer atributo
    struct row r1;
    r1.npos = 0;
    for(int i=1;1;i++){
        //El %hd es para que reconozca el short int        
        int end = fscanf(ftake,"%hd,%hd,%hd,%f,%*s",&r1.sourceid,&r1.dstid,&r1.hod,&r1.mean);

        r1.mpos=i;
        if(end==EOF){
            printf("Terminó lectura del .csv!\n");
            break;
        }

        fwrite(&r1,sizeof(struct row),1,fsave);
    }
    fclose(ftake);
    fclose(fsave);

    return 0;
}