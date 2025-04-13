#include <iostream>
using namespace std;

//Declaracion Nodo
struct nodo {
    int valor;
    struct nodo *sig;
};

struct nodo *cab, *aux, *ultimo, *temp;
int mostrarNodos(){
    for(aux=cab; aux!=NULL; aux=aux->sig){
        cout<<aux->valor<<" <- Valor del Nodo"<<endl;
        
    }
}
int crearNodo(){    
    aux = ((struct nodo *) malloc(sizeof(struct nodo)));
    cout<<"Registre el valor: ";
    cin>>aux->valor;
    aux->sig = NULL;
    if(cab==NULL){
        cab = aux;
    } else {
        ultimo = cab;
        while(ultimo->sig!=NULL){
            ultimo = ultimo->sig;
        }
        ultimo->sig = aux;
    }

} 
int eliminarNodos(){
  if(cab==NULL){
    cout<<"No Hay Valores Registrados"<<endl;
  }else{
     temp = cab;
     cab = cab->sig;
     free(temp);
  }
}

int main(){
    int opc;
    do {
        cout<<"1. Registrar Nodo"<<endl;
        cout<<"2. Mostrar Nodos"<<endl;
        cout<<"3. Eliminar Nodos"<<endl;
        cout<<"4. Salir"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: crearNodo(); break;
            case 2: mostrarNodos(); break;
            case 3: eliminarNodos(); break;
        }
    }while(opc!=4);
}