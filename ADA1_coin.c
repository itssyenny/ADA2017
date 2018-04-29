#include<stdio.h>
#include<string.h>
//n : tipe coins
//p : total yang harus dibayar
#define imod 1000000007

long long int mod(long long int a , long long int b) {
	return ((a%b + b) % b);
}
int A[100];
long long int Coins(int n, int p) {
	long long int helpme[p+1];
	memset(helpme, 0, sizeof(helpme));

	helpme[0] = 1;
	for(int i = 0; i < n; i++) {
		for(int j = A[i]; j <= p; j++) {
			helpme[j] += mod(helpme[j-A[i]], imod);
			//printf("helpme[%d] %d , helpme[%d] %d\n",j, helpme[j], j-A[i], helpme[j-A[i]]);
		}
	}
	return helpme[p];
}
int main () {
	int n, p; scanf("%d%d", &n, &p);
	long long int count = 0;

	for(int i = 0; i < n; i++) {
		scanf("%d", &A[i]);
	}

	count += Coins(n,p);
	printf("%lld\n", mod(count,imod));
	return 0;
}