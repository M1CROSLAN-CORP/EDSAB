#include <iostream>
#include <string.h>
using namespace std;

struct cinemania {
    char nombre_pelicula[50];
    int año_realizado;
    char genero[50];
    float dinero_recaudado;
    struct cinemania *izq;
    struct cinemania *der;
};

struct cinemania *raiz, *aux;

void posicionar(struct cinemania *nuevaraiz){
    if(aux->valor<nuevaraiz->valor){
        if(nuevaraiz->izq==NULL){
            nuevaraiz->izq = aux;
        } else {
            posicionar(nuevaraiz->izq);
        }
    } else {
        if(nuevaraiz->der==NULL){
            nuevaraiz->der = aux;
        } else {
            posicionar(nuevaraiz->der);
        }
    }
}

int registrar(){
    aux = ((struct cinemania *) malloc(sizeof(struct cinemania)));
    aux->izq = aux->der = NULL;
    cout<<"Cual es el valor del nodo? ";
    cin>>aux->valor;
    if(raiz==NULL){
        raiz = aux;        
    } else {
        posicionar(raiz);
    }
    aux = NULL;
    free(aux);
}
//Pre Orden - In Orden - Pos Orden
int mostrar(struct cinemania *nuevaraiz){
    if(nuevaraiz!=NULL){
        cout<<"Valor: "<<nuevaraiz->valor<<endl;        
        mostrar(nuevaraiz->izq);
        mostrar(nuevaraiz->der);
    }
}

int main(){
    int opcion;
    do{
        cout<<"1. Registrar Una Nueva Pelicula"<<endl;
        cout<<"2. Buscar Una Pelicula Por Nombre"<<endl;
        cout<<"3. Buscar Peliculas Por Genero"<<endl;
        cout<<"4. Mostrar los 3 Fracasos Taquilleros"<<endl;
        cout<<"5. Mostrar Arbol En Inorden"<<endl;
        cout<<"6. Mostrar Arbol En Preorden"<<endl;
        cout<<"7. Mostrar Arbol En Posorden"<<endl;
        cout<<"8. Salir Del Sistema"<<endl;
        cout<<"Su opcion es:"<<endl;
        cin>>opcion;
        switch(opcion){
            case 1: registrar(); break;
            case 2: mostrar(raiz); break;
        };
    }while(opcion!=8);
}