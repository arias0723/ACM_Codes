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

const int MAXN = 200000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


// STREE
template<class T>
class Stree {

public:
	Stree(int size) {
		this->size = size;
		stree.reserve(size*4);
		build(1, 0, size -1);
	}

	void updateRange(int x, int y, T val) {
		__updateRange(1, 0, this->size -1, x, y, val);
	}
	T queryRange(int x, int y) {
		return __queryRange(1, 0, this->size -1, x, y);
	}

private:
	// Funtion used for combine results of the children
	static T combine(T v1, T v2) {
		// ... reimplement for problem specifics
		return v1 + v2;
	}
	template<typename U/*, typename V*/>
	struct Node {
		U val, lazy;
		int left, right;

		Node() {}
		Node(U v, U lz) {val = v; lazy = lz;}
		Node(U v, U lz, int l, int r) {val = v; lazy = lz; left = l; right = r;}
		// Init node with default value
		void init(Node& lchild, Node& rchild) {
			// ... reimplement for problem specifics
			this->lazy = 0;
			if(this->left == this->right) {
				this->val = 0;
			}
			else {
				this->val = combine(lchild.value(), rchild.value());
			}			
		}
		// Get node value
		U value() {
			// ... reimplement for problem specifics
			return val;
		}		
		// Apply on updates
		void apply(U v) {
			// ... reimplement for problem specifics
			this->val += v*(right - left + 1);
			this->lazy += v;
		}
		// Push lazy values to node children
		void pushLazy(Node& lchild, Node& rchild) {
			// ... reimplement for problem specifics
			if(lazy) {
				lchild.apply(lazy);
				rchild.apply(lazy);
				this->lazy = 0;
			}
		}
		// Update node val with children values
		void update(Node& lchild, Node& rchild) {
			// ... reimplement for problem specifics
			this->val = combine(lchild.value(), rchild.value());
		}
	};
	vector<Node<T>> stree;
	int size;

	void build(int root, int l, int r) {

		if(r > l) {
			build(2*root, l, (l+r)/2);
			build(2*root +1, (l+r)/2 +1, r);
		}
		stree[root].left = l; stree[root].right = r;
		stree[root].init(stree[root*2], stree[root*2 + 1]);
	}
	void __updateRange(int root, int i, int j, const int l, const int r, const T val) {

		// Completely out-range
		if(i > j || i > r || j < l) return;
		// Completely in-range
		if(i >= l && j <= r) {
			// Update node and lazy value(to push() later)
			stree[root].apply(val);
			return;
		}
		// If you go down into node children, you need to:
		// 1: Push lazy stored values to children
		stree[root].pushLazy(stree[root*2], stree[root*2 + 1]);
		// 2: Split the range
		__updateRange(2*root, i, (i+j)/2, l, r, val);
		__updateRange(2*root +1, (i+j)/2 +1, j, l, r, val);
		// 3: Update node value with children values
		stree[root].update(stree[root*2], stree[root*2 + 1]);
	}
	T __queryRange(int root, int i, int j, const int l, const int r) {

		// Completely out-range
		if(i > j || i > r || j < l) return 0;
		// Completely in-range
		if(i >= l && j <= r) {
			return stree[root].value();
		}
		// Push lazy value to children
		stree[root].pushLazy(stree[root*2], stree[root*2 + 1]);
		// Partialy in-range
		T v1 = __queryRange(2*root, i, (i+j)/2, l, r);
		T v2 = __queryRange(2*root +1, (i+j)/2 +1, j, l, r);

		return combine(v1, v2);
	}


};

int N, Q, T;
int A[MAXN];

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
	int c, p, q, v;
	while(T--) {

		cin >> N >> Q;
		Stree<ll> stree(N);
		while(Q--) {
			cin >> c;
			if(c) {
				cin >> p >> q;
				cout << stree.queryRange(p-1, q-1) << endl;
			}
			else {
				cin >> p >> q >> v;
				stree.updateRange(p-1, q-1, v);
			}
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