/*starter file for lab2*/

unsigned int factorial(unsigned int n){
		unsigned int rc = 1;
		if (n > 1) {
				rc = n * factorial(n - 1)
		}
		return rc;
}

// O(n)
double power (double base, unsigned int n){
		if (n == 0) {
				return 1;
		}
		else
				return base * power(base, n - 1);
}

double powerChallenge(double base, unsigned int n) {
// O(log n)
		double x;

		if (n == 0) {
				return 1;
		}
		else if (n % 2 == 0) {
				x = powerChallenge(base, n / 2);
				return x * x;
		}
		else
				return base * powerChallenge(base, n - 1);
}

unsigned int fibonacci (unsigned int n){

		if (n < 2) {
				return n;
		}
		return (fibonacci(n - 1) + fibonacci(n - 2));
}
