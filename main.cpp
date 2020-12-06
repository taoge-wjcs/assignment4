#include"matrix.h"
int main() {
	int r1 = 3;
	int r2 = 2;
	int c1 = 2;
	int c2 = 3;
	matrix m1(r1, c1), m2(r2, c2);
	for (int i = 0; i < r1; i++) {
		for (int j = 0; j < c1; j++) {
			m1.fu(i, j, rand() % 10);
		}
	}
	for (int i = 0; i < r2; i++) {
		for (int j = 0; j < c2; j++) {
			m2.fu(i, j, rand() % 10);
		}
	}

	cout << m1<<endl;
	cout << m2 << endl;
	cout << m1 + m1 << endl;
	cout << m1*2 << endl;
	cout << 3*m2 << endl;
	matrix m3=(m1*m2);
	cout << m3 << endl;
	return 0;
}