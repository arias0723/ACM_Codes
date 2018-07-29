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

const int MAXN = 500000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 9;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


// input
int N, M, C[MAXN];
vi G[MAXN];
set<int> fillqueries, emptyqueries[MAXN];

vi queries1[MAXN], queries2[MAXN], queries3[MAXN];
int ans[MAXN];

void dfs(int p, int r, set<int>& fillqueries) {

	// init fills
	for(auto it : queries1[r]) {
		fillqueries.insert(it);
	}	

	// dfs
	for(auto v : G[r]) {
		if(v != p)
			dfs(r, v, fillqueries);
	}

	// init empty
	for(auto it : queries2[r]) {
		emptyqueries[r].insert(it);
	}	

	// solve
	for(auto v : G[r]) {
		if(v != p) {
			// small-to-large on the node sets
			if(emptyqueries[r].size() < emptyqueries[v].size()) {
				swap(emptyqueries[r], emptyqueries[v]);
			}
			// merge
			for(auto it : emptyqueries[v]) {
				emptyqueries[r].insert(it);
			}
		}
	}

	// ans queries for r
	for(int x : queries3[r]) {
		int fq = 0;
		if(fillqueries.size() > 0) {
			auto it = fillqueries.lbound(x);
			if(it != fillqueries.begin()) {
				it--;
				fq = *it;
			}
		}
		int eq = 0;
		if(emptyqueries[r].size() > 0) {
			auto it = emptyqueries[r].lbound(x);
			if(it != emptyqueries[r].begin()) {
				it--;
				eq = *it;
			}
		}
		if(eq >= fq) ans[x] = 0;
		else ans[x] = 1;
	}

	// clear fills
	for(auto it : queries1[r]) {
		fillqueries.erase(it);
	}	
}


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


	cin >> N;
	int u, v, k;
	for (int i = 1; i < N; ++i) {
		cin >> u >> v;
		G[u].pback(v);
		G[v].pback(u);
	}	
	// queries
	cin >> M;
	for (int i = 1; i <= M; ++i)
	{
		cin >> u >> v;
		if(u == 1) {
			queries1[v].pback(i);
		}
		if(u == 2) {
			queries2[v].pback(i);
		}
		if(u == 3) {
			queries3[v].pback(i);
		}
	}
	memset(ans, -1, sizeof ans);
	dfs(0, 1, fillqueries);

	for (int i = 1; i <= M; ++i) {
		if(ans[i] != -1)
			cout << ans[i] << endl;
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

