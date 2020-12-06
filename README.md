# Matrix

Assignment 4



## 主要功能：

* 用“类”定义储存了矩阵的行、列、数据等信息，并重载定义了矩阵的+、*、=、<<运算符。
* 实现了运算过程中的内存维护，防止了析构函数删除指针时可能会出现的报错情况。



## 代码分析：

* ##### 矩阵类的定义：

* ```C++
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
  ```

* ##### 此外，定义了一个结构ai，用于内存维护：

* ```C++
  struct ai {
  	float** am;
  	int k;
  };
  ```

* ai中储存了矩阵数据的指针，以及一个用来计数的k，k代表指向指针的矩阵的数量，在析构函数删除指针时，会起到作用。

* ##### 构造函数：

* ```c++
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
  ```

* 构造函数matirx()会生成一个一行一列的矩阵，而matrix(x,y)会生成一个x行y列的矩阵，而它们的a.k默认为1；matrix（matrix）会生成一个和括号中相同的矩阵，由于两个矩阵的指针指向同一块内存，所以它们的结构ai中的计数器会加1。

* ##### 赋值函数：

* ```c++
  void matrix::fu(int x, int y, float z) {
  	this->a.am[x][y] = z;
  }
  ```

* 用于给矩阵x行y列赋值z。

* ##### “=”重载符：

* ```C++
  matrix& matrix::operator =(const matrix& m) {
  	this->row = m.row;
  	this->col = m.col;
  	delete[] this->a.am;
  	this->a = m.a;
  	this->a.k++;
  	return *this;
  }
  ```

* “=”重载符会令指向一块内存的指针增加一个，因此需要让a.k++；

* ##### “+”重载符：

* ```c++
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
  ```

* ##### “*”重载符：

* ```c++
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
  ```

* “*”分为三种情况，矩阵乘标量，标量乘矩阵，以及矩阵相乘。

* ##### “<<”重载符：

* ```c++
  std::ostream& operator <<(std::ostream& os, const matrix m) {
  	for (int i = 0; i < m.row; i++) {
  		for (int j = 0; j < m.col; j++) {
  			os << m.a.am[i][j] << " ";
  		}
  		cout << endl;
  	}
  	return os;
  }
  ```

* ##### 析构函数：

* ```c++
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
  ```

* 为了防止回收指针时，同一块内存被多次删除导致程序报错的情况，通过用结构ai来将指针与计数器k绑定，在回收指针时根据k的值进行操作，在k大于1时，令k-1，并输出一条提示信息表明进行过此操作，k=1时，删除指针的内存并输出信息表明删除成功。

* ##### 主程序：

* ```c++
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
  ```

* 创建了两个矩阵，大小分别为3X2的和2X3，通过随机函数为它们赋值。

* ```C++
      cout << m1 << endl;
  	cout << m2 << endl;
  	cout << m1 + m1 << endl;
  	cout << m1*2 << endl;
  	cout << 3*m2 << endl;
  	matrix m3=(m1*m2);
  	cout << m3 << endl;
  	return 0;
  ```

* 输出的部分检验了之前写过的所有方法。

* ##### 输出示例：

* <img src="D:\cx\assignment4\picture\图片1.png" alt="图片1" style="zoom: 50%;" />

* 输出矩阵的计算结果是正确的，并且在程序中创建的三个matrix中的指针都在最后被成功回收，说明析构函数成功起到了作用。

