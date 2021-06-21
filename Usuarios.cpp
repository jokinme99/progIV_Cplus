/*
 * Usuarios.cpp
 *
 *  Created on: 12 jun. 2021
 *      Author: Suhar
 */
#include "Usuario.h"
#include "Usuarios.h"
#include <string.h>
#include "Administrador.h"
#include "DatosSQL.h"
#include "sqlite/sqlite3.h" //include para base de datos
#include <iostream>
using namespace std;


	Usuarios::Usuarios(){


		this->numUsuarios=0;


	}
	Usuarios::~Usuarios(){
		delete[] &this->numUsuarios;
		delete[] this->u;

	}

	void Usuarios::anyadirUsuario(Usuario *u){
		this->u[this->numUsuarios]= u;
		this->numUsuarios++;

	}
	void Usuarios::rellenarDeUsuarios(){

		//SEGURAMENTE SE PUEDA SUSTITUIR POR EL CONSTRUCTOR
		sqlite3 *db;
		const char *data = "LLamada a Base de datos";
		char *zErrMsg = 0;
		int rc = sqlite3_open("hotelandia_final.s3db", &db);

		char sql[] = "SELECT * from USUARIO";

		/* Execute SQL statement */
		//rc = sqlite3_exec(db, sql, &this->callbackUsuarios, (void*) data, &zErrMsg);//ARREGLAR ESTO
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		} else {
			//fprintf(stdout, "Operation done successfully\n");
		}
		sqlite3_close(db);




	}
	void Usuarios::quitarUsuario(int id){
		int var;
		cout<<"Llego"<<endl;
		for(var=0;var<this->numUsuarios;++var){
			cout<<"Variable"<<var<<endl;
			if(this->u[var]->getIdUsuario()==id){
				cout<< "Variable"<< var<<endl;
				numUsuarios--;
				for(int j=var;j<this->numUsuarios;++j){
					cout<<"Variable j"<<j<<endl;
					cout<<"Variable j"<<this->getNumUsuarios()<<endl;
					this->u[j] = this->u[j+1];
				}
			}
		}
	}


	void Usuarios::imprimirUsuarios(){
		for (int i = 0; i < this->numUsuarios; ++i) {
			this->u[i]->imprimirUsuario();
		}
	}

	int Usuarios::getNumUsuarios(){
		return this->numUsuarios;
	}
	Reservas* Usuarios::getReservas(int idUsuario){
		int i =0;
				for (i = 0; i < this->numUsuarios;++i) {
					if (this->u[i]->getIdUsuario()==idUsuario) {
						break;
					}
				}
				return this->u[i]->getReservaUsuario();
//				return new Reservas();
	}

	Usuario* Usuarios::getUsuario(int id){
		int i;
		for (i = 0; i < this->numUsuarios; ++i) {
			if (this->u[i]->getIdUsuario()==id) {
				break;
			}
		}
		return this->u[i];
	}
	Usuario* Usuarios::getUsuario(char*nombre){
		int i;
		for (i = 0; i < this->numUsuarios; ++i) {
			if (strcmp(this->u[i]->getNombreUsuario(),nombre)==0) {
				break;

			}
		}
		return this->u[i];
	}

	//Todo:arreglar
	void Usuarios::editarUsuario(int id, char* nombre, char* correo, char* contrasenya, int edad /* ,Reservas* reserva */){
		Usuario* usuario = getUsuario(id);
		usuario->setNombreUsuario(nombre);
		usuario->setCorreoUsuario(correo);
		usuario->setContrasenyaUsuario(contrasenya);
		usuario->setEdadUsuario(id);
		//usuario->setReservaUsuario(reserva);
	}

	bool Usuarios::usuarioExiste(int numUsuario){

		int var = 0;
		bool verdadero= false;
		for (var = 0; var < this->numUsuarios; ++var) {
			if (this->u[var]->getIdUsuario() == numUsuario) {
				verdadero = true;
				break;
			}

		}
		return verdadero;
	}

	void Usuarios::anyadirUsuario(Usuarios *usuario) { /////////////////ESTABLECER EL TAMAÑO DE LOS ARRAYS DE CARACTERES A LA QUE SE LES TIENE PREDISPUESTO

		int idUsuario;
		char nombreUsuario[100];
		char correo[9];
		char contrasenya[100];
		int edad;




		cout
		<< "Ingrese el identificador del usuario que desea anyadir: ";
		cin >> idUsuario;
		cout << endl;

		while (usuario->usuarioExiste(idUsuario) != 0) {
			cout << "Ya hay un trabajador con ese identificaro, introduce otro"
					<< endl;
			cin >> idUsuario;
		}
		cout << "Ingrese el nombre del usuario que desea anyadir: ";
		cin >> nombreUsuario;
	//	strcpy(nombre,nombreTrabajador);

		cout << endl;
		cout << "Ingrese el correo del usuario : ";
		cin >> correo;

		cout << endl;
		cout << "Ingrese la contraseña del usuario: ";
		cin >> contrasenya;
		cout << endl;

		cout << "Ingrese la edad del usuario: ";

		cout << endl;

		cin >> edad;



		Usuario *us = new Usuario(idUsuario, nombreUsuario,
				correo, contrasenya, edad);

		usuario->anyadirUsuario(us);



		//ESTE METODO AÑADE UNA RESERVA

		/* Create SQL statement */
		char sql[] = "INSERT INTO USUARIO VALUES (";

		char con[] = "'", con1[] = ",", con2[] = ",", con3[] = ",", con8[] = ")",
				con9[] = "";

		string s = to_string(idUsuario);
		char const *pchar = s.c_str();  //use char const* as target type
		char con10[5];
		strcpy(con10, pchar);
		cout << pchar << endl;
		cout << con10 << endl;
		s = to_string(edad);
		char const *pchar2 = s.c_str();  //use char const* as target type
		cout << pchar << endl;
		char con12[200];
		strcpy(con12, pchar2);


		char t[] = "Usuario";

		char tipoR[10];
		strcpy(tipoR, t);

		char *retval = new char[strlen(sql) + strlen(con) + strlen(con10)
				+ strlen(con) + strlen(con1) + strlen(nombreUsuario)
				+ strlen(con) + strlen(con2) + strlen(con) + strlen(correo)
				+ strlen(con) + strlen(con3) + strlen(con) + strlen(contrasenya)
				+ strlen(con) + strlen(con3) + strlen(con) + strlen(con12)
				+ strlen(con) + strlen(con3) + strlen(con) + strlen(tipoR)
				+ strlen(con) + strlen(con8) + strlen(con9)];

		*retval = '\0';

		strcat(retval, sql);
		strcat(retval, con);
		strcat(retval, con10);
		strcat(retval, con);
		strcat(retval, con1);
		strcat(retval, con);
		strcat(retval, nombreUsuario);
		strcat(retval, con);
		strcat(retval, con2);
		strcat(retval, con);
		strcat(retval, correo);
		strcat(retval, con);
		strcat(retval, con3);
		strcat(retval, con);
		strcat(retval, contrasenya);  //CONVERTIR INT A CHAR
		strcat(retval, con);
		strcat(retval, con3);
		strcat(retval, con);
		strcat(retval, con12);
		strcat(retval, con);
		strcat(retval, con3);
		strcat(retval, con);
		strcat(retval, tipoR);
		strcat(retval, con);
		strcat(retval, con8);
		strcat(retval, con9);

		cout << retval << endl;

		llamadaSQL(retval);

	}

	void Usuarios::editarUsuarios(Usuarios *us) {


		char nombre[100];
		int idUsuario;
		char correo[100];

		cout << endl;
		cout << "Aqui tienes la lista de los usuarios" << endl;

		system("pause");

		us->imprimirUsuarios();

		cout << endl;

		cout << "introduce el id del usuario que quieres modificar" << endl;

		cin >> idUsuario;

		cout << "introduce el nuevo nombre del usuario:" << endl;

		cin >> nombre;

		cout << "introduce el nuevo correo del trabajador:" << endl;

		cin >> correo;


		us->getUsuario(idUsuario)->setNombreUsuario(nombre);
		us->getUsuario(idUsuario)->setCorreoUsuario(correo);

		char sql[] = "UPDATE USUARIO SET nombre_usuario ='";

		char con[] = "'", con1[] = ",", con2[] = "correo_usuario='"
				, con8[] = " WHERE id_usuario='", con9[] = ";";

		string s = to_string(idUsuario);
		char const *pchar2 = s.c_str();  //use char const* as target type
		char con11[5];
		strcpy(con11, pchar2);

		cout << endl;

		char *retVal = new char[strlen(sql) + strlen(nombre) + strlen(con)
				+ strlen(con1) + strlen(con2) + strlen(correo) + strlen(con)
				+ strlen(con1) + strlen(con8) + strlen(con11) + strlen(con)
				 + 1];

		*retVal = '\0';
		strcat(retVal, sql);
		strcat(retVal, nombre);
		strcat(retVal, con);
		strcat(retVal, con1);
		strcat(retVal, con2);
		strcat(retVal, correo);
		strcat(retVal, con);
		strcat(retVal, con1);
		strcat(retVal, con8);
		strcat(retVal, con11);
		strcat(retVal, con);
		cout << sql << endl;
		cout << retVal << endl;

		llamadaSQL(retVal);
	}

	int Usuarios::eliminarUsuario(Usuarios *us) {



		int numUsuario;
		char afirmacion[5];

		cout << "Estos son los usuarios actuales " << endl;
		cout << endl;
		us->imprimirUsuarios();
		cout << endl;
		cout << "Selecciona el numero de usuario que quieres Eliminar: ";

		cin >> numUsuario;

		cout << endl;

		while (us->usuarioExiste(numUsuario) == 0) {
			cout << "por favor elija un trabajador adecuado" << endl;
			cin >> numUsuario;
		}
		cout << endl;

		cout << "Esta seguro que desea eliminar la siguiente trserva?(diga si o no)"
				<< endl;
		cout << endl;


		us->getUsuario(numUsuario);
		cout << endl;
		cout << "Respuesta(diga si o no):  ";
		cin >> afirmacion;
		while (strcmp(afirmacion, "si") != 0 && strcmp(afirmacion, "no") != 0) {
			cout << "por favor, elija una respuesta valida" << endl;
			cout << endl;
			cout << "Respuesta(diga si o no):  ";
			cin >> afirmacion;
		}
		if (strcmp(afirmacion, "no") == 0) {

			cout << "Entonces no cancelamos" << endl;
			return 0;
		}

		us->quitarUsuario(numUsuario);

		char sql[] = "DELETE FROM USUARIO WHERE id_usuario ='";

		char con[] = "'";

		string s = to_string(numUsuario);
		char const *pchar2 = s.c_str();  //use char const* as target type
		char con11[5];
		strcpy(con11, pchar2);

		char *retval = new char[strlen(sql) + strlen(con11) + strlen(con)];

		*retval = '\0';
		strcat(retval, sql);
		strcat(retval, con11);
		strcat(retval, con);

		cout << endl;

		//cout<<sql<<endl;

		llamadaSQL(retval);

		return 0;
	}

