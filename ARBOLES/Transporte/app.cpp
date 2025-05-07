#include <iostream>
using namespace std;

int contBarcos = 0; 

struct barco {   
    int id; 
    int eslora;
    int manga;
    int calado;
    int capacidad;//Toneladas
    struct barco *izq;
    struct barco *der;
    //Conecto barco con contenedor
    struct contenedor *cab;
};

struct barco *raiz, *auxBarco, *aux2Barco;

struct contenedor {        
    int capacidad;//Toneladas
    struct contenedor *sig;    
};

struct contenedor *auxContenedor, *ultimoContenedor;

//Para gestionar los barcos
void posicionar(struct barco *nuevaraiz){
    if(auxBarco->capacidad<nuevaraiz->capacidad){
        if(nuevaraiz->izq==NULL){
            nuevaraiz->izq = auxBarco;
        } else {
            posicionar(nuevaraiz->izq);
        }
    } else {
        if(nuevaraiz->der==NULL){
            nuevaraiz->der = auxBarco;
        } else {
            posicionar(nuevaraiz->der);
        }
    }
}

int registrarBarco(){    
    auxBarco = ((struct barco *) malloc(sizeof(struct barco)));
    auxBarco->izq = auxBarco->der = NULL;
    contBarcos++;
    auxBarco->id = contBarcos;
    auxBarco->cab = NULL;
    cout<<"Cual es el eslora del barco? ";
    cin>>auxBarco->eslora;
    cout<<"Cual es el manga del barco? ";
    cin>>auxBarco->manga;
    cout<<"Cual es el calado del barco? ";
    cin>>auxBarco->calado;
    cout<<"Cual es el capacidad del barco? ";
    cin>>auxBarco->capacidad;
    if(raiz==NULL){
        raiz = auxBarco;        
    } else {
        posicionar(raiz);
    }
    auxBarco = NULL;
    free(auxBarco);
}
//Pre Orden - In Orden - Pos Orden

int registrarContenedor(struct barco *dondeVa){    
    auxContenedor = ((struct contenedor *) malloc(sizeof(struct contenedor)));
    cout<<"Del contenedor registre la capacidad: ";
    cin>>auxContenedor->capacidad;
    auxContenedor->sig = NULL;
    if(dondeVa->cab==NULL){
        cout<<"Asignado a cabeza"<<endl;
        dondeVa->cab = auxContenedor;
    } else {
        ultimoContenedor = dondeVa->cab;
        while(ultimoContenedor->sig!=NULL){
            cout<<"Saltando contenedor "<<ultimoContenedor->capacidad<<endl;
            ultimoContenedor = ultimoContenedor->sig;
        }
        cout<<"Asignado a la cola "<<endl;
        ultimoContenedor->sig = auxContenedor;

        ultimoContenedor = NULL;
        free(ultimoContenedor);
    }
    auxContenedor = NULL;
    free(auxContenedor);
}
int mostrarBarcos(struct barco *nuevaraiz){
    if(nuevaraiz!=NULL){
        cout<<"ID: "<<nuevaraiz->id<<endl;        
        cout<<"Eslora: "<<nuevaraiz->eslora<<endl;        
        cout<<"Capacidad: "<<nuevaraiz->capacidad<<endl;        
        cout<<"-----------";        
        mostrarBarcos(nuevaraiz->izq);
        mostrarBarcos(nuevaraiz->der);
    }
}
int buscarBarcos(struct barco *nuevaraiz, int idBuscado){    
    if(nuevaraiz!=NULL){
        if(nuevaraiz->id==idBuscado){
            auxBarco = nuevaraiz;
            return 0;
        }
        buscarBarcos(nuevaraiz->izq, idBuscado);
        buscarBarcos(nuevaraiz->der, idBuscado);
    }    
}
int mostrarTodo(struct barco *nuevaraiz){
    if(nuevaraiz!=NULL){
        cout<<"ID: "<<nuevaraiz->id<<endl;        
        cout<<"Eslora: "<<nuevaraiz->eslora<<endl;        
        cout<<"Capacidad: "<<nuevaraiz->capacidad<<endl;        
        cout<<"-----------"; 
        for(auxContenedor=nuevaraiz->cab; auxContenedor!=NULL; auxContenedor=auxContenedor->sig){
            cout<<auxContenedor->capacidad<<" <- Capacidad del Contenedor"<<endl;        
        }       
        mostrarTodo(nuevaraiz->izq);
        mostrarTodo(nuevaraiz->der);
    }
}

int main(){
    int opcion;
    int opcionBarco;
    do{
        cout<<"Menu"<<endl;
        cout<<"1. Registrar Barco"<<endl;
        cout<<"2. Registrar Contenedor"<<endl;
        cout<<"3. Mostrar Barcos y Contenedores"<<endl;
        cout<<"4. Salir"<<endl;
        cin>>opcion;
        switch(opcion){
            case 1: registrarBarco();  break;
            case 2: 
                    mostrarBarcos(raiz);
                    cout<<"Seleccione ID del barco: ";
                    cin>>opcionBarco;
                    buscarBarcos(raiz, opcionBarco);                    
                    registrarContenedor(auxBarco);  
            break;
            case 3: mostrarTodo(raiz);  break;
        }
    } while(opcion!=4);
}