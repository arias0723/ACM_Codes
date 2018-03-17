#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

// Add defines here ...
#define MAXN 100005
const int MOD = 2537;
const int INF = 1e9;

// Function to apply in the ranges
inline int f(int a, int b) {return (a>b)?a:b;}

// STree
struct STree {
	int stree[4*MAXN];

	void build(int r, int b, int e) {
		if(b == e) {
			stree[r] = 0;
			return;
		}
		build(2*r, b, (b+e)/2);
		build(2*r +1, (b+e)/2 +1, e);
		stree[r] = f(stree[2*r], stree[2*r +1]);
	}
	void update(int r, int b, int e, const int pos, const int val) {

		if(b > e || e < pos || b > pos) return;
		if(b >= pos && e <= pos) {
			stree[r] = val;
			return;
		}
		update(2*r, b, (b+e)/2, pos, val);
		update(2*r +1, (b+e)/2 +1, e, pos, val);
		stree[r] = f(stree[2*r], stree[2*r +1]);
	}
	int query(int r, int b, int e, const int B, const int E) {

		if(b > e || e < B || b > E) return 0;
		if(b >= B && e <= E) {
			return stree[r];
		}
		int v1 = query(2*r, b, (b+e)/2, B, E);
		int v2 = query(2*r +1, (b+e)/2 +1, e, B, E);
		return f(v1, v2);
	}
};
STree stree;

// Heavy Light
struct HLD {

    int n, curhead, curloc;
    vi sz;						// Size of subtree rooted at u
    vi parent;					// Parent of u
    vi depth;					// Depth of u in the tree
    vi head;					// First node in the chain containing u
    vi location;				// Location of node u in the segment tree
    vvi adj;					// Adj matrix of tree

    HLD(int N) : n(N), sz(N, 1), parent(N, -1), depth(N, 0), head(N), location(N), adj(N) {
    	stree.build(1, 0, N-1);
    }
    int dfs(int u) {
    	sz[u] = 1;
        for(int i = 0; i < (int)adj[u].size(); ++i)
		if (adj[u][i] != parent[u]) {

			parent[adj[u][i]] = u;
			depth[adj[u][i]] = depth[u] + 1;
			sz[u] += dfs(adj[u][i]);
		}
        return sz[u];
    }
	void decompose(int u) {
		head[u] = curhead;
		location[u] = curloc++;
		int best = -1;
		for(int i = 0; i < (int)adj[u].size(); ++i)
		if (adj[u][i] != parent[u] && (best == -1 || sz[adj[u][i]] > sz[best]))
			best = adj[u][i];

		if (best != -1) decompose(best);

		for(int i = 0; i < (int)adj[u].size(); ++i)
		if (adj[u][i] != parent[u] && adj[u][i] != best)
			decompose(curhead = adj[u][i]);
	}
    // Assume that v is an ancestor of u in the tree, so you compute the f(x)
    // in the range [v+1, u] because weight is stored in the child node of the edge
	int query_upto(int u, int v) {
		int res = 0;
		while (head[u] != head[v]) {
			res = f( res, stree.query(1, 0, n-1, location[head[u]], location[u]) );
			u = parent[head[u]];
		}
		res = f( res, stree.query(1, 0, n-1, location[v] +1, location[u]) );
		return res;
	}

	// Public Methods
    void build(int root = 0) {
    	curhead = root; curloc = 0;
    	dfs(root);
    	decompose(curhead);
    }
    int LCA(int u, int v) {
    	while (head[u] != head[v]) {
			if (depth[head[u]] > depth[head[v]])
				u = parent[head[u]];
			else
				v = parent[head[v]];
    	}
    	return depth[u] < depth[v] ? u : v;
    }
    void add_edge(int u, int v) { adj[u].push_back(v), adj[v].push_back(u); }
    void update_edge(int u, int v, int c) {
    	// Values of edges are stored in child nodes
        if (parent[v] == u) swap(u, v);
        assert(parent[u] == v);
        stree.update(1, 0, n-1, location[u], c);
    }
    int query(int u, int v) {
    	int l = LCA(u, v);
        return f(query_upto(u, l), query_upto(v, l));
    }
};

// Input
int T, N, a, b, c, pos, val;
struct edge {int a, b, c;};
vector<edge> edges;
char cmd[10];


int main() {

	//Input region
	#ifndef ONLINE_JUDGE
	system("notepad.exe name.in");
	freopen("name.in", "r", stdin);
	FILE * FILE_NAME = freopen("name.out", "w", stdout);
	int TIME = clock();
	#endif


	//Add your code here...
	std::ios::sync_with_stdio(false); cin.tie(0);

	cin >> T;
	while(T --) {

		cin >> N;
		HLD hld(N);
		edges.clear();
		// get edges
		for (int i = 0; i < N-1; ++i) {
			cin >> a >> b >> c;
			a--, b--;
			edges.push_back( (edge){a, b, c} );
			hld.add_edge(a, b);
		}
		hld.build();

		for (int i = 0; i < N-1; ++i) {
			edge ed = edges[i];
			hld.update_edge(ed.a, ed.b, ed.c);
		}
		while(1) {
			cin >> cmd;
			if(cmd[0]=='D') break;

			if(cmd[0]=='C') {
				cin >> pos >> val;
				pos --;
				hld.update_edge(edges[pos].a, edges[pos].b, val);
			}
			else {
				cin >> a >> b;
				a--, b--;
				cout << hld.query(a, b) << endl;
			}
		}
	}

	//cout << ans << endl;


	//Output region
	#ifndef ONLINE_JUDGE
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("notepad.exe name.out");
	#endif

	return 0;
}

