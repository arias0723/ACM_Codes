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
const int MAXN = 100005;
const int MOD = 2537;
const int INF = 1e9;


// Input
struct node {
	int cnt;
	node *left, *right; 
};

int N, T, K, trieSz;
node trie[50 * MAXN];

node* addNode() {

	trie[trieSz].cnt = 0;
	trie[trieSz].left = 0;
	trie[trieSz].right = 0;

	return &(trie[trieSz ++]);
}
int calcCnt(node* r) { return (r == 0) ? 0 : r->cnt; }

void insert(node* r, int x, int depth = 21) {

	if(depth < 0) {
		r->cnt ++;
		return;
	}

	int mask = x&(1<<depth);
	if(mask) {

		if(r->right == 0) {
			r->right = addNode();
		}
		insert(r->right, x, depth - 1);
	}
	else {

		if(r->left == 0) {
			r->left = addNode();
		}
		insert(r->left, x, depth - 1);
	}

	int v1 = calcCnt(r->left);
	int v2 = calcCnt(r->right);	
	r->cnt = v1 + v2;
}

int query(node* r, int x, int depth = 21) {

	if(r == 0)
		return 0;
	if(depth < 0)
		return 0;//return r->cnt;	

	int mask = x&(1<<depth);
	if(mask) {

		if(K&(1<<depth)) {

			return query(r->left, x, depth - 1) + calcCnt(r->right);
		}
		return query(r->right, x, depth - 1);
	}
	else {

		if(K&(1<<depth)) {

			return query(r->right, x, depth - 1) + calcCnt(r->left);
		}
		return query(r->left, x, depth - 1);
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
	


	cin >> T;
	while(T--) {

		trieSz = 0;
		node* root = addNode();

		cin >> N >> K;

		int x, cum = 0;
		ll ans = 0;
		// insert(trie, 0);
		for (int i = 0; i < N; ++i)
		{
			cin >> x;
			cum ^= x;			

			ans += query(root, cum);
			insert(root, cum);
			//cout << ans << endl;
		}
		cout << ans << endl;
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

