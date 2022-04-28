#include<stdio.h>
#include<stdlib.h>
#include"../header.h"

int main(){
    /*
    Este script es para la consulta
    */

    /*Puntero FILE para leer de share.bin que el archivo que sirve para comunicar
    interface.c y este código llamado find.c*/

    FILE *fshare;
    fshare = fopen("share.bin","r+b");
    if(fshare==NULL){
        printf("Ocurrió un problema con el opening de share.bin!\n");
    }
    struct sharerow sr1;
    fread(&sr1,sizeof(struct sharerow),1,fshare);
    fclose(fshare);
    
    //Memoria dinámica en este lugar, sólo aquí
    int *np=malloc(sizeof(int));
 
    //Si no se escriben datos en interface.bin no es necesario seguir con el código más adelante
    if(sr1.sourceid == 0 || sr1.dstid == 0){
        printf("N/A\n");
        exit(0);
    }

    struct row r1;
    struct hashrow hr1;

    FILE *filehash;
    filehash = fopen("hashtable.bin","r+b");
    if(filehash==NULL){
        printf("Ocurrió un problema con el opening del FILE hashtable.bin");
        exit(0);
    }

    FILE *filedata;
    filedata = fopen("data.bin","r+b");
    if(filedata==NULL){
        printf("Ocurrió un problema con el opening del FILE data.bin");
        exit(0);
    }
    

    fseek(filehash,(sr1.sourceid-1)*sizeof(struct hashrow),SEEK_SET);
    fread(&hr1,sizeof(struct hashrow),1,filehash);
    fclose(filehash);

    //El valor para buscar ahora en data.bin
    *np = hr1.img;
    
    short int forWait;

    while(*np!=0){
        fseek(filedata,(*np-1)*sizeof(struct row),SEEK_SET);
        fread(&r1,sizeof(struct row),1,filedata);
        if(sr1.sourceid==r1.sourceid && sr1.dstid==r1.dstid && sr1.hod==r1.hod){
            printf("\nTiempo de viaje medio: %0.2f\n\n",r1.mean);
            printf("mpos: %d \nnpos: %d\n",r1.mpos,r1.npos);
            printf("sourceid: %d \ndstid: %d \nhod: %d\n",r1.sourceid,r1.dstid,r1.hod);
            fclose(filedata);
            free(np);
            //Para la prueba de tiempo no debe estar activo las siguientes dos líneas
            //printf("\nEsperando el ingreso de cualquier número para terminar el proceso: ");
            //scanf("%hd",&forWait);
            exit(0);
        }
        *np=r1.npos;
    }
    printf("NA\n");
    fclose(filedata);
    free(np);
    //Para la prueba de tiempo no debe estar activo las siguientes dos líneas
    //printf("\nEsperando el ingreso de cualquier número para terminar el proceso: ");
    //scanf("%hd",&forWait);
    return 0;
}