#pragma once
#include<string>
#include"Contrasena.h"

using std::string;
class Cuenta {
private:
	string tipo, nombre;
	Contrasena contrasenia;
public:
	Cuenta(string t = " ", string n = " ", string c = " ") :tipo(t), nombre(n){
		contrasenia.setContrasena(c);
	};
	~Cuenta() {}
	string getTipo() {
		return tipo;
	}
	string getNombre() {
		return nombre;
	}
	string getContrasena() {
		return contrasenia.getContrasena();
	}
	void setTipo(string t) {
		this->tipo = t;
	}
	void setNombre(string n) {
		this->nombre = n;
	}
	void setContrasena(string c) {
		this->contrasenia = c;
	}
};