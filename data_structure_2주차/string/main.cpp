#include <iostream>
#include <string>
#include <cstdlib>

void frequency(std::string& str)
{
	char frequency_array[256] = { 0, };	//빈도수 저장하는 배열
	for (size_t i = 0; i < str.length(); ++i)
	{
		int idx = static_cast<int>(str[i]);
		if (idx < 0)
		{
			throw std::exception("string out of range");
		}
		frequency_array[idx] += 1;
	}

	for (int i = 0; i < 255; ++i)
	{
		if (frequency_array[i] > 0)
		{
			char c = static_cast<char>(i);
			int d = static_cast<int>(frequency_array[i]);
			std::cout << c 
					<< " : " 
					<< d
					<< std::endl;
		}
	}
}

std::string Delete(std::string & str)
{
	std::string ret_str;
	size_t start, end;

	size_t len;
	len = str.length();
	
	std::cout << "input start end" << std::endl;
	std::cin >> start >> end;

	//start가 0보다 작거나 len보다 크거나 end가 start보다 작거나 end가 len보다 크면
	//익셉션 발생
	if (start < 0 || start > len || end < start || end > len)
	{
		throw std::exception("start or len out of range");
	}

	for (size_t i = 0; i < len; ++i)
	{
		if (i < start || i > end)
		{
			ret_str.push_back(str[i]);
		}
	}

	return ret_str;
}

std::string CharDelete(std::string& str)
{
	std::string ret_str;
	char delete_char;
	
	std::cout << "input delete char" << std::endl;

	std::cin >> delete_char;

	for (size_t i = 0; i < str.length(); ++i)
	{
		if (str[i] != delete_char)
		{
			ret_str.push_back(str[i]);

		}
	}

	return ret_str;
}


int main()
{
	std::string s1 = "asdfasndflfnlksadfnlaksdnflnl";
	std::cout << "original string : " << s1 << std::endl;
	try 
	{	
		frequency(s1);
		std::cout << Delete(s1) << std::endl;
	}
	catch (std::exception &e) 
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}
	std::cout << CharDelete(s1) << std::endl;
	return 0;
}