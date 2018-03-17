#include <bits/stdc++.h>
#define endl '\n'
using namespace std;
typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;

// Add defines here ...
#define MAXN 100005
const int MOD = 1e9 + 7;
const int INF = 1e9;

// Persist STree
struct data{ int len, max1, max1prefix, max1suffix; };
struct node {
	data d;
	int leftIdx, rightIdx;
};
data mergeData(data d1, data d2) {
	int max1 = max(max(d1.max1, d2.max1), d1.max1suffix + d2.max1prefix);
	int max1prefix = d1.max1prefix;
	if(d1.max1prefix == d1.len)
		max1prefix += d2.max1prefix;
	int max1suffix = d2.max1suffix;
	if(d2.max1suffix == d2.len)
		max1suffix += d1.max1suffix;

	return (data){ d1.len + d2.len, max1, max1prefix, max1suffix };
}
vector<node> persistentStree;

int build(int l, int r) {

	if(l == r) {
		int idx = persistentStree.size();
		persistentStree.push_back( (node){ (data){1, 0, 0, 0}, -1, -1} );
		return idx;
	}

	int mid = (l+r)>>1;
	int lidx = build(l, mid);
	int ridx = build(mid+1, r);

	int len = persistentStree[lidx].d.len + persistentStree[ridx].d.len;
	int idx = persistentStree.size();
	persistentStree.push_back( (node){ (data){len, 0, 0, 0}, lidx, ridx} );

	return idx;
}

int update(int root, int i, int j, int pos, int val = 1) {

	if(i == j) {
		int idx = persistentStree.size();
		persistentStree.push_back( (node){ (data){1, 1, 1, 1}, -1, -1} );
		return idx;
	}

	int mid = (i+j)>>1;
	int lidx = persistentStree[root].leftIdx;
	int ridx = persistentStree[root].rightIdx;
	if(pos <= mid) {

		int new_lidx = update(lidx, i, mid, pos, val);

		int idx = persistentStree.size();
		data nodeData = mergeData(persistentStree[new_lidx].d, persistentStree[ridx].d);
		persistentStree.push_back( (node){nodeData, new_lidx, ridx} );
		return idx;
	}

	int new_ridx = update(ridx, mid+1, j, pos, val);

	int idx = persistentStree.size();
	data nodeData = mergeData(persistentStree[lidx].d, persistentStree[new_ridx].d);
	persistentStree.push_back( (node){nodeData, lidx, new_ridx} );
	return idx;
}

data query(int root, int i, int j, int l, int r) {

	if(i>j || i>r || j<l) return (data){ 0,0,0,0 };

	if(i>=l && j<=r) {
		return persistentStree[root].d;
	}

	int mid = (i+j)>>1;
	data d1 = query(persistentStree[root].leftIdx, i, mid, l, r);
	data d2 = query(persistentStree[root].rightIdx, mid+1, j, l, r);

	return mergeData(d1, d2);
}

// Input
int N, M, strees[MAXN];
pair<int, int> H[MAXN];

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

	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> H[i].first;
		H[i].second = i;
	}
	sort(H, H + N);

	// build stree
	int root = build(0, N-1);
	for (int i = N-1; i >= 0; --i) {
		root = update(root, 0, N-1, H[i].second);
		strees[ H[i].second ] = root;
	}

	cin >> M;
	int l, r, w;
	while(M --) {

		cin >> l >> r >> w;
		l --, r--;

		int b = 0, e = N;
		int ans = 0;
		while(b < e) {

			int mid = (b+e)/2;
			int res = query(strees[ H[mid].second ], 0, N-1, l, r).max1;

			if(res < w)	e = mid;
			else {
				ans = H[mid].first;
				b = mid + 1;
			}
		}

		cout << ans << endl;
	}


	//Output region
	#ifndef ONLINE_JUDGE
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("notepad.exe name.out");
	#endif

	return 0;
}
