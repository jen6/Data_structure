
#ifndef STRING_H
#define STRING_H

#include <iostream>
#include <cstdlib>

class String
{
private:
	char* str;
	int len ,capacity;
	int* f;
public:
	// Constructor with content *init, length m
	String();
	String(char* );

	~String();

	// Return true if *this's string is equal to t's
	// Otherwise, return false
	bool operator==(String);
	friend std::ostream & operator<<(std::ostream & os, const String s);

	// Return the number of *this's characters
	int length();

	void push_back(char );

	void getFrequencyEachChar();

	String deleteSubString(int , int );

	String deleteChar(char );
};

String::String()
{
	len = 0;
	f = nullptr;
	capacity = 3;
	str = new char[capacity];
	str[0] = 0;
}

String::String(char * init)
{
	len = std::strlen(init);
	capacity = len + 1;
	f = nullptr;

	str = new char[capacity];
	std::copy(init, init + len + 1, str);
}

String::~String()
{
	delete[] str;
	if (f != nullptr)
	{
		delete[] f;
	}
}

bool String::operator==(String t)
{
	int ret = std::strcmp(str, t.str);
	if (ret == 0)
		return 1;
	else
		return 0;
}

// Return the number of *this's characters

int String::length()
{
	return len;
}

void String::push_back(char c)
{
	if (len == capacity)
	{
		capacity *= 2;
		char * ptr = new char[capacity];
		std::copy(str, str + len + 1, ptr);
		delete[] str;
		str = ptr;
	}
	str[len] = c;
	++len;
	str[len] = 0;
}

void String::getFrequencyEachChar()
{
	f = new int[256];
	for (size_t i = 0; i < length(); ++i)
	{
		int idx = static_cast<int>(str[i]);
		if (idx < 0)
		{
			throw std::exception("string out of range");
		}
		f[idx] += 1;
	}

	for (int i = 0; i < 255; ++i)
	{
		if (f[i] > 0)
		{
			char c = static_cast<char>(i);
			int d = static_cast<int>(f[i]);
			std::cout << c
				<< " : "
				<< d
				<< std::endl;
		}
	}
}

String String::deleteSubString(int idxStart, int deleteLength)
{
	String *ret_str = new String();

	int len;
	len = length();

	//start가 0보다 작거나 len보다 크거나 end가 start보다 작거나 end가 len보다 크면
	//익셉션 발생
	if (idxStart < 0 || idxStart > len || deleteLength < idxStart || deleteLength > len)
	{
		throw std::exception("start or len out of range");
	}

	for (size_t i = 0; i < len; ++i)
	{
		if (i < idxStart || i > deleteLength)
		{
			ret_str->push_back(str[i]);
		}
	}
	return *ret_str;
}

String String::deleteChar(char c)
{
	String *ret_str = new String();

	for (size_t i = 0; i < length(); ++i)
	{
		if (str[i] != c)
		{
			ret_str->push_back(str[i]);

		}
	}
	return *ret_str;
}
#endif