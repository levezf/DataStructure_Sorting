#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RANDOM 0
#define ASCENDING 1
#define DESCENDING 2

#define AMOUNT_ALGO 5

typedef char * String;

struct data_sorting{
	int amount_values;
	int order; 
	time_t duration;
	String name;
	unsigned int comparisons;
	unsigned int movement; 
} 
typedef struct data_sorting DataSorting;

struct vector{
	int *vec;
	int len;
	DataSorting ds;
};
typedef struct vector Vector;

String createString(String str);
void freeString(String str);
Vector createVetor(int lenVector, int lenVecInVector);
void freeVector(Vector *v);

void bubbleSort(Vector *vec);
void insertSort(Vector *vec);
void selectionSort(Vector *vec);
void shellSort(Vector *vec);
void quickSorte(Vector *vec);
void getSort(Vector *vec, int algo);

void generateValues(int *vetor, int len, int order);
time_t timeCalculator(time_t start, time_t final);
void printTables(Vector *vec);

int main(){
	
	
	
	int *vec_lens = (int *)malloc(sizeof(int)*9);
	vec_lens={10, 100, 500, 1000, 10000, 50000, 100000, 500000, 1000000}	
	
	
	for(int i=0; i<9; i++){
		for(int j=0; j<3; j++){
			//adicionar cabeçalho e pular linhas
			Vector *vector = createVector(AMOUNT_ALGO, vec_lens[i]);	
			generateValues(vector->vec, vec_lens[i], j)
	
			for(int k=0; k<AMOUNT_ALGO; k++){
								
				getSort(vector, k);
							
			}
			printTables(vector);
			freeVector(vector);
'		}
			
	}	
	return 0;
}

String createString(String str){
	String string = (String)malloc(sizeof(char)*strlen(str));
	strcpy(string, str);
	return string;
}
void freeString(String str){
	free(str);
}
Vector createVetor(int lenVector, int lenVecInVector){
	Vector *vec = (Vector *) malloc(sizeof(Vector)*n);
	vec->vec = (int *)malloc(sizeof(int)*m);
	vec->len = m;
	return vec;
}
void freeVector(Vector *v){
	for(int i=0; i<AMOUNT_ALGO;i++){
		free(v->vec);	
	}
	free(v);
}
void generateValues(int *vetor, int len, int order){
	switch(order){
		case ASCENDING:
			for(int i=0; i<len;i++){
				vetor[i]= i;		
			}
			break;
		case DESCENDING:
			for(int i=0, int j=len-1; i<len;i++, j--){
				vetor[i]= j;		
			}
			break;
		case RANDOM:
			srand(time(NULL));
			for(int i=0; i<len;i++){
				vetor[i]= (rand%1000001);		
			}
			break;
	}
}
time_t timeCalculator(time_t start, time_t final){
	return (final-start);
}

void getSort(Vector *vec, int algo){
	switch(algo){
		case 0:
			bubbleSort(vec, algo);
			break;
		case 1:
			insertSort(vec, algo);
			break;
		case 2:
			selectionSort(vec, algo);
			break;
          	case 3:
			shellSort(vec, algo);
			break;
		case 4:	
			quickSort(vec, algo);
			break;
	}
}
void printTables(Vector *vec){


"|        							     |      				          |     								     |     									 |   
"|           Algoritmo           |       Tempo (s)       |       Movimentacoes       |       Comparacoes       |   
"|        							     |      				          |     								     |     									 |   
"+--------------------------------------------------------------------------------------------------------------------------+"	
"|           Algoritmo           |       Tempo (s)       |       Movimentacoes       |       Comparacoes       | \n" 
 
}

void addHeader(Vector *vec){

	int aux;
	String str_partition = criaString("+--------------------------------------------------------------------------------------------------------------------------+\n");
	String str_order = criaString("+ 													   		ORDEM ");
	String str_elem = criaString("+ 															      %d Eementos");
	
	switch(vec->len){
	
		case <10:
			aux=1;
			break;
		case <100:
			aux=2;
			break;
		case <1000:
				aux=3;
				break;
			case <10000:
				aux=4;
				break;
			case <100000:
				aux=5;
				break;
			case <1000000:
				aux=6;
				break;
			default:
				aux=7;
				break;	
	}
	
	switch(vec->ds->order){
		case RANDOM:
			strconcat(str_order, "ALEATORIA");
			break;
		case ASCENDING:
			strconcat(str_order, "CRESCENTE");
			break;
		case DESCENDING:
			strconcat(str_order, "DECRESCENTE");
			break;

	}
	
	printf(str_partition);	
	printf(str_order);
	addWhiteSpaces(strlen(str_order), strlen(str_partition)-1);
	printf("+\n");
	printf(str_partition);

	printf("+ 															      %d Eementos", vec->len);
	for(int i=0; i<strlen("+ 															       Eementos")-aux)		

	printf("+\n");
	printf(str_partition);
	
}


void addWhiteSpaces(int lenCurrent, int lenFinal){
    for(int j=lenCurrent;j<lenFinal;j++){
        printf(" ");
    }
}

