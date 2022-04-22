#include <stdio.h>
#include <stdlib.h>

int main()
{

}

int hash(int number){
  // Sin coliciones para menos de 1300 datos
  return ((((3*number))%9803)%1300);
}
