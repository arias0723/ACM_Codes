/*
	http://codeforces.com/contest/894/problem/D
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
const int MAXN = 2000005;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
 
// Input

#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)

int N, M, K, X;
int tree[MAXN];
vi mergeArr[MAXN];
vll mergeSum[MAXN];

void mergeSort(int r = 1) {

	// out of tree
	if(r > N) {
		return;
	}

	// divide ...
	mergeSort(LCHILD(r));
	mergeSort(RCHILD(r));

	// ... and merge
	int left = LCHILD(r);
	int right = RCHILD(r);
	int lptr = 0, rptr = 0;
	int suml = tree[left], sumr = tree[right];

	mergeArr[r].push_back(0);	// dist to itself
	while(lptr < mergeArr[left].size() && rptr < mergeArr[right].size()) {

		if(suml + mergeArr[left][lptr] < sumr + mergeArr[right][rptr]) {
			mergeArr[r].push_back(suml + mergeArr[left][lptr]);
			lptr ++;
		}
		else {
			mergeArr[r].push_back(sumr + mergeArr[right][rptr]);
			rptr ++;
		}
	}
	while(lptr < mergeArr[left].size()) { mergeArr[r].push_back(suml + mergeArr[left][lptr]); lptr ++; }
	while(rptr < mergeArr[right].size()) { mergeArr[r].push_back(sumr + mergeArr[right][rptr]); rptr ++; }

	// cumul sum
	mergeSum[r].push_back(0);
	for (int i = 1; i < mergeArr[r].size(); ++i) {
		mergeSum[r].push_back(mergeSum[r][i-1] + mergeArr[r][i]);
	}
}

ll nodeQuery(int r, int len) {

	int pos = upper_bound(mergeArr[r].begin(), mergeArr[r].end(), len) - mergeArr[r].begin();
	if(pos > 0) {
		// cumul sum of nodes with len < current len
		return (ll)len*pos - mergeSum[r][pos-1];
	}
	return 0;
}
ll query(int r, int len) {

	ll ans = nodeQuery(r, len);
	//cout << ans << endl;
	while(r > 1 && len > 0) {		

		// is right node
		if(r&1) {
			len -= tree[r];
			r = RPARENT(r);
			// sum parent node
			if(len > 0) ans += len;
			// sum left child
			ans += nodeQuery(LCHILD(r), len - tree[LCHILD(r)]);
		}
		else {
			len -= tree[r];
			r = RPARENT(r);
			// sum parent node
			if(len > 0) ans += len;
			// sum right child
			ans += nodeQuery(RCHILD(r), len - tree[RCHILD(r)]);
		}

		//cout << ans << endl;
	}
	return ans;
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
	int l;
	for (int i = 2; i <= N; ++i)
	{
		cin >> l;
		// ending node of edge
		tree[i] = l;
	}

	// pre-process
	mergeSort();

	// for (int i = 0; i < mergeArr[1].size(); ++i)
	// {
	// 	cout << mergeArr[1][i] << endl;
	// }
	// cout << tree[4] << endl;

	// queries
	int A, H;
	while(M--) {

		cin >> A >> H;

		ll ans = query(A, H);
		cout << ans << endl;
		//cout << "--" << endl;
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