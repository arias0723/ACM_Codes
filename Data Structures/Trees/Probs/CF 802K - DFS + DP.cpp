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


int N, K, u, v, c;
int end_here[MAXN], end_down[MAXN], C[MAXN];
vii G[MAXN];

void solve(int p, int r, int val) {

	bool leaf = true;
	for (int i = 0; i < G[r].size(); ++i) {
		int u = G[r][i].first;
		if(u != p) {
			leaf = false;
			solve(r, u, G[r][i].second);
		}
	}

	// Init
	// end_here[r] = end_down[r] = val;
	// if(leaf) return;

	// Solve
	vii tmp;
	//int len = G[r].size();
	for (int i = 0; i < G[r].size(); ++i) {
		int u = G[r][i].first;
		if(u != p) {
			tmp.push_back(make_pair(end_here[u], u));
		}
	}
	sort(tmp.begin(), tmp.end(), greater<pii>());

	// Get k-1 best children
	int to = min((int)tmp.size(), K - 1);
	int sumtokminus1 = 0; //accumulate(tmp.begin(), tmp.begin() + to, 0);
	for (int i = 0; i < to; ++i) {
		sumtokminus1 += tmp[i].first;
	}
	int sumtok = sumtokminus1;
	if(tmp.size() > to) sumtok += tmp[to].first;

	end_here[r] = sumtokminus1;
	for (int i = 0; i < tmp.size(); ++i) {
		int u = tmp[i].second;
		if(i < to) {
			end_down[r] = max(end_down[r], end_down[u] + sumtok - tmp[i].first);
		}
		else {
			end_down[r] = max(end_down[r], end_down[u] + sumtokminus1);
		}
	}
	end_here[r] += val;
	end_down[r] += val;
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


	cin >> N >> K;
	for (int i = 1; i < N; ++i)
	{
		cin >> u >> v >> c;
		G[u].push_back(make_pair(v, c));
		G[v].push_back(make_pair(u, c));
	}

	solve(-1, 0, 0);
	int ans = end_down[0];

	cout << ans << endl;



	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}