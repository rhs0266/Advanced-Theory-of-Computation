#include <stdio.h>
#include <algorithm>
#pragma warning (disable:4996)
#define NM 105
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
typedef long long int ll;
FILE *in, *sol, *out;

int M, N;
int numKey = 5;
int keys[6] = { 0,31,37,41,47,53 };
ll vals[6], key_M[6];
char pat[NM][NM], text[NM][NM];
ll P[NM][NM][6], T[NM][NM][6];
ll keyP[6], keyT[6];
int ans[NM][NM];
int checker[NM*NM][2];
void input() {
	fscanf(in, "%d %d\n", &M, &N);
	FOR(i, 1, M) fscanf(in, "%s", &pat[i][1]);
	FOR(i, 1, N) fscanf(in, "%s", &text[i][1]);
	FOR(i, 1, numKey) {
		key_M[i] = 1;
		FOR(j, 1, M) key_M[i] *= keys[i];
	}
}
void check(int x, int y) {
	FOR(i, x, x + M - 1) {
		FOR(j, y, y + M - 1) {
			if (pat[i - x + 1][j - y + 1] != text[i][j]) 
				return;
		}
	}
	ans[x+M-1][y+M-1] = 1;
}
int pro() {
	// Pattern Hashing
	FOR(i, 1, M) {
		FOR(j, 1, M) {
			FOR(k, 1, numKey) {
				P[i][j][k] = P[i][j - 1][k] * keys[k] + (pat[i][j] - 'a');
			}
		}
	}
	FOR(i, 1, M) {
		FOR(k, 1, numKey) {
			keyP[k] = keyP[k] * keys[k] + P[i][M][k];
		}
	}

	// Text Hashing
	FOR(i, 1, N) {
		FOR(j, 1, N) {
			FOR(k, 1, numKey) {
				T[i][j][k] = T[i][j - 1][k] * keys[k] + (text[i][j] - 'a');
				if (j > M) {
					T[i][j][k] -= (text[i][j - M] - 'a') * key_M[k];
				}
			}
		}
	}
	
	// Find Candidate
	FOR(j, M, N) {
		FOR(k, 1, numKey) keyT[k] = 0;
		FOR(i, 1, N) {
			FOR(k, 1, numKey) {
				keyT[k] = keyT[k] * keys[k] + T[i][j][k];
				if (i > M) {
					keyT[k] -= T[i - M][j][k] * key_M[k];
				}
			}
			if (i >= M) {
				int sameCnt = 0;
				FOR(k, 1, numKey) {
					if (keyT[k] == keyP[k]) sameCnt++;
				}
				if (sameCnt == numKey) check(i - M + 1, j - M + 1);
			}
		}
	}

	// Save answer
	int checkerN = 0;
	FOR(i, 1, N) {
		FOR(j, 1, N) {
			if (ans[i][j]){
				checker[++checkerN][0]=i-1, checker[checkerN][1]=j-1;
			}
		}
	}

	// Compare with hw1's solution
	FOR (i,1,checkerN){
		int x, y;
		if (fscanf(sol,"%d %d",&x,&y)==2){
			if (x==checker[i][0] && y==checker[i][1])
				continue;
			else
				return false;
			
		}
		else{
			return false;
		}
	}
	int temp=0;
	if (fscanf(sol,"%d",&temp)!=EOF) return false;
	return true;

}
int main(int argc, char* argv[]) {
    in = fopen(argv[1],"r");
    sol = fopen(argv[2],"r");
    out = fopen(argv[3],"w");
	input();
	fprintf(out,"%s",pro()?"yes":"no");
	return 0;
}
