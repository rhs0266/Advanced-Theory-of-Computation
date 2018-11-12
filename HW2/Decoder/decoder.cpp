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
int curLen = 0;

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

inline int reqLen(int id) {
	// (id,ch) pair를 표현하는 데에 필요한 최소 출력 글자 수
	int target = id * (S+1);

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
	int x = id * S + ch;
	push(x, len);
}

int trieN;
struct TRIE {
public:
	TRIE() {}
	TRIE(int id) :id(id) {}
	int id;
	TRIE *next[71];
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
void print(int id){
	if (id==0) return;
	print(parIdx[id]);
	cout << convert(parEdge[id]);
}

void decoding() {
	char ch;
	TRIE *root = &trie[0];
	TRIE *node = root, *nextNode;


	// make edge for every character
	FOR(i, 0, S - 1) {
		getNext(root, i);
	}

	int temp=0;
	// decode text
	while (true) {
		scanf("%c",&ch);
		int encode = (unsigned char)ch;

		if (ch == (char)INC){
			curLen++;
			continue;
		}
		if (ch == (char)END){
			while (true) {
				scanf("%c", &ch);
				if (ch == (char) INC) {
					curLen++;
					continue;
				} else break;
			}
			encode = (unsigned char)ch;
			FOR (i, 2, curLen) {
				scanf("%c", &ch);
				encode = encode * PrintableCnt + (unsigned char) ch;
			}
			print(encode / S);
			break;
		}
		FOR (i,2, curLen){
			scanf("%c",&ch);
			encode = encode * PrintableCnt + (unsigned char)ch;
		}

		int id = encode / S;
		int _ch = encode % S;
		fprintf(out,"%d\t%d\n",id,_ch);

		print(id);
		cout << convert(_ch);
		getNext(&trie[id], _ch);
	}

}

int main() {
	freopen("../../Encoder/cmake-build-debug/encoded_file.txt","r",stdin);
	freopen("decoded_file.txt","w",stdout);
	init();
	decoding();
	return 0;
}