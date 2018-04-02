#include <bits/stdc++.h>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long llu;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<pii> vii;
// find_by_order(k): 	iterator to the k-th largest element (counting from zero)
// order_of_key(val):	number of items strictly smaller than val
template <class T> using StdTreap = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
// Add defines here ...
#define endl '\n'
#define F0R(i, a) for (int i = 0; i < (a); ++i)
//#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define FORR(i, a, b) for (int i = (b)-1; i >= a; --i)
#define F0RR(i, a) for (int i = (a)-1; i >= 0; --i)
#define REP(i,n) for ( int i=0; i<int(n); i++ )
#define REP1(i,a,b) for ( int i=(a); i<=int(b); i++ )
#define REPeste(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
#define FOR(it,c) for ( auto it=(c).begin(); it!=(c).end(); it++ )
#define mp make_pair
#define pback push_back
#define lbound lower_bound
#define ubound upper_bound 
#define popcount __builtin_popcount

const int MAXN = 500000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 9;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


// input
int N, M, C[MAXN];
vi G[MAXN];
set<int> fillqueries, emptyqueries[MAXN];

vi queries1[MAXN], queries2[MAXN], queries3[MAXN];
int ans[MAXN];

void dfs(int p, int r, set<int>& fillqueries) {

	// init fills
	for(auto it : queries1[r]) {
		fillqueries.insert(it);
	}	

	// dfs
	for(auto v : G[r]) {
		if(v != p)
			dfs(r, v, fillqueries);
	}

	// init empty
	for(auto it : queries2[r]) {
		emptyqueries[r].insert(it);
	}	

	// solve
	for(auto v : G[r]) {
		if(v != p) {
			// small-to-large on the node sets
			if(emptyqueries[r].size() < emptyqueries[v].size()) {
				swap(emptyqueries[r], emptyqueries[v]);
			}
			// merge
			for(auto it : emptyqueries[v]) {
				emptyqueries[r].insert(it);
			}
		}
	}

	// cout << "fills for: " << r << endl;
	// for(auto x : fillqueries) {
	// 	cout << " " << x << endl;
	// }
	// 	cout << "empties for: " << r << endl;
	// for(auto x : emptyqueries[r]) {
	// 	cout << " " << x << endl;
	// }

	// ans queries for r
	for(int x : queries3[r]) {
		int fq = 0;
		if(fillqueries.size() > 0) {
			auto it = fillqueries.lbound(x);
			if(it != fillqueries.begin()) {
				it--;
				fq = *it;
			}
		}
		int eq = 0;
		if(emptyqueries[r].size() > 0) {
			auto it = emptyqueries[r].lbound(x);
			if(it != emptyqueries[r].begin()) {
				it--;
				eq = *it;
			}
		}
		if(eq >= fq) ans[x] = 0;
		else ans[x] = 1;
	}

	// clear fills
	for(auto it : queries1[r]) {
		fillqueries.erase(it);
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


	cin >> N;
	int u, v, k;
	for (int i = 1; i < N; ++i) {
		cin >> u >> v;
		G[u].pback(v);
		G[v].pback(u);
	}	
	// queries
	cin >> M;
	for (int i = 1; i <= M; ++i)
	{
		cin >> u >> v;
		if(u == 1) {
			queries1[v].pback(i);
		}
		if(u == 2) {
			queries2[v].pback(i);
		}
		if(u == 3) {
			queries3[v].pback(i);
		}
	}
	memset(ans, -1, sizeof ans);
	dfs(0, 1, fillqueries);

	for (int i = 1; i <= M; ++i) {
		if(ans[i] != -1)
			cout << ans[i] << endl;
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


//D. Tree and Queries
// #include <bits/stdc++.h>
// #include <ext/pb_ds/tree_policy.hpp>
// #include <ext/pb_ds/assoc_container.hpp>
// using namespace std;
// using namespace __gnu_pbds;

// typedef long long ll;
// typedef unsigned long long llu;
// typedef vector<int> vi;
// typedef vector<ll> vll;
// typedef vector<vi> vvi;
// typedef pair<int, int> pii;
// typedef pair<ll, ll> pll;
// typedef vector<pii> vii;
// // find_by_order(k): 	iterator to the k-th largest element (counting from zero)
// // order_of_key(val):	number of items strictly smaller than val
// template <class T> using StdTreap = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
// // Add defines here ...
// #define endl '\n'
// #define F0R(i, a) for (int i = 0; i < (a); ++i)
// //#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
// #define FORR(i, a, b) for (int i = (b)-1; i >= a; --i)
// #define F0RR(i, a) for (int i = (a)-1; i >= 0; --i)
// #define REP(i,n) for ( int i=0; i<int(n); i++ )
// #define REP1(i,a,b) for ( int i=(a); i<=int(b); i++ )
// #define REPeste(i,n) for((i)=0;(i)<(int)(n);(i)++)
// #define foreach(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
// #define FOR(it,c) for ( auto it=(c).begin(); it!=(c).end(); it++ )
// #define mp make_pair
// #define pback push_back
// #define lbound lower_bound
// #define ubound upper_bound 
// #define popcount __builtin_popcount

// const int MAXN = 100000 + 5, MAXNLOG = 22;
// const int MOD = 1e9 + 9;
// const int INF = 1e9;
// const int BASE = 31;
// const long double EPS = 1e-9;
// const double PI = 4*atan(1);

// // Input
// #define LCHILD(x) ((x)<<1)
// #define RCHILD(x) (((x)<<1)+1)
// #define RPARENT(x) ((x)>>1)



// // Treap
// template<class T>
// class Treap {

// public:
// 	Treap() {
// 		this->treapRoot = NULL;
// 	}

// 	int size() {
// 		if(this->treapRoot == NULL) return 0;
// 		return this->treapRoot->size;
// 	}
// 	void insert(T val) {
// 		this->treapRoot = __insert(this->treapRoot, val);
// 	}
// 	void erase(T val) {
// 		this->treapRoot = __erase(this->treapRoot, val);
// 	}
// 	// TODO: How return Node type here ??
// 	bool find(T val) {
// 		return this->__find(this->treapRoot, val) != NULL;
// 	}
// 	// 1-based indexes
// 	int findKth(int kth) {
// 		return this->__findKth(this->treapRoot, kth);
// 	}
// 	// Upper bound of val
// 	int countLessThanEq(T val) {
// 		return this->__countLessThanEq(this->treapRoot, val);
// 	}	
// 	void swap(Treap<T> other) {
// 		Node<T>* tmp = this->treapRoot;
// 		this->treapRoot = other.treapRoot;
// 		other.treapRoot = tmp;
// 	}

// 		template<typename U>
// 	struct Node {
// 		U val; 
// 		int priority, size;
// 		Node<U> *left, *right;

// 		Node() {}
// 		Node(U v) {
// 			val = v; size = 1;
// 			priority = rand();			
// 			left = right = NULL;
// 		}
// 		void updateSize() {
// 			int lsize = left != NULL ? left->size : 0;
// 			int rsize = right != NULL ? right->size : 0;			
// 			size = lsize + rsize + 1;
// 		}
// 	};
// 	Node<T>* treapRoot;

// private:


// 	// Return 2 treaps, where nodes in the left are less-than-equal & nodes in the right are greater than val
// 	pair<Node<T>*, Node<T>*> split(Node<T>* root, T val) {

// 		if(root == NULL) return make_pair((Node<T>*)NULL, (Node<T>*)NULL);

// 		if(val > root->val) {
// 			pair<Node<T>*, Node<T>*> rightSplit = split(root->right, val);
// 			root->right = rightSplit.first;
// 			root->updateSize();
// 			return make_pair(root, rightSplit.second);
// 		}
// 		pair<Node<T>*, Node<T>*> leftSplit = split(root->left, val);
// 		root->left = leftSplit.second;
// 		root->updateSize();
// 		return make_pair(leftSplit.first, root);
// 	}
// 	// Merges 2 treaps in one, always keeping treap constrains. Values in T1 are all smaller than values in T2
// 	Node<T>* merge(Node<T>* T1, Node<T>* T2) {

// 		if(T1 == NULL) return T2;
// 		if(T2 == NULL) return T1;
		
// 		if(T1->priority > T2->priority) {
// 			T1->right = merge(T1->right, T2);
// 			T1->updateSize();
// 			return T1;
// 		}
// 		T2->left = merge(T1, T2->left);
// 		T2->updateSize();
// 		return T2;
// 	}
// 	Node<T>* __find(Node<T>* root, T val) {

// 		if(root == NULL) return NULL;

// 		if(val < root->val) return __find(root->left, val);
// 		if(val > root->val) return __find(root->right, val);
// 		return root;
// 	}
// 	Node<T>* __insert(Node<T>* root, T val) {
// 		// Make split to the Treap
// 		pair<Node<T>*, Node<T>*> splitTreap = split(root, val);
// 		// Merge T1 with the merge of new Node and T2. 
// 		// As merge() selects the root based on node priorities, it assures the new Treap preserves both of its constrains
// 		return merge(splitTreap.first, merge(new Node<T>(val), splitTreap.second));
// 	}
// 	Node<T>* __erase(Node<T>* root, T val) {

// 		if(root == NULL) return NULL;

// 		if(val > root->val) {
// 			root->right = __erase(root->right, val);
// 		}
// 		else if(val < root->val) {
// 			root->left = __erase(root->left, val);
// 		}
// 		else {
// 			// Split and delete root, then merge both children
// 			Node<T>* eraseNode = root;
// 			root = merge(root->left, root->right);
// 			delete eraseNode;
// 		}
// 		if(root != NULL) root->updateSize();
// 		return root;
// 	}
// 	// 1-based indexes
// 	int __findKth(Node<T>* root, int kth) {
// 		// Out of bounds
// 		if(root == NULL) return -1;

// 		int leftSize = root->left != NULL ? root->left->size : 0;		
// 		if (leftSize >= kth) return __findKth(root->left, kth);
// 		if (leftSize + 1 == kth) return root->val;
// 		return __findKth(root->right, kth - leftSize - 1);
// 	}
// 	// Upper bound of val
// 	int __countLessThanEq(Node<T>* root, T val) {

// 		if(root == NULL) return 0;

// 		if(val >= root->val) {
// 			int lessThanEq = root->left != NULL ? root->left->size : 0;
// 			return __countLessThanEq(root->right, val) + lessThanEq + 1;
// 		}
// 		return __countLessThanEq(root->left, val);
// 	}
// };
// // input
// int N, M, C[MAXN];
// vi G[MAXN];
// map<int, int> colorCnt[MAXN];
// Treap<int> cnt[MAXN];
// vii queries[MAXN];
// int ans[MAXN];

// void dfs(int p, int r) {
// 	// dfs
// 	for(auto v : G[r]) {
// 		if(v != p)
// 			dfs(r, v);
// 	}
// 	// init
// 	colorCnt[r][C[r]] = 1;
// 	cnt[r].insert(1);
// 	// solve
// 	for(auto v : G[r]) {
// 		if(v != p) {
// 			// small-to-large on the node sets
// 			if(colorCnt[r].size() < colorCnt[v].size()) {
// 				swap(colorCnt[r], colorCnt[v]);
// 				// TODO: Test aki lo del swap
// 				// swap(cnt[r], cnt[v]);
// 				cnt[r].swap(cnt[v]);	
// 			}
// 			// merge
// 			for(auto it : colorCnt[v]) {
// 				int color = it.first;
// 				int vfreq = it.second;
// 				int rfreq = colorCnt[r][color];
// 				// erase v color freq from root, if exist that color in root
// 				//if(colorCnt[r].find(color) != colorCnt[r].end()) {
// 					cnt[r].erase(rfreq);
// 				//}				
// 				// update color freq and insert new freq
// 				colorCnt[r][color] += vfreq;
// 				cnt[r].insert(colorCnt[r][color]);
// 			}			
// 		}
// 	}
// 	// queries for this node
// 	// cout << "(" << r << ") --> " << cnt[r].size() << endl; 
// 	// for(auto it : colorCnt[r]) {
// 	// 	cout << " " << it.first << " == " << it.second << endl;
// 	// }
// 	for(auto it : queries[r]) {
// 		ans[it.second] = cnt[r].size() - cnt[r].countLessThanEq(it.first - 1);
// 		//cout << "(" << r << ", " << it.first << ") --> " << colorCnt[r].size() << endl; 
// 	}
// }


// int main() {

// 	//Input region
// 	#ifdef GHOST
// 	system("subl name.in");
// 	freopen("name.in", "r", stdin);
// 	FILE * FILE_NAME = freopen("name.out", "w", stdout);
// 	int TIME = clock();
// 	#endif

// 	std::ios::sync_with_stdio(false); cin.tie(0);
// 	//Add your code here...


// 	cin >> N >> M;
// 	for (int i = 1; i <= N; ++i) {
// 		cin >> C[i];
// 	}
// 	int u, v, k;
// 	for (int i = 1; i < N; ++i) {
// 		cin >> u >> v;
// 		G[u].pback(v);
// 		G[v].pback(u);
// 	}	
// 	// queries
// 	for (int i = 0; i < M; ++i)
// 	{
// 		cin >> v >> k;
// 		queries[v].pback({k, i}); 
// 	}

// 	dfs(-1, 1);

// 	for (int i = 0; i < M; ++i) {
// 		cout << ans[i] << endl;
// 	}





// 	//Output region
// 	#ifdef GHOST
// 	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
// 	cout.flush();
// 	fclose(FILE_NAME);
// 	system("subl name.out");
// 	#endif

// 	return 0;
// }    