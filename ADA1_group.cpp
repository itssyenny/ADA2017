#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<iostream>
#include<vector>

using namespace std;

long long int sum1[2000001], sum2[2000001];

long long int min(long long int a, long long int b) { return (a < b)? a : b; }

long long int cost(long long int from, long long int to) { return (to * (sum1[to]-sum1[from-1]) - (sum2[to]- sum2[from-1])); }


int main() {
	long long int n, k; scanf("%llu%llu", &n, &k);

	long long int w[n+1];

	for(long long int i = 1; i <= n; i++) {
		
		scanf("%llu", &w[i]);
	}

	if(n == k) puts("0");
	else {
		if(n < k) k = min(20,k);
		//cout << "k " << k << endl;

		vector<vector<long long int> >dp(k+1, vector<long long int>(n+1));	//IT'S A MUST

		sum1[0] = 0; sum2[0] = 0;
		sum1[1] = w[1]; sum2[1] = w[1];

		for(long long int i = 2; i <= n ; i++) {
			sum1[i] = sum1[i-1] + w[i];
			sum2[i] = sum2[i-1] + (i * w[i]);
		}

		//this is DP
		for(long long int i = 1; i <= k; i++) {
			for(long long int j = 1; j <= n; j++) {
				
				if(i >= j) dp[i][j] = 0; //impossible
				else if(i == 1) dp[i][j] = cost(i,j);
				else if(i > 1) {

					long long int total = LLONG_MAX;
					
					for(long long int z = 1; z < j; z++) {
						total = min( dp[i-1][z] + cost(z+1, j), total);
					}
					dp[i][j] = total;
				}

				//printf("i %d j %d : %d\n", i, j, dp[i][j]);
			}

		}

		// for(int i = 1; i <=k; i++) {
		// 	for(int j = 1; j <= n; j++)
		// 		printf("%lld\n", dp[i][j]);
		// }
		printf("%llu\n", dp[k][n]);
	}

	return 0;

}
