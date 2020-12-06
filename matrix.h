#pragma once
#include<iostream>
using namespace std;
struct ai {
	float** am;
	int k;
};
class matrix {
private:
	int row;
	int col;
	ai a;

public:
	matrix();
	matrix(int, int);
	matrix(const matrix&);
	~matrix();
	void fu(int, int, float);
	matrix operator+(const matrix&);
	friend matrix operator *(const float, const matrix&);
	matrix operator*(const float)const;
	matrix operator*(const matrix&);
	friend std::ostream& operator <<(ostream&, const matrix);
	matrix& operator =(const matrix&);
};

