#include "Arco.hpp"
#include "ListaSimple.hpp"

template <typename T>
class NodoGrafo{
    T valor;
    ListaSimple<Arco<T>*> * arcos;
    bool procesado;
    int fallasGeneradas;
    int fallasRecibidas;

    public:
        T getValor(){return this->valor;}
        ListaSimple<Arco<T>*> * getArcos(){return this->arcos;}
        bool getProcesado(){return this->procesado;}
        void setProcesado(bool procesado){this->procesado=procesado;}
        NodoGrafo(T valor){
            this->valor=valor;
            this->arcos=new ListaSimple<Arco<T>*>();
            this->procesado=false;
        }

        int getFallasGeneradas(){return this->fallasGeneradas;}
        void addFallasGeneradas(){this->fallasGeneradas++;}
        
        int getFallasRecibidas(){return this->fallasRecibidas;}
        void addFallaRecibida(){this->fallasRecibidas++;}
};