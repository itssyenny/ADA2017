#include<stdio.h>
#include<vector>
#include<stack>
#include<stdint.h>
#include<bitset>
#include<iostream>

using namespace std;

int mod(int a , int b) {
	if( a >= 0  && a <= 2) return a;
	else return ((a%b + b) % b);
}


int main () {
	int T; scanf("%d", &T);

	for(int casei = 1; casei <= T; casei++) {
		
		int n; scanf("%d", &n);

		unsigned long long int l,r; scanf("%llu%llu", &l, &r);

		printf("Case #%d:\n", casei);

		vector<stack<int> >V(3);
		
		bitset<101>B;

		unsigned long long int initial = l-1;
		int j = n-1;
		for(int c = 0; c < n; c++, j--) {
			B[j] = initial % 2;
			initial /= 2;
		}
		// for(int x = 0; x < n; x++)
		// 	cout << B[x];
		// cout << endl;

		int from,to, disk = 1;

		to = (B[0] == 0) ? 0 : 2;
		

		for(int digit = 1; digit <= n; digit++) {
			V[to].push(disk);
			from = to;
			if(digit == n) break;
			disk = disk+1;
			
			//cout << "digit " << digit << " " << B[digit] << endl;
			if(B[digit-1] == B[digit]) {
				//cout << "digit " << digit << B[digit-1] << " " << B[digit] << endl;
				to = from;
			}else if(B[digit-1] != B[digit]) {
					if((digit+1)%2 == 0) {
						to = (B[digit] == 1) ? from+1 : from-1 ;
					} else if((digit+1) %2 != 0) {
						if(B[digit] == 1) to = from-1;
						else to = from+1;

					}
			}
			to = mod(to, 3);
			//cout << to << endl;
			// cout << "digit " << digit << endl;
		 // 	cout << "from " << from << endl;
		 // 	cout << "to " << to << endl;
			
		}
		//print_board(V);

		//printf("%llu\n", l-1);

		unsigned long long int m = l;
		for(int times = 0; times <= (r-l); times++, m++ ) {
			switch(m%3) {
				case 0 :
					if(n % 2 == 0) {from = 1; to = 2;}
					else if(n % 2 == 1) {from = 2; to = 1;}
					break;
				case 1:
					if(n % 2 == 0) {from = 0; to = 1;}
					else if(n % 2 == 1) {from = 0; to = 2;}
					break;
				case 2 :
					if(n % 2 == 0) {from = 0; to = 2;}
					else if(n % 2 == 1) {from = 0; to = 1;}
					break;
				default : break;
			}

			//is it legal ?
			int legal = 1;
			
			if(V[from].empty() ) legal = 0;
			else if(!V[from].empty() && !V[to].empty() ) {
				if(V[from].top() < V[to].top() ) legal = 0;
			}
			//if(m == 89789453) printf("%d %d legal %d \n", V[from].top(), V[to].top(), legal);
			if(legal == 0) {
				int temp = from; // from = 2
				from = to;
				to = temp; // to = 1
			} 

			int a = V[from].top();
			V[from].pop();
			V[to].push(a);

			
			printf("Step %llu: #%d -> #%d\n", m, from+1, to+1);
		}
		
	}
	return 0;

}