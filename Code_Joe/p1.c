#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int mostrar_menu() {
    int opcion;
    int bucle = 1;
   	int sourceID = 0;
   	int destID = 0;
   	int hod = 0;
    
    
    while(bucle!=0) {
    	system("clear");
 		printf("\nBienbenido\n\n"
 			"1.  Ingresar origen\n"
 			"2.  Ingresar destino\n"
 			"3.  Ingresar hora\n"
 			"4.  Buscar tiempo de viaje medio\n"
 			"5.  Salir\n"
 			"*********************************************\n\t¿Opción?: ");
	 			
	 	scanf("%d", &opcion);

	 	switch(opcion) {
	 		case 1:
	  			system("clear");
	  			printf("\nIngrese ID del origen: ");
	  			scanf("%d", &sourceID);
	  			bucle=-1;
	  			break;
	  			return(1);

	     	case 2:
	 			system("clear");
	  			printf("\nIngrese ID del destino: ");
	  			scanf("%d", &destID);
	  			bucle=-1;
	  			break;
	  			return(1);
	  			
	     	case 3:
	  			system("clear");
	  			printf("\nIngrese hora del día: ");
	  			scanf("%d", &hod);
	  			while(hod < 0 || hod > 23){
	  			        printf("Ingrese un valor valido\n");
	  			        scanf("%d", &hod);
	  			}
	  			bucle=-1;
	  			break;
	  			return(1);
	  			
	     	case 4:
				system("clear");
				printf("\nOpción 4.");
				bucle=-1;
				break;
				return(1);
				
	     	case 5:
				system("clear");
				printf("\nHasta Luego!!!\n\n");
				bucle=0;
				break;
				return(1);
				
	     	default:
				system("clear");
				printf("\n¡Esa opción no es válida!\n");

	 	}
    }
}

int main()
{
	int(*m_menu)(int);
	m_menu = &mostrar_menu;
	int opcion = 1;
	(*m_menu)(opcion);
	return 0;
}
