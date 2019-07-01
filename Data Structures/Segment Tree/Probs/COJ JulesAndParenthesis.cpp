/**
    http://coj.uci.cu/24h/problem.xhtml?pid=4075
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

const int MAXN = 100005 + 5, MAXNLOG = 25;
const ll MOD = 998244353;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);
const int boardi[] = {-1, -1, +0, +1, +1, +1, +0, -1};
const int boardj[] = {+0, +1, +1, +1, +0, -1, -1, -1};



// Input
int N, M, Q, P, K;
char A[MAXN];


// Segment Tree
struct data {int opened, closed;};
struct node {
	int l, r;
	data val;

	void apply_update(node& left, node& right) {
		val.opened = right.val.opened + left.val.opened - min(left.val.opened, right.val.closed);
		val.closed = left.val.closed + right.val.closed - min(left.val.opened, right.val.closed);
	}
	data get_val() {
		return val;
	}
};
class STree {
public:
	STree(int N) {
		nodes.reserve(4 * N);
		init(0, N - 1);
	}
	void update(const int l, const int r, const data val, int root = 1) {

		node& rnode = nodes[root];

		if(rnode.r < l || rnode.l > r || rnode.l > rnode.r) {
			return;
		}
		if(rnode.l >= l && rnode.r <= r) {
			// update node state
			rnode.val = val;
			return;
		}
		// split segment
		update(l, r, val, 2*root);
		update(l, r, val, 2*root + 1);
		// update values
		rnode.apply_update(nodes[2*root], nodes[2*root + 1]);
	}
	data query(const int l, const int r, int root = 1) {

		node& rnode = nodes[root];

		if(rnode.r < l || rnode.l > r || rnode.l > rnode.r) {
			return {0, 0};
		}
		if(rnode.l >= l && rnode.r <= r) {
			// calc node value
			return rnode.get_val();
		}
		// split segment
		data le = query(l, r, 2*root);
		data ri = query(l, r, 2*root + 1);

		int opnd = ri.opened + le.opened - min(le.opened, ri.closed);
		int clsd = le.closed + ri.closed - min(le.opened, ri.closed);

		return {opnd, clsd};
	}
private:
	vector<node> nodes;
	void init(const int l, const int r, int root = 1) {
		// init node
		node& rnode = nodes[root];
		rnode.l = l; rnode.r = r;
		rnode.val = {0, 0};
		// leaf nodes
		if(r == l) {			
			if(A[l] == '(')
				rnode.val = {1, 0};
			else
				rnode.val = {0, 1};
			return;
		}
		init(l, (l+r)/2, 2*root);
		init((l+r)/2 + 1, r, 2*root + 1);
		rnode.apply_update(nodes[2*root], nodes[2*root + 1]);
	}
};


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

	
	cin >> A;
	int openCost, closeCost, op, a, b, len = strlen(A);
	cin >> Q >> openCost >> closeCost >> K;

	STree stree(len);

	while(Q--) {

		cin >> op;
		if(op == 1) {
			cin >> a;
			a--;
			if(A[a] == '(') {
				A[a] = ')';
				stree.update(a, a, {0, 1});
			}
			else {
				A[a] = '(';
				stree.update(a, a, {1, 0});
			}
		}
		else {
			cin >> a >> b;
			data ans = stree.query(a-1, b-1);

			// cout << "[" << a-1 << ", " << b-1 << "] -> " << ans.opened << ", " << ans.closed << endl;  

			if( (ans.opened + ans.closed) % 2 == 0 && 
				(ans.opened + 1)/2 + (ans.closed + 1)/2 <= K ) {
				cout << ((ans.opened + 1)/2)*openCost + ((ans.closed + 1)/2)*closeCost << endl;
			} 
			else {
				cout << "Impossible" << endl;
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