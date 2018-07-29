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

const int MAXN = 1000000 + 5, MAXNLOG = 22;
const ll MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);
const int boardi[] = {-1, -1, +0, +1, +1, +1, +0, -1};
const int boardj[] = {+0, +1, +1, +1, +0, -1, -1, -1};



// Input
int N, M, Q, P, S;
int stablemin[MAXN][20], stablegcd[MAXN][20];
int A[MAXN];

// Compute RMQ
void RMQ(int A[], int N) {

	for (int i = 0; i < N; ++i) {
   		stablemin[i][0] = A[i];
   		stablegcd[i][0] = A[i];
	}

	for (int j = 1; (1<<j) <= N; ++j)
   	for (int i = 0; i+(1<<j)-1 < N; ++i) {
   		// Min
   		stablemin[i][j] = min(stablemin[i][j-1], stablemin[i + (1<<(j-1))][j-1]);
   		// Gcd
       	stablegcd[i][j] = __gcd(stablegcd[i][j-1], stablegcd[i + (1<<(j-1))][j-1]);
   	}
}
// Query
inline int log2(int x) { int l = 0; while((1<<l) <= x) l++; return (l-1);}
int querymin(int i, int j) {
    int k = log2(j-i+1);
    return min(stablemin[i][k], stablemin[j-(1<<k)+1][k]);
}
int querygcd(int i, int j) {
    int k = log2(j-i+1);
    return __gcd(stablegcd[i][k], stablegcd[j-(1<<k)+1][k]);
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
		cin >> A[i];
	}

	RMQ(A, N);

	int b = 0, e = N-1;
	while(e > b) 
	{
		int mid = (b+e+1)/2;
		bool ok = 0;
		for (int i = 0; i + mid < N; ++i)
		{
			if(querygcd(i, i + mid) == querymin(i, i + mid)) {
				ok = 1;
				break;
			}
		}
		if(ok) {
			b = mid;
		}
		else {
			e = mid - 1;
		}
	}

	vi ans;
	for (int i = 0; i < N - b; ++i) {
		if(querygcd(i, i + b) == querymin(i, i + b)) {
			ans.pback(i + 1);
		}
	}

	cout << ans.size() << " " << b << endl;
	for(int v : ans) {
		cout << v << " ";
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