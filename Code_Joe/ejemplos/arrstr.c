#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int ido;
	int idd;
	int hod;
	float avt;
		
}viajes;

viajes *vj;


void vaciar(char temp[]);
void copiarido(char temp[], int i);
void copiaridd(char temp[], int i);
void copiarhod(char temp[], int i);


int main()
{
	unsigned int i, j;
	unsigned int cont = 0;
	char temp[30];
	char aux;
	
	FILE* f = fopen("bta_final.csv", "r");
	FILE* salida = fopen("reg.txt", "w");
	if(f == NULL){
		printf("No se ha podido abrir el archivo \n");
		exit(1);
	}
	
	while(!feof(f)){
		fgets(temp, 30, f);
		cont++;
	}

	rewind(f);
	
	vj = (viajes*)malloc(cont*sizeof(viajes));  //asignacion de memoria
	
	
	if(vj == NULL){
		printf("No se ha podido reservar la memoria");
		exit(1);
	}
	
	for(i = 0; !feof(f); i++)
	{
		vaciar(temp);
		
		aux = '0';
		
		for(j = 0; aux != ','; j++){
			aux = fgetc(f);
			
			if(aux != ','){
				temp[j] = aux;
			}
		}
		
		copiarido(temp, i);
		
		
		vaciar(temp);
		
		aux = '0';
		
		for(j = 0; aux != ','; j++){
			aux = fgetc(f);
			
			if(aux != ','){
				temp[j] = aux;
			}
		}
		
		copiaridd(temp, i);
		
		vaciar(temp);
		
		aux = '0';
		
		for(j = 0; aux != ','; j++){
			aux = fgetc(f);
			
			if(aux != ','){
				temp[j] = aux;
			}
		}
		
		copiarhod(temp, i);
		
		fgets(temp, 8,f);
		vj[i].avt = atof(temp);
		
	
		//printf("ID origen: %d ID Destino: %d  Hora: %d  AVT: %.2f \n", 				vj[i].ido,vj[i].idd, vj[i].hod, vj[i].avt);
		
		fprintf(salida, "%d, %d, %d, %.2f\n", vj[i].ido,vj[i].idd, vj[i].hod, 			vj[i].avt);
		
		
	}
	
	fclose(f);
	fclose(salida);
	return 0;
}

void vaciar(char temp[]){
	int i;
	for(i = 0; i < 30; i++){
		temp[i] = '\0';
	}
}


void copiarido(char temp[], int i){
	vj[i].ido = atoi(temp);
}


void copiaridd(char temp[], int i){
	vj[i].idd = atoi(temp);
}

void copiarhod(char temp[], int i){
	vj[i].hod = atoi(temp);
}


