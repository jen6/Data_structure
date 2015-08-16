#define _SCL_SECURE_NO_WARNINGS
//std::copy c4999 error disable
//http://codeyarns.com/2010/08/30/visual-c-c4996-warning-on-copy-with-array-parameters/
#include <iostream>
#include <algorithm>

/*
	시간복잡도는 Add함수가 O(m+n)이고
	Multyply함수안에서는 for문이 m*n번돈다.
	그러므로 Multyply함수의 시간복잡도는 O(mn(m+n))이다.
*/

class Polyminal;

class Term {
	friend Polyminal;
	Term() : coef(0), exp(0) {}
private:
	float coef;
	int exp;
};

class Polyminal {
	enum : int {init_capacity = 2};
public:
	Polyminal();
	const Polyminal Multiply(const Polyminal &b);
	~Polyminal();
	const Polyminal Add(const Polyminal &b);
	void NewTerm(const float coef, const int exp);
	void operator=(const Polyminal&);
	void print();
private:
	Term * termArray;
	int capacity;		//term arry 크기
	int terms;			//차수
};
Polyminal::Polyminal() : termArray(new Term[init_capacity]())
{
	capacity = init_capacity;
	terms = 0;
}

Polyminal::~Polyminal()
{
	delete[] termArray;
}

const Polyminal Polyminal::Multiply(const Polyminal &b)
{
	Polyminal *c = new Polyminal();
	for (size_t aPos = 0; aPos < terms; aPos++)
	{
		Polyminal buf;
		for (size_t bPos = 0; bPos < b.terms; bPos++)
		{
			float term_buf = termArray[aPos].coef * b.termArray[bPos].coef;

			if (term_buf)
			{
				buf.NewTerm(term_buf, termArray[aPos].exp + b.termArray[bPos].exp);
			}
		}
		std::cout << "buf : ";
		buf.print();
		*c = c->Add(buf);
		std::cout << "c : ";
		c->print();
	}

	return *c;
}

const Polyminal Polyminal::Add(const Polyminal &b)
{
	Polyminal *c = new Polyminal();
	int aPos = 0; 
	int bPos = 0;

	while ((aPos < terms) && (bPos < b.terms))
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp) 
		{
			float t = termArray[aPos].coef + b.termArray[bPos].coef;
			if (t)
			{
				c->NewTerm(t, termArray[aPos].exp);
			}
			++aPos;
			++bPos;
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp)
		{
			//b의 차수가 더 클 때
			c->NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
			++bPos;
		}
		else
		{
			//a의 차수가 더 클때
			c->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
			++aPos;
		}
	}

	for (; aPos < terms; ++aPos)
	{
		c->NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	}
	for (; bPos < b.terms; ++bPos)
	{
		c->NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	}
	return *c;
}

void Polyminal::NewTerm(const float coef, const int exp)
{
	if (terms == capacity)
	{
		capacity *= 2;
		Term * temp = new Term[capacity];
		std::copy(termArray, termArray + terms, temp);
		delete[] termArray;
		termArray = temp;
	}

	termArray[terms].coef = coef;
	termArray[terms].exp = exp;
	++terms; //term증가
}

void Polyminal::operator=(const Polyminal &b)
{
	Term * ptr = new Term[b.terms];
	std::copy(b.termArray, b.termArray + b.terms, ptr);
	delete[] termArray;
	termArray = ptr;
	terms = b.terms;
	capacity = b.capacity;
}

void Polyminal::print()
{
	for (int i = 0; i < terms; ++i)
	{
		std::cout
			<< "( "
			<< termArray[i].coef
			<< " , "
			<< termArray[i].exp
			<< " ) ";
	}
	std::cout << std::endl;
}

int main()
{
	Polyminal a, b;
	a.NewTerm(3, 2);
	a.NewTerm(2, 1);
	a.NewTerm(4, 0);

	b.NewTerm(1, 1);
	b.NewTerm(1, 0);

	a.print();
	b.print();


	Polyminal c = a.Add(b);
	Polyminal d = a.Multiply(b);

	c.print();
	d.print();

}	