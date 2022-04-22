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


int fhash(int sourceid);
int fhash2(int sourceid);

void reversetravel(FILE *filedata, struct row *r1);

int main(){
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
    
    
    struct row r1;
    struct hashrow hr1;

    //Lo que primero se hace es sacar la útlima posición del data.bin
    fseek(filedata,0,SEEK_END);
    
    //int counter =1;
    while(1){
        if(ftell(filedata)==0){
            //printf("<<<PUNTERO READ: %ld\n",ftell(filedata));
            //No es necesario hacer este reversetravel porque el row 2 lo deja en 16 y no en 0
            //reversetravel(filedata,&r1);
            //printf("<<<PUNTERO READ: %ld\n",ftell(filedata));
            /*
            rewind(filehash);
            while(1){
                fread(&hr1,sizeof(struct hashrow),1,filehash);
                if(feof(filehash)){
                    printf("Terminó lectura de hashtable.bin!\n");
                    break;
                }
                if(hr1.img!=0){
                    printf("El valor2 de hr1.img es: %d\n",hr1.img);
                    printf("PUNTERO2 posición del filehash: %ld\n",ftell(filehash));
                }
            }
            */
            printf("Ya se llegó al principio de data.bin!\n");
            break;
        }
        //printf("<<<PUNTERO READ: %ld\n",ftell(filedata));
        reversetravel(filedata,&r1);
        
        //printf("EL VALOR DEL SOURCE ES: %d\n", r1.sourceid);
        //printf("EL VALOR DEL SOURCE MULTIPLICADO ES: %d\n", r1.sourceid*4);
        //El siguiente no funciona con el hash
        long int bytepos = (fhash2(r1.sourceid)-1)*sizeof(struct hashrow);
        //CREO QUE AQUÍ ESTÁ EL ERROR, AQUÍ DEBERÍA EXISTIR EL -1
        fseek(filehash,bytepos,SEEK_SET);
        //printf("<<<PUNTERO VALOR: %ld\n",ftell(filehash));
        fread(&hr1,sizeof(struct hashrow),1,filehash);
        //printf("<<<PUNTERO VALOR: %ld\n",ftell(filehash));
        fseek(filehash,-sizeof(struct hashrow),SEEK_CUR);
        //printf("<<<PUNTERO VALOR: %ld\n",ftell(filehash));
        //printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img);
        //printf("El valor que retorna el fhash es: %hd\n",fhash(r1.sourceid)*SIZE_STRUCT_ROW);
        //printf("El valor que retorna el fhash es: %hd\n",r1.sourceid);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        //fseek(filehash,hashindex,SEEK_SET);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        //fread(&hr1,sizeof(struct hashrow),1,filehash);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        //printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        //printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        //r1.hod,r1.mean);

        if (hr1.img==0){
            //printf("La posición del row es: %d\n",r1.mpos);
            //Para asegurar que siga siendo 0
            r1.npos=0;
            //puts("ERA CERO!!!!");
        }else{
            //Si llega acá es porque hay una colisión entonces
            r1.npos=hr1.img;
            fwrite(&r1,sizeof(struct row),1,filedata);
            fseek(filedata,-sizeof(struct row),SEEK_CUR);
            //puts("NO ERA CERO!!!!");
        }
        /*
        Si llega la primera vez (no hay colisión pq es la 1ra vez) se debe escribir la posición,
        Si llega la segunda vez (hay colisión) también se debe escribir la nueva posición
        Por esa razón se escribe la siguiente ínea de código
        */
        //printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img);
        //printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        //r1.hod,r1.mean);
        hr1.img = r1.mpos;
        //printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img);
        //printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        //r1.hod,r1.mean);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        fwrite(&hr1,sizeof(struct hashrow),1,filehash);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        //printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img);
        //printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1.mpos,r1.npos,r1.sourceid,r1.dstid,
        //r1.hod,r1.mean);
        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        fseek(filehash,-sizeof(struct hashrow),SEEK_CUR);
        //printf("El valor del hr1.img es: %d\n",hr1.img);
        //fread(&hr1,sizeof(struct hashrow),1,filehash);
        //printf("El valor1 del hr1.img es: %d\n",hr1.img);
        //printf("PUNTERO1 posición del filehash: %ld\n",ftell(filehash));
        //fseek(filehash,-sizeof(struct hashrow),SEEK_CUR);
        // 4 9 10

        //printf("<<<PUNTERO filehash: %ld\n",ftell(filehash));
        


        //printf("<<<PUNTERO READ: %ld\n",ftell(filedata));
        //printf("El valor del counter es: %d\n",counter);
        //counter++;
        //printf(">>>>>>>>>>\n");
    }


    /*
    rewind(filehash);
    while(1){
        fread(&hr1,sizeof(struct hashrow),1,filehash);
        if(feof(filehash)){
            printf("Terminó lectura de hashtable.bin!\n");
            break;
        }
        if(hr1.img!=0){
            printf("El valor de hr1.img es: %d\n",hr1.img);
        }
    }
    */

    


    fclose(filehash);
    fclose(filedata);
    
    

    /*
    for(int i=0;i<M;i++){
        fread(&hr1,sizeof(struct hashrow),1,filehash);
        printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img); 
    }
    fseek(filehash,1101*4,SEEK_SET);
    printf("<<<PUNTERO VALOR: %ld\n",ftell(filehash));
    fread(&hr1,sizeof(struct hashrow),1,filehash);
    printf("<<<PUNTERO VALOR: %ld\n",ftell(filehash));
    printf("El valor que está en esa posición del hashtable es: %d\n",hr1.img);
    
    printf("<<<PUNTERO FINAL READ: %ld\n",ftell(filedata));
    */

    


    //Después se debe comprobar si en el hashtable.bin está o no la memoria
    //int x = 1160;
    //int position = fhash(x);
    //printf("%d\n",position);

    return 0;
}

int fhash(int sourceid){
    /*
    //Functions
    #define a 98
    #define b 12
    #define p 1373
    #define M 1300
    */
    return ((((98*sourceid)+12)%1373)%1300);
}

int fhash2(int sourceid){
  // Sin coliciones para menos de 1300 datos
  return ((((3*sourceid))%9803)%1300);
}

void reversetravel(FILE *filedata, struct row *r1){
    fseek(filedata,-sizeof(struct row),SEEK_CUR);
    //printf("<<<PUNTERO filehash: %ld\n",ftell(filedata));
    fread(r1,sizeof(struct row),1,filedata);
    //printf("<<<PUNTERO filehash: %ld\n",ftell(filedata));
    //printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1->mpos,r1->npos,r1->sourceid,r1->dstid,
    //r1->hod,r1->mean);
    //printf("El valor que retorna el fhash es: %hd\n",r1->sourceid);
    fseek(filedata,-sizeof(struct row),SEEK_CUR);
}


/*
void reversetravel(FILE *filedata, struct row *r1){
    fseek(filedata,-16,SEEK_CUR);
    fread(r1,sizeof(struct row),1,filedata);
    printf("%d\t  %d\t %d\t %d\t %d\t %0.2f\t\n",r1->mpos,r1->npos,r1->sourceid,r1->dstid,
    r1->hod,r1->mean);
    printf("El valor que retorna el fhash es: %hd\n",r1->sourceid);
    fseek(filedata,-16,SEEK_CUR);
}
*/
