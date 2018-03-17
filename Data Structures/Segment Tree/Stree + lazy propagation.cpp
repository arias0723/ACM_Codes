#include <bits/stdc++.h>
using namespace std;
#define MAXN 100005

typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vii;
const int mod = 2537;


class STREE {

private:
	static const int MOD = 1000000009;
	int size;
	vector<llu> stree;
	vector<llu> lazy;

	void __build(int root, int l, int r) {

		if(r > l) {
			__build(2*root, l, (l+r)/2);
			__build(2*root +1, (l+r)/2 +1, r);
		}

		if(l == r) {
			stree[root] = 1;
			lazy[root] = 1;
		}
		else {
			stree[root] = stree[2*root] + stree[2*root + 1];
			lazy[root] = 1;
		}
	}

	// A node is always updated. Lazy is pushed to children when needed to go down
	void __pushLazy(int root, int lazyValue) {

		stree[root*2] *= lazyValue;
		stree[root*2] %= MOD;
		lazy[root*2] *= lazyValue;
		lazy[root*2] %= MOD;

		stree[root*2 +1] *= lazyValue;
		stree[root*2 +1] %= MOD;
		lazy[root*2 +1] *= lazyValue;
		lazy[root*2 +1] %= MOD;

		lazy[root] = 1;
	}

	void __updateRange(int root, int i, int j, const int l, const int r, const int val) {

		// Completely out-range
		if(i > j || i > r || j < l) return;

		// Completely in-range
		if(i >= l && j <= r) {

			// Update node and lazy value(to push() later)
			stree[root] *= val;
			stree[root] %= MOD;
			lazy[root] *= val;
			lazy[root] %= MOD;

			return;
		}

		// If you go down into node children, you need to:
		// 1: Push lazy stored values
		// 2: Split the range
		// 3: Update node value with children values

		// Push lazy value to children
		__pushLazy(root, lazy[root]);

		// Partialy in-range
		__updateRange(2*root, i, (i+j)/2, l, r, val);
		__updateRange(2*root +1, (i+j)/2 +1, j, l, r, val);

		// Update parent value
		stree[root] = stree[root*2] + stree[root*2 +1];
	}

	llu __queryRange(int root, int i, int j, const int l, const int r) {

		// Completely out-range
		if(i > j || i > r || j < l) return 0;

		// Completely in-range
		if(i >= l && j <= r) {

			return stree[root];
		}

		// Push lazy value to children
		__pushLazy(root, lazy[root]);

		// Partialy in-range
		llu v1 = __queryRange(2*root, i, (i+j)/2, l, r);
		llu v2 = __queryRange(2*root +1, (i+j)/2 +1, j, l, r);

		return (v1 + v2) % MOD;
	}

public:
	STREE() {
		this->size = 0;
	}

	void createStree(int size) {

		this->size = size;

		stree.assign(size*4, 1);
		lazy.assign(size*4, 1);

		__build(1, 0, size -1);
	}

	void updateRange(int x, int y, int val) {

		__updateRange(1, 0, this->size -1, x, y, val);
	}

	llu queryRange(int x, int y) {

		return __queryRange(1, 0, this->size -1, x, y);
	}

};


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

	int N, M, x, y, k, op;
	STREE S;
	while(scanf("%d%d", &N,&M) != EOF) {

		S.createStree(N);
		while(M --) {

			scanf("%d", &op);
			if(op == 0) {

				scanf("%d%d%d", &x,&y,&k);
				S.updateRange(x-1, y-1, k);
			}
			else {

				scanf("%d%d", &x,&y);
				printf("%lld\n", S.queryRange(x-1, y-1));
			}
		}
	}



	//Output region
	#ifndef ONLINE_JUDGE
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	fclose(FILE_NAME);
	system("notepad.exe name.out");
	#endif

	return 0;
}

