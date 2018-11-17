#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <assert.h>
#define FOR(i,n,m) for (int i=n;i<=m;i++)
#define si(n) fscanf(in,"%d",&n)
#define NM 500005
using namespace std;
FILE *in = fopen("s", "r"), *out=fopen("output.txt","w");
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
int curLen = 0; // current reading length
int trieN;

/// same structure as encoder
struct TRIE {
public:
	TRIE() {}
	TRIE(int id) :id(id) {}
	int id;
	TRIE *next[71];
}trie[NM];
int parIdx[NM], parEdge[NM];

void init(int argc, char **argv) {
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
	FOR(i, 0, NM - 1) trie[i].id = i;
}

TRIE *getNext(TRIE *node, int x) {
	if (node->next[x]) return node->next[x];
	node->next[x] = &trie[++trieN];
	parIdx[trieN] = node->id;
	parEdge[trieN] = x;
	return node->next[x];
}

/// inverse conversion of encoder
inline char convert(int x) {
	if (0<=x && x<26) return char(x-0+'a');
	if (26<=x && x<52) return char(x-26+'A');
	if (52<=x && x<62) return char(x-52+'0');
	if (x==62) return '?';
	if (x==63) return '!';
	if (x==64) return ' ';
	if (x==65) return ',';
	if (x==66) return '.';
	if (x==67) return ':';
	if (x==68) return ';';
	if (x==69) return '\n';
	if (x==70) return '\r';
}

/// print string of trie's id-th node
void print(int id){
	if (id==0) return;
	print(parIdx[id]);
	cout << convert(parEdge[id]);
}

/// decode given encoded text
void decoding() {
	char ch;
	TRIE *root = &trie[0];
	TRIE *node = root, *nextNode;
	int END_FLAG = 0;


	// make edge for every character
	FOR(i, 0, S - 1) {
		getNext(root, i);
	}

	// decode text
	while (true) {
		scanf("%c",&ch);
		int encode = (unsigned char)ch;

		if (ch == (char)INC){
			// if inputted single byte is 'INC', then increasing curLen which means number of reading bytes
			curLen++;
			continue;
		}
		if (ch == (char)END){
			// if inputted single byte is 'END', do the last decoding
			END_FLAG = 1;
			continue;
		}
		FOR (i,2, curLen){
			scanf("%c",&ch);
			encode = encode * PrintableCnt + (unsigned char)ch;
		}
		if (curLen > 3 ) curLen = 3;

		int id = encode / S;
		int _ch = encode % S;

		print(id);
		if (END_FLAG) break;
		cout << convert(_ch);
		getNext(&trie[id], _ch);
	}

}

int main(int argc, char **argv) {
	init(argc, argv);
	decoding();
	return 0;
}