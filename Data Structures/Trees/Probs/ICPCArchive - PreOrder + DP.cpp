/*
	https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&category=508&page=show_problem&problem=3788
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
const int MAXN = 100000 + 5;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
 

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


int N, K, W[MAXN];

int preorder[MAXN], nxt[MAXN], pcnt;
int dp[1005][MAXN];


void dfs(vi G[], int p, int r) {

	preorder[pcnt ++] = r;
	for (int i = 0; i < G[r].size(); ++i)
	{
		int u = G[r][i];
		if(p != u) {
			dfs(G, r, u);
		}
	}
	nxt[r] = pcnt;
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

	

	int p, w, root;
	while(cin >> N >> K/*, N + K*/) {

		if(N == 0 && K == 0)
			break;

		// init
		//memset(preorder, 0, sizeof preorder);
		//memset(nxt, 0, sizeof nxt);
		//memset(dp, 0, sizeof dp);
		pcnt = 0;
		vi G[N+5];
		// for (int i = 0; i <= N; ++i) {
		// 	G[i].clear();
		// }

		// input
		for (int i = 1; i <= N; ++i)
		{
			cin >> p >> w;
			if(p == 0) 
				root = i;
			else {
				G[p].push_back(i);
				G[i].push_back(p);
			}
			W[i] = w;			
		}

		// solve
		dfs(G, -1, root);

		// for (int i = 0; i <= N; ++i) {
		// 	cout << preorder[i] << " " << nxt[preorder[i]] << endl;
		// }
		// cout << endl;

		for (int i = 1; i <= K; ++i)
		{
			dp[i][N] = 0;
			for (int j = N-1; j >= 0; --j)
			{
				int u = preorder[j];
				dp[i][j] = max( dp[i][j+1], dp[i-1][nxt[u]] + W[u] );
			}
		}

		cout << dp[K][0] << endl;
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