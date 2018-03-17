/*
http://codeforces.com/problemset/problem/592/D
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
const int MAXN = 123456 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
 

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


int N, M;
vi G[MAXN];
bool attack[MAXN];

int maxLevel, minNode1 = MAXN, minNode2 = MAXN, sumEdges;
bool canGo[MAXN];

void findDiameter1(int p, int r, int level) {

	for (int i = 0; i < G[r].size(); ++i) {
		int u = G[r][i];
		if(u != p) {
			findDiameter1(r, u, level + 1);
			if(canGo[u])
				canGo[r] = 1;
		}		
	}
	//
	if(attack[r]) {
		canGo[r] = 1;
		if(level == maxLevel) {
			minNode1 = min(r, minNode1);
		}
		else if(level > maxLevel) {
			maxLevel = level;
			minNode1 = r;
		}
	}
}
void findDiameter2(int p, int r, int level) {

	for (int i = 0; i < G[r].size(); ++i) {
		int u = G[r][i];
		if(u != p && canGo[u]) {
			sumEdges += 2;
			findDiameter2(r, u, level + 1);
		}		
	}
	//
	if(attack[r]) {
		if(level == maxLevel) {
			minNode2 = min(r, minNode2);
		}
		else if(level > maxLevel) {
			maxLevel = level;
			minNode2 = r;
		}
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

	

	cin >> N >> M;
	int u, v;
	for (int i = 0; i < N-1; ++i)
	{
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);	
	}
	for (int i = 0; i < M; ++i) {
		cin >> u;
		attack[u] = 1;
	}

	// solve
	findDiameter1(-1, u, 0);
	//maxLevel = 0;
	findDiameter2(-1, minNode1, 0);

	// for (int i = 1; i <= N; ++i) {
	// 	cout << canGo[i] << " ";
	// }

	cout << min(minNode1, minNode2) << endl;
	// cout << sumEdges << endl;
	// cout << maxLevel << endl;
	cout << sumEdges - maxLevel << endl;




	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}