#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define FOR(i,n,m) for (int i=n;i<=m;i++)
#define si(n) fscanf(in,"%d",&n)
#define NM 1000005
using namespace std;
FILE *in;
//FILE *in = stdin, *out = stdout;
typedef long long int ll;
const double EPS = 1e-8;

#define PrintableBegin 0
#define PrintableEnd 255
#define PrintableCnt 254
#define END 255
#define INC 254

int S = 71;
vector<int> mem;
int curLen = 0; // current encoding length
int trieN;

/// implement dictionary as TRIE data structure
struct TRIE {
public:
	TRIE() {}
	TRIE(int id) :id(id) {}
	int id;
	TRIE *next[71];
}trie[NM];
int parIdx[NM], parEdge[NM];

/// Iniialization
void init(int argc, char **argv) {
	in = fopen(argv[1],"r");
	freopen(argv[2],"w",stdout);
	FOR(i, 0, NM - 1) trie[i].id = i;
}

/// follow edge
TRIE *getNext(TRIE *node, int x) {
	if (node->next[x]) return node->next[x];
	node->next[x] = &trie[++trieN];
	parIdx[trieN] = node->id;
	parEdge[trieN] = x;
	return node->next[x];
}

// convert character to integer from 0 to 70
inline int convert(char x) {
	if (x >= 'a' && x <= 'z') return x - 'a' + 0;
	if (x >= 'A' && x <= 'Z') return x - 'A' + 26;
	if (x >= '0' && x <= '9') return x - '0' + 52;
	if (x == '?') return 62;
	if (x == '!') return 63;
	if (x == ' ') return 64;
	if (x == ',') return 65;
	if (x == '.') return 66;
	if (x == ':') return 67;
	if (x == ';') return 68;
	if (x == '\n') return 69;
	if (x == '\r') return 70;
}

/// calculate encoded length of given information (id, ch) pair
inline int reqLen(int id, int ch) {
	ll target = id * S + ch;

	int pBit = 1;
	ll pP = PrintableCnt;
	while (pP <= target) {
		pP *= PrintableCnt;
		pBit++;
	}
	return pBit;
}

/// encode given information 'x' with 'len' length
void push(ll x,int len) {
	if (len == 0) return;
	push(x / PrintableCnt, len - 1);
	cout << (unsigned char)((x % PrintableCnt) + PrintableBegin);
}

/// encode (id, ch) pair
void f(int id, int ch, int len) {
	ll x = (id) * S + ch;
	push(x, len);
}

/// manage encoding length and printing
void print(int id, int ch){
	int _reqLen = reqLen(id, ch);
	while (curLen < _reqLen) {
		cout << (char) (INC);
		curLen++;
	}
	if (ch==END) ch = 0;
	f(id, ch, curLen);
	if (curLen > 3) curLen = 3;
}

/// encode given text
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
	cout << (char)END;
	print(node->id,END);

}

int main(int argc, char **argv) {
	init(argc, argv);
	encoding();
	return 0;
}
