#include <iostream>
#include <cstdlib>

class SparseMatrix;

class MatrixTerm
{
public:
	MatrixTerm() : row(0), col(0), val(0){}
	MatrixTerm(int r, int c, int v) : row(r), col(c), val(v){}
private:
	int row, col, val;

	friend class SparseMatrix;
	friend std::ostream& operator<<(std::ostream& os, const SparseMatrix& m);
};

class SparseMatrix
{
public:
	SparseMatrix(int r, int c, int t);
	~SparseMatrix();
	inline void insert(const MatrixTerm&b);
	SparseMatrix Add(const SparseMatrix&b);
	SparseMatrix Subtract(const SparseMatrix&b);
private:
	int rows, cols, terms, capacity;
	MatrixTerm * smArray;

	friend std::ostream& operator<<(std::ostream& os, const SparseMatrix& m);
};

std::ostream& operator<<(std::ostream& os, const SparseMatrix& m)
{
	for (int i = 0; i < m.terms; ++i)
	{
		os << "row : "
			<< m.smArray[i].row
			<<" col : "
			<< m.smArray[i].col
			<<" val : "
			<< m.smArray[i].val
			<< "\n";
	}
	return os;
}

SparseMatrix& operator>>(const MatrixTerm mt, SparseMatrix& sm)
{
	sm.insert(mt);
	return sm;
}


SparseMatrix::SparseMatrix(int r, int c, int t)
	: rows(r), cols(c), capacity(t), terms(0), 
	smArray(new MatrixTerm[capacity]) {}

SparseMatrix::~SparseMatrix()
{
	delete[] smArray;
}

void SparseMatrix::insert(const MatrixTerm& b)
{
	if (b.val)
	{
		if (terms == capacity)
		{
			capacity *= 2;
			MatrixTerm * ptr = new MatrixTerm[capacity];
			std::copy(smArray, smArray + terms, ptr);
			delete[]smArray;
			smArray = ptr;
		}
		if (b.row > rows || cols < b.col || b.row < 0 || b.col < 0)
		{
			throw std::exception("row or col out of range");
			return;
		}

		smArray[terms] = b;
		terms += 1;
	}
}

SparseMatrix SparseMatrix::Add(const SparseMatrix& b)
{
	if (rows != b.rows || cols != b.cols)
	{
		throw std::exception("rows and cols not match");
	}

	SparseMatrix * ptr = new SparseMatrix(rows, cols, rows*cols);

	int aPos = 0, bPos = 0;
	while (aPos < terms && bPos < b.terms)
	{
		if (smArray[aPos].col < b.smArray[bPos].col)
		{
			ptr->insert(smArray[aPos]);
			++aPos;
		}
		else if(smArray[aPos].col > b.smArray[bPos].col)
		{
			ptr->insert(b.smArray[bPos]);
			++bPos;
		}
		else if(smArray[aPos].row < b.smArray[bPos].row)
		{
			ptr->insert(smArray[aPos]);
			++aPos;
		}
		else if (smArray[aPos].row > b.smArray[bPos].row)
		{
			ptr->insert(b.smArray[bPos]);
			++bPos;
		}
		else		//smArray[apos] == b.smarray[bpos] 
		{
			int val = smArray[aPos].val + b.smArray[bPos].val;
			ptr->insert(MatrixTerm(smArray[aPos].row, smArray[aPos].col, val));
			++aPos;
			++bPos;
		}
	}
	for (; aPos < terms; ++aPos)
	{
		ptr->insert(smArray[aPos]);
	}

	for (; bPos < b.terms; ++bPos)
	{
		ptr->insert(b.smArray[bPos]);
	}
	return *ptr;
}
SparseMatrix SparseMatrix::Subtract(const SparseMatrix& b) 
{
	if (rows != b.rows || cols != b.cols)
	{
		throw std::exception("rows and cols not match");
	}

	SparseMatrix * ptr = new SparseMatrix(rows, cols, rows*cols);

	int aPos = 0, bPos = 0;
	while (aPos < terms && bPos < b.terms)
	{
		if (smArray[aPos].col < b.smArray[bPos].col)
		{
			ptr->insert(smArray[aPos]);
			++aPos;
		}
		else if (smArray[aPos].col > b.smArray[bPos].col)
		{
			MatrixTerm buf(b.smArray[bPos].row, b.smArray[bPos].col, -(b.smArray[bPos].val));
			ptr->insert(buf);
			++bPos;
		}
		else if (smArray[aPos].row < b.smArray[bPos].row)
		{
			ptr->insert(smArray[aPos]);
			++aPos;
		}
		else if (smArray[aPos].row > b.smArray[bPos].row)
		{
			MatrixTerm buf(b.smArray[bPos].row, b.smArray[bPos].col, -(b.smArray[bPos].val));
			ptr->insert(buf);
			++bPos;
		}
		else		//smArray[apos] == b.smarray[bpos] 
		{
			int val = smArray[aPos].val - b.smArray[bPos].val;
			ptr->insert(MatrixTerm(smArray[aPos].row, smArray[aPos].col, val));
			++aPos;
			++bPos;
		}
	}
	for (; aPos < terms; ++aPos)
	{
		ptr->insert(smArray[aPos]);
	}

	for (; bPos < b.terms; ++bPos)
	{
		MatrixTerm buf(b.smArray[bPos].row, b.smArray[bPos].col, -(b.smArray[bPos].val));
		ptr->insert(buf);
	}
	return *ptr;
}


int main() 
{
	try {
		SparseMatrix s1(3, 3, 4);
		MatrixTerm(0, 0, 3) >> s1;
		MatrixTerm(1, 1, 1) >> s1;
		MatrixTerm(2, 2, 2) >> s1;
		std::cout << "s1\n" << s1 << std::endl;

		SparseMatrix s2(3, 3, 4);
		MatrixTerm(0, 0, 3) >> s2;
		MatrixTerm(1, 0, 1) >> s2;
		MatrixTerm(2, 2, 2) >> s2;
		std::cout << "s2\n" << s2 << std::endl;

		SparseMatrix s3 = s1.Add(s2);
		SparseMatrix s4 = s1.Subtract(s2);
		std::cout << "s3\n" << s3 << std::endl;
		std::cout << "s4\n" << s4 << std::endl;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}