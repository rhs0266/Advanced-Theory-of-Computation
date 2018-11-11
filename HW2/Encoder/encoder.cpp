#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define FOR(i,n,m) for (int i=n;i<=m;i++)
#define si(n) fscanf(in,"%d",&n)
#define NM 500005
using namespace std;
FILE *in = fopen("../infile.txt", "r");
//FILE *in = stdin, *out = stdout;
typedef long long int ll;
const double EPS = 1e-8;

#define PrintableBegin 0
#define PrintableEnd 255
#define PrintableCnt 254
#define END 255
#define INC 254

int S = 70;
vector<int> mem;
int curLen = 0;

inline int convert(char x) {
	if (x >= 'a' && x <= 'z') return x - 'a' + 0;
	if (x >= 'A' && x <= 'Z') return x - 'A' + 26;
	if (x >= '0' && x <= '9') return x - 'a' + 52;
	if (x == '?') return 62;
	if (x == '!') return 63;
	if (x == ' ') return 64;
	if (x == ',') return 65;
	if (x == '.') return 66;
	if (x == ':') return 67;
	if (x == ';') return 68;
	if (x == '\n') return 69;
}

inline int reqLen(int id) {
	// (id,ch) pair를 표현하는 데에 필요한 최소 출력 글자 수
	int target = id << 7;

	unsigned int pBit = 1, pP = PrintableCnt;
	while (pP <= target) {
		pP *= PrintableCnt;
		pBit++;
	}
	return pBit;
}

void push(int x,int len) {
	if (len == 0) return;
	push(x / PrintableCnt, len - 1);
//	fprintf(out, "%c", (x % PrintableCnt) + PrintableBegin);
	cout << (char)((x % PrintableCnt) + PrintableBegin);
}
void f(int id, int ch, int len) {
	int x = (id << 7) + ch;
	push(x, len);
}
void print(int id, int ch){
	int _reqLen = reqLen(id);
	while (curLen < _reqLen) {
		cout << (char)(INC);
		curLen++;
	}
	f(id, ch, curLen);
}

int trieN;
struct TRIE {
public:
	TRIE() {}
	TRIE(int id) :id(id) {}
	int id;
	TRIE *next[70];
}trie[NM];
int parIdx[NM], parEdge[NM];

void init() {
	FOR(i, 0, NM - 1) trie[i].id = i;
}

TRIE *getNext(TRIE *node, int x) {
	if (node->next[x]) return node->next[x];
	node->next[x] = &trie[++trieN];
	parIdx[trieN] = node->id;
	parEdge[trieN] = x;
	return node->next[x];
}

void encoding() {
	char ch;
	TRIE *root = &trie[0];
	TRIE *node = root, *nextNode;


	// make edge for every character
	FOR(i, 0, S - 1) {
		getNext(root, i);
	}

	// encode text
	while (fscanf(in, "%c", &ch) != EOF) {
		int _ch = convert(ch);
		nextNode = getNext(node, _ch);
		if (nextNode == trie + trieN) {
			// print
			print(node->id, _ch);
			node = root;
		}
		else {
			node = nextNode;
		}
	}
	print(node->id,END);

}

int main() {
	freopen("output.txt","w",stdout);
	init();
	encoding();
//	FOR (i,PrintableBegin, PrintableEnd){
//		cout << char(i);
//	}
	return 0;
}