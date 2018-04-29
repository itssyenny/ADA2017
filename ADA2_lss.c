#include<stdio.h>
int memo[2001][2001][21];

int max(int a , int b) {
	return (a > b) ? a : b;
}
int maxx(int a , int b , int c) {
	int x = max(a,b);
	return (x > c) ? x : c;
}
//memo (n, m)
// void lcs(int a[], int b[], int n, int m, int unmatch, int others) {
// 	for(int i = 0; i <= n; i++) memo[i][0] = i * others;
// 	for(int j = 0; j <= m; j++) memo[0][j] = j * others;

// 	int thus;
// 	//printf("n %d m %d\n", n, m);
// 	for(int i = 1; i <= n; i++) {
// 		//printf("i %d\n", i);
// 		for(int j = 1; j <= m; j++) {
			
// 			if(a[i-1] == b[j-1]) thus = memo[i-1][j-1];
// 			else thus = memo[i-1][j-1] + unmatch;
			
// 			memo[i][j] = maxx(thus, memo[i-1][j]+others, memo[i][j-1]+others);
// 		}
// 	}

// }
int LSS(int a[], int b[], int n, int m, int change) {
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			for(int k = 0; k <= change; k++) {
				if(i == 0 || j == 0) memo[i][j][k] = 0;
				else if(a[i-1] == b[j-1]) memo[i][j][k] = memo[i-1][j-1][k] + 1;
				else {
					if( k > 0) memo[i][j][k] = maxx(memo[i-1][j-1][k-1]+1, memo[i-1][j][k], memo[i][j-1][k]);
					else memo[i][j][k] = max(memo[i-1][j][k], memo[i][j-1][k]);
				}
				

			}
		}
	}
	return memo[n][m][change];

			
}

int main() {
	int n,m,k; scanf("%d%d%d", &n, &m, &k);

	int a[n+1], b[m+1];
	for(int i = 0; i < n; i++) scanf("%d", &a[i]);
	for(int i = 0; i < m; i++) scanf("%d", &b[i]);

	// lcs(a,b,n,m,7,4);
	int ret = LSS(a,b,n,m,k);
	
	for(int i = 0; i <= n; i++) {
		for(int j = 0; j <= m; j++) {
			for(int z = 0 ; z <= k ; z++) {
				printf("(%d,%d,%d) %d\n", i,j,z,memo[i][j][z]);
			}
		}		
	}

	//find_solution(a,b,n,m,7,4);

	//printf("replace %d, ret %d\n", replace[0], ret[0]);

	// if(replace > k) ret += k;
	// else if(replace <= k) ret += replace;

	printf("%d\n", ret);
	
	return 0;

}

/*
5 4 2
2 1 3 4 2
2 4 3 2

8 9 1
3 5 6 7 8 9 1 0
6 5 7 8 1 0 9 0 1
*/