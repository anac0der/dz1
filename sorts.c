#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define start_size 10
#define curr_seq_type 1 //текущий тип генерируемого массива

long long int *mas_gen(int n, int type){ //генерация массива
    int i;
    long long int *a = (long long int *)malloc(n * sizeof(long long int));
    if(type < 3){
        srand(time(NULL));
        for(i = 0; i < n; i++){
            a[i] = (long long int) (rand() + 1) * (rand() + 1) * (rand() + 1); // генерируем случайное число
            a[i] = a[i] * (rand() % 2 ? 1 : -1); // определяем знак числа
        }
    }
    else if(type == 3){//так как в случае упорядоченного массива (или массива, упорядоченного в обратном порядке) сами значения не важны
                       // для оценки количества сравнений и обменов, проинициализируем от 1 до n
        for(i = 0; i < n; i++){
            a[i] = i + 1 ;
            a[i] = a[i] * (rand() % 2 ? 1 : -1);
        }
    }
    else{
        for(i = 0; i < n; i++){
            a[i] = n - i ;
            a[i] = a[i] * (rand() % 2 ? 1 : -1);
        }
    }
    return a;
}

void swap(long long int *a, long long int *b){
    long long int t = *a;
    *a = *b;
    *b = t;
}

int cmp(long long int a, long long int b){ // компаратор
    a = a > 0 ? a : -a;
    b = b > 0 ? b : -b;
    return a > b;
}

void Bubble_Sort(long long int *a, int n){ // сортировка пузырьком
    int swaps = 0;
    int compares = 0;
    swaps = compares = 0;
    for(int i = n - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            compares++;
            if(cmp(a[j], a[j + 1])){
                swap(&a[j], &a[j + 1]);
                swaps++;
            }
        }
    }
    printf("%s%d%s\n", "---- BUBBLE SORT WITH N = ", n, " ----");
    printf("%s%d %c %s%d\n", "Compares: ", compares, ' ', "Swaps: ", swaps);
}

void sift(long long int *a, int i, int n, int *swaps, int *compares){ // просеивает элемент с индексом i в подмассиве [i ; n - 1]
    long long int parent_ind, max_son_ind, elem; // индекс родителя, максимального сына, просеиваемый элемент
    parent_ind = i; max_son_ind = 2 * i + 1, elem = a[i];
    (*compares) += 2; // если += 1, то одно сравнение при выходе из цикла не посчитается
    if(max_son_ind < n - 1 && !cmp(a[max_son_ind], a[max_son_ind + 1])){ //инициализация максимального сына
        max_son_ind++;
    }
    while(max_son_ind < n && !cmp(elem, a[max_son_ind])){ //просеивание
        a[parent_ind] = a[max_son_ind];
        a[max_son_ind] = elem;
        parent_ind = max_son_ind;
        max_son_ind = 2 * max_son_ind + 1;
        if(max_son_ind < n - 1 && !cmp(a[max_son_ind], a[max_son_ind + 1])){
            max_son_ind++;
        }
        (*swaps)++;
        (*compares) += 2;
    }
}

void Heap_Sort(long long int *a, int n){ // сортировка пирамидой
    int i, swaps = 0, compares = 0;
    for(i = n / 2 - 1; i >= 0; i--){
        sift(a, i, n, &swaps, &compares); // формируем пирамиду из массива
    }
    for(i = n - 1; i > 0; i--){
        swaps++;
        swap(&a[0], &a[i]); // ставим максимум в конец
        sift(a, 0, i, &swaps, &compares); // просеиваем новый корень пирамиды
    }
    printf("%s%d%s\n", "---- HEAP SORT WITH N = ", n, " ----");
    printf("%s%d %c %s%d\n", "Compares: ", compares, ' ',  "Swaps: ", swaps);
}

int main(void){
    int n, i, size = start_size;
    long long int *a;
    //a = mas_gen(size, curr_seq_type);
    //for(i = 0; i < size; i++){
        //printf("%lld ", a[i]);
    //}
    //printf("%c", '\n');
    //Bubble_Sort(a, size);
    //for(i = 0; i < size; i++){
        //printf("%lld ", a[i]);
    //}
    //return 0;
    for(int i = 0; i < 4; i++){
        a = mas_gen(size, curr_seq_type);
        Heap_Sort(a, size);
        a = mas_gen(size, curr_seq_type);
        Bubble_Sort(a, size);
        size *= 10;
        printf("%c", '\n');
    }
    free(a);
    return 0;
}
