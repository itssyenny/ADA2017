#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<iostream>
#include<cstring>
using namespace std;


int main () {
	int T; scanf("%d", &T);
	while(T--) {
		int n, k; scanf("%d%d", &n, &k);
		int dp[n+1][k+1][2], count[10001]={0};
		long long int sum[10001]={0};
		for(int i = 0 ; i <= n; i++) {
			for(int j = 0; j < k ; j++) {
				dp[i][j][0] = 0; //store the number of fish
				dp[i][j][1] = 0; //store the pool
			}
		}
		
		long long int max = -1;
		int max_idx = -1, temp = k;

		for(int i = 1; i <= n; i++) {
			int merge[10001]={0}; //not initial, 
			int f,d; scanf("%d%d", &f, &d);
			int index1 = 0, index2 = 0;
			//if(f == 0) continue;
			if(i == 1) {
				while(f >= 0 && index1 < temp) {
					//printf("f %d\n", f);
					dp[i][index1][0] = f;
					dp[i][index1++][1] = i;
					//printf("dp %d, %d\n",  dp[i][index1][0], dp[i][index1][1]);
					f -= d;
				}
				// puts("merge array");
				// for(int g = 0 ; g < temp; g++) {
				// 	printf("%d ", merge[g]);
				// } puts("");


				
				// puts("dp array");
				// for(int h = 0; h < temp; h++) {
				// 	printf("%d ", dp[i-1][h][0]);
				// }puts("");
						
				
			}
			else {
				while(f >= 0 && index2 < temp) {
					merge[index2++] = f;
					f -= d;
					
				}
				// puts("merge array");
				// for(int g = 0 ; g < temp; g++) {
				// 	printf("%d ", merge[g]);
				// } puts("");


				
				// puts("dp array");
				// for(int h = 0; h < temp; h++) {
				// 	printf("%d ", dp[i-1][h][0]);
				// }puts("");

				index1 = 0; index2 = 0;
				for(int j = 0; j < temp ; j++) {
					if(dp[i-1][index1][0] > merge[index2]) { //dp is bigger
						dp[i][j][0] = dp[i-1][index1][0];
						
						dp[i][j][1] = dp[i-1][index1][1];
						index1++;
					} else {	//merge is bigger
						dp[i][j][0] = merge[index2];
						dp[i][j][1] = i;
						index2++;
					}
				}
			}
			//printf("temp %d\n", temp);
			for(int z = 0; z < temp; z++) {
				sum[i] += dp[i][z][0];
			}
			if(sum[i] > max) {
				max = sum[i];
				max_idx = i;
			}

			temp--;

		} //end of for

		// for(int i = 1; i <= n; i++ ) {
		// 	for(int j = 0; j < k; j++) {
		// 		printf("%d ", dp[i][j][0]);
		// 		//printf("dp[%d][%d][1] %d\n", i,j, dp[i][j][1]);
				
		//  	} puts("");
		// }
		
		//printf("max = %lld at row %d\n", max, max_idx);

		for(int j=0;j<k;j++){
			int temp = dp[max_idx][j][1];
			count[temp]++;
		}

		int step = 0, index = 1;
		while(index <= n) {
			if(count[index] == 0 && count[index+1]!=0) step++;
			else if(count[index] > 0 && count[index+1] == 0) step++;
			else if(count[index] > 0 && count[index+1] > 0) step+= 2;
			index++;
		}
		
		printf("%lld %d\n", max, step);

		int turn = 1;
		index = 1;
		while(step >= 1) {
			if(count[index] == 0 && count[index+1]!=0) {
				printf("move %d\n", index+1);
				step--;
			}
			else if(count[index] > 0 && count[index+1] == 0) {
				printf("fish %d\n", count[index]);
				step--;
			}
			else if(count[index] > 0 && count[index+1] > 0) {
				printf("fish %d\n", count[index]);
				printf("move %d\n", index+1);
				step -= 2;
			}
			index++;
		}

		
	} //end of while


	return 0;
}