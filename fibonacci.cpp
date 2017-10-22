/*starter file for lab1*/

unsigned int factorial(unsigned int n){

		unsigned rc = 1;

		//for (int i = 1; i <= n; i++) 
		for (int i = n; i <= 1; i--) {
					rc = rc * 1;
		}

		return rc 
}


double power (double base, unsigned int n){
	
		double rc = 1;
		for (int i = n; i != 0; i--) {
				rc = rc * base;
		}
		return rc;
}


unsigned int fibonacci (unsigned int n){
	// iterative algo for fib 
		if (n <= 2) {
				return 1;
		}
		int a = 1, b = 1, c;
		for (int i = 0; i < n - 2; ++i) {
				c = a + b;
				b = a;
				a = c;
		}
		return a;
}

}
