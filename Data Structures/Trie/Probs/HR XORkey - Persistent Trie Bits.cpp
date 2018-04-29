/**
	https://www.hackerrank.com/challenges/xor-key/problem
**/
#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
// find_by_order(k): 	iterator to the k-th largest element (counting from zero)
// order_of_key(val):	number of items strictly smaller than val
template <class T> using StdTreap = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
// Add defines here ...
#define endl '\n'
#define F0R(i, a) for (int i = 0; i < (a); ++i)
//#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (b)-1; i >= a; --i)
#define F0RR(i, a) for (int i = (a)-1; i >= 0; --i)
#define REP(i,n) for ( int i=0; i<int(n); i++ )
#define REP1(i,a,b) for ( int i=(a); i<=int(b); i++ )
#define REPeste(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define FOR(it,c) for ( auto it=(c).begin(); it!=(c).end(); it++ )
#define mp make_pair
#define pback push_back
#define lbound lower_bound
#define ubound upper_bound 
#define popcount __builtin_popcount

const int MAXN = 100000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 9;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)



// Input
struct node {
	int cnt;
	node *left, *right; 
};
int trieSz;
node trieNodes[100 * MAXN];

node* addNode() {
	trieNodes[trieSz].cnt = 0;
	trieNodes[trieSz].left = 0;
	trieNodes[trieSz].right = 0;
	return &(trieNodes[trieSz ++]);
}

void init(node* r, int depth = 16) {
	if(depth < 0) return;

	r->left = addNode();
	init(r->left, depth - 1);

	r->right = addNode();
	init(r->right, depth - 1);
}
node* insert(node* r, int x, int depth = 16) {

	node* nr = addNode();
	if(depth < 0) {
		nr->cnt = r->cnt + 1;		
		return nr;
	}

	int mask = x&(1<<depth);
	if(mask) {
		node* rch = insert(r->right, x, depth - 1);
		nr->right = rch;
		nr->left = r->left;
		nr->cnt = r->cnt + 1;
	}
	else {
		node* lch = insert(r->left, x, depth - 1);
		nr->left = lch;
		nr->right = r->right;
		nr->cnt = r->cnt + 1;
	}
	return nr;
}
int paralellQuery(node* frontRoot, node* backRoot, int x, int depth = 16) {

	if(depth < 0) {
		return 0;
	}

	int mask = x&(1<<depth);
	if(mask) {
		if( (frontRoot->left->cnt - backRoot->left->cnt) > 0 ) {
			return paralellQuery(frontRoot->left, backRoot->left, x, depth - 1) | (1<<depth);
		}
		return paralellQuery(frontRoot->right, backRoot->right, x, depth - 1);
	}
	else {
		if( (frontRoot->right->cnt - backRoot->right->cnt) > 0 ) {
			return paralellQuery(frontRoot->right, backRoot->right, x, depth - 1) | (1<<depth);
		}
		return paralellQuery(frontRoot->left, backRoot->left, x, depth - 1);
	}
}

int T, N, Q, ni, a, p, q;
node* roots[MAXN];
int roots_cnt;


int main() {

	//Input region
	#ifdef GHOST
	system("subl name.in");
	freopen("name.in", "r", stdin);
	FILE * FILE_NAME = freopen("name.out", "w", stdout);
	int TIME = clock();
	#endif

	std::ios::sync_with_stdio(false); cin.tie(0);
	//Add your code here...


	cin >> T;
	while(T --) {

		cin >> N >> Q;

		trieSz = roots_cnt = 0;
		roots[roots_cnt] = addNode();
		init( roots[0] );
		roots_cnt ++;

		for (int i = 0; i < N; ++i)
		{
			cin >> ni;
			roots[roots_cnt] = insert(roots[roots_cnt - 1], ni);
			roots_cnt ++;
		}

		while(Q--) {

			cin >> a >> p >> q;
			cout << paralellQuery(roots[q], roots[p-1], a) << endl;
		}
	}



	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}