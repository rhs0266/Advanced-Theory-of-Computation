#include <stdio.h>
#include <algorithm>
#pragma warning (disable:4996)
#define NM 105
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
typedef long long int ll;
FILE *in,*out;

int M, N;
int uniqueRowFlag[NM], matchingIdx[NM], kmpPointer[NM];
int patLinear[NM], patFail[NM];
char pat[NM][NM], text[NM][NM];

int acN;
struct AC{
    int id;
    AC* next[26];
    AC* fail;
    AC(){
        id = -1;
        FOR (i,0,25) next[i] = nullptr;
        fail = nullptr;
    }
}ac[NM*NM];

void input() {
    fscanf(in, "%d %d\n", &M, &N);
    FOR(i, 1, M) fscanf(in, "%s", &pat[i][1]);
    FOR(i, 1, N) fscanf(in, "%s", &text[i][1]);
}

void numberingRow(){
    acN = 0;
    FOR (i,1,M){
        AC* cur = &ac[0];
        FOR (j,1,M){
            /* TEST */
            if (pat[i][j] == '-') break;
            /********/
            if (cur->next[pat[i][j]-'a'] == nullptr)
                cur->next[pat[i][j]-'a'] = &ac[++acN];
            cur = cur->next[pat[i][j]-'a'];
        }
        if (cur->id == -1) cur->id = i, uniqueRowFlag[i] = 1;
        patLinear[i] = cur->id;
    }
}
void constructACs(){
    FOR (i,0,acN){
        // Find failure link for its children
        FOR (j,0,25){
            AC* child = ac[i].next[j];
            if (child == nullptr) continue;

            AC* cur = &ac[i];
            for (;;){
                cur = cur->fail;
                if (cur == nullptr){
                    child->fail = &ac[0];
                    break;
                }
                if (cur->next[j] != nullptr){
                    child->fail = cur->next[j];
                    break;
                }
            }
        }
    }
}

void patKMP(){
    patFail[0] = -1;
    patFail[1] = 0;

    int pointer = 0;
    FOR (i,2,M){
        for (;;){
            if (patLinear[pointer+1] == patLinear[i]){
                patFail[i] = pointer+1;
                pointer++;
                break;
            }else{
                if (pointer!=0) pointer = patFail[pointer];
                else{
                    patFail[i] = 0;
                    pointer = 0;
                    break;
                }
            }
        }
    }
}

void Baker_Bird(){
    /* Preprocess */

    // assign number for each line with considering uniqueness
    numberingRow();

    // construct Aho-Corasick
    constructACs();

    // calculate KMP failure function for patLinear
    patKMP();

    /**************/

    /* Baker Bird Algorithm */

    // setup each column's kmp pointers
    FOR (j,1,N) kmpPointer[j]=0;


    // searching pattern in text
    FOR (i,1,N){

        // Calculate pattern matching for i-th text row
        AC* cur = &ac[0];
        FOR (j,1,N){

            // Find matching row for text[i][j-M+1 ... j]
            while (cur->next[text[i][j]-'a'] == nullptr){
                if (cur->fail == nullptr) break;
                cur = cur->fail;
            }
            if (cur->next[text[i][j]-'a'] != nullptr){
                cur = cur->next[text[i][j]-'a'];
            }
            int matchingIdx = 0;
            if (cur->id != -1) matchingIdx = cur->id;

            if (matchingIdx == 0){ // if this point has no matching row in pattern
                kmpPointer[j] = 0;
            }else{ // otherwise, processing kmp algorithm
                for (;;){
                    if (patLinear[kmpPointer[j]+1] == matchingIdx){
                        kmpPointer[j]++;
                        break;
                    }else{
                        if (kmpPointer[j] != 0) kmpPointer[j] = patFail[kmpPointer[j]];
                        else break;
                    }
                }
                if (kmpPointer[j] == M){
                    fprintf(out,"%d %d\n",i-1, j-1);
                    kmpPointer[j] = patFail[M];
                }
            }
        }
    }

    /************************/
}

int main(int argc, char* argv[]){
    if (argc>=3){
        in = fopen(argv[1],"r");
        out = fopen(argv[2],"w");
    }else{
        in = fopen("../input.txt","r");
        out = fopen("../output.txt","w");
    }
    input();
    Baker_Bird();
    return 0;
}