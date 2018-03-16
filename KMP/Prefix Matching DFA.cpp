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