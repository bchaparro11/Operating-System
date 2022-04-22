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
        int end = fscanf(ftake,"%d,%d,%d,%f,%*s",&r1.sourceid,&r1.dstid,&r1.hod,&r1.mean);

        r1.mpos=i;
        if(end==EOF){
            printf("Terminó lectura del .csv!\n");
            break;
        }
        //La siguiente línea es para comprobar si se están obteniendo los datos adecuados
        //printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        //r1.hod,r1.mean);

        fwrite(&r1,sizeof(struct row),1,fsave);
    }
    fclose(ftake);

    /*
    El siguiente código es para comprobar que se guardó bien todo en el data.bin
    Entonces el siguiente código lee todo desde el data.bin

    //printf("A continuación empieza la lectura: %d\n");

    //Vuelve el puntero fsave a la primera posición del file data.bin
    rewind(fsave);
    while(1){
        fread(&r1,sizeof(struct row),1,fsave);
        if(feof(fsave)){
            printf("Terminó lectura de data.bin!\n");
            break;
        }
        printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        r1.hod,r1.mean);
    }
    //Siguiente línea es para comprobar cuántos bytes tiene cada struct row
    printf("El peso del struct es igual a: %d\n",sizeof(struct row));
    printf("El puntero terminó en la posición: %ld\n",ftell(fsave));
    */
    fclose(fsave);

    return 0;
}