#include<stdio.h>
#include<cstring>
using namespace std;
#define MAXN 150

int pi[MAXN];

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

char S[MAXN];
