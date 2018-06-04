/**
	https://www.hackerrank.com/contests/hourrank-28/challenges/xorry-queries/submissions/code/1307959965
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
const ll MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);
const int boardi[] = {-1, -1, +0, +1, +1, +1, +0, -1};
const int boardj[] = {+0, +1, +1, +1, +0, -1, -1, -1};


int A[MAXN], cum[MAXN], xA[MAXN];

// Segment Tree
struct node {
	int l, r;
	int bitscnt[20], lazyval;
	bool lazy;

	void push(node& left, node& right) {
		// left child
		left.lazy = 1;
		left.lazyval ^= lazyval;
		left.apply_lazy(lazyval);
		// right child
		right.lazy = 1;
		right.lazyval ^= lazyval;
		right.apply_lazy(lazyval);

		lazy = 0; lazyval = 0;
	}
	void apply_lazy(int v) {
		for (int i = 0; i < 20; ++i) {
			if( v&(1<<i) ) {
				bitscnt[i] = (r - l + 1) - bitscnt[i];
			}
		}
	}
	void update(node& left, node& right) {
		for (int i = 0; i < 20; ++i) {
			bitscnt[i] = left.bitscnt[i] + right.bitscnt[i];
		}
	}
};
class STree {
public:
	STree(int N) {
		nodes.reserve(4*N);
		init(0, N - 1);
	}
	void update(const int l, const int r, int val, int root = 1) {

		node& rnode = nodes[root];

		if(rnode.r < l || rnode.l > r || rnode.l > rnode.r) {
			return;
		}

		if(rnode.l >= l && rnode.r <= r) {
			rnode.lazy = 1;
			rnode.lazyval ^= val;
			// update node state
			rnode.apply_lazy(val);

			return;
		}
		// lazy to children
		if(rnode.lazy) {
			rnode.push(nodes[2*root], nodes[2*root + 1]);
		}
		// split segment
		update(l, r, val, 2*root);
		update(l, r, val, 2*root + 1);
		// update values
		rnode.update(nodes[2*root], nodes[2*root + 1]);
	}
	ll query(const int l, const int r, int root = 1) {

		node& rnode = nodes[root];

		if(rnode.r < l || rnode.l > r || rnode.l > rnode.r) {
			return 0;
		}

		if(rnode.l >= l && rnode.r <= r) {
			ll ans = 0;
			for (int i = 0; i < 20; ++i) {
				// cout << i << ": " << rnode.bitscnt[i] << endl;
				ans += (1LL<<i) * rnode.bitscnt[i];
			}
			return ans;
		}
		// lazy to children
		if(rnode.lazy) {
			rnode.push(nodes[2*root], nodes[2*root + 1]);
		}
		// split segment
		ll v1 = query(l, r, 2*root);
		ll v2 = query(l, r, 2*root + 1);

		return v1 + v2;
	}
private:
	vector<node> nodes;
	void init(const int l, const int r, int root = 1) {
		node& rnode = nodes[root];
		rnode.l = l; rnode.r = r;
		rnode.lazyval = 0; rnode.lazy = 0;
		// init
		if(r == l) {			
			for (int i = 0; i < 20; ++i) {
				rnode.bitscnt[i] = (xA[l] & (1<<i)) > 0;
			}
			return;
		}		
		init(l, (l+r)/2, 2*root);
		init((l+r)/2 + 1, r, 2*root + 1);
		rnode.update(nodes[2*root], nodes[2*root + 1]);
	}
};

// Input
int N, M, K, P;

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


	cin >> N >> M >> P;
	for (int i = 0; i < N; ++i)
	{
		cin >> A[i];
		cum[i] = A[i];
		if(i) {
			cum[i] ^= cum[i-1];
		}
	}
	// precalc xor
	for (int i = 0; i < N; ++i) {
		if(i + P - 1 < N) {
			xA[i] = cum[i + P - 1];
			if(i) {
				xA[i] ^= cum[i-1];
			}
		}
		else {
			xA[i] = 0;
		}
		//cout << xA[i] << endl;
	}
	// solve
	STree stree(N); 
	int op, a, b;
	while(M--) {
		
		cin >> op >> a >> b;
		if(op == 1) {
			a--;
			int l = max(0, a - P + 1);
			int r = min(a, N - P);
			// cout << l << " ------- " << r << endl;
			stree.update(l, r, b);
		}
		else {
			cout <<  stree.query(a-1, b-1) << endl;
		}
		//cout << stree.query(0, N-1) << endl;
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