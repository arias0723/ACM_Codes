/**
    We can all benefit by doing occasional "toy" programs, when artificial
    restrictions are set up, so that we are forced to push our abilities to
    the limit.The art of tackling miniproblems with all our energy will sharpen
    our talents for the real problems.
                                        Donald E. Knuth
**/
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

const int MAXN = 800000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 9;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)


ll ans;
vii vans;
vi name_end[MAXN], pse_end[MAXN];
int curr_word;
bool pse;


// Trie
class Trie {

public:

	Trie() {
		addNode();
	}

	// Insert a new word in the Trie
	void insert(char* str, const int id = 0) {
		
		if(pse) {			
			if(*str == 0) {
				pse_end[ id ].pback(curr_word);
				return;
			}
		}
		else {
			if(*str == 0) {
				name_end[ id ].pback(curr_word);
				return;
			}
		}
		// Init
		if(nodes[id].children[*str - first_char] == -1) {
			int idx = addNode();
			nodes[id].children[*str - first_char] = idx;
		}
		insert(str + 1, nodes[id].children[*str - first_char]);
	}

	// solve
	void solve(int level = 0, const int id = 0) {
		for(int cid : nodes[id].children) {	
			if(cid != -1) {
				solve(level + 1, cid);
			}
		}
		// init
		for(int cid : nodes[id].children) { 
			if(cid != -1) {
				// SmallToLarge to join unused names from children
				if(name_end[id].size() < name_end[cid].size()) {
					swap(name_end[id], name_end[cid]);
				}
				for(int v : name_end[cid]) {
					name_end[id].pback(v);
				}
				// The same for pseuds
				if(pse_end[id].size() < pse_end[cid].size()) {
					swap(pse_end[id], pse_end[cid]);
				}
				for(int v : pse_end[cid]) {
					pse_end[id].pback(v);
				}
			}
		}
		// solve
		int plus = min(name_end[id].size(), pse_end[id].size());
		while(name_end[id].size() && pse_end[id].size()) {
			ans += level;
			vans.pback({ name_end[id].back(), pse_end[id].back() });
			name_end[id].pop_back();
			pse_end[id].pop_back();
		}
	}


private:
	// Node data
	static const int alpha_size = 30;
	static const char first_char = 'a';
	struct Node {
		// data
		int id;
		int children[alpha_size];

		Node() {
			memset(children, -1, sizeof children);
		}
	};
	vector<Node> nodes;
	
	// Push new node
	int addNode() {
		Node n;
		n.id = nodes.size();
		nodes.push_back(n);
		return nodes.size() - 1;
	}

};

int N, Q;
char A[MAXN];


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
	Trie T;
	for (int i = 0; i < N; ++i)
	{
		cin >> A;
		curr_word = i + 1;
		pse = 0;
		T.insert(A);
	}
	for (int i = 0; i < N; ++i)
	{
		cin >> A;
		curr_word = i + 1;
		pse = 1;
		T.insert(A);
	}
	T.solve();

	cout << ans << endl;
	for (int i = 0; i < vans.size(); ++i) {
		cout << vans[i].first << " " << vans[i].second << endl;
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