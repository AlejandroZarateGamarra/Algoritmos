#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include "Vector.h"
#include "Cuenta.h"

using std::function;
using std::cout;
using std::endl;
class Usuario
{
private:
	string nombre;
	Vector<Cuenta> cuentas;
public:
	Usuario() {
		this->nombre = "-";
	}
	~Usuario() {
		//archivo.close();
	}
	bool validar(string opc, function<bool(char)> comparar) {
		bool cmp = false;
		for (size_t i = 0; i < opc.length(); ++i)
		{
			cmp = comparar(opc[i]);
		}
		return cmp;
	}
	void insertarDatos(string n, string t, string c, string p)
	{
		auto lambda = [](char x) {return (x >= 65 && x <= 90) || (x >= 97 && x <= 122); };//nombre
		auto lambda2 = [](char x) {return (x >= 65 && x <= 90) || (x >= 97 && x <= 122) || (x >= 48 && x <= 57); };
		if (validar(n, lambda)) {
			this->nombre = n;
		}
		/*
		else {
			n = "---------";
			this->nombre = n;
		}
		/*
		if (!validar(c, lambda2)) {
			c = "---------";
		}
		*/
		Cuenta aux(t, c, p);
		this->cuentas.push_back(aux);
	}
	void insertarCuenta(Cuenta a) {
		this->cuentas.push_back(a);
	}
	void modificar(Cuenta a, int pos) {
		if (pos >= 0 || pos < cuentas.getSize()) {
			this->cuentas[pos] = a;
		}
		return;
	}
	void setNombre(string n) { this->nombre = n; }
	string getNombre() { return this->nombre; }
	string toString() {
		string toString;
		for (size_t i = 0; i < cuentas.getSize(); ++i) {//cuenta
			toString += this->nombre + "|" + this->cuentas[i].getTipo() + "|" + this->cuentas[i].getNombre() + "|" + this->cuentas[i].getContrasena() + "\n";
		}
		return toString;
	}
	void detalles()
	{
		cout << "\n\tDetalles de insercion\n";
		cout << "Numero de cuentas: " << cuentas.getSize() << endl;
		cout << "Nombre: " << nombre << endl;

		for (size_t i = 0; i < cuentas.getSize(); i++)
		{
			cout << "Numero de cuentas: " << cuentas.getSize() << endl;
		}

		cout << "\n\n";
	}
};