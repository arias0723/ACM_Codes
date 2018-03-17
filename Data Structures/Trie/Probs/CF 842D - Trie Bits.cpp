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
const int MAXN = 300005;
const int MOD = 2537;
const int INF = 1e9;


// Input
struct node {
	int cnt, h;
	node* left, *right;	

	node() {
		cnt = h = 0;
		left = right = 0;
	}
};
int N, M;


void build(node* r, int depht = 20) {

	if(depht < 0) return;

	r->left = new node();
	r->right = new node();

	build(r->left, depht - 1);
	build(r->right, depht - 1);

	// height of nodes
	r->h = r->left->h + 1;
}

void insert(node* r, int x, int depht = 20) {

	if(depht < 0) {
		r->cnt = 1;
		return;
	}

	int mask = x&(1<<depht);
	if(mask) 
		insert(r->right, x, depht - 1);
	else
		insert(r->left, x, depht - 1);

	r->cnt = r->left->cnt + r->right->cnt;
}

int ans;
int query(node* r, int x, int depht = 20) {

	if(depht < 0)
		return ans;

	int mask = x&(1<<depht);
	if(mask) {
		//swap(r->left, r->right);

		if( r->right->cnt < (1 << (r->right->h)) ) {
			return query(r->right, x, depht - 1);
		}
		ans |= (1<<depht);
		return query(r->left, x, depht - 1);
	}

	if( r->left->cnt < (1 << (r->left->h)) ) {
		return query(r->left, x, depht - 1);
	}
	ans |= (1<<depht);
	return query(r->right, x, depht - 1);	
}


int main() {

	//Input region
	#ifdef GHOST
	system("subl name.in");
	freopen("name.in", "r", stdin);
	FILE * FILE_NAME = freopen("name.out", "w", stdout);
	int TIME = clock();
	#endif


	//Add your code here...
	std::ios::sync_with_stdio(false); cin.tie(0);

	node* tree = new node();
	build(tree);

	cin >> N >> M;
	int x;
	for (int i = 0; i < N; ++i)
	{
		cin >> x;
		insert(tree, x);

		//cout << endl << tree->cnt << endl;
	}

	int xors = 0;
	while(M --) {

		cin >> x;
		xors ^= x;
		ans = 0;
		cout << query(tree, xors) << endl;
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

