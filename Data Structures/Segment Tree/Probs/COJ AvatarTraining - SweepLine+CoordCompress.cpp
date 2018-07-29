/*
	http://coj.uci.cu/24h/problem.xhtml?pid=1921
*/

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

const int MAXN = 200000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 9;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)



// normalization
vector<int> Y;
int normY[MAXN];
// stree update range
int times[4*MAXN], lazy[4*MAXN];
llu amount[4*MAXN];
void update(int r, int i, int j, const int B, const int E, int val) {
	
	if(j < B || i > E || j < i) return;

	if(i >= B && j <= E) {

		times[r] += val;
		if(times[r] > 0)
			amount[r] = (normY[j] - normY[i-1]);
		else
			amount[r] = amount[2*r] + amount[2*r + 1];

		return;
	}	
	// split stree
	int mid = (i+j)/2;
	update(2*r, i, mid, B, E, val);
	update(2*r + 1, mid + 1, j, B, E, val);		
	// update root
	if(times[r] > 0) {
		// Interval fully covered
		amount[r] = (normY[j] - normY[i-1]);
	} 
	else {
		// Sum of children intervals
		amount[r] = amount[2*r] + amount[2*r + 1];
	}
}

int N, Q, T;
struct event
{
	int st, lo, hi;
	bool isclose;
	bool operator <(const event &e) const {
		if(st == e.st)
			return isclose > e.isclose;
		return st < e.st;
	}
};
vector<event> events;


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


	int x1, y1, x2, y2;
	cin >> N;
	for (int i = 0; i < N; ++i)
	{
		cin >> x1 >> x2 >> y1 >> y2;
		Y.pback(y1);
		Y.pback(y2);
		events.pback( {x1, y1, y2, 0} );
		events.pback( {x2, y1, y2, 1} );			
	}
	sort(events.begin(), events.end());
	// compress coord
	sort(Y.begin(), Y.end());
	Y.erase( unique(Y.begin(), Y.end()), Y.end() );
	for (int i = 0; i < Y.size(); ++i) {
		normY[i] = Y[i];
	}
	// sweep line
	llu area = 0;
	for (int i = 0; i < events.size(); ++i)
	{
		if(i > 0) {
			area += amount[1] * (events[i].st - events[i-1].st);
		}
		int lo = lbound(normY, normY + Y.size(), events[i].lo) - normY;
		int hi = lbound(normY, normY + Y.size(), events[i].hi) - normY;
		update(1, 0, Y.size(), lo + 1, hi, events[i].isclose ? -1 : 1);
	}
	cout << area << endl;

    


	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}    