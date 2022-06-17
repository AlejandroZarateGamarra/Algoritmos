#pragma once
#include<string>
using std::string;
using std::to_string;
class Contrasena {
private:
	int	length;
	string complexity;
	string password;
	char* arrChar;
public:
	Contrasena(string password = " ")
		:password(password)
	{
		length = this->password.length();
		complexity = "Infefinida";
	};
	~Contrasena() {}
	string getContrasena() 
	{
		return password;
	}
	int getLength() 
	{
		return length;
	}
	void definirComplejidad()
	{
		string dscrp;
		char* arr = new char[password.length() + 1];
		strcpy(arr, password.c_str());

	}
	string getComplexity() 
	{
		return complexity;
	}
	void setContrasena(string n) 
	{
		this->password = n;
	}
};