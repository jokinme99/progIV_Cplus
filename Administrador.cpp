/*
 * Administrador.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */

#include "Administrador.h"
#include "Usuario.h"
#include <iostream>
using namespace std;

Administrador::Administrador(Usuario* u):Usuario(*u){//METER DATOS RELEVANTES


}
Administrador::Administrador(const Administrador& a):Usuario(a){

}
Administrador::~Administrador(){

}

void Administrador::crearHabitaciones(){

}
void Administrador::eliminarHabitaciones(){

}
void Administrador::listarReservas(){
	//usar el objeto reservasy sobreescribir el metodo de la clase pafre
}
void Administrador::crearReserva(){
	//rellenarlo con datos de usuario
}
void Administrador::eliminarReserva(){
	//(?)
}
void Administrador::listarTrabajadores(){

}
void Administrador::CrearTrabajadores(){

}
void Administrador::eliminarTrabajadores(){

}
void Administrador::listarUsuarios(){

}
char* Administrador::getTipoUsuario(){
	Usuario::getTipoUsuario();
	return "admin";
}

//void Administrador::imprimirUsuario(){
//
//	Usuario::imprimirUsuario();
//	cout<<"Usuario "<<this->getIdUsuario()<<": "<<endl;
//	cout<<"Nombre: "<<this->getNombreUsuario()<<" Correo: "<<this->getCorreoUsuario()<<endl;
//	cout<<"Edad: "<<this->getEdadUsuario()<<" Tipo de usuario: "<< this->getTipoUsuario()<<endl;
//	cout<<"Reservas: "<<endl;
//	cout<<"----------"<<endl;
////	if (this->getReservaUsuario()==NULL) {
////		cout<<"(este usuario no tiene reservas)"<<endl;
////	}else{
////	this->getReservaUsuario()->imprimirReservas();
////	}
//
//}
