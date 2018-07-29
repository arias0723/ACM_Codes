/**
    https://www.hackerrank.com/contests/inscription2015/challenges/the-natural-selection/problem
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

const int MAXN = 2000000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 9;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)



// Trie
class Trie {

public:
	Trie() {
		addNode();
	}

	// Insert a new word in the Trie
	void insert(char* str, const int id = 0) {
		// Update node word count
		nodes[id].word_cnt ++;
		// End of word (... as we know it :D)
		if(*str == 0) {
			nodes[id].word_end ++;
			return;
		}
		// Init
		if(nodes[id].children[*str - first_char] == -1) {
			int idx = addNode();
			nodes[id].children[*str - first_char] = idx;
		}
		insert(str + 1, nodes[id].children[*str - first_char]);
	}
	void findAndMark(char* str, int p, vector<bool>& mark, const int id = 0) {
		// Word not found
		if(id == -1) return;
		// Mark all ends of a word
		if(nodes[id].word_end) {
			mark[p] = 1;
		}
		return findAndMark(str + 1, p + 1, mark, nodes[id].children[*str - first_char]);
	}

private:
	// Node data
	static const int alpha_size = 30;
	static const char first_char = 'a';
	struct Node {
		// data
		int id, word_cnt, word_end;
		int children[alpha_size];

		Node() {
			id = word_cnt = word_end = 0;
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

Trie forwT, backwT;

bool solve(char* str) {

	int l = strlen(str);
	vector<bool> forwMark(l + 1, 0), backwMark(l + 1, 0);
	forwMark[0] = backwMark[0] = 1;

	forwT.findAndMark(str, 0, forwMark);

	reverse(str, str + l);
	backwT.findAndMark(str, 0, backwMark);

	// Concat of 2 strings
	for (int i = 0; i <= l; ++i) {
		if(forwMark[i] && backwMark[l-i]) {
			// cout << str << ": " << i << endl;
			return true;
		}
	}
	return false;
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
	for (int i = 0; i < N; ++i)
	{
		cin >> A;
		int l = strlen(A);
		forwT.insert(A);
		reverse(A, A + l);
		backwT.insert(A);
	}
	cin >> Q;
	int ans = 0;
	while(Q--) {
		cin >> A;
		ans += solve(A);		
	}

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