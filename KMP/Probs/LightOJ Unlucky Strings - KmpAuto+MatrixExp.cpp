/*
http://lightoj.com/volume_showproblem.php?problem=1268
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
const int MAXN = 55;
const ll MOD = 1e4 + 7;
const int INF = 1e9;
const int BASE = 31;
 
// Input

int N, T, n, x;
int pi[MAXN], aut[MAXN][30];
unsigned int MA[MAXN][MAXN];
char allowed[MAXN];

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

	prefix_function(S);

	for (int i=0; i<n; ++i) {
		for (int j=0; j<x; ++j) {
			char c = allowed[j]-'a';
 		//for (char c=0; c<26; ++c) {

  			if (i > 0 && c != (S[i] - 'a'))
   				aut[i][c] = aut[pi[i-1]][c];
  			else
   				aut[i][c] = i + (c == (S[i] - 'a'));
   		}
   	}
}

// Matix Expo...
struct mat
{
	unsigned int M[MAXN][MAXN];

	mat() {
		memset(M, 0, sizeof M);
	}
	mat(unsigned int m[MAXN][MAXN]) {
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {				
				M[i][j] = m[i][j];
			}
		}
	}
	mat operator *(const mat& M2) {

		mat res;
		for (int i = 0; i < N; ++i) {			
			for (int j = 0; j < N; ++j) {

				unsigned int val = 0;				
				for (int k = 0; k < N; ++k)
				{
					val += M[i][k]*(M2.M[k][j]);					
				}
				res.M[i][j] = val;				
			}
		}
		return res;
	}	
};

mat matpow(mat m, unsigned int b) {

	if(b == 1) return m;

	mat mm = matpow(m, b/2);
	mm = mm * mm;

	if(b%2) return mm*m;
	return mm;
}

// Solve
char S[MAXN];

unsigned binpow(unsigned int a, unsigned int b) {

	if(b == 1) return a;

	unsigned int aa = binpow(a, b/2);
	aa = aa * aa;

	if(b%2) return aa*a;
	return aa;
}

unsigned int solve() {

	memset(aut, 0, sizeof aut);
	prefix_dfa(S);
	N ++;

	// build adj matrix
	memset(MA, 0, sizeof MA);
	for (int i = 0; i < N-1; ++i) {
		for (int j=0; j<x; ++j) {

			int c = allowed[j]-'a';
			MA[i][aut[i][c]] ++;
		}
	}
	MA[N-1][N-1] = x;


	// do matrix exponetiation
	mat m(MA);	
	m = matpow(m, n);

	unsigned int total = binpow(x, n);

	return total - m.M[0][N-1];
	//cout << total - m.M[0][N-1] << endl;
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
	

	cin >> T;
	for (int cc = 1; cc <= T; ++cc) {

		cin >> n;

		cin >> allowed;
		x = strlen(allowed);
		cin >> S;
		N = strlen(S);

		cout << "Case " << cc <<": ";
		cout << solve() << endl;
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

