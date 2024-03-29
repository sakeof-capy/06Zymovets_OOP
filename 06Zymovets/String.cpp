#include "String.h"

//***************************************************
//��������� � ���������� ������� ���� ����� String:
//����������� �� �-������, STL-������, ���������� 
//� ��������� ����������� � ���������, ������� 
//���������, ��������� [], +, ==,!=. ����������� 
//��������� ��������� ������� �������� ��� 
//�������� �������, �-������� � STL-�������.
//Developed by Ruslan Zymovets (IPZ, group 1)
//on March 15
//Version 1.0
//***************************************************

size_t String::freeId = 0;

String::String()
	: _len(0), _id(++freeId), _allocator(new char[1]{'\0'})
{
#ifndef NDEBUG
	cout << "--String id" << _id << " created [String()]." << endl;
#endif // !NDEBUG

	return;
}

String::String(const char ch)
	: _len(1), _id(++freeId), _allocator(new char[2]{ch, '\0'})
{
#ifndef NDEBUG
	cout << "--String id" << _id << " created [String(const char)]." << endl;
#endif // !NDEBUG

	return;
}

String::String(const char* c)
	: _len(strlen(c)), _id(++freeId), _allocator(new char[_len + 1])
{
#ifndef NDEBUG
	cout << "--String id" << _id << " created [String(const char*)]." << endl;
#endif // !NDEBUG
	strcpy(_allocator, c);
	return;
}

String::String(const string& s)
	: _len(s.length()), _id(++freeId), _allocator(new char[_len + 1])
{
#ifndef NDEBUG
	cout << "--String id" << _id << " created [String(const string&)]." << endl;
#endif // !NDEBUG
	strcpy(_allocator, s.c_str());
	return;
}

String::String(const String& s)
	: _len(s.length()), _id(++freeId), _allocator(new char[_len + 1])
{
#ifndef NDEBUG
	cout << "--String id" << _id << " copied [String(const String&)]." << endl;
#endif // !NDEBUG
	strcpy(_allocator, s.c_str());
	return;
}

String::String(String&& s) 
	: _len(s._len), _id(++freeId), _allocator(s._allocator)
{
#ifndef NDEBUG
	cout << "--String id" << _id << " created [String(String&&)]." << endl;
#endif // !NDEBUG

	s._len = 0;
	s._allocator = nullptr;

	return;
}

String::String(char*&& s)
	: _len(strlen(s)), _id(++freeId), _allocator(s)
{
#ifndef NDEBUG
	cout << "--String id" << _id << " created [String(char*&& s)]." << endl;
#endif // !NDEBUG

	s = nullptr;

	return;
}

String::~String()
{
#ifndef NDEBUG
	cout << "--String id" << _id << " deleted." << endl;
#endif // !NDEBUG

	delete[] _allocator;
	return;
}

String& String::operator=(const String& s)&
{
#ifndef NDEBUG
	cout << "--String id" << s._id << " copy-assigned to id" << _id << " [operator=(const String& s)&]." << endl;
#endif // !NDEBUG

	if (this == &s)
	{
		return *this;
	}

	delete _allocator;
	_len = s._len;
	_allocator = new char[s._len + 1];
	strcpy(_allocator, s._allocator);

	return *this;
}

String& String::operator=(String&& s)&
{
#ifndef NDEBUG
	cout << "--String id" << s._id << " move-assigned to id" << _id << " [operator=(String&& s)&]." << endl;
#endif // !NDEBUG

	delete _allocator;
	_allocator = s._allocator;
	_len = s._len;

	s._allocator = nullptr;
	s._len = 0;

	return *this;
}

String& String::operator=(char*&& s)&
{
#ifndef NDEBUG
	cout << "--char* " << s << " move-assigned to id" << _id << " [operator=(char*&& s)&]." << endl;
#endif // !NDEBUG

	_len = strlen(s);
	_allocator = s;

	s = nullptr;

	return *this;
}

String& String::operator+=(const String& s)&
{
	return *this = *this + s;
}

bool operator==(const String& s1, const String& s2)
{
	if (s1.length() != s2.length()) return false;
	
	for (size_t i = 0; i < s1.length(); ++i)
	{
		if (s1[i] != s2[i]) return false;
	}

	return true;
}

bool operator!=(const String& s1, const String& s2)
{
	return !(s1 == s2);
}

String operator+(const String& s1, const String& s2)
{
	const size_t res_lengtn = s1.length() + s2.length() + 1;
	char* res = new char[res_lengtn];
	
	for (size_t i = 0; i < res_lengtn - 1; ++i)
	{
		res[i] = (i < s1.length()) ? s1[i] : s2[i - s1.length()];
	}

	res[res_lengtn - 1] = '\0';

	return std::move(res); //String(char*&&) call!
}

ostream& operator<<(ostream& o, const String& s)
{
	for (size_t i = 0; i < s.length(); ++i)
	{
		o << s[i];
	}

	return o;
}