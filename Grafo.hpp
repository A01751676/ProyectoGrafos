#include "NodoGrafo.hpp"
#include "Fila.hpp"

template <typename T>
class Grafo{
    int tam;
    ListaSimple<NodoGrafo<T> *> * nodos;
    public:
        Grafo(){
            this->tam=0;
            this->nodos=new ListaSimple<NodoGrafo<T>*>();
        }
        NodoGrafo<T> * buscarNodoGrafo(T valor){
            NodoT<NodoGrafo<T>*> * actual=this->nodos->getHead();
            while(actual){
                //Busqueda del valor dentro de los nodos
                if(actual->getDato()->getValor()==valor)
                    return actual->getDato();
                actual=actual->getSiguiente();
            }
            return nullptr;            
        }    

        void insertarNodoGrafo(T valorOrigen, T valorDestino){
            //Revisar para el nodo origen
            NodoGrafo<T>* nodoOrigen = this->buscarNodoGrafo(valorOrigen);
            if(!this->buscarNodoGrafo(valorOrigen)){
                nodoOrigen = new NodoGrafo<T>(valorOrigen);
                this->nodos->agregarInicio(nodoOrigen);
                this->tam++;

            }else{
                cout<<"Nodo Origen existente"<<endl;}
            
            nodoOrigen->addFallasGeneradas(); //origen genera falla

            //Revisar para el nodo destino
            NodoGrafo<T>* nodoDestino = this->buscarNodoGrafo(valorDestino);
            if(!this->buscarNodoGrafo(valorDestino)){
                nodoDestino = new NodoGrafo<T>(valorOrigen);
                this->nodos->agregarInicio(nodoDestino);
                this->tam++;

            }else{
                cout<<"Nodo Destino existente"<<endl;}

            nodoDestino->addFallaRecibida();  // destino recibe falla

            // agregar arco
            this->agregarArco(valorOrigen, valorDestino,0);
                 
        }

        void agregarArco(T valorNodoOrigen, T valorNodoDestino, int peso){
            //Validar la existencia de los nodos origen y destino
            NodoGrafo<T> * origen=this->buscarNodoGrafo(valorNodoOrigen);
            NodoGrafo<T> * destino=this->buscarNodoGrafo(valorNodoDestino);
            if(origen&&destino){
                // si ambos existen revisar si la conexion ya existe
                
                if (origen->getArcos()->getTam() > 0){ // el nodo tiene conexiones
                    // buscar conexion
                    NodoT<Arco<T>*> * arco = origen->getArcos()->getHead();
                    while(arco){
                        if (arco->getDato()->getValorNodoDestino() == valorNodoDestino){
                            // la conexion existe
                            arco->getDato()->setPeso(arco->getDato()->getPeso() + 1);
                            return;
                        }
                        arco=arco->getSiguiente();
                    }
                    // la conexion no existe
                    origen->getArcos()->agregarInicio(new Arco<T>(valorNodoDestino,1));
                }
                else{
                    // la conexion no existe, crearla con peso en 0
                    origen->getArcos()->agregarInicio(new Arco<T>(valorNodoDestino,1));
                }
            }
            else
                cout<<"Ambos nodos tanto origen como destino deben existir"<<endl;
        }


        void imprimirGrafo(){
            NodoT<NodoGrafo<T>*> * nodo=this->nodos->getHead();
            //Recorrer la lista de nodos
            while(nodo){
                cout<<"Nodo:"<< nodo->getDato()->getValor()<<" \n";
                NodoT<Arco<T>*> * arco = nodo->getDato()->getArcos()->getHead();
                //Recorrer la lista de arcos de cada nodo
                while(arco){
                    cout<<"->"<<arco->getDato()->getValorNodoDestino()<<":"<<arco->getDato()->getPeso()<<" ";
                    arco=arco->getSiguiente();
                }
                cout<<endl;
                cout<<endl;
                nodo=nodo->getSiguiente();                
            }
            cout<<endl;
        }

        void BreadthFirst(NodoGrafo<T> * nodoG){
            //Crear la fila de control
            Fila<NodoGrafo<T> *> * fila = new Fila<NodoGrafo<T> *>();
            //Inicializar procesado de cada NodoGrafo
            NodoT<NodoGrafo<T>*> * actual=this->nodos->getHead();
            if(actual){
                while(actual){
                    actual->getDato()->setProcesado(false);
                    actual=actual->getSiguiente();
                }
                //Metemos el NodoGrafo por el que inicia el recorrido
                nodoG->setProcesado(true);
                fila->push(nodoG);
                while(fila->front()){
                    NodoGrafo<T> * aux = fila->pop()->getDato();
                    //Imprimo el valor del nodoGrafo
                    cout<< aux->getValor()<<" ";
                    //Checar las conexiones sin procesar
                    NodoT<Arco<T>*> * con=aux->getArcos()->getHead();
                    while(con){
                        NodoGrafo<T> * vecino = this->buscarNodoGrafo(con->getDato()->getValorNodoDestino());
                        if(!vecino->getProcesado()){
                            vecino->setProcesado(true);
                            //Meter a la fila
                            fila->push(vecino);
                        }
                        con=con->getSiguiente();
                    }
                }
                cout<<endl;

            }else{
                cout<<"Grafo vacio"<<endl;
            }
        }

        void ipGeneraMasFallas(){
            NodoT<NodoGrafo<T>*> * nodoG = this->nodos->getHead();
            int masFallasNum = 0;
            while(nodoG){
                if(nodoG->getDato()->getFallasGeneradas() > masFallasNum){
                    masFallasNum = nodoG->getDato()->getFallasGeneradas();
                }
                nodoG = nodoG->getSiguiente();
            }

            cout << "Los o el nodo con mas fallas generadas generan " << masFallasNum << " fallas y son: " <<endl;
            nodoG = this->nodos->getHead();
            while(nodoG){
                if(nodoG->getDato()->getFallasGeneradas() == masFallasNum){
                    cout << "    "<< nodoG->getDato()->getValor() << endl;
                }
                nodoG = nodoG->getSiguiente();
            }

            cout << endl;
        }
};