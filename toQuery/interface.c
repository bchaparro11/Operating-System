#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../header.h"

int main(){
	/*
	Script para la interface
	*/

    FILE *fshare;
    fshare = fopen("share.bin","w+b");
    if(fshare==NULL){
        printf("Ocurrió un problema con el opening de share.bin!\n");
    }
    struct sharerow sr1={0,0,0};

    short int opcion;

    
    while(1) {
        system("clear");
 		printf("\nBienvenido\n\n"
 			"1.  Ingresar origen\n"
 			"2.  Ingresar destino\n"
 			"3.  Ingresar hora\n"
 			"4.  Buscar tiempo de viaje medio\n"
 			"5.  Salir\n"
 			"*********************************************\n¿Elige la opción?: ");
	 			
	 	scanf("%hd", &opcion);

	 	switch(opcion) {
	 		case 1:
	  			system("clear");
	  			printf("\nIngrese ID del origen: ");
	  			scanf("%hd", &sr1.sourceid);
                if (sr1.sourceid<0 || sr1.sourceid>1160){
					system("clear");
                    printf("\nValor incorrecto, se espera un número entre 1 y 1160\n");
                    sleep(3);
                    break;    
                }
				break;

	     	case 2:
	 			system("clear");
	  			printf("\nIngrese ID del destino: ");
	  			scanf("%hd", &sr1.dstid);
                if (sr1.dstid<0 || sr1.dstid>1160){
                    system("clear");
                    printf("\nValor incorrecto, se espera un número entre 1 y 1160\n");
                    sleep(3);  
                    break;      
                }
				break;

	     	case 3:
	  			system("clear");
	  			printf("\nIngrese hora del día: ");
	  			scanf("%hd",&sr1.hod);
                if (sr1.hod<0 || sr1.hod>23){
                    system("clear");
                    printf("\nValor incorrecto, se espera un número entre 0 y 23\n");
                    sleep(3);
                    break;        
                }

	  			break;
	     	case 4:
				system("clear");
                fwrite(&sr1,sizeof(struct sharerow),1,fshare);
                fclose(fshare);
                system("gcc find.c -o find");
                char *args[]={"./find",NULL};
                execv(args[0],args); //No aparentado

	     	case 5:
				system("clear");
				fclose(fshare);
				printf("\nHasta Luego!\n\n");
				exit(0);
				//return(1);	
	     	default:
				system("clear");
                printf("\n¡Esa opción no es válida!\n");
                sleep(1);
                break;
	 	}
    }
    return 0;
}