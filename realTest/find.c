#include<stdio.h>
#include<stdlib.h>

int fhash2(int sourceid);

struct row{
    /*
    mpost = My position
    npost = Next position
    */
    //We must be careful with the padding 
    //https://www.geeksforgeeks.org/is-sizeof-for-a-struct-equal-to-the-sum-of-sizeof-of-each-member/
    int mpos,npos,sourceid,dstid,hod;
    float mean;
};

struct row2{
    /*
    mpost = My position
    npost = Next position
    */
    char x;
    char y;
    char z;
    short int a;
    //int mpos,npos,sourceid,dstid,hod;
    
    //float mean;
};

struct hashrow{
    int img;
};

int main(){
    //printf("El tamaño del struct row2 es: %ld\n",sizeof(struct row2));
    int mp,np;
    int s,d,h;

    //478,627,0,1145.57
    //912,667,15,1514.33
    //252,435,20,1403.8
    //907,1072,14,1801.23
    s = 478;
    d =627;
    h= 0;

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
    
    /*
    Hay que mirar aquí por qué no sirve con (s-1)*4 porque así debería ser!
    Quizá, por esto es que uno funciona el hash
    */
    
    fseek(filehash,(fhash2(s)-1)*sizeof(struct hashrow),SEEK_SET);
    fread(&hr1,sizeof(struct hashrow),1,filehash);
    fclose(filehash);

    //El valor para buscar ahora en data.bin
    np = hr1.img;

    printf("El valor encontrado en el hashtable.bin es: %d\n",np);

    while(np!=0){
        fseek(filedata,(np-1)*sizeof(struct row),SEEK_SET);
        fread(&r1,sizeof(struct row),1,filedata);
        if(s==r1.sourceid && d==r1.dstid && h==r1.hod){
            printf("\nTiempo de viaje medio: %0.2f\n",r1.mean);
            printf("mpos: %d \nnpos: %d\n",r1.mpos,r1.npos);
            printf("sourceid: %d \ndstid: %d \nhod: %d\n",r1.sourceid,r1.dstid,r1.hod);
            fclose(filedata);
            exit(0);
        }
        np=r1.npos;
    }
    printf("NA\n");
    fclose(filedata);

    return 0;
}

int fhash2(int sourceid){
  // Sin coliciones para menos de 1300 datos
  return ((((3*sourceid))%9803)%1300);
}