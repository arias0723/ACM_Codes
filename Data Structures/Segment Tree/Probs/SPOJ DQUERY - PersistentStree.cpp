#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000005

typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
const int mod = 2537;


struct node {
	int val;
	int leftIdx, rightIdx;

	/*node(int v) : val(v), leftIdx(-1), rightIdx(-1) {}
	node(int l, int r) : val(0), leftIdx(l), rightIdx(r) {

		if(left) val += left->val;
		if(right) val += right->val;
	}*/
};
vector<node> persistentStree;

int build(int l, int r) {

	if(l == r) {
		int idx = persistentStree.size();
		persistentStree.push_back( (node){0, -1, -1} );
		return idx;
	}

	int mid = (l+r)>>1;
	int lidx = build(l, mid);
	int ridx = build(mid+1, r);

	int v = persistentStree[lidx].val + persistentStree[ridx].val;
	int idx = persistentStree.size();
	persistentStree.push_back( (node){v, lidx, ridx} );

	return idx;
}

int update(int root, int i, int j, int pos, int val) {

	if(i == j) {
		int idx = persistentStree.size();
		persistentStree.push_back( (node){val, -1, -1} );
		return idx;
	}

	int mid = (i+j)>>1;
	int lidx = persistentStree[root].leftIdx;
	int ridx = persistentStree[root].rightIdx;
	if(pos <= mid) {

		int new_lidx = update(lidx, i, mid, pos, val);

		int v = persistentStree[new_lidx].val + persistentStree[ridx].val;
		int idx = persistentStree.size();
		persistentStree.push_back( (node){v, new_lidx, ridx} );
		return idx;
	}

	int new_ridx = update(ridx, mid+1, j, pos, val);

	int v = persistentStree[lidx].val + persistentStree[new_ridx].val;
	int idx = persistentStree.size();
	persistentStree.push_back( (node){v, lidx, new_ridx} );
	return idx;
}

int query(int root, int i, int j, int l, int r) {

	if(i>j || i>r || j<l) return 0;

	if(i>=l && j<=r) return persistentStree[root].val;

	int mid = (i+j)>>1;
	int v1 = query(persistentStree[root].leftIdx, i, mid, l, r);
	int v2 = query(persistentStree[root].rightIdx, mid +1, j, l, r);

	return v1+v2;
}

// input
int posRigth[MAXN];
int N, Q, x;
vector<int> roots;


int main() {

	//Input region
	#ifndef ONLINE_JUDGE
	system("notepad.exe name.in");
	freopen("name.in", "r", stdin);
	FILE * FILE_NAME = freopen("name.out", "w", stdout);
	int TIME = clock();
	#endif
	//ios_base::sync_with_stdio(false);

	//Add your code here...

	scanf("%d", &N);
	memset(posRigth, -1, sizeof posRigth);
	roots.push_back( build(0, N-1) );

	for (int i = 0; i < N; ++i) {

		scanf("%d", &x);
		if(posRigth[x] == -1) {

			roots.push_back( update(roots[roots.size() -1], 0, N-1, i, 1) );
		}
		else {

			int tmpRoot = update( roots[roots.size() -1], 0, N-1, posRigth[x], 0);
			roots.push_back( update( tmpRoot, 0, N-1, i, 1) );
		}

		posRigth[x] = i;
	}

	//cout << roots.size() << endl;
	//cout << query(roots[roots.size() -4], 0, N-1, 0, N-1);

	scanf("%d", &Q);
	int i, j;
	while(Q --) {

		scanf("%d%d", &i,&j);
		//i--, j--;

		printf("%d\n", query(roots[j], 0, N-1, i-1, N-1) );
	}



	//Output region
	#ifndef ONLINE_JUDGE
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	fclose(FILE_NAME);
	system("notepad.exe name.out");
	#endif

	return 0;
}
