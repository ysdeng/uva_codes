#include <stdio.h>
#include <math.h>

int main () {

	double PI = 2 * acos(0.0);

	int i, j, k;
	int a1, b1, t1, a2, b2, t2;
	int testCase = 0;
	while(1) {
		scanf("%d%d%d%d%d%d", &a1, &b1, &t1, &a2, &b2, &t2);
		if(0 == a1 && 0 == b1 && 0 == t1 
			&& 0 == a2 && 0 == b2 && 0 == t2) break;

		double a = a2, b = b2;

		double c = sqrt( a*a - b*b);
		double area = PI * a * b;

		double period = sqrt( (t1*t1) * (a*a*a) / (a1*a1*a1));
		double sweep = t2 * area / period;
		
		while (1) {
			if(sweep >= area) sweep -= area;
			else break;
		}
		
		double leftBoundary = 0, rightBoundary = 2*PI, phi;
		for( i = 0; i < 50; i++) {
			phi = (leftBoundary + rightBoundary) / 2;

			/* compute area of phi */
			double x = a * cos(phi);
			double y = b * sin(phi);
			
			double A = a*b*phi/2 - c*y/2;
			if (A > sweep)
				rightBoundary = phi;
			else
				leftBoundary = phi;
		}
		phi = (leftBoundary + rightBoundary) / 2;

		/* output */
		printf("Solar System %d: %.3lf %.3lf\n", ++testCase, a*cos(phi), b*sin(phi));
	}
	
}