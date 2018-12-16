#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <vector>
#include <time.h>
#include <queue>
#include <iostream>
using namespace std;
#define FOR(i,n,m) for (int i=(n);i<=(m);i++)
#define NM 100005

FILE *logging = fopen("log.txt", "w");

string str;
int n, Q, par[NM];
void BruteForce(string filename) {
	FILE *in = fopen(("data/" + filename).c_str(), "r");
	FILE *out = fopen(("testing/" + filename + "BruteForce.out").c_str(), "w");

	//fscanf(in, "%d %d", &n, &Q);
	FOR(i, 1, n) par[i] = 0;
	FOR(q, 1, Q) {
		int type;
		fscanf(in, "%d", &type);
		if (type == 1) {
			int u, v;
			fscanf(in, "%d %d", &u, &v);
			par[u] = v;
		}
		else if (type == 2) {
			int v;
			fscanf(in, "%d", &v);
			par[v] = 0;
		}
		else {
			int u, v;
			fscanf(in, "%d %d", &u, &v);
			vector<int> U, V;
			while (u != 0) {
				U.push_back(u);
				u = par[u];
			}
			while (v != 0) {
				V.push_back(v);
				v = par[v];
			}
			for (int i = 0; i < U.size(); i++) {
				int flag = 0;
				for (int j = 0; j < V.size(); j++) {
					if (U[i] == V[j]) flag = 1;
				}
				if (flag == 1) {
					fprintf(out, "%d\n", U[i]);
					break;
				}
			}
		}
	}
	fclose(in);
	fclose(out);
}

////////////////////////////////////////////

struct NODE {
public:
	NODE() :key(0), par(nullptr), left(nullptr), right(nullptr), pp(nullptr) {}
	NODE(int _key) :key(_key), par(nullptr), left(nullptr), right(nullptr), pp(nullptr) {}
	NODE *par, *left, *right, *pp;
	int key;
}vertex[NM];

/*
* isLeftChild(x)
*/
bool isLeftChild(NODE *x) {
	if (x->par == nullptr) return false;
	return x == x->par->left;
}

/*
* rotate(cur) ; rearrange relations between adjacent two layers
* cur : make cur as parent of its parent
*/
void rotate(NODE *cur) {
	NODE *p_cur = cur->par;
	if (isLeftChild(cur)) {   // if cur is left child
		p_cur->left = cur->right;
		if (cur->right) cur->right->par = p_cur;
		cur->right = p_cur;
	}
	else {                    // if cur is right child
		p_cur->right = cur->left;
		if (cur->left) cur->left->par = p_cur;
		cur->left = p_cur;
	}
	cur->par = p_cur->par;
	p_cur->par = cur;
	if (cur->par) {
		if (cur->par->left == p_cur) cur->par->left = cur;
		else cur->par->right = cur;
	}
	else {
		cur->pp = p_cur->pp;
		p_cur->pp = NULL;
	}
}

/*
* splay(cur) ; apply splay operation on \cur\ node
*/
void splay(NODE *cur) {
	while (cur->par) {
		NODE *p_cur = cur->par;
		NODE *p_p_cur = p_cur->par;
		if (p_cur->par != nullptr) {
			if (isLeftChild(cur) == isLeftChild(p_cur)) rotate(p_cur);
			else rotate(cur);
		}
		rotate(cur);
	}
}

/*
* access(cur) ; make preferred-path from \cur\ node to root node
*/
void access(NODE *cur) {
	splay(cur);
	if (cur->right) {                   // cut lower preferred-path of cur & make path-parent edge
		cur->right->pp = cur;
		cur->right->par = NULL;
		cur->right = NULL;
	}

	// below part ; repeating splay operation and making preferred-path towards root node
	while (cur->pp) {
		NODE *pp = cur->pp;
		splay(pp);
		if (pp->right) {
			pp->right->pp = pp;
			pp->right->par = NULL;
		}
		pp->right = cur;
		cur->par = pp;
		cur->pp = NULL;
		splay(cur);
	}
}

/*
* link(u, v) ; link edge between \u\ node and \v\ node. \u\ node will be a parent of \v\ node
*/
void link(NODE *u, NODE *v) {
	access(u);
	access(v);
	u->left = v;
	v->par = u;
}

/*
* cut(cur) ; cut edge between \cur\ node and its parent node
*/
void cut(NODE *cur) {
	access(cur);
	if (cur->left) {
		cur->left->par = NULL;
		cur->left = NULL;
	}
}

/*
* lca(u, v) ; find lowest common ancestor of \u\ and \v\ nodes
*/
NODE *lca(NODE *u, NODE *v) {
	access(u);
	access(v);
	splay(u);
	if (u->pp == nullptr) return u;
	return u->pp;
}

void DynamicTree(string filename) {
	FILE *in = fopen(("data/" + filename).c_str(), "r");
	FILE *out = fopen(("testing/" + filename + "DynamicTree.out").c_str(), "w");

	//fscanf(in, "%d %d", &n, &Q);
	for (int i = 1; i <= n; i++) {
		vertex[i].par = vertex[i].left = vertex[i].right = vertex[i].pp = nullptr;
		vertex[i].key = i;
	}
	for (; Q--;) {
		int type;
		fscanf(in, "%d", &type);
		if (type == 1) {
			int x, y;
			fscanf(in, "%d %d", &x, &y);
			link(&vertex[x], &vertex[y]);
		}
		else if (type == 2) {
			int x;
			fscanf(in, "%d", &x);
			cut(&vertex[x]);
		}
		else {
			int x, y;
			fscanf(in, "%d %d", &x, &y);
			fprintf(out, "%d\n", lca(&vertex[x], &vertex[y])->key);
		}
	}
	fclose(in);
	fclose(out);
}

void comparing(string filename) {
	clock_t bfStart, bfEnd, dtStart, dtEnd;
	bfStart = clock();
	BruteForce(filename);
	bfEnd = clock();
	dtStart = clock();
	DynamicTree(filename);
	dtEnd = clock();

	fprintf(logging, "%d %d\n", bfEnd - bfStart, dtEnd - dtStart);
}

int main() {
	FILE *in = fopen("data/inputList.txt", "r");
	for (int i = 1; i <= 80; i++) {
		printf("%d\n", i);
		char str[100];
		fscanf(in, "%s", str);
		n = 0, Q = 0;
		int j = 0;
		for (; j < 100; j++) {
			if (str[j] == '_') break;
			n = n * 10 + (str[j] - '0');
		}
		j++;
		for (; j < 100; j++) {
			if (str[j] == '_') break;
			Q = Q * 10 + (str[j] - '0');
		}

		comparing(str);
	}
	return 0;
}