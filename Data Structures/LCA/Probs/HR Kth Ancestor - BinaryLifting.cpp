/*
	https://www.hackerrank.com/challenges/kth-ancestor/problem
*/

#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
 
// Add defines here ...
const int MAXN = 100000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
 

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


int N, M, Q;
vi G[MAXN];
int sparse[MAXN][MAXNLOG], level[MAXN];
bool is[MAXN];


// LCA + Binary Lifting

void dfs(int p, int r) {

	sparse[r][0] = p;
	level[r] = level[p] + 1;
	for (int i = 0; i < G[r].size(); ++i) {
		int u = G[r][i];
		if(u != p)
			dfs(r, u);
	}
}
// Build sparse table. sparse[i][j] = for node i get the (2^j)-th parent
void build_sparse() {

	for (int j = 1; j < MAXNLOG; ++j) {
		for (int i = 1; i < MAXN; ++i) {
			sparse[i][j] = sparse[sparse[i][j-1]][j-1];
		}
	}
}
// Kth parent of node u (binary lifting). If not exist return 0.
int find_kth(int u, int k) {
	
	for (int i = MAXNLOG; i >= 0; --i) {
		if(u && (1<<i) <= k) {
			u = sparse[u][i];
			k -= (1<<i);
		}
	}
	return (k) ? 0 : u;
}

// Solve
void add_node(int x, int p) {
	sparse[x][0] = p;
	for (int j = 1; j < MAXNLOG; ++j) {
		sparse[x][j] = sparse[sparse[x][j-1]][j-1];
	}
	is[x] = 1;
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


	// Init
	int T, x, y;
	cin >> T;
	while(T --) {

		int r = 1;
		cin >> N;

		// init
		memset(is, 0, sizeof is);
		for (int i = 0; i < MAXN; ++i) {
			G[i].clear();
		}

		for (int i = 0; i < N; ++i)
		{
			cin >> x >> y;
			is[x] = 1;
			if(y == 0) r = x;
			else {
				G[x].push_back(y);
				G[y].push_back(x);	
			}
		}

		// Node 0 is mark to the root
		dfs(0, r);
		build_sparse();

		cin >> Q;
		int op;
		while(Q --) {

			cin >> op;
			if(op == 0) {

				cin >> y >> x;
				add_node(x, y);
			}	
			else if(op == 1) {

				cin >> x;
				is[x] = 0;
			}
			else {

				cin >> x >> y;
				if(! is[x]) cout << 0 << endl;
				else cout << find_kth(x, y) << endl;
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