#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define RANDOM 0
#define ASCENDING 1
#define DESCENDING 2

#define AMOUNT_ALGO 5

typedef char* String;

struct data_sorting{
    int order;
    time_t duration;
    String name;
    unsigned int comparisons;
    unsigned int movement;
};
typedef struct data_sorting DataSorting;

struct vector{
    int *vec;
    int len;
    DataSorting *ds;
};
typedef struct vector Vector;

String createString(int n);
void freeString(String str);
void createVector(Vector *vec, int lenVector, int lenVecInVector);
void freeVector(Vector *v);

void bubbleSort(Vector *vec);
void insertSort(Vector *vec);
void selectionSort(Vector *vec);
void shellSort(Vector *vec);
void quickSort(Vector *vec, int begin, int end);
//heapsort e mais

void move(int *vect, int position1, int position2);
void getSort(Vector *vec, int algo);

void cpyValues(Vector *vector);
void generateValues(Vector *vetor, int len, int order);
time_t timeCalculator(time_t start, time_t final);
void printTables(Vector *vec);
void addLine(Vector *vec);
void addWhiteSpaces(int lenCurrent, int lenFinal);
void addHeader(Vector *vec);

int main(){

    Vector vector[AMOUNT_ALGO];
    int i,j, k;
    int vec_lens[9];
    vec_lens[0]=10;
    vec_lens[1]=100;
    vec_lens[2]=500;
    vec_lens[3]=1000;
    vec_lens[4]=10000;
    vec_lens[5]=50000;
    vec_lens[6]=100000;
    vec_lens[7]=500000;
    vec_lens[8]=1000000;


    for(i=0; i<9; i++){
        for(j=0; j<3; j++){
           createVector(vector, AMOUNT_ALGO, vec_lens[i]);

            generateValues(vector, vec_lens[i], j);
            cpyValues(vector);

            for(k=0; k<AMOUNT_ALGO; k++){

                getSort(&vector[k], k);

            }
            printTables(vector);
            freeVector(vector);
        }
    }

    return 0;
}

String createString(int n){
    String string = (String)malloc(sizeof(char)*n);
    return string;
}
void freeString(String str){
    free(str);
}
void createVector(Vector vec[], int lenVector, int lenVecInVector){
    int i;
    for(i=0;i<lenVector;i++){
        vec[i].vec=(int *)malloc(sizeof(int)*lenVecInVector);
    }
    vec->len = lenVecInVector;
}
void freeVector(Vector *v){
    int i;
    for(i=0; i<AMOUNT_ALGO;i++){
        free(v->vec);
    }
    free(v);
}
void generateValues(Vector *vetor, int len, int order){
    int i,j;
    switch(order){
        case ASCENDING:
            for(i=0; i<len;i++){
                vetor[0].vec[i]= i;
            }
            break;
        case DESCENDING:
            for(i=0, j=len-1; i<len; i++, j--){
                 vetor[0].vec[i]= j;
            }
            break;
        case RANDOM:
            srand(time(NULL));
            for(i=0; i<len;i++){
                 vetor[0].vec[i] = (rand()%1000001);
            }
            break;
    }
}
void cpyValues(Vector *vector){
    int i, j;
    for(i=1; i<AMOUNT_ALGO;i++){
        for(j=0; j<vector->len;j++){
            vector[i].vec[j]= vector[0].vec[j];
        }
    }
}

time_t timeCalculator(time_t start, time_t final){
    return (final-start)/1000;//ms
}

void getSort(Vector *vec, int algo){
    switch(algo){
        case 0:
            strcpy(vec->ds->name,"BubbleSort");
            bubbleSort(vec);
            break;
        case 1:
            strcpy(vec->ds->name,"InsertSort");
            insertSort(vec);
            break;
        case 2:
            strcpy(vec->ds->name,"SelectionSort");
            selectionSort(vec);
            break;
            case 3:
            strcpy(vec->ds->name,"ShellSort");
            shellSort(vec);
            break;
        case 4:
            strcpy(vec->ds->name,"QuickSort");
            quickSort(vec, 0, vec->len);
            break;
    }
}
void printTables(Vector *vec){

    int i;
    addHeader(vec);

    for(i=0; i<vec->len;i++){
        addLine(&vec[i]);
    }
    printf("+-------------------------------------------------------------------------------------------------------------+\n\n");
}

void addHeader(Vector *vec){

    int aux;

    String str_partition = createString(100);
    strcpy(str_partition, "+-------------------------------------------------------------------------------------------------------------+");

    String str_order = createString(100);
    strcpy(str_order, "+ 													   		ORDEM ");

    String str_elem = createString(100);
    strcpy(str_elem, "+ 															      ");

    if(vec->len<10)
        aux=1;
    else if (vec->len<100)
        aux=2;
    else if(vec->len<1000)
        aux=3;
    else if (vec->len<10000)
        aux=4;
    else if (vec->len<100000)
        aux=5;
    else if (vec->len<1000000)
        aux=6;
    else
        aux=7;

    switch(vec->ds->order){
        case RANDOM:
            strcat(str_order, "ALEATORIA");
            break;
        case ASCENDING:
            strcat(str_order, "CRESCENTE");
            break;
        case DESCENDING:
            strcat(str_order, "DECRESCENTE");
            break;

    }

    printf(str_partition);
    printf(str_order);
    addWhiteSpaces(strlen(str_order), strlen(str_partition)-1);
    printf("+\n");

    printf(str_elem);
    printf("%d Elementos", vec->len);
    addWhiteSpaces((strlen(str_elem)+aux+10), strlen(str_partition)-1);
    printf("+\n");

    printf(str_partition);
    printf("|           Algoritmo           |      Tempo (ms)       |       Movimentacoes       |       Comparacoes       |\n");
    printf(str_partition);

}


