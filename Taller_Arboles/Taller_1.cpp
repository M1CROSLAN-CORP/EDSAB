#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

struct cinemania {
    char nombre_pelicula[50];
    int ano_realizado;
    char genero[50];
    float dinero_recaudado;
    struct cinemania *izq;
    struct cinemania *der;
};

struct cinemania *raiz, *aux;
char BusquedaPorNombre[50];

void posicionar(struct cinemania *nuevaraiz){
    if(aux->ano_realizado<nuevaraiz->ano_realizado){
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
    // Declaracion De Variables Temporales
    char temp_nombre_pelis[50];
    int opc;

    cout<<"Cual es el Nombre De La Pelicula "<<endl;
    cin.ignore();  // Limpiar el buffer antes de usar getline
    cin.getline(aux->nombre_pelicula, 50);  // Leer una línea completa, hasta 50 caracteres

    cout<<" Registre El Año En Que Se Realizo "<<endl;
    cin>>aux->ano_realizado;
    
    cout<<" Registre El Genero De La Pelicula "<<endl;    
    do {
        cout<<"1. Accion "<<endl;
        cout<<"2. Romance "<<endl;
        cout<<"3. Terror"<<endl;
        cout<<"4. Comedia"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 2: strcpy(aux->genero,"Accion"); break;
            case 3: strcpy(aux->genero,"Romance"); break;
            case 1: strcpy(aux->genero,"Terror"); break;
            case 4: strcpy(aux->genero,"Comedia"); break;
            default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 4 "<<endl;
        }
        
    }while(opc<1 || opc>4);

    cout<<" Registre La totalidad De Dinero Recaudado ";
    cin>>aux->dinero_recaudado;


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
        cout<<"Nombre Pelicula = "<<nuevaraiz->nombre_pelicula<<endl;
        cout<<"Ano De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;        
        mostrar(nuevaraiz->izq);
        mostrar(nuevaraiz->der);
    }
}

int BuscarNombrePelicula(struct cinemania *buscar_raiz){
    if(strcmp(BusquedaPorNombre, "") == 0){
      cout<<"Ingrese el Nombre De la Pelicula A Buscar";
      cin.ignore();  // Limpiar el buffer antes de usar getline
      cin.getline(BusquedaPorNombre, 50);  // Leer una línea completa, hasta 50 caracteres
    }                     
                      
    
    if(buscar_raiz!=NULL){
        if(strcmp(BusquedaPorNombre, aux->nombre_pelicula) == 0){
            cout<<"Nombre Pelicula = "<<buscar_raiz->nombre_pelicula<<endl;
            cout<<"Ano De Estreno = "<<buscar_raiz->ano_realizado<<endl<<endl;
            BuscarNombrePelicula(buscar_raiz->izq);
            BuscarNombrePelicula(buscar_raiz->der);
        }else{      
            BuscarNombrePelicula(buscar_raiz->izq);
            BuscarNombrePelicula(buscar_raiz->der);
        } 
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
            case 2: BuscarNombrePelicula(raiz); break;
            case 5: mostrar(raiz); break;
        };
    }while(opcion!=8);
}