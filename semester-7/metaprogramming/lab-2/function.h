#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int size;
    int arr[100][100];
} ResultType;

ResultType generate_matrix(int triplets[10000][3], int num){
    ResultType matrix;
    matrix.size=num;
    for (int i = 0; i < num; ++i){
    	int row = triplets[i][0];
    	int col = triplets[i][1];
    	int val = triplets[i][2];
        matrix.arr[row][col] = val;
    }
    return matrix;
}

int find_range(ResultType res){
    int result = 99;
    for(int i = 99; i >= 0; i--){
        for(int j = 0; j <= i; j++){
            if(res.arr[i][j] != 0){
                return i;
            }
            if(res.arr[j][i] != 0){
                return i;
            }
        }
    }
}















/*
int words[100][100];
size_t i, count = 0;

for (char *word = strtok(text, DELIM); word; word = strtok(NULL, DELIM)) {
if (count < MAX_WORDS - 1) {
    count += add_words(words, word);
}
else  {
    fprintf(stderr, "Error: array full\n");
    break;
}
}
sort_dict(words, count);
ResultArray d= create(num, words);
fprintf (stdout, "Cfunction:\n");



#define DELIM " .,!?\t\n"

#define MAX_WORDS 10000
#define MAX_WORD 100


typedef struct {
    char word[MAX_WORD + 1];
    int count;
} word_t;

typedef struct {
    int size;
    word_t *arr;
} ResultArray;

int add_words(word_t *words, char *word)
{
    if (strlen(word) > MAX_WORD) {
        fprintf( stderr,"Error: length word > %d!\n", MAX_WORD);
        return 0;
    }

    int res = 1;
    static size_t count = 0;
    size_t i = 0;
    if (count == 0) {
        memcpy(words[0].word, word, strlen(word) + 1);
        words[0].count = 1;
        count = 1;
    } else {
        for (i = 0; i < count; ++i)
            if (strcmp(words[i].word, word) == 0) {
                words[i].count++;
                res = 0;
                break;
            }
        if (i == count) {
            memcpy(words[i].word, word, strlen(word) + 1);
            words[i++].count = 1;
            count++;
        }
    }
    return res;
}

void sort_dict(word_t *words,int count){
    size_t n = count;
    for(int i = 0 ; i < n - 1; i++) {
        for(int j = 0 ; j < n - i - 1 ; j++) {
            if(words[j].count < words[j+1].count) {
                word_t tmp = words[j];
                words[j] = words[j+1] ;
                words[j+1] = tmp;
            }
        }
    }
}

ResultArray create(int size, word_t* words){
    ResultArray res;
    res.size=size;
    res.arr=(word_t *)malloc(size*sizeof(word_t));
    for(int i=0;i<size;i++){
        strncpy(res.arr[i].word, words[i].word, 501 );
        res.arr[i].count=words[i].count;
    }

    return res;
}
*/



