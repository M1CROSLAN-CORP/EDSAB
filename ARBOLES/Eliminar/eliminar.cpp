#include <iostream>
using namespace std;

struct nodo {
    int value;
    struct nodo *izq;
    struct nodo *der;
};

struct nodo *raiz, *aux;

void posicionarNodo(struct nodo *nuevaRaiz){
    if(aux->value<nuevaRaiz->value){
        if(nuevaRaiz->izq == NULL) {
            nuevaRaiz->izq = aux;
        } else {
            posicionarNodo(nuevaRaiz->izq);
        }
    } else {
        if(nuevaRaiz->der == NULL) {
            nuevaRaiz->der = aux;
        } else {
            posicionarNodo(nuevaRaiz->der);
        }
    }
    
}
void adicionarNodo(){
    aux = (struct nodo *) malloc(sizeof(struct nodo));
    aux->izq = aux->der = NULL;
    cout<<"Digite el valor del nodo:";
    cin>>aux->value;
    if(raiz==NULL){
        raiz = aux;
        aux = NULL;
        free(aux);
    }
    else {
        posicionarNodo(raiz);
    }
}

int mostrarNodo(struct nodo *nuevaRaiz){
    
    if(nuevaRaiz->izq!=NULL){
        mostrarNodo(nuevaRaiz->izq);
    }
    cout<<"Valor nodo: "<<nuevaRaiz->value<<endl;
    if(nuevaRaiz->der!=NULL){
        mostrarNodo(nuevaRaiz->der);  
    }
}

// Busca el nodo con su padre; deja el resultado en 'aux' y el padre en 'padre'
nodo* buscarConPadre(nodo *nuevaRaiz, int clave, nodo **padre) {
    *padre = NULL;
    while (nuevaRaiz != NULL) {
        if (nuevaRaiz->value == clave) {
            aux = nuevaRaiz;            
            return aux;
        }
        *padre = nuevaRaiz;
        if (clave < nuevaRaiz->value)
            nuevaRaiz = nuevaRaiz->izq;
        else
            nuevaRaiz = nuevaRaiz->der;
    }
    aux = NULL;
    return NULL;
}

void eliminarNodo() {
    if (raiz == NULL) {
        cout << "El arbol está vacio.\n";
        return;
    }

    int clave;
    cout << "Digite el valor a eliminar: ";
    cin  >> clave;

    nodo *padre = NULL;
    buscarConPadre(raiz, clave, &padre);
    if (aux == NULL) {
        cout << "Nodo con valor " << clave << " no encontrado.\n";
        return;
    }

    // Caso de dos hijos: no implementado
    if (aux->izq != NULL && aux->der != NULL) {
        cout << "El nodo tiene dos hijos; este caso no esta implementado.\n";
        return;
    }

    // Determinar único hijo (o sin hijo)
    nodo *hijo = (aux->izq != NULL) ? aux->izq : aux->der;

    // Ajustar el puntero del padre (o raíz)
    if (padre == NULL) {
        // Eliminando la raíz
        raiz = hijo;
    }
    else if (padre->izq == aux) {
        padre->izq = hijo;
    }
    else {
        padre->der = hijo;
    }

    free(aux);
    aux = NULL;
    cout << "Nodo eliminado correctamente.\n";
}


int main(){
    int opcion=0;
    do {
        cout<<"1. Registrar"<<endl;
        cout<<"2. Mostrar"<<endl;
        cout<<"3. Eliminar"<<endl;
        cout<<"5. Salir"<<endl;
        cout<<"Digite la opcion: ";
        cin>>opcion;
        switch(opcion){
            case 1: adicionarNodo(); break;
            case 2: mostrarNodo(raiz); break;
            case 3: eliminarNodo(); break;
        }
    }while(opcion!=5);
}