#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>


int fhash2(int sourceid){
  // Sin coliciones para menos de 1300 datos
  return ((((3*sourceid))%9803)%1300);
}

struct row{
    /*
    mpost = My position
    npost = Next position
    */
    int mpos,npos,sourceid,dstid,hod;
    float mean;
};

struct hashrow{
    int img;
};

float buscar(int s, int d, int h){
    int mp,np;
    float m;

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

    fseek(filehash,(fhash2(s)-1)*4,SEEK_SET);
    fread(&hr1,sizeof(struct hashrow),1,filehash);
    fclose(filehash);

    //El valor para buscar ahora en data.bin
    np = hr1.img;

    while(np!=0){
        fseek(filedata,(np-1)*24,SEEK_SET);
        fread(&r1,sizeof(struct row),1,filedata);
        //printf("El valor encontrado en el data.bin para npos es: %d\n",r1.npos);
        if(s==r1.sourceid && d==r1.dstid && h==r1.hod){
            m = r1.mean;
        }
        np=r1.npos;
    }

    return m;
}


int mostrar_menu() {
    int opcion;
    int bucle = 1;
   	int sourceID = 0;
   	int destID = 0;
   	int hod = 0;
	float avt;  
	//Para medir tiempo
	struct timeval ti, tf;
	double tiempo;  
    
    while(bucle!=0) {
    	//system("clear");
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