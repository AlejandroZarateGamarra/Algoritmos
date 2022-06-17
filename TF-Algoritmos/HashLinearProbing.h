#ifndef __HASHTABLA_HPP__
#define __HASHTABLA_HPP__
#include <iostream>
#include <functional>
#include <cmath>
#include "HashEntidad.h"
using std::function;
template<class V>
class HashTabla {
private:
	HashEntidad<V>** tabla;
	int numElementos;
	int TABLE_SIZE;
	size_t colision;
public:
	HashTabla(int TABLE_SIZE = 128) {
		if (primoCercano(TABLE_SIZE) != -1) this->TABLE_SIZE = primoCercano(TABLE_SIZE);
		else this->TABLE_SIZE = TABLE_SIZE;
		tabla = new HashEntidad<V>*[this->TABLE_SIZE];
		for (int i = 0; i < this->TABLE_SIZE; ++i) {
			tabla[i] = nullptr;
		}
		numElementos = 0;
		colision = 0;
	}
	~HashTabla()
	{
		for (int i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr) {
				delete tabla[i];
			}
		}
		delete[] tabla;
	}
	void swap(HashEntidad<V>* a, HashEntidad<V>* b) {
		HashEntidad<V> aux = *a;
		*a = *b;
		*b = aux;
	}
	HashEntidad<V> retornarValor(size_t pos) {
		if (tabla[pos] != nullptr)
			return *tabla[pos];
	}
	HashEntidad<V>* retornarPuntero(size_t pos) {
		if (tabla[pos] != nullptr)
			return tabla[pos];
		else return nullptr;
	}
	bool esPrimo(int n) {
		if (n <= 1) return false;
		for (int i = 2; i < sqrt(n); ++i) {
			if (n % i == 0) {
				return false;
				break;
			}
		}
		return true;
	}
	int primoCercano(int n) {
		for (size_t i = n; i < 2 * n - 2; ++i) {
			if (esPrimo(i)) {
				return i;
			}
		}
		return -1;
	}
	void setPrimo() {
		if (primoCercano() == -1) return;
		this->TABLE_SIZE = primoCercano();
	}
	int suma(string& a) {
		int x = 0;
		for (size_t i = 0; i < a.length(); ++i) {
			x += int(a[i]);
		}
		return x;
	}
	//Direccionamiento según Prueba Lineal
	void insertar(string key, V value) {
		//Hash prima
		int base, step, hash;
		//validar si la tabla está llena
		if (numElementos == TABLE_SIZE) { return; }
		//Función Hash1
		base = suma(key) % TABLE_SIZE;
		hash = base;
		//constante para Hash2
		step = 0;
		while (tabla[hash] != nullptr)
		{
			//Función Hash2
			hash = (base + step) % TABLE_SIZE;
			step++;
			colision++;
		}
		//almacenarlo en la tabla
		tabla[hash] = new HashEntidad<V>(key, value);
		numElementos++;
	}
	void insertar_pos(size_t pos, string key, V value) {
		//Hash prima
		int step, base, hash;
		//validar si la tabla está llena
		if (numElementos == TABLE_SIZE) { return; }
		base = pos;
		hash = base;
		//constante para Hash2
		step = 0;
		while (tabla[hash] != nullptr)
		{
			//Función Hash2
			hash = (base + step) % TABLE_SIZE;
			step++;
			colision++;
		}
		//almacenarlo en la tabla
		tabla[hash] = new HashEntidad<V>(key, value);
		numElementos++;
	}
	size_t getColision() {
		return colision;
	}
	int size() {
		return TABLE_SIZE;
	}
	int sizeactual() {
		return numElementos;
	}
	int buscar(string key, function<bool(string, string)> comp) {
		int step = 0;
		int i, base;
		i = base = suma(key) % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
		while (true)
		{
			if (tabla[i] == nullptr) return -1;
			else if (comp(tabla[i]->getKey(), key)) {
				return i;
				break;
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
	void mostrar(string key, function<void(V)> most) {
		int step = 0;
		int i, base;
		i = base = suma(key) % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
		while (true)
		{
			if (tabla[i] == nullptr) { break; return; }
			else if (tabla[i]->getKey() == key) {
				most(tabla[i]->getValue());
				break;
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
	bool elemento_existe(string key, V value, function<bool(string, string)> comp) {
		int step = 0;
		int i, base;
		i = base = suma(key) % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
		while (true)
		{
			if (tabla[i] == nullptr) return false;
			else if (comp(tabla[i]->getKey(), key)) {
				return true;
				break;
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
	void erase_pos(string key, function<bool(V, string)> comp) {
		int step = 0;
		int i, base;
		i = base = suma(key) % TABLE_SIZE; //hash1 es = a hash2 cuando step=0;
		while (true)
		{
			if (tabla[i] == nullptr) return;
			else if (comp(tabla[i]->getValue(), key)) {
				delete tabla[i];
				break;
			}
			else step++;

			i = (base + step) % TABLE_SIZE;
		}
	}
	void print(function<void(V)> show) {
		for (size_t i = 0; i < TABLE_SIZE; ++i) {
			if (tabla[i] != nullptr)
				show(tabla[i]->getValue());
		}
	}
};


#endif // !__HASHTABLA_HPP__
