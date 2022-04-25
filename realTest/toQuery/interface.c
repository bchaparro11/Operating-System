#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include"../header.h"

int main(){
    FILE *fshare;
    fshare = fopen("share.bin","w+b");
    if(fshare==NULL){
        printf("Ocurrió un problema con el opening de share.bin!\n");
    }
    struct sharerow sr1={0,0,0};
    //fwrite(&sr1,sizeof(struct sharerow),1,fshare);

    /*
    int opcion;
    int bucle = 1;
   	int sourceid = 0;
   	int dstid = 0;
   	int hod = 0;
    */
    short int opcion;
    //short int bucle = 1;
	//float avt;
    //float mean;

	//Para medir tiempo
	//struct timeval ti, tf;
	//double tiempo;  

    
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
	  			//printf("NO ENTRÓ");
				break;
	  			//return(1);
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
	  			//bucle= 1;
				break;
	  			//return(1);
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
                /*
                while(hod < 0 || hod > 23){
	  			        printf("Ingrese un valor valido\n");
	  			        scanf("%d", &hod);
	  			}
                */		
	  			//bucle= 1;
	  			break;
	  			//return(1);
	     	case 4:
				system("clear");
                fwrite(&sr1,sizeof(struct sharerow),1,fshare);
                fclose(fshare);
                system("gcc find.c -o find");
                char *args[]={"./find",NULL};
                execv(args[0],args);
                /*
                gettimeofday(&ti, NULL);				// Instante inicial
				avt = buscar(sourceID, destID, hod);
				gettimeofday(&tf, NULL);   				// Instante final
				tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
				printf("La busqueda Ha tardado: %g milisegundos\n", tiempo);
				if(avt == 0.0){
					printf("Los datos para este viaje no son Validos");
				}else{
					printf("El tiempo de viaje medio para estos datos son: %.2f\n ", avt);
				}
                */
				//bucle= 1;
				//break;
				//return(1);
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
    //fclose(fshare);
    return 0;
}