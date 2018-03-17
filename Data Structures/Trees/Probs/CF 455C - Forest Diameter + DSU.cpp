/*
	http://codeforces.com/problemset/problem/455/C
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
const int MAXN = 300000 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
 

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


int N, M, q ;
vi T[MAXN];

// Union find vertex of the same tree
int C[MAXN];

int find(int k) {
    while(C[k] >= 0) {
       	k = C[k];
    }
    return k;
}
int unite(int k1, int k2) {
    k1 = find(k1);
    k2 = find(k2);
    if(k1 != k2) {
    	// the k1 set is larger then k2 set
        if(C[k1] < C[k2]) {	
            int tmp = k1;
			k1 = k2;
			k2 = tmp;
        }
	    C[k2] += C[k1];
	    C[k1] = k2;
    }
    // the component joined
    return k2;
}

// Center of tree
//set<int> centers;	// max centers always 2
int degree[MAXN]; // out degree of nodes
int level[MAXN], diam[MAXN], maxlevel[MAXN], centers[MAXN];

void bfs(vi T[]) {

	queue<int> Q;
	memset(maxlevel, -1, sizeof maxlevel);

	for (int i = 0; i < N; ++i) {
		// leaves (0) or isolated nodes (1)
		if(degree[i] == 1 || degree[i] == 0) {
			Q.push(i);
			level[i] = 0;
		}
	}

	while(!Q.empty()) {

		int l = Q.front(); Q.pop();
		int lc = find(l);
		maxlevel[lc] = max(maxlevel[lc], level[l]);

		for (int i = 0; i < T[l].size(); ++i) {
			int u = T[l][i];
			degree[u] --;
			// parent becomes a leave
			if(degree[u] == 1) {
				level[u] = level[l] + 1;
				Q.push(u);
			}
		}
	}
	// Cnt of centers by componets
	for (int i = 0; i < N; ++i) {
		int nc = find(i);
		if(maxlevel[nc] !=-1 && level[i] == maxlevel[nc]) {
			centers[nc] ++;
		}
	}
	// Diameters of componets
	for (int i = 0; i < N; ++i) {
		int nc = find(i);
		diam[nc] = max( 0, 2*maxlevel[nc] + centers[nc] - 1 );
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


	// Init
	memset(C, -1, sizeof C);
	
	cin >> N >> M >> q;
	int u, v;
	for (int i = 0; i < M; ++i)
	{
		cin >> u >> v;
		u --, v --;
		T[u].push_back(v);
		degree[u] ++;
		T[v].push_back(u);
		degree[v] ++;

		// join components
		unite(u, v);
	}

	// Solve
	bfs(T);

	// int c = find(4);
	// cout << c << " : " << diam[c] << endl;

	int x, y;
	while(q--) {

		int op;
		cin >> op;
		if(op == 1) {
			cin >> x;
			x --;
			int c = find(x);
			cout << diam[c] << endl; 
		}
		else {
			cin >> x >> y;
			x --, y --;
			int k1 = find(x);
			int k2 = find(y);
			if(k1 != k2) {
				int c = unite(x, y);
				//cout << diam[k1] << " : " << diam[k2] << " : ";
				diam[c] =  max( max(diam[k1], diam[k2]), (diam[k1]+1)/2 + (diam[k2]+1)/2 + 1 );
				//cout << diam[c] << endl;
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