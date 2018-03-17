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
	node* left, *right;	

	node() {
		left = right = 0;
	}
};
int N, T;


void insert(node* r, int x, int depth = 30) {

	if(depth < 0)
		return;

	int mask = x&(1<<depth);
	if(mask) {

		if(r->right == 0)
			r->right = new node();

		insert(r->right, x, depth - 1);
	}
	else {

		if(r->left == 0)
			r->left = new node();

		insert(r->left, x, depth - 1);
	}
}

int res;
void query(node* r, int x, int depth = 30) {

	if(depth < 0)
		return ;

	int mask = x&(1<<depth);
	if(mask) {

		if( r->left ) {
			res |= (1<<depth);
			return query(r->left, x, depth - 1);
		}
		return query(r->right, x, depth - 1);
	}
	else {

		if( r->right ) {
			res |= (1<<depth);
			return query(r->right, x, depth - 1);
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

		node* tree = new node();

		cin >> N;

		int x, cum = 0, ans = 0;
		insert(tree, 0);
		for (int i = 0; i < N; ++i)
		{
			cin >> x;

			cum ^= x;			
			insert(tree, cum);

			res = 0;
			query(tree, cum);
			//cout << res << endl;
			ans = max(ans, res);
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

