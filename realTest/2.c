#include<stdio.h>
#include<stdlib.h>


struct hashrow{
    /*
    Este no puede ser un short int porque este guarda las posiciones
    y las posiciones llegan hasta casi seis millones
    que es un número que no puede guardar un short int
    */
    int img;
};

int main(){
    /*
    Esto es para poder navegar en el archivo con bytes usando fseek, 
    ya que no funciona con puro texto. Esto para luego poder usar 
    la función hash y que el data.bin quede completo
    */
    FILE *freserve;
    freserve = fopen("hashtable.bin","w+b");
    if(freserve==NULL){
        printf("Ocurrió un error con el opening del file hashtable.bin");
    }

    struct hashrow hr1;
    hr1.img = 0;
    
    for(int i=0;i<1300;i++){
        fwrite(&hr1,sizeof(struct hashrow),1,freserve);
        //printf("Byte terminal: %ld\n",ftell(freserve));
    }
    
    printf("Terminó la reserva de memoria en hashtable.bin\ny el puntero terminó en la posición: %ld\n",ftell(freserve));
    fclose(freserve);
    return 0;
}