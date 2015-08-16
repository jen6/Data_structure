#include <iostream>
#include <vector>

using namespace std;
class matrix {
private:
	int add_cnt = 0;
	int multipl_cnt = 0;
	size_t size;
	vector<int> real, imagin;
public:
	matrix(size_t s) : size(s) {};
	matrix(vector<int>& r, vector<int>& i, size_t s) : 
		real(r), imagin(i), size(s) {};
	void insert_data()
	{
		cout << "input real" << endl;
		for (size_t i = 0; i < size*size; ++i)
		{
			int input_data;
			cin >> input_data;
			real.push_back(input_data);
		}
		cout << "input imagine" << endl;
		for (size_t i = 0; i < size*size; ++i)
		{
			int input_data;
			cin >> input_data;
			imagin.push_back(input_data);
		}
	}


	matrix operator*(matrix& mt)
	{
		vector<int> v_real, v_imagin;
		for (size_t i = 0; i < size*size; ++i)
		{
			int i_real, i_imagin;
			i_real = this->real[i] * mt.real[i] - this->imagin[i] * mt.imagin[i];
			//(ac - bd)
			multipl_cnt += 2;
			i_imagin = this->real[i] * mt.imagin[i] + this->imagin[i] * mt.real[i];
			//+i(ad + bc)
			add_cnt += 2;
			multipl_cnt += 2;
			v_real.push_back(i_real);
			v_imagin.push_back(i_imagin);
		}
		auto ret = *this;
		ret.real = move(v_real);
		ret.imagin = move(v_imagin);
		return ret;
	}

	void print()
	{
		cout << size << endl;
		for (size_t i = 0; i < size; ++i)
		{
			for (size_t j = 0; j < size; ++j)
			{
				cout << "("
					<< real[i*size + j]
					<< ", "
					<< imagin[i*size + j]
					<< ") ";
			}
			cout << endl;
		}
		cout << "total add : " << add_cnt << endl;
		cout << "total multipl : " << multipl_cnt << endl;
	}

	~matrix() {};
};


int main()
{
	size_t matrix_size;
	cout << "matrix size : " << endl;
	cin >> matrix_size;
	matrix X(matrix_size), Y(matrix_size);

	X.insert_data();
	Y.insert_data();

	matrix Z = X * Y;
	Z.print();
}
