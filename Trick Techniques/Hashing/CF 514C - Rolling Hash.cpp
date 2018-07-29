#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long llu;
#define S1(a) scanf("%d", &a)
#define S2(a, b) scanf("%d%d", &a, &b)

#define oo 100000000
const ll MOD = 1000000000007LL;
#define PRIME 11
#define MAXN 600005



/////////////////////////

int N, M;
set<ll> st;
char s[MAXN];
ll pi[MAXN];

ll getHash(int len) {

	ll h = 0;
	for (int i = 0; i < len; ++i) {

		h = h + (pi[i]*(s[i]-'a'+1))%MOD;
		h %= MOD;
	}

	return h;
}


int main() {
	//Input region
#ifndef ONLINE_JUDGE
	system("notepad.exe name.in");
	freopen("name.in", "r", stdin);
	FILE * FILE_NAME = freopen("name.out", "w", stdout);
	int TIME = clock();
#endif

	//Add your code here...

	pi[0] = 1;
	for (int i = 1; i < MAXN; ++i) {

		pi[i] = (pi[i-1]*PRIME) % MOD;
	}

	S2(N, M);

	for (int i = 0; i < N; ++i) {

		scanf("%s", s);

		int l = strlen(s);
		st.insert(getHash(l));
	}

	for (int i = 0; i < M; ++i) {

		scanf("%s", s);

		int l = strlen(s);
		ll hash = getHash(l);

		bool ok = false;
		for (int i = 0; i < l; ++i) {

			ll hash2 = hash - (pi[i]*(s[i]-'a'+1)) % MOD;
			hash2 = (hash2 + MOD) % MOD;
			for (int j = 1; j <= 3; ++j) {

				if( s[i]-'a'+1 != j ) {

					if( st.count( (hash2 + (pi[i]*j)%MOD) % MOD) )
						ok = true;

				}
			}

			if(ok)
				break;
		}

		puts(ok ? "YES" : "NO");
	}





	//Output region

#ifndef ONLINE_JUDGE
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	fclose(FILE_NAME);
	system("notepad.exe name.out");
#endif

} 
