/*
	http://codeforces.com/problemset/problem/291/E
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
const int MAXN = 200005;
const int MOD = 2537;
const int INF = 1e9;


// Input

int N, T;
vi tree[MAXN];
vector<char> endingStr[MAXN];
char str[MAXN], t[MAXN];
int matchingState;

// KMP Automata
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
	S[n] = ('z'+1); n++;
	matchingState = n-1;

	prefix_function(S);

	for (int i=0; i<n; ++i) {
 		for (char c=0; c<26; ++c) {

  			if (i > 0 && c != (S[i] - 'a'))
   				aut[i][c] = aut[pi[i-1]][c];
  			else
   				aut[i][c] = i + (c == (S[i] - 'a'));
   		}
   	}
}


ll ans = 0;
void solve(int p, int r, int autState) {

	//cout << autState << endl;

	int currState = autState;
	for (int i = 0; i < endingStr[r].size(); ++i)
	{
		char c = endingStr[r][i];
		currState = aut[currState][c-'a'];

		if(currState == matchingState)
			ans ++;
	}

	for (int i = 0; i < tree[r].size(); ++i)
	{
		int u = tree[r][i];
		if(u != p) {

			solve(r, u, currState);
		}
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
	int u;
	for (int i = 2; i <= N; ++i)
	{
		cin >> u;
		tree[i].push_back(u);
		tree[u].push_back(i);
		
		cin >> str;
		for (int j = 0; str[j] ; ++j)
		{
			endingStr[i].push_back(str[j]);
		}
	}
	cin >> t;

	prefix_dfa(t);
	solve(-1, 1, 0);

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