void addWhiteSpaces(int lenCurrent, int lenFinal){
    int j;
    for( j=lenCurrent;j<lenFinal-1;j++){
        printf(" ");
    }
}
void addLine(Vector* vec){

    String aux = createString(10);

    printf("|");
    printf("%s", vec->ds->name);
    addWhiteSpaces(strlen(vec->ds->name), 32);



    printf("|");
    sprintf(aux, "%ud",(unsigned int)vec->ds->duration);
    printf("%s", aux);
    addWhiteSpaces(33+strlen(aux), 33+23);
    freeString(aux);

    aux = createString(10);

    printf("|");
    sprintf(aux, "%d",vec->ds->movement);
    printf("%s", aux);
    addWhiteSpaces(57+strlen(aux), 57+27);
    freeString(aux);

    aux = createString(10);

    printf("|");
    sprintf(aux, "%d",vec->ds->comparisons);
    printf("%s", aux);
    addWhiteSpaces(85+strlen(aux), 85+25);
    freeString(aux);

    printf("|\n");

}



void move(int *vect, int position1, int position2){
    int aux;
    aux = vect[position1];
    vect[position1] = vect[position2];
    vect[position2] = aux;
}

void bubbleSort(Vector *vec){

    int i, j, movement=0, comparisons=0;
    time_t start, final;

    start = time(NULL);
    for (i = vec->len - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            comparisons++;
            if (vec->vec[j] > vec->vec[j + 1]) {
                move(vec->vec, j, j+1);
                movement++;
            }
        }
    }
    final = time(NULL);

    vec->ds->comparisons = comparisons;
    vec->ds->duration = timeCalculator(start, final);
    vec->ds->movement = movement;

}
void insertSort(Vector *vec){
    int i, j,movement=0, comparisons=0;
    time_t start, final;

    start = time(NULL);
    for (i = 1; i < vec->len; i++) {
        j = i;

        while (j > 0) {
            comparisons++;
            if(vec->vec[j - 1] > vec->vec[j]){
                move(vec->vec, j, j-1);
                movement++;
            }else{
                break;
            }
            j--;
        }
    }
    final = time(NULL);

    vec->ds->comparisons = comparisons;
    vec->ds->duration = timeCalculator(start, final);
    vec->ds->movement = movement;
}
void selectionSort(Vector *vec){
    int i, j, minimum, movement=0, comparisons=0;
    time_t start, final;

    start = time(NULL);
    for (i = 0; i < ( vec->len - 1 ); i++) {
            minimum = i;
        for (j = ( i + 1 ); j < vec->len; j++){
            if( vec->vec[j] < vec->vec[minimum] ) {
                comparisons++;
                minimum = j;
            }
        }
        if ( i != minimum ) {
            comparisons++;
            move(vec->vec, minimum, i);
            movement++;
        }
    }
    final = time(NULL);

    vec->ds->comparisons = comparisons;
    vec->ds->duration = timeCalculator(start, final);
    vec->ds->movement = movement;
}
void shellSort(Vector *vec){
    int i = (vec->len - 1) / 2;
    int key, k, movement=0, comparisons=0;
    time_t start, final;

    start = time(NULL);
    while(i != 0){
        do{
            key = 1;
            for(k = 0; k < vec->len - i; ++k){
                comparisons++;
                if(vec->vec[k] > vec->vec[k + i]){
                    move(vec->vec, k, k+i);
                    key = 0;
                    movement++;
                }
            }
        }while(key == 0);
        i = i / 2;
    }
    final = time(NULL);

    vec->ds->comparisons = comparisons;
    vec->ds->duration = timeCalculator(start, final);
    vec->ds->movement = movement;
}
void quickSort(Vector *vec, int begin, int end){

    int i, j, middle;
    time_t start, final;

    i = begin;
    j = end;
    middle = vec->vec[(begin + end) / 2];

    start = time(NULL);

    do{
        while(vec->vec[i] < middle){i++; vec->ds->comparisons++;}
        while(vec->vec[j] > middle){j--; vec->ds->comparisons++;}
        if(i <= j){
            vec->ds->comparisons++;
            move(vec->vec, i, j);
            vec->ds->movement++;
            i++;
            j--;
        }
    }while(i <= j);

    vec->ds->comparisons++;
    if(begin < j){
        quickSort(vec, begin, j);

    }
    vec->ds->comparisons++;
    if(i < end){
        quickSort(vec, i, end);
    }
    final = time(NULL);

    vec->ds->duration = timeCalculator(start, final);
}

