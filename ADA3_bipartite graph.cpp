#include<stdio.h>
#include<cstdio>
#include<stdlib.h>
#include<iostream>
#include<vector>
#include<queue>
#include<string>
#include<limits.h>
#include<list>
#include<algorithm>
using namespace std;

long long int sum1, sum0;
int VERTEX;
int color[100001];

int reverse(int type) {
	if(type == 1) return 0;
	return 1;
}
bool isBipartite(int x, int type,vector<list<int> >&G) {
	bool bipartite = true;
	color[x] = type;
	// cout << "Start " << x << " : " << endl;
	list<int>::iterator y = G[x].begin();
	for( ; y != G[x].end() ; y++) {
		// cout << "	Adjacency " << *y << endl;
		if(color[*y] == -1) {
			VERTEX++; 
			if(!isBipartite(*y, reverse(color[x]), G)) bipartite = false;
			// cout << "hello " << *y << " , " << color[*y] << endl;
		}
		else if(color[*y] == color[x]) bipartite = false;
		
	}
	// cout << "Hello " << x << "Color " << color[x] << endl; 
	if(color[x] == 1) sum1++;
	else sum0++;
	
	return bipartite;
}
long long int gcd(long long int x, long long int y) {
	while(y != 0) {
		long long int t = x % y;
		x = y; y = t;
	}
	return x ;
}
long long int combination(long long int n, long long int k) {
	long long int r = 1;
	for(long long int i = 1; i <= k; i++, n--) {
		long long int a = gcd(r,i);
		r /= a;
		long long int b = n /(i/a);
		r *= b;
	}
	return r;
}
int main() {
	std::ios::sync_with_stdio(false);
	int t; cin >> t;
	while(t--) {
		int n, m; cin >> n >> m;
		vector<list<int> > G(n+1);
		for(int i = 1; i <= n; i++) color[i] = -1;

		for(int i = 0 ; i < m; i++) {
			int u,v; cin >> u >> v;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		long long int answer = 0;
		for(int i = 1; i <= n; i++) {
			if(color[i] == -1) {
				sum1 = 0; sum0 = 0; VERTEX = 1;
				if(isBipartite(i,1,G) == true) {
					long long int r = sum1 * sum0;
					answer += r;
					// cout << "bip " << answer << endl;
				} 
				else {
					// cout << "Vertex " << VERTEX << endl;
					long long int p = combination(VERTEX, 2);
					answer += p;
					// cout << "not " << answer << endl;
				}
				// cout << sum1 << "," << sum0 << "Vertex " << VERTEX << endl;
			}
		}
		answer -= m;
		cout << answer << endl;
		// puts("hello");
		// for(int i = 1; i <= n; i++) {
		// 	// cout << i << "-> " << "Color : " << color[i] << endl;
		// }
	}

	return 0;
}