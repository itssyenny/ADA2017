#include<stdio.h>
#include<iostream>
#include<stdint.h>
#include<string>
#include<vector>
#include<queue>
using namespace std;
int l[1000001], r[1000001];

int main() {
	string s; cin >> s;

	int len = s.size();
	int count = 0;

	for(int i = 0; i < len; i++) {
		if(s[i] == '?') count++;
	}

	for(int i = 0; i < count; i++) {
		scanf("%d%d", &l[i], &r[i]);
	}

	uint64_t cost = 0, x;
	int prefix = 0, the_index = 0;

	priority_queue<int,vector<int>, greater<int> > Q;

	for(int i = 0; i < len; i++) {
		if(s[i] == '(') prefix++;
		else if(s[i] == ')') {
			prefix--;
			if(prefix < 0) {
				if(Q.empty()) break;
				else {
					if(prefix < 0) {
						x = Q.top();
						Q.pop();
						cost += x;
						prefix = 1;
					}
				}
			}
		} 
		else if(s[i] == '?') {
			cost += r[the_index];
			Q.push(l[the_index]-r[the_index]);
			prefix--;
			//if pop zero is invalid
			if(prefix < 0) {
				if(Q.empty()) break;
				else {
					if(prefix < 0) {
						x = Q.top();
						Q.pop();
						cost += x;
						prefix = 1;
					}
				}
			}
			the_index++;
		}
		//printf("%d prefix %d\n", i, prefix);
	}
	if(prefix != 0) {
		// while(!Q.empty()) {
		// 	Q.pop();
		// }
		puts("Impossible");
	}else printf("%llu\n", cost);

	return 0;
}


