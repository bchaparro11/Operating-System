/*
Desde un header se puede estar llamando otro header y después si se ejecuta en el .
ya sería dos veces. Creo que estaría mal en esa parte
*/
void sumCrack(short int a, short int b){
    short int var = fhash2(a+b);
    printf("El valor de la suma es entonces: %hd\n",var);
}


struct rowrow{
    int a,b;
};


