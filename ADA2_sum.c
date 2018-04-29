#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main() {
	int t; scanf("%d", &t);
	while(t--) {

		unsigned long long int  n, k; scanf("%llu%llu", &n , &k);
		unsigned long long int a[n], note[n];

		for(unsigned long long int i = 0; i < n ; i++) {
			scanf("%llu", &a[i]);
		}

		int count = 0, is_subset = 1;
		memset(note, 0, n);

		for(unsigned long long int i = n-1 ; ; i--) {
			if(k >= a[i]) {
				//printf("a %llu, k %llu\n", a[i], k);
				k -= a[i];
				note[count] = a[i];
				//printf("coutn %d note %llu\n", count, note[count]);
				count++;
			} 

			if(i == 0 || k == 0) break;
		}
		
		if(k != 0) is_subset = 0;

		if(is_subset == 0) {
			puts("-1");
		} else {

			printf("%d\n", count);
			for(int i = count-1; i >= 0 ; i--) {
				printf("%llu%c", note[i], " \n"[i == 0]);
			}
		}
		
	}
	return 0;
}