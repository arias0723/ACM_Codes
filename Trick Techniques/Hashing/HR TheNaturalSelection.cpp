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




int N, Q;
char A[MAXN];

set<llu> forwS, backwS;

llu getHash(char* s) {
	llu hash = 0;
	while(*s != 0) {
		hash = hash*BASE + (*s);
		s++;
	}
	return hash;
}

bool solve(char* str) {

	int l = strlen(str);
	vector<llu> forwH(l + 1, 0), backwH(l + 1, 0);
	
	// backwards hash
	for (int i = l-1; i > 0; --i)
	{
		backwH[i] = str[i];
		backwH[i] += backwH[i+1]*BASE;
	}
	// forward hash
	for (int i = 0; i < l; ++i)
	{
		forwH[i] = str[i];
		if(i) forwH[i] += forwH[i-1]*BASE;

		// solve
		if(forwS.count(forwH[i]) && backwS.count(backwH[i+1]))
			return true;
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


	// empty strings
	forwS.insert(0);
	backwS.insert(0);

	cin >> N;	
	for (int i = 0; i < N; ++i)
	{
		cin >> A;
		int l = strlen(A);
		forwS.insert(getHash(A));
		reverse(A, A + l);
		backwS.insert(getHash(A));
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