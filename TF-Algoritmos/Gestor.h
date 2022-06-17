#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "Usuario.h"
#include "HashLinearProbing.h"
#include<functional>
#include <conio.h>
#include <istream>
#include <ostream>

using std::cout;
using std::cin;
using std::string;
using std::getline;
using std::function;
using std::endl;
using std::ios;
using std::ifstream;
using std::ofstream;
const int RUN = 32;
using std::min;

class Gestor {
	HashTabla<Usuario> usuarios;
	ifstream archivo;
	short cant;
	char separador = '|';
	string nombre_archivo;
public:
	Gestor() {
		this->nombre_archivo = "registro.txt";
		archivo.open(this->nombre_archivo);
		lectura();
	}
	void lectura() {
		auto lambda = [](string x, string y) {return x == y; };
		string linea;
		string usuario, tipo, nombre, contrasenia;
		getline(archivo, linea);
		while (getline(archivo, usuario, separador))
		{
			getline(archivo, tipo, separador);
			getline(archivo, nombre, separador);
			getline(archivo, contrasenia);
			Usuario a;
			a.insertarDatos(usuario, tipo, nombre, contrasenia);
			if (usuarios.elemento_existe(a.getNombre(), a, lambda)) {
				Cuenta b(tipo, nombre, contrasenia);
				int x = usuarios.buscar(a.getNombre(), lambda);
				usuarios.retornarValor(x).getValue().insertarCuenta(b);
			}
			else {
				usuarios.insertar(a.getNombre(), a);
			}
		}
		archivo.close();
	}
	bool validar(char opc) {
		if (opc != '1' && opc != '2' &&
			opc != '3' && opc != '4' && opc != '5' &&
			opc != '6' && opc != '7' && opc != '8') {
			return false;
		}
		return true;
	}
	bool validar2(char opc) {
		if (opc != '1' && opc != '2' && opc != '3') {
			return false;
		}
		return true;
	}
	int menu() {
		char opc1;
		do {
			system("CLS");
			cout << "\tRewindPass\n\n";
			cout << "Opciones\n";
			cout << "1. Insertar\n";
			cout << "2. Modificar\n";
			cout << "3. Ordenar\n";
			cout << "4. Desordenar\n";
			cout << "5. Eliminar\n";
			cout << "6. Buscar\n";
			cout << "7. Mostrar\n";
			cout << "8. Salir\n";
			cout << "Ingrese opcion: ";
			cin >> opc1;
			if (validar(opc1) == false) cout << "\nOpcion invalida";
		} while (validar(opc1) == false);
		return int(opc1 - 48);
	}
	void insercion() {
		char* arr;
		short ma, mi, nm, cs;
		ma = mi = nm = cs = 0;
		bool valido = false;
		auto lambda = [](string x, string y) {return x == y; };
		auto lambda2 = [](string x, string y) {return x == y; };
		string nombre, tipo, contrasenia, nombreCuenta;
		char opcion;
		do {
			system("cls");
			cout << "\tRewindPass\n\n";
			cout << "Ingrese nombre: ";
			cin.ignore();
			getline(cin, nombre);
			cout << "Ingrese el tipo de la cuenta: ";
			while (_kbhit())_getch();
			getline(cin, tipo);
			cout << "Ingrese el nombre de la cuenta: ";
			while (_kbhit())_getch();
			getline(cin, nombreCuenta);

			//Validacion de inserción correcta de contraseña
			do
			{
				cout << "Ingrese contrasenia: ";
				while (_kbhit())_getch();
				getline(cin, contrasenia);

				if (contrasenia.length() >= 8)
				{
					arr = new char[contrasenia.length() + 1];
					strcpy(arr, contrasenia.c_str());
					for (size_t i = 0; i < contrasenia.length(); i++)
					{
						if ((arr[i] >= 65 && arr[i] <= 90) ||	//Mayusculas
							(arr[i] >= 97 && arr[i] <= 122) ||	//Minusculas
							(arr[i] >= 33 && arr[i] <= 47) ||	//Car Espec.
							(arr[i] >= 48 && arr[i] <= 57)) {	//Numeros
							valido = true;
						}
						else {
							cout << "\tCaracteres no permitidos\n";
							valido = false;
							break;
						}
					}
				} 

			} while (valido == false);
			//

			Usuario a;
			a.insertarDatos(nombre, tipo, nombreCuenta, contrasenia);
			if (usuarios.elemento_existe(a.getNombre(), a, lambda)) {
				Cuenta b(tipo, nombreCuenta, contrasenia);
				int x = usuarios.buscar(a.getNombre(), lambda);
				usuarios.retornarValor(x).getValue().insertarCuenta(b);
			}
			else {
				usuarios.insertar(a.getNombre(), a);
			}

			int y = usuarios.buscar(a.getNombre(), lambda);
			usuarios.retornarValor(y).getValue().detalles();

			cout << "Desea continuar (S/N): ";
			cin >> opcion;
		} while (opcion == toupper(115));
	}
	void modificar() {
		system("cls");
		int pos, pos1;
		string nombre_cuenta, contrasenia;
		cout << "Ingrese el nombre de la cuenta: ";
		cin.ignore();
		getline(cin, nombre_cuenta);
		cout << "Ingrese la contrasenia cuenta: ";
		cin.ignore();
		getline(cin, contrasenia);
		cout << "Ingrese la posición del usuario: ";
		cin >> pos;
		cout << "Ingrese la posición de la cuenta ";
		cin >> pos1;
		Cuenta cuenta;
		cuenta.setNombre(nombre_cuenta);
		cuenta.setContrasena(contrasenia);
		cout << "Elemento seleccionado: " << usuarios.retornarValor(pos).getValue().toString() << endl;
		usuarios.retornarValor(pos).getValue().modificar(cuenta, pos1);
		cout << "Elemento modificado: " << usuarios.retornarValor(pos).getValue().toString() << endl;
		_getch();

	}
private:
	void insertionSort(int left, int right, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp)
	{
		for (int i = left + 1; i <= right; i++)
		{
			HashEntidad<Usuario> temp = usuarios.retornarValor(i);
			int j = i - 1;
			while (j >= left && comp(usuarios.retornarValor(j), temp))//>
			{
				usuarios.swap(usuarios.retornarPuntero(j + 1), usuarios.retornarPuntero(j));
				j--;
			}
			usuarios.swap(usuarios.retornarPuntero(j + 1), &temp);
		}
	}
	// Iterative Timsort function to sort the
	// array[0...n-1] (similar to merge sort)
	void _timSort(int n, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp2)
	{

		// Sort individual subarrays of size RUN
		for (int i = 0; i < n; i += RUN)
			insertionSort(i, min((i + RUN - 1), (n - 1)), comp);

		// Start merging from size RUN (or 32).
		// It will merge
		// to form size 64, then 128, 256
		// and so on ....
		for (int size = RUN; size < n;
			size = 2 * size)
		{

			// pick starting point of
			// left sub array. We
			// are going to merge
			// arr[left..left+size-1]
			// and arr[left+size, left+2*size-1]
			// After every merge, we
			// increase left by 2*size
			for (int left = 0; left < n; left += 2 * size)
			{

				// find ending point of
				// left sub array
				// mid+1 is starting point
				// of right sub array
				int mid = left + size - 1;
				int right = min((left + 2 * size - 1), (n - 1));

				// merge sub array arr[left.....mid] &
				// arr[mid+1....right]
				if (mid < right)
					merge(left, mid, right, comp2);
			}
		}
	}

