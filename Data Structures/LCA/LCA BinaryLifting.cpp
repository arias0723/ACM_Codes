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
int A[MAXN], order_start[MAXN], order_end[MAXN], order_pos;

// LCA + Binary Lifting
void dfs(int p, int r) {

	sparse[r][0] = p;
	level[r] = level[p] + 1;
	order_start[r] = order_pos;
	order_pos ++;
	for (int i = 0; i < G[r].size(); ++i) {
		int u = G[r][i];
		if(u != p)
			dfs(r, u);
	}
	order_end[r] = order_pos - 1;
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
int kth_ancs(int u, int k) {
	if(k < 0) return 0;
	for (int i = MAXNLOG - 1; i >= 0; --i) {
		if (k & (1<<i)) 
			u = sparse[u][i];
	}
	return u;
}
// Using dfs order to determine if u == v or u is ancestor of v
bool is_ancs(int u, int v) {
	return (order_start[v] >= order_start[u] && order_start[v] <= order_end[u]);
}
// LCA using binary lifting. First put nodes on the same level, 
// next lift the nodes to the children-level of the lca.
int LCA(int u, int v) {

	if (level[u] < level[v]) swap(u, v);
	int ldif = level[u] - level[v];
	u = kth_ancs(u, ldif);

	//cout << "nodes: " << u << " " << v << endl;

	if (u == v) return u;

	for (int i = MAXNLOG - 1; i >= 0; --i) 
		if (sparse[u][i] != sparse[v][i]) {
			u = sparse[u][i];
			v = sparse[v][i];
			//cout << "nodes(kth=" << i << "): " << u << " " << v << endl;
	}
	// u and v are at children-level of the lca, so lca is the parent.
	return sparse[u][0];
}



// Node 0 is parent of the root
dfs(0, r);
build_sparse();
