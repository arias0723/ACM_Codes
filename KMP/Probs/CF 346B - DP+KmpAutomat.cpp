/*
	http://codeforces.com/problemset/problem/346/B
*/

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
const int MAXN = 105;
const int MOD = 2537;
const int INF = 1e9;


// Input

int N, T;
int pi[MAXN], aut[MAXN][30];

void prefix_function(char* S) {

 	int n = strlen(S);
 	for (int i = 1; i < n; ++i) {

		int j = pi[i-1];  		
  		while (j > 0 && S[i] != S[j])
   			j = pi[j-1];
  		
  		if (S[i] == S[j]) ++j;

  		pi[i] = j;
 	}
}

void prefix_dfa(char* S) {	

	int n = strlen(S);
	S[n] = ('Z'+1); n++;

	prefix_function(S);

	for (int i=0; i<n; ++i) {
 		for (char c=0; c<26; ++c) {

  			if (i > 0 && c != (S[i] - 'A'))
   				aut[i][c] = aut[pi[i-1]][c];
  			else
   				aut[i][c] = i + (c == (S[i] - 'A'));
   		}
   	}
}

char S1[MAXN], S2[MAXN], V[MAXN];
int dp[MAXN][MAXN][MAXN], L1, L2, LV;

int solve(int x, int y, int z) {

	// base case
	if(z >= LV-1) return -MAXN;
	if(x==L1 || y==L2) return 0;

	// dp
	if(dp[x][y][z] != -2*MAXN) return dp[x][y][z];

	int v = solve(x+1, y, z);
	if(v > dp[x][y][z]) {
		dp[x][y][z] = v;
	}
	v = solve(x, y+1, z);
	if(v > dp[x][y][z]) {
		dp[x][y][z] = v;
	}
	if(S1[x] == S2[y]) {
		v = 1 + solve(x+1, y+1, aut[z][S1[x]-'A']);
		if(v > dp[x][y][z]) {
			dp[x][y][z] = v;
		}
	}

	return dp[x][y][z];
}

void str(int x, int y, int z) {

	if(x==L1 || y==L2) return;
	
	if(S1[x] == S2[y] && dp[x][y][z] == dp[x+1][y+1][aut[z][S1[x]-'A']] + 1) {
		cout << S1[x];
		return str(x+1, y+1, aut[z][S1[x]-'A']);
	}
	if(dp[x][y][z] == dp[x+1][y][z])
		return str(x+1, y, z);
	if(dp[x][y][z] == dp[x][y+1][z])
		return str(x, y+1, z);
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
	

	cin >> S1 >> S2;
	cin >> V;
	prefix_dfa(V);

	L1 = strlen(S1); L2 = strlen(S2); LV = strlen(V);	
	for (int i = 0; i < L1; ++i) {
		for (int j = 0; j < L2; ++j) {
			for (int k = 0; k < LV; ++k) {

				dp[i][j][k] = -2*MAXN;
			}
		}
	}

	int v = solve(0, 0, 0);
	if(v == 0)
		cout << v << endl;
	else
		str(0,0,0);
	//cout << endl << v << endl;
	

	//Output region
	#ifdef GHOST
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	cout.flush();
	fclose(FILE_NAME);
	system("subl name.out");
	#endif

	return 0;
}