	void merge(int i, int middle, int f, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		size_t size = (f - i) + 1;
		HashTabla<Usuario>* aux = new HashTabla<Usuario>(size);
		size_t l = i, r = middle + 1, k = 0;
		while (l <= middle && r <= f) {
			if (comp(usuarios.retornarValor(l), usuarios.retornarValor(r)))//<
				aux->insertar(usuarios.retornarValor(l++).getKey(), usuarios.retornarValor(l++).getValue());
			else
				aux->insertar(usuarios.retornarValor(r++).getKey(), usuarios.retornarValor(r++).getValue());
		}
		while (l <= middle)
			aux->insertar(usuarios.retornarValor(l++).getKey(), usuarios.retornarValor(l++).getValue());
		while (r <= f)
			aux->insertar(usuarios.retornarValor(r++).getKey(), usuarios.retornarValor(r++).getValue());
		for (size_t j = 0; j < size; ++j)
			this->usuarios.insertar_pos(i + j, usuarios.retornarValor(j).getValue().getNombre(), usuarios.retornarValor(j).getValue());
		delete aux;
	}
	int partition(int izq, int der, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		HashEntidad<Usuario> pivote = usuarios.retornarValor(der);  //Seleccionado como elemento pivot
		int i = (izq - 1);
		for (size_t j = izq; j <= der - 1; j++)
		{
			if (comp(usuarios.retornarValor(j), pivote)) {//<
				i++;
				usuarios.swap(usuarios.retornarPuntero(i), usuarios.retornarPuntero(j));
			}
		}
		usuarios.swap(usuarios.retornarPuntero(i + 1), usuarios.retornarPuntero(der));
		return  (i + 1);
	}
	void _quickSort(int izq, int der, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		if (izq < der) {
			int pivot = partition(izq, der, comp);
			int x = pivot - 1, y = pivot + 1;
			_quickSort(izq, x, comp);
			_quickSort(y, der, comp);
		}
		else return;
	}void heapify(int n, int i, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp)
	{

		// Initialize largest as root
		int largest = i;

		// left = 2*i + 1
		int l = 2 * i + 1;

		// right = 2*i + 2
		int r = 2 * i + 2;

		// If left child is larger than root
		if (l < n && comp(usuarios.retornarValor(l), usuarios.retornarValor(largest)))//>
			largest = l;

		// If right child is larger than largest
		// so far
		if (r < n && comp(usuarios.retornarValor(r), usuarios.retornarValor(largest)))//>
			largest = r;

		// If largest is not root
		if (largest != i) {
			usuarios.swap(usuarios.retornarPuntero(i), usuarios.retornarPuntero(largest));

			// Recursively heapify the affected
			// sub-tree
			heapify(n, largest, comp);
		}
	}

