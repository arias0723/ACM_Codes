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



int N, M, ans[MAXN];
vi G[MAXN];
map<int, set<string>> MP[MAXN];
string names[MAXN];
vii queries[MAXN];

void dfs(int p, int r, int level = 0) {
	// dfs
	for(auto v : G[r]) {
		if(v != p)
			dfs(r, v, level + 1);
	}
	// init
	MP[r][level].insert(names[r]);
	// solve
	for(auto v : G[r]) {
		if(v != p) {
			// small-to-large on the node sets
			if(MP[r].size() < MP[v].size()) {
				swap(MP[r], MP[v]);
			}
			// merge
			for(auto it : MP[v]) {
				// small-to-large on the different names set
				if(MP[r][it.first].size() < MP[v][it.first].size()) {
					swap(MP[r][it.first], MP[v][it.first]);
				}
				MP[r][it.first].insert( MP[v][it.first].begin(), MP[v][it.first].end() );
			}
			
		}
	}
	// queries for this node
	for(auto it : queries[r]) {
		ans[it.second] += MP[r][level + it.first].size();
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
	string name;
	int parent;
	for (int i = 1; i <= N; ++i)
	{
		cin >> name >> parent;
		names[i] = name;
		G[parent].pback(i);
		G[i].pback(parent);
	}
	cin >> M;
	int v, k;
	for (int i = 0; i < M; ++i)
	{
		cin >> v >> k;
		queries[v].pback({k, i}); 
	}

	dfs(-1, 0);

	for (int i = 0; i < M; ++i) {
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