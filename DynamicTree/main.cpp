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
int findRoot(int x) {
	return par[x] == 0 ? x : findRoot(par[x]);
}

inline int myRand() {
	if (RAND_MAX == 0x7fff){
		return rand()*RAND_MAX + rand();
	}else return rand();
}

int makeType(int link, int cut, int lca) {
	int x = myRand() % (link + cut + lca);
	if (x < link) return 1;
	if (x < link + cut) return 2;
	return 3;
}

void makeData(int n,int Q, string filename){ // node n, query M
	FILE *out = fopen(("data/" + filename + ".in").c_str(), "w");

	FOR(i, 1, n) par[i] = 0, child[i].clear();
	parCnt = 0;
	fprintf(out, "%d\n", Q);
	FOR(q, 1, Q) {
		if (q == 36425) {
			q = q+1;
			q=q-1;
		}
		int type = makeType(50, 10, 10);
		//printf("%d %d\n", q, type);
		if (type == 1) { // link
			if (parCnt > n*0.8) {
				q--;
				continue;
			}
			// find u
			int u, v;
			u = myRand() % n + 1;
			while (par[u] != 0) {
				u++;
				if (u > n) u = 1;
			}

			// find v
			v = myRand() % n + 1;
			int _u = findRoot(u);
			while (_u == findRoot(v)) {
				v = myRand() % n + 1;
			}

			fprintf(out, "1 %d %d\n", u, v);

			par[v] = u;

			child[u].emplace_back(v);
			parCnt++;
		}
		else if (type == 2) {
			if (parCnt < n * 0.1) {
				q--;
				continue;
			}
			// find v
			int v;
			v = myRand() % n + 1;
			while (par[v] == 0) {
				v++;
				if (v > n) v = 1;
			}

			fprintf(out, "2 %d\n", v);

			int p_v = par[v];
			int flag = 0;
			for (int i = 0; i < child[p_v].size()-1; i++) {
				if (child[p_v][i] == v) flag = 1;
				if (flag) child[p_v][i] = child[p_v][i + 1];
			}
			child[p_v].resize(child[p_v].size() - 1);

			par[v] = 0;
			parCnt--;
		}
		else {
			// find u
			int u;
			u = myRand() % n + 1;
			while (par[u] != 0) {
				u++;
				if (u > n) u = 1;
			}

			queue<int> Q;
			vector<int> cand;
			Q.push(u);
			while (!Q.empty()) {
				int x = Q.front(); Q.pop();
				cand.emplace_back(x);
				for (auto& c : child[x]) {
					Q.push(c);
				}
			}
			int x = myRand() % cand.size();
			int y = myRand() % cand.size();
			fprintf(out, "3 %d %d\n", cand[x], cand[y]);
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
	//srand(time(NULL));
//	sampling(100, 200);
//	sampling(1000, 2000);
//sampling(10000, 20000);
sampling(10000, 50000);
//sampling(10000, 100000);
//sampling(100000, 200000);
//sampling(100000, 500000);
	//sampling(100000, 1000000);
	return 0;
}