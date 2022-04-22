#include <stdio.h>
#include <stdlib.h>
  
int main()
{
    FILE *file;
    file = fopen("in.csv","r");
    int a,b,c;  
    while(1){
        //Para hacerle un salto de línea
        fscanf(file,"%*s");
        int c = fscanf(file,"%d,%d,%*s",&a,&b);
        if(c==EOF){
            printf("entró");
            break;
        }
        printf("%d\n",a+b);
    }
    
    //fscanf(file,"%d,%d,%d",&a,&b,&c);
    //printf("La suma es: %d",a+b+c);
    return 0;
}