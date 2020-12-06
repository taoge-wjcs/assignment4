#include"matrix.h"
matrix::matrix() {
	this->row = 1;
	this->col = 1;
	this->a.am = new float* [row];
	for (int i = 0; i < row; i++) {
		a.am[i] = new float[col];
	}
	this->a.k = 1;
}
matrix::matrix(int x, int y) {
	this->row = x;
	this->col = y;
	this->a.am = new float* [row];
	for (int i = 0; i < row; i++) {
		a.am[i] = new float[col];
	}
	this->a.k = 1;
}
matrix::matrix(const matrix& m) {
	this->row = m.row;
	this->col = m.col;
	this->a = m.a;
	this->a.k++;
}
matrix::~matrix() {
	if (this->a.k > 1) {
		this->a.k--;
		cout << row << "*" << col << " -1\n";
	}
	else if(a.k==1) {
		cout << "delete " << this->row << "*" << this->col << endl;
		delete[] this->a.am;
	}
}
void matrix::fu(int x, int y, float z) {
	this->a.am[x][y] = z;
}
matrix matrix::operator+(const matrix& m) {
	matrix n(m.row,m.col);
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			n.a.am[i][j] = m.a.am[i][j] +this->a.am[i][j];
		}
	}
	n.a.k++;
	return n;
}
matrix operator *(const float b, const matrix& m) {
	matrix n(m.row, m.col);
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			n.a.am[i][j] = m.a.am[i][j] * b;
		}
	}
	n.a.k ++;
	return n;
}
matrix matrix::operator*(const float b)const {
	matrix n(this->row, this->col);
	for (int i = 0; i < this->row; i++) {
		for (int j = 0; j < this->col; j++) {
			n.a.am[i][j] = this->a.am[i][j] * b;
		}
	}
	n.a.k ++;
	return n;
}
std::ostream& operator <<(std::ostream& os, const matrix m) {
	for (int i = 0; i < m.row; i++) {
		for (int j = 0; j < m.col; j++) {
			os << m.a.am[i][j] << " ";
		}
		cout << endl;
	}
	return os;
}
matrix& matrix::operator =(const matrix& m) {
	this->row = m.row;
	this->col = m.col;
	delete[] this->a.am;
	this->a = m.a;
	this->a.k++;
	return *this;
}
matrix matrix::operator*(const matrix& m) {
	matrix n(this->row, m.col);
	for (int i = 0; i < n.row; i++) {
		for (int j = 0; j < n.col; j++) {
			n.a.am[i][j] = 0;
		}
	}
	n.a.k = 0;
	if (this->col != m.row) {
		cout << "The matrices can not multiply" << endl;
		return *this;
	}
	else {
		for (int i = 0; i < n.row; i++) {
			for (int j = 0; j < n.col; j++) {
				for (int p = 0; p < this->col; p++) {
					n.a.am[i][j] += this->a.am[i][p] * m.a.am[p][j];
				}
			}
		}
		return n;
	}
}