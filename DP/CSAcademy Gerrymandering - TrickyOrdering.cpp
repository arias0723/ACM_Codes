/**
	https://csacademy.com/contest/archive/task/gerrymandering/
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

const int MAXN = 100000 + 5, MAXNLOG = 22;
const ll MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);
const int boardi[] = {-1, -1, +0, +1, +1, +1, +0, -1};
const int boardj[] = {+0, +1, +1, +1, +0, -1, -1, -1};



// Input
int N, M, Q, X;

pii dp[MAXN];


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
	char county, sz;
	int largeCnt = 0, last = 0, prev = 0;
	for (int i = 1; i <= N; ++i)
	{
		cin >> county >> sz;

		if(county == 'A') {
			dp[i].first = 1;
		}
		else {
			dp[i].first = -1;
		}
		// partial sum
		dp[i].first += dp[i-1].first;
		// init dp
		if(dp[i].first >= 0) {
			dp[i].second = 1;
		}

		if(sz == 'L') {
			largeCnt ++;
			prev = last;
			last = i;
			// sort previous segment
			sort(dp + prev, dp + last);
			// cumul max dp
			for (int j = prev + 1; j < last; ++j) {
				dp[j].second = max(dp[j].second, dp[j-1].second);
			}	
		}

		// solve
		if(largeCnt > 1) {
			// init dp
			dp[i].second = dp[last-1].second;
			// best dp in (sum, dp) such that sum <= current sum
			int pos = ubound(dp + prev, dp + last, mp(dp[i].first, MAXN * 2 )) - dp;
			if(pos > prev) {
				pos --;
				dp[i].second = max(dp[i].second, dp[pos].second + 1);
			}
		}

	}

	cout << dp[N].second;




	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}