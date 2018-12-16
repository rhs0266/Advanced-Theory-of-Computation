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
	FILE *out = fopen(("data/" + filename + ".in").c_str(), "w");

	parCnt = 0;
	for (int i = 1; i <= n; i++) par[i] = 0, child[i].clear();

	for (int q = 1; q <= Q; q++) {
		//printf("%d\n", q);
		int type = makeType(50, 10, 10);
		if (type == 1) {
			if (parCnt > n*0.9) {
				q--;
				continue;
			}
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
		else if (type == 2) {
			if (parCnt < n*0.1) {
				q--;
				continue;
			}
			int v; // v 를 부모와의 연결을 끊는다.
			v = myRand() % n + 1;
			while (par[v] == 0) {
				v = myRand() % n + 1;
			}

			fprintf(out, "2 %d\n", v);

			// make cut
			parCnt--;
			for (int i = 0; i < child[par[v]].size(); i++)
				if (child[par[v]][i] == v)
					child[par[v]][i] = -1;
			par[v] = 0;
		}
		else {
			int x = myRand() % n + 1;
			cand.clear();
			Queue.push(x);
			while (!Queue.empty()) {
				x = Queue.front(); Queue.pop();
				cand.push_back(x);
				for (int y : child[x]) {
					if (y == -1) continue;
					Queue.push(y);
				}
			}

			int u, v;
			u = cand[myRand() % cand.size()];
			v = cand[myRand() % cand.size()];
			fprintf(out, "3 %d %d\n", u, v);
		}
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
	sampling(100, 200);
	sampling(1000, 2000);
	sampling(10000, 20000);
	sampling(10000, 50000);
	sampling(10000, 100000);
	sampling(100000, 200000);
	sampling(100000, 500000);
	sampling(100000, 1000000);
	return 0;
}