	// Main function to do heap sort
	void _heapSort(int n, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp)
	{

		// Build heap (rearrange array)
		for (int i = n / 2 - 1; i >= 0; i--)
			heapify(n, i, comp);

		// One by one extract an element
		// from heap
		for (int i = n - 1; i > 0; i--) {

			// Move current root to end
			usuarios.swap(usuarios.retornarPuntero(0), usuarios.retornarPuntero(i));

			// call max heapify on the reduced heap
			heapify(i, 0, comp);
		}
	}
	int _binary_search(int izq, int der, HashEntidad<Usuario> e, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp2) {
		while (izq <= der) {
			int mitad = izq + (der - izq) / 2;
			if (comp(usuarios.retornarValor(mitad), e)) // ==
				return mitad;
			else if (comp2(usuarios.retornarValor(mitad), e))// <
				izq = mitad + 1;
			else
				der = mitad - 1;
		}
		return -1;
	}
	//JumpSearch
	int _jump_search(HashEntidad<Usuario> x, int n, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp2)
	{
		//calculando cuantas posiciones se hará el salto
		int paso = sqrt(n);
		//previo para hacer busqueda lineal 
		int previo = 0;
		while (comp(usuarios.retornarValor(min(paso, n) - 1), x))// < mientras la pos del paso-1 o el n-1 sea menor al elemento a buscar 
		{
			previo = paso;//se guarda el paso anterior al previo 
			paso += sqrt(n);//se aumenta el salto
			if (previo >= n)//si el previo ya llego al tamaño de n-1 o lo sobre paso 
				return -1;
		}

		while (comp(usuarios.retornarValor(previo), x))//busqueda lineal con el previo
		{
			previo++;

			if (previo == min(paso, n))// si la pos previo es igual al tamaño del arreglo o al paso, significa que no se encontro el elemento
				return -1;
		}

		if (comp2(usuarios.retornarValor(previo), x))// == si el elemento es encontrado
			return previo;

		return -1;
	}
	//LinearSearch
	int _linear_search(HashEntidad<Usuario> e, int n, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		int indice = 0;
		while (indice < n) {
			if (comp(usuarios.retornarValor(indice), e)) {// ==
				return indice;
			}
			indice++;
		}
		return -1;
	}
public:
	void ordShuffle() {
		for (long i = usuarios.size() - 1; i > 0; --i) {
			long j = rand() % (i + 1);
			usuarios.swap(usuarios.retornarPuntero(i), usuarios.retornarPuntero(j));
		}
	}
	void quickSort(function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		_quickSort(0, usuarios.size() - 1, comp);
	}
	void heapSort(function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		_heapSort(usuarios.size(), comp);
	}
	void timSort(function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp2) {
		_timSort(usuarios.size(), comp, comp2);
	}
	int search(HashEntidad<Usuario> e, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp2) {
		return _binary_search(0, usuarios.size() - 1, e, comp, comp2);
	}
	int search_2(HashEntidad<Usuario> e, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp2) {
		return _jump_search(e, usuarios.size(), comp, comp2);
	}
	int search_3(HashEntidad<Usuario> e, function<bool(HashEntidad<Usuario>, HashEntidad<Usuario>)> comp) {
		return _linear_search(e, usuarios.size(), comp);
	}
	void eliminar() {
		short pos;
		auto lambda = [](Usuario x, string y) {return x.getNombre() == y; };
		system("cls");
		cout << "\n\tIngrese posicion del usuario a eliminar: "; cin >> pos;
		if (usuarios.size() > 0) {
			cout << "Elemento eliminado: " << usuarios.retornarValor(pos).getValue().toString() << endl;
			usuarios.erase_pos(usuarios.retornarValor(pos).getKey(), lambda);
		}
		else {
			cout << "La lista esta vacia" << endl;
		}
		_getch();
	}
	void busquedaLineal() {
		string nombre;
		HashEntidad<Usuario> key;
		Usuario a;
		auto l1 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() == b.getValue().getNombre(); };
		system("cls");
		cout << "\n\tIngrese el nombre del usuario a buscar: "; getline(cin, nombre);
		a.setNombre(nombre);
		key.setValue(a);
		if (search_3(key, l1) != -1) {
			cout << "Elemento encontrado en la posicion: " << search_3(key, l1) << "---" << usuarios.retornarValor(search_3(key, l1)).getValue().toString() << endl;
		}
		else {
			cout << "Elemento no encontrado" << endl;
		}
		_getch();
	}
	void busquedaBinaria() {
		string nombre;
		HashEntidad<Usuario> key;
		Usuario a;
		auto l1 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() == b.getValue().getNombre(); };
		auto l2 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() < b.getValue().getNombre(); };
		system("cls");
		cout << "\n\tIngrese el nombre del usuario a buscar: "; getline(cin, nombre);
		a.setNombre(nombre);
		key.setValue(a);
		if (search(key, l1, l2) != -1) {
			cout << "Elemento encontrado en la posicion: " << search(key, l1, l2) << "---" << usuarios.retornarValor(search(key, l1, l2)).getValue().toString() << endl;
		}
		else {
			cout << "Elemento no encontrado" << endl;
		}
		_getch();
	}
	void busquedaDeSalto() {
		string nombre;
		HashEntidad<Usuario> key;
		Usuario a;
		auto l1 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() == b.getValue().getNombre(); };
		auto l2 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() < b.getValue().getNombre(); };
		system("cls");
		cout << "\n\tIngrese el nombre del usuario a buscar: "; getline(cin, nombre);
		a.setNombre(nombre);
		key.setValue(a);
		if (search_2(key, l1, l2) != -1) {
			cout << "Elemento encontrado en la posicion: " << search_2(key, l1, l2) << "---" << usuarios.retornarValor(search_2(key, l1, l2)).getValue().toString() << endl;
		}
		else {
			cout << "Elemento no encontrado" << endl;
		}
		_getch();
	}
	void ordenar() {
		char x;
		system("cls");
		do {
			cout << "Eliga el tipo de ordenamiento a usar: \n";
			cout << "Opciones\n";
			cout << "1. Quick Sort\n";
			cout << "2. Heap Sort\n";
			cout << "3. Tim Sort\n";
			cin >> x;
			if (validar2(x) == false) cout << "\nOpcion invalida";
		} while (validar2(x) == false);
		switch (int(x))
		{
		case 1: {
			auto l1 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() < b.getValue().getNombre(); };
			quickSort(l1);
			listar();
			break;
		}
		case 2: {
			auto l1 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() > b.getValue().getNombre(); };
			heapSort(l1);
			listar();
			break;
		}
		case 3: {
			auto l1 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() > b.getValue().getNombre(); };
			auto l2 = [](HashEntidad<Usuario> a, HashEntidad<Usuario> b) {return a.getValue().getNombre() < b.getValue().getNombre(); };
			timSort(l1, l2);
			listar();
			break;
		}
		default:
			break;
		}
	}
	void buscar() {
		char x;
		system("cls");
		do {
			cout << "Eliga el tipo de busqueda a usar: \n";
			cout << "Opciones\n";
			cout << "1. Linear search\n";
			cout << "2. Binary Search\n";
			cout << "3. Jump Search\n";
			cin >> x;
			if (validar2(x) == false) cout << "\nOpcion invalida";
		} while (validar2(x) == false);
		switch (int(x))
		{
		case 1:
			busquedaLineal();
			break;
		case 2:
			busquedaBinaria();
			break;
		case 3:
			busquedaDeSalto();
			break;
		default:
			break;
		}
	}
	void listar() {
		ofstream arch;
		arch.open(nombre_archivo);
		cout << endl;
		usuarios.print([](Usuario e) { cout << e.toString() << endl; });
		arch << "Usuario|Tipo|Nombre de Cuenta|Contrasenia" << endl;
		usuarios.print([&arch](Usuario e) {arch << e.toString(); });
		arch.close();
	}
};