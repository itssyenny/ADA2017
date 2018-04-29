#include<stdio.h>
#include<string.h>
#define imod 1000000007

long long int mod(long long int a , long long int b) {
	return ((a%b + b) % b);
}

void multiply(long long int Matrix1[2][2], long long int Matrix2[2][2]) {
	long long int x = Matrix1[0][0] * Matrix2[0][0] + Matrix1[0][1] * Matrix2[1][0];
	long long int y = Matrix1[0][0] * Matrix2[0][1] + Matrix1[0][1] * Matrix2[1][1];
	long long int w = Matrix1[1][0] * Matrix2[0][0] + Matrix1[1][1] * Matrix2[1][0];
	long long int z = Matrix1[1][0] * Matrix2[0][1] + Matrix1[1][1] * Matrix2[1][1];

	Matrix1[0][0] = mod(x,imod);
	Matrix1[0][1] = mod(y,imod);
	Matrix1[1][0] = mod(w,imod);
	Matrix1[1][1] = mod(z,imod);
}

void power(long long int Matrix1[2][2], long long int n) {
	if(n == 0 || n == 1) return;

	long long int Matrix2[2][2] = {{1,1}, {1,0}};

	power(Matrix1, n/2);
	multiply(Matrix1, Matrix1);

	if(n%2 != 0)
		multiply(Matrix1, Matrix2);
}

long long int fib(long long int n) {
	long long int Matrix1[2][2] = {{1,1}, {1,0}};
	if(n == 0 || n == 1) return 0;

	power(Matrix1, n-1);

	return Matrix1[0][0];
}

int main () {
	int T; scanf("%d", &T);
	long long int Hanhan;
	for(int i = 0; i < T; i++) {
		long long int a,b,n; scanf("%lld%lld%lld", &a, &b, &n);
		if(n == 0) Hanhan = 0;
		else if(n == 1) Hanhan = a;
		else if(n == 2) Hanhan = b;
		else {
			Hanhan = fib(n-1)* b + fib(n-2) * a;
			//printf("%lld n-2 %lld\n", fib(n-1), fib(n-2));
		}

		printf("%lld\n", mod(Hanhan,imod));

	}
	return 0;

}
// 10 21 31 52 83 135 218 353 
// 1  2  3.  4  5. 6   7. 8 