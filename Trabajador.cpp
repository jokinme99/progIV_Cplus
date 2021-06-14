/*
 * Trabajador.cpp
 *
 *  Created on: 14 jun. 2021
 *      Author: jokin
 */

#include "Trabajador.h"
#include <iostream>
#include <string.h>
using namespace std;

Trabajador::Trabajador(){
	this->idTrabajador=0;
	this->nombreTrabajador = new char[1];
	this->nombreTrabajador[0] = '\0';
	this->dniTrabajador = new char[1];
	this->dniTrabajador[0] = '\0';
	this->telefonoTrabajador=0;
	this->sueldoTrabajador=0.0;
}
Trabajador::Trabajador(const int idTrabajador, char* nombreTrabajador, char* dniTrabajador,int telefonoTrabajador, float sueldoTrabajador){
	this->idTrabajador=idTrabajador;
	this->nombreTrabajador= new char[strlen(nombreTrabajador)+1];
	strcpy(this->nombreTrabajador,nombreTrabajador);
	this->dniTrabajador= new char[strlen(dniTrabajador)+1];
	strcpy(this->dniTrabajador,dniTrabajador);
	this->telefonoTrabajador = telefonoTrabajador;
	this->sueldoTrabajador=sueldoTrabajador;
}
Trabajador::Trabajador(const Trabajador& t){
	this->idTrabajador=t.idTrabajador;
	this->nombreTrabajador= new char[strlen(t.nombreTrabajador)+1];
	strcpy(this->nombreTrabajador,t.nombreTrabajador);
	this->dniTrabajador= new char[strlen(t.dniTrabajador)+1];
	strcpy(this->dniTrabajador,t.dniTrabajador);
	this->telefonoTrabajador = t.telefonoTrabajador;
	this->sueldoTrabajador=t.sueldoTrabajador;
}

int Trabajador::getIdTrabajador()const{
	return this->idTrabajador;
}
void Trabajador::setIdTrabajador(const int idTrabajador){
	this->idTrabajador=idTrabajador;
}
char* Trabajador::getNombreTrabajador()const{
	return this->nombreTrabajador;
}
void Trabajador::setNombreTrabajador(char* nombreTrabajador){
	this->nombreTrabajador= new char[strlen(nombreTrabajador)+1];
	strcpy(this->nombreTrabajador,nombreTrabajador);
}
char* Trabajador::getDNITrabajador()const{
	return this->dniTrabajador;
}
void Trabajador::setDNITrabajador(char* dniTrabajador){
	this->dniTrabajador= new char[strlen(dniTrabajador)+1];
	strcpy(this->dniTrabajador,dniTrabajador);
}
int Trabajador::getTelefonoTrabajador()const{
	return this->telefonoTrabajador;
}
void Trabajador::setTelefonoTrabajador(int telefonoTrabajador){
	this->telefonoTrabajador=telefonoTrabajador;
}
float Trabajador::getSueldoTrabajador()const{
	return this->sueldoTrabajador;
}
void Trabajador::setSueldoTrabajador(float sueldoTrabajador){
	this->sueldoTrabajador=sueldoTrabajador;
}


