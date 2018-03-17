/*
	http://codeforces.com/contest/916/problem/E
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
int A[MAXN], order_start[MAXN], order_end[MAXN], curr_root, order_pos;
int pos_nodes[MAXN];

// LCA + Binary Lifting
void dfs(int p, int r) {

	sparse[r][0] = p;
	level[r] = level[p] + 1;
	order_start[r] = order_pos;
	pos_nodes[order_pos] = r;
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


// Lazy segment tree
class STREE {

private:
	//static const int MOD = 1000000009;
	int size;
	vector<ll> stree;
	vector<ll> lazy;

	void __build(int root, int l, int r) {

		if(r > l) {
			__build(2*root, l, (l+r)/2);
			__build(2*root +1, (l+r)/2 +1, r);
		}

		if(l == r) {
			stree[root] = A[ pos_nodes[l] - 1 ];
			lazy[root] = 0;
		}
		else {
			stree[root] = stree[2*root] + stree[2*root + 1];
			lazy[root] = 0;
		}
	}

	// A node is always updated. Lazy is pushed to children when needed to go down
	void __pushLazy(int root, ll lazyValue, int l, int r) {

		int mid = (l+r)/2;

		stree[root*2] += lazyValue*(mid-l+1);
		//stree[root*2] %= MOD;
		lazy[root*2] += lazyValue;
		//lazy[root*2] %= MOD;

		stree[root*2 +1] += lazyValue*(r-mid);
		// stree[root*2 +1] %= MOD;
		lazy[root*2 +1] += lazyValue;
		// lazy[root*2 +1] %= MOD;

		lazy[root] = 0;
	}

	void __updateRange(int root, int i, int j, const int l, const int r, const ll val) {

		// Completely out-range
		if(i > j || i > r || j < l) return;

		// Completely in-range
		if(i >= l && j <= r) {
			// Update node and lazy value(to push() later)
			stree[root] += val*(j-i+1);
			//stree[root] %= MOD;
			lazy[root] += val;
			//lazy[root] %= MOD;

			return;
		}

		// If you go down into node children, you need to:
		// 1: Push lazy stored values
		// 2: Split the range
		// 3: Update node value with children values

		// Push lazy value to children
		__pushLazy(root, lazy[root], i, j);

		// Partialy in-range
		__updateRange(2*root, i, (i+j)/2, l, r, val);
		__updateRange(2*root +1, (i+j)/2 +1, j, l, r, val);

		// Update parent value
		stree[root] = stree[root*2] + stree[root*2 +1];
	}

	llu __queryRange(int root, int i, int j, const int l, const int r) {

		// Completely out-range
		if(i > j || i > r || j < l) return 0;

		// Completely in-range
		if(i >= l && j <= r) {
			return stree[root];
		}

		// Push lazy value to children
		__pushLazy(root, lazy[root], i, j);
		// Partialy in-range
		llu v1 = __queryRange(2*root, i, (i+j)/2, l, r);
		llu v2 = __queryRange(2*root +1, (i+j)/2 +1, j, l, r);

		return v1 + v2;
	}

public:
	STREE() {
		this->size = 0;
	}

	void createStree(int size) {
		this->size = size;

		stree.assign(size*4, 0);
		lazy.assign(size*4, 0);

		__build(1, 0, size - 1);
	}
	void updateRange(int x, int y, int val) {
		__updateRange(1, 0, this->size -1, x, y, val);
	}
	llu queryRange(int x, int y) {
		return __queryRange(1, 0, this->size -1, x, y);
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


	cin >> N >> Q;

	for (int i = 0; i < N; ++i) {
		cin >> A[i];
	}
	int u, v;
	for (int i = 1; i < N; ++i) {
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	// init
	curr_root = 1;
	dfs(0, 1);
	build_sparse();
	STREE S;
	S.createStree(N);

	// for (int i = 1; i <= order_pos; ++i)
	// {
	// 	cout << order_start[i] << " " << order_end[i] << endl;
	// }

	int op, x;
	while(Q--) {

		cin >> op;
		if(op == 1) {
			cin >> v;
			curr_root = v;
		} 
		else if(op == 2) {

			cin >> u >> v >> x;

			int lca = LCA(u, v);
			if(is_ancs(lca, curr_root)) {

				int lca1 = LCA(curr_root, u);
				int lca2 = LCA(curr_root, v);
				int modlca = (level[lca1] > level[lca2]) ? lca1 : lca2;

				S.updateRange(0, N - 1, x);
				int ldif = level[curr_root] - level[modlca] - 1;
				int ancs = kth_ancs(curr_root, ldif);
				if(ancs)
					S.updateRange(order_start[ancs], order_end[ancs], -x);
			}
			else {

				S.updateRange(order_start[lca], order_end[lca], x);
			}			
		}
		else {

			cin >> v;
			ll sum = 0;

			if(is_ancs(v, curr_root)) {

				sum = S.queryRange(0, N - 1);

				int ldif = level[curr_root] - level[v] - 1;
				int ancs = kth_ancs(curr_root, ldif);				
				if(ancs)
					sum -= S.queryRange(order_start[ancs], order_end[ancs]);
			}
			else {
				sum = S.queryRange(order_start[v], order_end[v]);
			}
			cout << sum << endl;
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