#include<stdio.h>
#include<stdlib.h>

struct st{
    int a,b;
};

int main(){
    FILE *file;
    file = fopen("csv.csv","r");
    if(file==NULL){
        printf("Hubo un error en el opening del FILE!");
        exit(1);
    }
    FILE *fileout;
    fileout = fopen("out.bin","wb");
    if(file==NULL){
        printf("Hubo un error en el opening del FILEOUT!");
        exit(1);
    }
    int a,b;
    struct st st1;
    while(1){
        //Para hacerle un salto de línea
        //fscanf(file,"%*s");
        printf("PUNTERO CSV: %ld\n",ftell(file));
        int c = fscanf(file,"%d,%d,%*s",&a,&b);
        printf("PUNTERO CSV: %ld\n",ftell(file));
        if(c==EOF){
            printf("<<<<<<<<<<<<<<<<<<<SE ACABÓ LECTURA Y ESCRITURA>>>>>>>>>>>>>>>>>>>>\n");
            break;
        }
        st1.a=a;
        st1.b=b;
        printf("CUANDO ESTÁ ESCRIBIENDO: %d %d\n",a,b);
        printf("PUNTERO WRITE: %ld\n",ftell(fileout));
        fwrite(&st1,sizeof(struct st),1,fileout);
        printf("PUNTERO WRITE: %ld\n",ftell(fileout));
        printf("<<<<<<<<<<<<CICLO Y LA SUMA: %d\n",a+b);
        //printf("LA CANTIDAD DE BYTES DEL STRUCT ES %ld\n",sizeof(struct st));
    }
    
    fclose(file);
    fclose(fileout);

    return 0;
}