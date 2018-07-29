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
/*struct STree {
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
STree stree;*/

// Heavy Light
struct node {
	int end, w;
};
struct HLD {

    int n, curhead, curloc;
    vi sz;						// Size of subtree rooted at u
    vi parent;					// Parent of u
    vi depth;					// Depth of u in the tree
    vi head;					// First node in the chain containing u
    vi location;				// Location of node u in the segment tree
    vector<vector<node> > adj;	// Adj matrix of tree

    vi dist;
    vi decompChain;

    HLD(int N) : n(N), sz(N, 1), parent(N, -1), depth(N, 0), head(N), location(N), adj(N), dist(N, 0), decompChain(N) {
    	//stree.build(1, 0, N-1);
    }
    int dfs(int u) {
    	sz[u] = 1;
        for(int i = 0; i < (int)adj[u].size(); ++i)
		if (adj[u][i].end != parent[u]) {

			parent[adj[u][i].end] = u;
			depth[adj[u][i].end] = depth[u] + 1;
			dist[adj[u][i].end] = dist[u] + adj[u][i].w;
			sz[u] += dfs(adj[u][i].end);
		}
        return sz[u];
    }
	void decompose(int u) {
		head[u] = curhead;
		decompChain[curloc] = u;
		location[u] = curloc++;
		int best = -1;
		for(int i = 0; i < (int)adj[u].size(); ++i)
		if (adj[u][i].end != parent[u] && (best == -1 || sz[adj[u][i].end] > sz[best]))
			best = adj[u][i].end;

		if (best != -1) decompose(best);

		for(int i = 0; i < (int)adj[u].size(); ++i)
		if (adj[u][i].end != parent[u] && adj[u][i].end != best)
			decompose(curhead = adj[u][i].end);
	}
    // Assume that v is an ancestor of u in the tree, so you compute the f(x)
    // in the range [v+1, u] because weight is stored in the child node of the edge
	/*int query_upto(int u, int v) {
		int res = 0;
		while (head[u] != head[v]) {
			res = f( res, stree.query(1, 0, n-1, location[head[u]], location[u]) );
			u = parent[head[u]];
		}
		res = f( res, stree.query(1, 0, n-1, location[v] +1, location[u]) );
		return res;
	}*/

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
    void add_edge(int u, int v, int w) { adj[u].push_back((node){v, w}), adj[v].push_back((node){u, w}); }
    /*void update_edge(int u, int v, int c) {
    	// Values of edges are stored in child nodes
        if (parent[v] == u) swap(u, v);
        assert(parent[u] == v);
        stree.update(1, 0, n-1, location[u], c);
    }*/
    int query_dist(int u, int v) {
    	int l = LCA(u, v);
        return dist[u] + dist[v] - 2*dist[l];
    }
    int kth_downto(int l, int u, int kth) {

    	while(depth[head[u]] - depth[l] >= kth)
    		u = parent[head[u]];

    	// head[u] and lca in same chain
    	if(head[l] == head[u]) {
    		return decompChain[location[l] + kth -1];
    	}
    	kth -= (depth[head[u]] - depth[l]);
    	return decompChain[location[head[u]] + kth -1];
    }
    int query_kth(int u, int v, int kth) {
    	int l = LCA(u, v);
    	int cnt = depth[u] - depth[l] +1;
    	if(kth <= cnt) {
    		return kth_downto(l, u, cnt - kth + 1);
    	}
    	return kth_downto(l, v, kth - cnt + 1);
    }
};

// Input
int T, N, a, b, c, pos, val;
//struct edge {int a, b, c;};
//vector<edge> edges;
char cmd[10];


int main() {



	//Add your code here...
	std::ios::sync_with_stdio(false); cin.tie(0);

	cin >> T;
	while(T --) {

		cin >> N;
		HLD hld(N);
		//edges.clear();
		// get edges
		for (int i = 0; i < N-1; ++i) {
			cin >> a >> b >> c;
			a--, b--;
			//edges.push_back( (edge){a, b, c} );
			hld.add_edge(a, b, c);
		}
		hld.build();

		/*for (int i = 0; i < N; ++i) {
			cout << hld.decompChain[i] + 1 << endl;
		}*/

		/*for (int i = 0; i < N-1; ++i) {
			edge ed = edges[i];
			hld.update_edge(ed.a, ed.b, ed.c);
		}*/
		while(1) {
			cin >> cmd;
			if(cmd[0]=='D' && cmd[1]=='O') break;

			if(cmd[0]=='D') {
				cin >> a >> b;
				a--, b--;
				cout << hld.query_dist(a, b) << endl;
			}
			else {
				cin >> a >> b >> c;
				a--, b--;
				cout << hld.query_kth(a, b, c) +1 << endl;
			}
		}
	}

	//cout << ans << endl;


	return 0;
}

