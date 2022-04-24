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

struct hashrow{
    int img;
};


short int fhash2(short int sourceid);

void reversetravel(FILE *filedata, struct row *r1);

int main(){
    FILE *filehash;
    filehash = fopen("../toQuery/hashtable.bin","r+b");
    if(filehash==NULL){
        printf("Ocurrió un problema con el opening del FILE hashtable.bin");
        exit(0);
    }

    FILE *filedata;
    filedata = fopen("../toQuery/data.bin","r+b");
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
    
            printf("\nYa se hizo la pseudo linked list en data.bin!\n");
            break;
        }
        
        reversetravel(filedata,&r1);

        //El valor de la mitad es para hallar la posición correcta en hashtable.bin
        fseek(filehash,(fhash2(r1.sourceid)-1)*sizeof(struct hashrow),SEEK_SET);

        fread(&hr1,sizeof(struct hashrow),1,filehash);

        fseek(filehash,-sizeof(struct hashrow),SEEK_CUR);


        if(hr1.img!=0){
            //Si llega acá es porque hay una colisión entonces
            r1.npos=hr1.img;
            fwrite(&r1,sizeof(struct row),1,filedata);
            fseek(filedata,-sizeof(struct row),SEEK_CUR);

        }
        /*
        Si llega la primera vez (no hay colisión pq es la 1ra vez) se debe escribir la posición,
        Si llega la segunda vez (hay colisión) también se debe escribir la nueva posición
        Por esa razón se escribe la siguiente ínea de código
        */

        hr1.img = r1.mpos;

        fwrite(&hr1,sizeof(struct hashrow),1,filehash);

        fseek(filehash,-sizeof(struct hashrow),SEEK_CUR);

    }

    fclose(filehash);
    fclose(filedata);

    return 0;
}


short int fhash2(short int sourceid){
  /*
  Sin coliciones para menos de 1300 datos
    Función hecha por Sebastián
  */
  return ((((3*sourceid))%9803)%1300);
}

void reversetravel(FILE *filedata, struct row *r1){
    fseek(filedata,-sizeof(struct row),SEEK_CUR);

    fread(r1,sizeof(struct row),1,filedata);

    fseek(filedata,-sizeof(struct row),SEEK_CUR);
}