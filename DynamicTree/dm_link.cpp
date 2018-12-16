#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <queue>
using namespace std;
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
#define NM 100005
int par[NM], parCnt;
vector<int> child[NM];
queue<int> Queue;
vector<int> cand;
int findRoot(int x) {
	return par[x] == 0 ? x : findRoot(par[x]);
}

inline int myRand() {
	if (RAND_MAX == 0x7fff) {
		return rand()*RAND_MAX + rand();
	}
	else return rand();
}

int makeType(int link, int cut, int lca) {
	int x = myRand() % (link + cut + lca);
	if (x < link) return 1;
	if (x < link + cut) return 2;
	return 3;
}

void makeData(int n, int Q, string filename) { // node n, querx	y M
	FILE *out = fopen(("../data_link/" + filename + ".in").c_str(), "w");

	parCnt = 0;
	for (int i = 1; i <= n; i++) par[i] = 0, child[i].clear();

	for (int q=1;q<=n-1;q++){
		int u, v; // u를 v의 자식으로 만든다
		u = myRand() % n + 1;
		u = findRoot(u);

		v = myRand() % n + 1;
		while (u == findRoot(v)) {
			v = myRand() % n + 1;
		}

		fprintf(out, "1 %d %d\n", u, v);

		// make link
		parCnt++;
		par[u] = v;
		child[v].emplace_back(u);
	}

	for (int q = 1; q <= Q - n + 1; q++) {
		fprintf(out, "3 %d %d\n", myRand() % n + 1, myRand() % n + 1);
	}

	fclose(out);
}
void sampling(int n, int Q) {
	char intStr[100];
	for (int i = 0; i < 10; i++) {
		printf("%d\n", i + 1);
		string strN = to_string(n);
		string strQ = to_string(Q);
		string strIdx = to_string(i);

		makeData(n, Q, strN + "_" + strQ + "_" + strIdx);
	}
}
int main() {
	srand(time(NULL));
	sampling(1000, 10000000);
	sampling(2000, 10000000);
	sampling(4000, 10000000);
	sampling(8000, 10000000);

	sampling(10000, 10000000);
	sampling(20000, 10000000);
	sampling(30000, 10000000);
	sampling(50000, 10000000);
	return 0;
}