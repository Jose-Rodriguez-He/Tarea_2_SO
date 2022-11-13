#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <string.h>
#include <vector>
#include <mutex>

using namespace std;
//Funciones
int contadorIp(string nombreArchivo);
void leerArchivo(string nombreArchivo, string paquetes);
void crearHebras(string ip, string paquetes);
void ping(string ip,string paquetes);
void escribrir(string valores);
//Variables
int num_hebras;
int n_hebras=0;
vector<thread> vectorThreads(1);
mutex myMutex;

int main(int argc, char * argv[]){
	
	string nombreArchivo=argv[1];
	string paquetes=argv[2];
	num_hebras=contadorIp(nombreArchivo);
	//cout<<num_hebras<<endl;
	vectorThreads.resize(num_hebras);
	
	leerArchivo(nombreArchivo,paquetes);
	for(int i=0;i<num_hebras;i++){
		vectorThreads[i].join();
	}
	cout<<"Programa finalizado"<<endl;
	return 0;
}

int contadorIp(string nombreArchivo){
	int count=0;
	string ip;

	ifstream contar;
	contar.open(nombreArchivo,ios::in);

	if(contar.fail()){
		cout<<"El programa no pudo contar la cantidad de IPs"<<endl;
		exit(1);
	}

	while(!contar.eof()){
		getline(contar,ip);
		if(ip != "" ){
			count++;
		}
	}
	contar.close();
	return count;
}

void leerArchivo(string nombreArchivo,string paquetes){
	string ip;

	ifstream archivo;
	archivo.open(nombreArchivo,ios::in);

	if(archivo.fail()){
		cout<<"No se pudo abrir el archivo primero"<<endl;
		exit(1);
	}

	while(!archivo.eof()){
		getline(archivo,ip);
//		cout<<ip<<endl;
		if(ip != ""){
			crearHebras(ip,paquetes);
		}
	}

	archivo.close();
//	return 0;
}

void crearHebras(string ip, string paquetes){
	vectorThreads[n_hebras]=thread(ping,ip,paquetes);
	n_hebras++;
}

void ping(string ip,string paquetes){
	string comando_ping;
	string valores_ping;

	comando_ping ="ping -q -c"+paquetes+" " + ip + " >> Valores_ip.txt";
	myMutex.lock();
	system(comando_ping.c_str());
	myMutex.unlock();
//	return 0;
}

void escribrir(string valores){
        ofstream archivo_ip;

        archivo_ip.open("Valores_ping.txt",ios::out);

        if(archivo_ip.fail()){
                cout<<"No se pudo crear el archivo";
                exit(1);
        }
        archivo_ip<<valores<<endl;

        archivo_ip.close();
}
