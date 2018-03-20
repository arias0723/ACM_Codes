/*
    https://csacademy.com/contest/round-71/task/russian-dolls/statement/
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
//template <class T> using Tree = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;
 
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

const int MAXN = 100000 + 5, MAXNLOG = 22;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const int BASE = 31;
const long double EPS = 1e-9;
const double PI = 4*atan(1);

// Input
#define LCHILD(x) ((x)<<1)
#define RCHILD(x) (((x)<<1)+1)
#define RPARENT(x) ((x)>>1)



int N, K;
map<int, ll> dolls;

ll checkSol(map<int, ll> tmp) {

    int maxsz; ll maxcnt; 
    tie(maxsz, maxcnt) = *tmp.rbegin();
    ll ans = 0;

    while(! tmp.empty()) {

        int currsz; ll currcnt;
        tie(currsz, currcnt) = *tmp.rbegin();

        // The 1 cannot be distributed further
        if(currsz == 1) {
            if(currcnt > maxcnt) {
                return 1e9;
            }
            return ans;
        }

        // No way to distribute 'currcnt' to lower levels and keep 'maxcnt' the max value
        // so 'maxsz' is not solution
        if(currcnt >= maxcnt*2) {
            return 1e9;
        }

        // Pass the surplus (if any) to lower levels
        if(currcnt > maxcnt) {
            tmp[currsz - 1] += (currcnt - maxcnt) * 2;
            ans += (currcnt - maxcnt);
        }
        
        tmp.erase((*tmp.rbegin()).first);
    }
    return ans; 
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
    int d;
    for (int i = 0; i < N; ++i)
    {
        cin >> d;
        dolls[d] ++;
    }

    ll ans = 1e9, splits = 0;
    // Only 30 iterations needed ( log(1e9) ) to reach max possible value of cnt
    for (int i = 0; i <= 30; ++i)
    {
        ans = min(ans, splits + checkSol(dolls));

        // Check for level 1
        if((*dolls.rbegin()).first == 1) {
            break;
        }        

        // Try next max for improving ans 
        int currsz; ll currcnt;
        tie(currsz, currcnt) = *dolls.rbegin();
        splits += currcnt;
        dolls[currsz - 1] += currcnt * 2;

        dolls.erase((*dolls.rbegin()).first);
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