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

        //cout << "IP Origen: " << ipOrigen << " IP Destino: " << ipDestino << endl;
        grafo->insertarNodoGrafo(ipOrigen, ipDestino);
    }
    datos.close();
    cout << "Lectura exitosa" << endl;
    cout << endl;

}

int main(){
    Grafo<string>* grafo = new Grafo<string>();
    cout << "--------------------------- LECTURA GRAFO ---------------------------" << endl;
    leerArchivo("bitacoraTest1.txt", grafo);
    cout << "-------------------------- IMPRIMIR GRAFO --------------------------" << endl;
    grafo->imprimirGrafo();
    cout << "----------------------- IP GENERA MAS FALLAS ------------------------" << endl;
    grafo->ipGeneraMasFallas();
    cout << "----------------------- IP RECIBE MAS FALLAS ------------------------" << endl;
    grafo->ipRecibeMasFallas();
    cout << "---------------------- RECORRIDO DEPTH FIRST ------------------------" << endl;
    grafo->DepthFirst(grafo->buscarNodoGrafo("81.142.27.233"));
}