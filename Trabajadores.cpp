/*
 * Trabajadores.cpp
 *
 *  Created on: 15 jun. 2021
 *      Author: jokin
 */
#include "Trabajador.h"
#include "Trabajadores.h"
#include <string.h>
#include <iostream>

using namespace std;

Trabajadores::Trabajadores(){
	this->numTrabajadores=0;
}
Trabajadores::~Trabajadores(){
	delete[]& this->numTrabajadores;
	delete t;
}

void Trabajadores::anyadirTrabajador(Trabajador* t){
	this->t[this->numTrabajadores] = t;
	numTrabajadores++;
}
void Trabajadores::quitarTrabajador(int id){
	int var;
	cout<<"Llego"<<endl;
	for(var=0;var<this->numTrabajadores;++var){
		cout<<"Variable"<<var<<endl;
		if(this->t[var]->getIdTrabajador()==id){
			cout<< "Variable"<< var<<endl;
			numTrabajadores--;
			for(int j=var;j<this->numTrabajadores;++j){
				cout<<"Variable j"<<j<<endl;
				cout<<"Variable j"<<this->getNumTrabajadores()<<endl;
				this->t[j] = this->t[j+1];
			}
		}
	}
}
void Trabajadores::imprimirTrabajadores(){
	for(int i=0;i<this->numTrabajadores;++i){
		this->t[i]->imprimir();
	}
}
int Trabajadores::getNumTrabajadores(){
	return this->getNumTrabajadores();
}
Trabajador* Trabajadores::getTrabajador(int idTrabajador){
	int var;
	for(var=0;var<this->numTrabajadores;++var){
		if(this->t[var]->getIdTrabajador() == idTrabajador){
			break;
		}
	}
	return this->t[var];
}
void Trabajadores::editarTrabajador(int id, float sueldo){
	Trabajador* trabajador = getTrabajador(id);
	trabajador->setSueldoTrabajador(sueldo);
}


