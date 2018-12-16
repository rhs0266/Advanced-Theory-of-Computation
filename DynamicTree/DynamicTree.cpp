#include <stdio.h>
#include <algorithm>
#define NM 100005
FILE *in=stdin,*out=stdout;
using namespace std;

struct NODE{
public:
    NODE():key(0),par(nullptr),left(nullptr),right(nullptr),pp(nullptr){}
    NODE(int _key):key(_key),par(nullptr),left(nullptr),right(nullptr),pp(nullptr){}
    NODE *par, *left, *right, *pp;
    int key;
}vertex[NM];

/*
 * isLeftChild(x)
 */
bool isLeftChild(NODE *x){
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
    } else {                    // if cur is right child
        p_cur->right = cur->left;
        if (cur->left) cur->left->par = p_cur;
        cur->left = p_cur;
    }
    cur->par = p_cur->par;
    p_cur->par = cur;
    if (cur->par) {
        if (cur->par->left == p_cur) cur->par->left = cur;
        else cur->par->right = cur;
    } else {
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

int n, Q;
void input(){
    fscanf(in,"%d %d",&n,&Q);
    for (int i=1;i<=n;i++) {
        vertex[i].key = i;
    }
}
void pro(){
    for (;Q--;){
        int type;
        fscanf(in,"%d",&type);
        if (type==1){
            int x, y;
            fscanf(in,"%d %d",&x,&y);
            link(&vertex[x], &vertex[y]);
        }else if (type==2){
            int x;
            fscanf(in,"%d",&x);
            cut(&vertex[x]);
        }else{
            int x, y;
            fscanf(in,"%d %d",&x,&y);
            fprintf(out,"%d\n",lca(&vertex[x], &vertex[y])->key);
        }
    }
}
int main(){
    input();
    pro();
    return 0;
}

