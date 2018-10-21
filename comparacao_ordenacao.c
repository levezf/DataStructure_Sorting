#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define RANDOM 0
#define ASCENDING 1
#define DESCENDING 2

#define AMOUNT_ALGO 5
#define AMOUNT_LEN 9

typedef char* String;

struct data_sorting{
    int order;
    double duration;
    String name;
    unsigned long int comparisons;
    unsigned long int movement;
    int *vec;
    int len;
};
typedef struct data_sorting Vector;

String createString(int n);

void freeString(String str);
void createVector(Vector *vec, int lenVector, int lenVecInVector);
void freeVector(Vector *v);
void bubbleSort(Vector *vec);
void insertSort(Vector *vec);
void selectionSort(Vector *vec);
void shellSort(Vector *vec);
void quickSort(Vector *vec, int begin, int end);
int partition (Vector* vec, int begin, int end);
//heapsort e mais


void move(int *vect, int position1, int position2);
void getSort(Vector *vec, int algo);
void cpyValues(Vector *vector);
void generateValues(Vector *vetor, int len, int order);
float timeCalculator(time_t start, time_t final);
void printTables(Vector *vec);
void addLine(Vector vec);
void addWhiteSpaces(int lenCurrent, int lenFinal);
void addHeader(Vector *vec);


