#include <stdio.h>
#include <algorithm>
#pragma warning (disable:4996)
#define NM 105
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
typedef long long int ll;
FILE *in,*out;

int M, N;
int uniqueRowFlag[NM];
char pat[NM][NM], text[NM][NM];

int acN;
struct AC{
    int id;
    AC* next[26];
    AC* fail;
    TRIE(){
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
            if (cur->next[pat[i][j]-'a'] == nullptr)
                cur->next[pat[i][j]-'a'] = &ac[++acN];
            cur = cur->next[pat[i][j]-'a'];
        }
        if (cur->id == -1) cur->id = i, uniqueRowFlag[i] = 1;
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

int main(int argc, char* argv[]){
    in = fopen(argv[1],"r");
    out = fopen(argv[2],"w");
    input();
    return 0;
}