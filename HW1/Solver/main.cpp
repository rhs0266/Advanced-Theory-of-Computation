#include <stdio.h>
#include <algorithm>
#pragma warning (disable:4996)
#define NM 105
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
typedef long long int ll;
FILE *in,*out;

int M, N;
char pat[NM][NM], text[NM][NM];

void input() {
    fscanf(in, "%d %d\n", &M, &N);
    FOR(i, 1, M) fscanf(in, "%s", &pat[i][1]);
    FOR(i, 1, N) fscanf(in, "%s", &text[i][1]);
}
int main(int argc, char* argv[]){
    in = fopen(argv[1],"r");
    out = fopen(argv[2],"w");
    input();
    return 0;
}