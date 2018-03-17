#include <bits/stdc++.h>
using namespace std;


struct node {
	int val;
	node *l, *r;

	node(int v) : val(v), l(NULL), r(NULL) {}
	node(node* _l, node* _r) : l(_l), r(_r) {
		val = 0;
		if(l != NULL) val += l->val;
		if(r != NULL) val += r->val;
	}
};
vector<int> A;
vector<node*> strees;


node* build(int l, int r) {

	if(l == r) return new node(0);

	return new node(build(l, (l+r)/2), build((l+r)/2 +1, r));
}

node* update(node* root, int i, int j, int pos, int val) {

	if(i == j) return new node(val);

	int mid = (i+j)>>1;
	if(mid>=pos)
		return new node(update(root->l, i, mid, pos, val), root->r);
	else
		return new node(root->l, update(root->r, mid+1, j, pos, val));
}

/*int query(node* root, int i, int j, int l, int r) {

	if(i > j || j < l || i > r) return 0;

	if(i>=l && j<=r) return root->val;

	return query(root->l, i, (i+j)>>1, l, r) +
			query(root->r, (i+j)>>1 +1, j, l, r);
}*/

int getVal(node* rootR, node* rootL) {

	int vr = rootR ? rootR->val : 0;
	int vl = rootL ? rootL->val : 0;
	return vr - vl;
}

int query(node* rootR, node* rootL, int l, int r, int v) {

	if(l == r) return l;

	int vl = getVal(rootR->l, rootL->l);

	if(vl >= v) return query(rootR->l, rootL->l, l, (l+r)>>1, v);
	else return query(rootR->r, rootL->r, ((l+r)>>1) +1, r, v - vl);
}


int N, M, x;
vector<pair<int, int> > input;

int main() {

	//Input region
	#ifndef ONLINE_JUDGE
	system("notepad.exe name.in");
	freopen("name.in", "r", stdin);
	FILE * FILE_NAME = freopen("name.out", "w", stdout);
	int TIME = clock();
	#endif


	scanf("%d%d", &N,&M);
	for (int i = 0; i < N; ++i)
	{
		scanf("%d", &x);
		input.push_back(make_pair(x, i));
	}
	sort(input.begin(), input.end());

	// build stree
	strees.push_back(build(0, N-1));

	A.resize(N);
	for (int i = 0; i < N; ++i) {
		A[input[i].second] = i;
	}

	// do updates
	for (int i = 0; i < N; ++i) {

		node* root = strees[strees.size() -1];
		strees.push_back(update(root, 0, N-1, A[i], 1));
	}

	//cout << query(strees[4], 0, N-1, 0, N-1) << endl;

	int i,j,k;
	while(M--) {

		scanf("%d%d%d", &i,&j,&k);
		//i--, j--;

		int q = query(strees[j], strees[i-1], 0, N-1, k);
		printf("%d\n", input[q].first);
	}

	//Output region
	#ifndef ONLINE_JUDGE
	cout << "\n\nTIME: " << (clock() - TIME) << " MS" << endl;
	fclose(FILE_NAME);
	system("notepad.exe name.out");
	#endif

	return 0;
}