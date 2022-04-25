#include"stdio.h"
#include"../header.h"
#include"header1.h"


int main(){
    short int x,y;
    x=10;
    y=20;
    //printf("El valor de la suma es entonces: %hd\n", sumCrack(x,y));
    struct rowrow structure;
    structure.a=100;
    structure.b=200;
    sumCrack(x,y);
    sumCrack(structure.a,structure.b);
    //printf("El valor de la suma de los structs es entonces: %hd\n",sumCrack(structure.a,structure.b));
    return 0;
}