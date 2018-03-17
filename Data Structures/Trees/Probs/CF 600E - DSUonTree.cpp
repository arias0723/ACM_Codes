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
//template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
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

const int MAXN = 100000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)



int N, M, K;
int color[MAXN], maxFreq[MAXN];
ll sum[MAXN], ans[MAXN];
map<int, ll> colorFreq[MAXN];
vi G[MAXN];

void dfs(int p, int u) {
	
	for(auto v : G[u]) {
		if(v != p) {
			dfs(u, v);
		}
	}
	// init	
	colorFreq[u][color[u]] = maxFreq[u] = 1;
	sum[u] = color[u];
	// merge
	for(auto v : G[u]) {
		if(v != p) {

			// Small-To-Large technique
			if( colorFreq[u].size() < colorFreq[v].size() ) {
				swap(colorFreq[u], colorFreq[v]);
				swap(sum[u], sum[v]);
				swap(maxFreq[u], maxFreq[v]);
			}
			// Merge to larger set
			for(auto it : colorFreq[v]) {

				int col; ll cnt; tie(col, cnt) = it;
				colorFreq[u][col] += cnt;

				ll newFreq = colorFreq[u][col];
				if(newFreq == maxFreq[u]) {
					sum[u] += col;
				}
				else if(newFreq > maxFreq[u]) {
					maxFreq[u] = newFreq;
					sum[u] = col;
				}
			}
		}
	}
	// ans
	ans[u] = sum[u];
	//cout << u << " -> " << colorFreq[u].size() << endl;
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
    for (int i = 1; i <= N; ++i) {
    	cin >> color[i];
    }
    int u, v;
    for (int i = 1; i < N; ++i) {
    	cin >> u >> v;
    	G[u].pback(v);
    	G[v].pback(u);	
    }
    dfs(-1, 1);
    for (int i = 1; i <= N; ++i) {
    	cout << ans[i] << " ";
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