/*
	http://coj.uci.cu/24h/problem.xhtml?pid=1910
*/

#include <cstdio>
#include <cstring>
#include <ctype.h>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
#define MAXN 100005
#define ll long long
#define llu unsigned long long

struct event {
	int id, type, stamp, level;
	event(int i, int t, int s, int l) :id(i), type(t), stamp(s), level(l) {}
	bool operator <(const event &e) const {
		if(stamp == e.stamp) return (type < e.type);
		return (stamp < e.stamp);
	}
};
vector<event> E;

//stree
struct node {
	int b, e, mxm;
}stree[3 * MAXN];
void init(int root, int b, int e) {
	if(e > b) {
		int mid = (b+e)/2;
		init(2*root, b, mid);
		init(2*root +1, mid+1, e);
	}
	stree[root].b = b, stree[root].e = e, stree[root].mxm =0;
}
void update(int root, int b, int e, int val) {
	if(stree[root].b == b && stree[root].e == e) {
		stree[root].mxm = val;
		return;
	}
	int mid = (stree[root].b + stree[root].e) /2;
	if(mid >= e) {
		update(2*root, b, e, val);
	} else {
		if(mid < b) update(2*root +1, b, e, val);
		else {
			update(2*root, b, mid, val);
			update(2*root +1, mid+1, e, val);
		}
	}
	stree[root].mxm = max(stree[2*root].mxm, stree[2*root +1].mxm);
}
int query(int root,int b, int e) {
	if(stree[root].b == b && stree[root].e == e) {
		return stree[root].mxm;
	}
	int mid = (stree[root].b + stree[root].e) /2;
	if(mid >= e) return query(2*root, b, e);
	if(mid < b) return query(2*root +1, b, e);
	return max(query(2*root, b, mid), query(2*root +1, mid+1, e));
}

//tree
vector<int> tree[MAXN];
int N, b, d, l, y, p, root;
vector<int> order;
int len[MAXN], pos[MAXN], ans[MAXN];


void tour(int root) {
	pos[root] = order.size();
	order.push_back(root);
	for (int i = 0; i < tree[root].size(); ++i) {
		tour(tree[root][i]);
	}
	len[root] = order.size() - pos[root] -1;
}

int main () {
	//order.push_back(0);
	scanf("%d", &N);
	root =0;
	for (int i = 0; i < N; ++i) {
		scanf("%d%d%d",&b,&d,&p);
		if(p == -1) root = i;
		else tree[p-1].push_back(i);

		E.push_back( event(i, 1, d, 0));
		scanf("%d", &p);
		while(p --) {
			scanf("%d%d",&l,&y);
			E.push_back(event(i, 0, y, l));
		}
	}
	tour(root);
	init(1, 0, N-1);
	sort(E.begin(), E.end());

	for (int i = 0; i < E.size(); ++i) {
		if(E[i].type == 0) update(1, pos[E[i].id], pos[E[i].id], E[i].level);
		else {
			if(len[E[i].id] == 0) ans[E[i].id] = 0;
			else ans[E[i].id] = query(1, pos[E[i].id]+1, pos[E[i].id]+len[E[i].id]);
		}
	}
	for (int i = 0; i < N; ++i) {
		printf("%d\n", ans[i]);
	}
}
