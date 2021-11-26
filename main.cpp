#include "Grafo.hpp"

#include <iostream>
#include <string>
#include <fstream> 
#include <vector>

using namespace std;

void leerArchivo(string nomArch, Grafo<string>* &grafo){

    // --- Lectura de archivos separada
    ifstream datos;
    datos.open(nomArch);
    string mes, dia, hora, ipOrigen, ipDestino, falla;

    while (datos.good()){
        getline(datos, mes,' ');
        getline(datos, dia,' ');
        getline(datos, hora,' ');
        getline(datos, ipOrigen,' ');
        getline(datos, ipDestino,' ');
        getline(datos, falla);

        cout << "IP Origen: " << ipOrigen << " IP Destino: " << ipDestino << endl;
        grafo->insertarNodoGrafo(ipOrigen, ipDestino);
    }
    datos.close();
    cout << "Lectura exitosa" << endl;
    
}

int main(){
    Grafo<string>* grafo = new Grafo<string>();
    leerArchivo("bitacoraTest1.txt", grafo);
    grafo->imprimirGrafo();
    grafo->ipGeneraMasFallas();
}