/*
http://codeforces.com/contest/734/problem/E
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
const int MAXN = 200000 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
 

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


int N, K ;
vi T[MAXN], cT[MAXN];

int color[MAXN];
int degree[MAXN]; // out degree of nodes
int level[MAXN], diam, rad;
set<int> centers;	// max centers always 2

// Condense the tree (by color of the node)
void dfs(int p, int r, int cond_p) {

	// create condensed graph
	if(color[r] != color[cond_p]) {
		cT[cond_p].push_back(r);
		// for center degree
		degree[cond_p] ++;
		cT[r].push_back(cond_p);
		// for center degree
		degree[r] ++;

		//cout << cond_p << ", " << r << endl;
		cond_p = r;			
	}

	for (int i = 0; i < T[r].size(); ++i) {

		int u = T[r][i];
		if(u != p) {			
			dfs(r, u, cond_p);
		}
	}
}

// Center of tree
void bfs(vi T[]) {

	queue<int> Q;
	int maxlevel = -1;

	// first leaves
	for (int i = 0; i < N; ++i) {
		if(degree[i] == 1) {
			Q.push(i);
			level[i] = 0;
		}
	}

	while(!Q.empty()) {

		int l = Q.front(); Q.pop();
		maxlevel = max(maxlevel, level[l]);

		for (int i = 0; i < T[l].size(); ++i)
		{
			int u = T[l][i];
			degree[u] --;
			// it's the parent
			if(degree[u] == 1) {
				level[u] = level[l] + 1;
				Q.push(u);
			}
		}
	}

	//cout << maxlevel << endl;
	// calc centers
	for (int i = 0; i < N; ++i)
	{
		if(maxlevel!=-1 && level[i] == maxlevel) {
			centers.insert(i);
		}
	}
	// calc diam & rad
	if(maxlevel != -1) {
		diam = 2*maxlevel + centers.size() - 1;
		rad = (diam + 1) / 2;
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
	for (int i = 0; i < N; ++i)
	{
		cin >> color[i];
	}
	int u, v;
	for (int i = 1; i < N; ++i)
	{
		cin >> u >> v;
		u --, v --;
		T[u].push_back(v);
		T[v].push_back(u);				
	}

	dfs(-1, 0, 0);
	// for (int i = 0; i < N; ++i) cout << degree[i] << " ";
	// cout << endl;
	bfs(cT);

	cout << rad << endl;

	// cout << diam << "  " << rad << endl;
	// for(set<int>::iterator it = centers.begin(); it != centers.end(); ++it)
	// 	cout << *it << " ";





	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}