int main(){

    Vector vector[AMOUNT_ALGO];
    int i,j, k;
    int vec_lens[AMOUNT_LEN];
    vec_lens[0]=10;
    vec_lens[1]=100;
    vec_lens[2]=500;
    vec_lens[3]=1000;
    vec_lens[4]=10000;
    vec_lens[5]=50000;
    vec_lens[6]=100000;
    vec_lens[7]=500000;
    vec_lens[8]=1000000;

    for(i=0; i<AMOUNT_LEN; i++){
        for(j=0; j<3; j++){
           createVector(vector, AMOUNT_ALGO, vec_lens[i]);

            generateValues(vector, vec_lens[i], j);
            cpyValues(vector);

            for(k=0; k<AMOUNT_ALGO; k++){
                getSort(vector, k);
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
void createVector(Vector *vec, int lenVector, int lenVecInVector){
    int i;
    for(i=0;i<lenVector;i++){
        vec[i].vec=(int *)malloc(sizeof(int)*lenVecInVector);
        vec[i].name = createString(100);
        vec[i].len = lenVecInVector;
        //vec[i].duration=0;
        vec[i].movement=0;
        vec[i].comparisons=0;
    }
}
void freeVector(Vector *v){
    int i;
    for(i=0; i<AMOUNT_ALGO;i++){
        free(v[i].vec);
        free(v[i].name);
    }
}
void generateValues(Vector *vetor, int len, int order){
    int i,j;
    switch(order){
        case ASCENDING:
            for(i=0; i<len;i++){
                vetor[0].vec[i]= i;
            }
            vetor[0].order=ASCENDING;
            break;
        case DESCENDING:
            for(i=0, j=len-1; i<len; i++, j--){
                 vetor[0].vec[i]= j;
            }
            vetor[0].order=DESCENDING;
            break;
        case RANDOM:
            srand(time(NULL));
            for(i=0; i<len;i++){
                 vetor[0].vec[i] = (rand()%1001);
            }
            vetor[0].order=RANDOM;
            break;
    }
}
void cpyValues(Vector *vector){
    int i, j;
    for(i=1; i<AMOUNT_ALGO;i++){

        for(j=0; j<vector->len;j++){
            vector[i].vec[j]= vector[0].vec[j];

        }
        vector[i].order = vector[0].order;

    }
}

float timeCalculator(time_t start, time_t final){
    return difftime(final, start)/1000;//ms
}

void getSort(Vector *vec, int algo){
    switch(algo){
        case 0:
            strcpy(vec[0].name,"BubbleSort");
            bubbleSort(&vec[0]);
            break;
        case 1:
            strcpy(vec[1].name,"InsertSort");
            insertSort(&vec[1]);
            break;
        case 2:
            strcpy(vec[2].name,"SelectionSort");
            selectionSort(&vec[2]);
            break;
            case 3:
            strcpy(vec[3].name,"ShellSort");
            shellSort(&vec[3]);
            break;
        case 4:
            strcpy(vec[4].name,"QuickSort");
            time_t start, final;

            start = time(NULL);


            quickSort(&vec[4], 0, vec[4].len-1);
            final = time(NULL);
            vec[4].duration = timeCalculator(start, final);
            break;
    }
}
void printTables(Vector *vec){
    int i;

    addHeader(&vec[0]);

    for(i=0; i<AMOUNT_ALGO;i++){
        addLine(vec[i]);
    }
    printf("+-------------------------------------------------------------------------------------------------------------+\n\n");
}

void addHeader(Vector *vec){
    int aux;

    String str_partition = createString(256);
    strcpy(str_partition, "+-------------------------------------------------------------------------------------------------------------+\n");

    String str_order = createString(20);

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

    switch(vec->order){
        case RANDOM:
            strcpy(str_order, "ALEATORIA");
            break;
        case ASCENDING:
            strcpy(str_order, "CRESCENTE");
            break;
        case DESCENDING:
            strcpy(str_order, "DECRESCENTE");
            break;

    }

    printf("%s", str_partition);
    printf("|                                                    ORDEM %s", str_order);

    addWhiteSpaces(strlen("|                                                    ORDEM")+
                   strlen(str_order)+2, strlen(str_partition));
    printf("|\n");
    printf("%s", str_partition);

    printf("|                                                    %d Elementos", vec->len);

    addWhiteSpaces(strlen("|                                                     Elementos")+
                   aux+1, strlen(str_partition));
    printf("|\n");

    printf("%s", str_partition);
    printf("|           Algoritmo           |      Tempo (ms)       |       Movimentacoes       |       Comparacoes       |\n");
    printf("%s", str_partition);

}


void addWhiteSpaces(int lenCurrent, int lenFinal){
    int j;
    for( j=lenCurrent;j<lenFinal-1;j++){
        printf(" ");
    }
}
void addLine(Vector vec){

    String aux = createString(100);

    printf("|");
    printf("%s", vec.name);
    addWhiteSpaces(strlen(vec.name), 32);



    printf("|");
    sprintf(aux, "%lf", vec.duration);
    printf("%s", aux);
    addWhiteSpaces(33+strlen(aux), 34+23);
    freeString(aux);

    aux = createString(100);

    printf("|");
    sprintf(aux, "%lu",vec.movement);
    printf("%s", aux);
    addWhiteSpaces(57+strlen(aux), 58+27);
    freeString(aux);

    aux = createString(100);

    printf("|");
    sprintf(aux, "%lu",vec.comparisons);
    printf("%s", aux);
    addWhiteSpaces(85+strlen(aux), 86+25);
    freeString(aux);

    printf("|\n");

}



void move(int *vect, int position1, int position2){
    int aux;
    aux = vect[position1];
    vect[position1] = vect[position2];
    vect[position2] = aux;
}

void bubbleSort(Vector* vec){

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

    vec->comparisons = comparisons;
    vec->duration = timeCalculator(start, final);
    vec->movement = movement;

}
void insertSort(Vector* vec){
    int i, j,movement=0, comparisons=0;
    time_t start, final;

    start = time(NULL);
    for (i = 1; i < vec->len; i++) {
        j = i;
        while (j > 0) {
            comparisons++;
            if(vec->vec[j - 1] <= vec->vec[j]){
                break;
            }
            move(vec->vec, j, j-1);
            movement++;

            j--;
        }
    }
    final = time(NULL);

    vec->comparisons = comparisons;
    vec->duration = timeCalculator(start, final);
    vec->movement = movement;
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

    vec->comparisons = comparisons;
    vec->duration = timeCalculator(start, final);
    vec->movement = movement;
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

    vec->comparisons = comparisons;
    vec->duration = timeCalculator(start, final);
    vec->movement = movement;
}

int partition (Vector* vec, int begin, int end){
    int pivot = vec->vec[end];
    int i = (begin - 1);
    int j;

    for ( j = begin; j <= end- 1; j++)
    {

        if (vec->vec[j] <= pivot)
        {
            vec->comparisons++;
            i++;
            move(vec->vec,i, j);
            vec->movement++;
        }
    }
    move(vec->vec,i+1, end);
    vec->movement++;
    return (i + 1);
}

void quickSort(Vector* vec, int begin, int end){

    vec->comparisons++;
    if (begin < end)
    {

        int pi = partition(vec, begin, end);

        quickSort(vec, begin,(pi-1));
        quickSort(vec, pi + 1, end);
    }

}
