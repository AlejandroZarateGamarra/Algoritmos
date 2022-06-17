#pragma once
#include "Gestor.h"

class Controladora {
	Gestor* registros;
public:
	Controladora() {
		registros = new Gestor();
	}
	~Controladora() {
		delete registros;
	}
	void run() {
		int opcRun = 0;

		while (opcRun != 8)
		{
			system("cls");
			opcRun = registros->menu();
			//cout << registros->menu()<<endl;
			switch (opcRun)
			{
			case 1:registros->insercion();
				break;
			case 2:registros->modificar();
				break;
			case 3:registros->ordenar();
				break;
			case 4:registros->ordShuffle();
				break;
			case 5:registros->eliminar(); //**
				break;
			case 6:registros->buscar();
				break;
			case 7:registros->listar();
				_getch();
				break;
			}
		}
	}
};