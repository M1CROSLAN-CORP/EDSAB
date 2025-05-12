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
char BusquedaPorNombre[50],BusquedaPorGenero[50];

void posicionar(struct cinemania *nuevaraiz){
    //Si el Nuevo Año ingresado es menor o igual al año ya registrado va para la izquierda
    if(aux->ano_realizado<nuevaraiz->ano_realizado || aux->ano_realizado==nuevaraiz->ano_realizado){ 
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

    cout<<"Registre El Año En Que Se Realizo "<<endl;
    cin>>aux->ano_realizado;
    
    cout<<"Registre El Genero De La Pelicula "<<endl;    
    do {
        cout<<"1. Accion "<<endl;
        cout<<"2. Romance "<<endl;
        cout<<"3. Terror"<<endl;
        cout<<"4. Comedia"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: strcpy(aux->genero,"Accion"); break;
            case 2: strcpy(aux->genero,"Romance"); break;
            case 3: strcpy(aux->genero,"Terror"); break;
            case 4: strcpy(aux->genero,"Comedia"); break;
            default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 4 "<<endl;
        }
        
    }while(opc<1 || opc>4);

    cout<<"Registre La totalidad De Dinero Recaudado ";
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
int mostrarPreOrden(struct cinemania *nuevaraiz){
    if(nuevaraiz!=NULL){
        cout<<"Nombre Pelicula = "<<nuevaraiz->nombre_pelicula<<endl;
        cout<<"Ano De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;        
        mostrarPreOrden(nuevaraiz->izq);
        mostrarPreOrden(nuevaraiz->der);
    }
}

int mostrarPostOrden(struct cinemania *nuevaraiz){
    if(nuevaraiz!=NULL){        
        mostrarPostOrden(nuevaraiz->izq);
        mostrarPostOrden(nuevaraiz->der);
        cout<<"Nombre Pelicula = "<<nuevaraiz->nombre_pelicula<<endl;
        cout<<"Ano De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;
    }
}

int mostrarInOrden(struct cinemania *nuevaraiz){
    if(nuevaraiz!=NULL){        
        mostrarInOrden(nuevaraiz->izq);
        cout<<"Nombre Pelicula = "<<nuevaraiz->nombre_pelicula<<endl;
        cout<<"Ano De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;
        mostrarInOrden(nuevaraiz->der);
    }
}

int BuscarNombrePelicula(struct cinemania *buscar_raiz){                
    if(buscar_raiz!=NULL){
        if(strcmp(BusquedaPorNombre, buscar_raiz->nombre_pelicula) == 0){
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

int BuscarPeliculasPorGenero(struct cinemania *buscar_raiz){
    if(buscar_raiz!=NULL){   
        if(strcmp(BusquedaPorGenero, buscar_raiz->genero)==0){
            cout<<"Nombre Pelicula = "<<buscar_raiz->nombre_pelicula<<endl;
            cout<<"Ano De Estreno = "<<buscar_raiz->ano_realizado<<endl;
            cout<<"Genero Pelicula = "<<buscar_raiz->genero<<endl<<endl;
            BuscarPeliculasPorGenero(buscar_raiz->izq);
            BuscarPeliculasPorGenero(buscar_raiz->der);
        }else{      
             BuscarPeliculasPorGenero(buscar_raiz->izq);
             BuscarPeliculasPorGenero(buscar_raiz->der);
        }       
    }
}

int fracasostaquilleros(struct cinemania *buscar_raiz){
  cout<<"Los Tres Ultimos Fracasos Taquilleros"<<endl;
}

cinemania* buscarConPadre(cinemania *nuevaRaiz, cinemania **padre) {
    *padre = NULL;
     if(nuevaRaiz !=NULL){
         if (strcmp(BusquedaPorNombre, nuevaRaiz->nombre_pelicula) == 0) {
            aux = nuevaRaiz;            
            return aux;
         }
         *padre = nuevaRaiz;
         buscarConPadre(nuevaRaiz->izq, padre);
         buscarConPadre(nuevaRaiz->der, padre);
     }
     aux = NULL;
     return NULL;
    
    /* 
    while (nuevaRaiz != NULL) {
        if (strcmp(BusquedaPorNombre, nuevaRaiz->nombre_pelicula) == 0) {
            aux = nuevaRaiz;            
            return aux;
        }
        *padre = nuevaRaiz;
        if (clave < nuevaRaiz->ano_realizado)
            nuevaRaiz = nuevaRaiz->izq;
        else
            nuevaRaiz = nuevaRaiz->der;
    }
    aux = NULL;
    return NULL;
    */
}

void eliminarPelicula() {
    if (raiz == NULL) {
        cout << "El arbol está vacio.\n";
        return;
    }
    
    cinemania *padre = NULL;
    buscarConPadre(raiz, &padre);
    if (aux == NULL) {
        cout << "La Pelicula Con Nombre " << BusquedaPorNombre << " no se ha encontrado.\n";
        return;
    }

    // Caso de dos hijos: no implementado
    if (aux->izq != NULL && aux->der != NULL) {
        cout << "El nodo tiene dos hijos; este caso no esta implementado.\n";
        return;
    }

    // Determinar único hijo (o sin hijo)
    cinemania *hijo = (aux->izq != NULL) ? aux->izq : aux->der;

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
    int opcion;
    do{
        cout<<"1. Registrar Una Nueva Pelicula "<<endl;
        cout<<"2. Buscar Una Pelicula Por Nombre "<<endl;
        cout<<"3. Buscar Peliculas Por Genero "<<endl;
        cout<<"4. Mostrar los 3 Fracasos Taquilleros "<<endl;
        cout<<"5. Mostrar Arbol En PRE-orden "<<endl;
        cout<<"6. Mostrar Arbol En IN-orden "<<endl;
        cout<<"7. Mostrar Arbol En POST-orden "<<endl;
        cout<<"8. Eliminar Una Pelicula "<<endl;
        cout<<"9. Salir Del Sistema "<<endl;
        cout<<"Su opcion es: "<<endl;
        cin>>opcion;
        switch(opcion){
            case 1: registrar(); break;
            case 2:{
                       strcpy(BusquedaPorNombre,"");
                       cout<<"Ingrese el Nombre De la Pelicula A Buscar "<<endl;
                       cin.ignore();
                       cin.getline(BusquedaPorNombre, 50);  // Leer una línea completa, hasta 50 caracteres
                       BuscarNombrePelicula(raiz); break;} 
            case 3:{
                        int opc=0;
                        cout<<"Seleccione El Genero Para Mostrar Peliculas"<<endl;    
                        do {
                            cout<<"1. Accion "<<endl;
                            cout<<"2. Romance "<<endl;
                            cout<<"3. Terror"<<endl;
                            cout<<"4. Comedia"<<endl;
                            cin>>opc;
                            switch (opc)
                            {
                                case 1: strcpy(BusquedaPorGenero,"Accion"); break;
                                case 2: strcpy(BusquedaPorGenero,"Romance"); break;
                                case 3: strcpy(BusquedaPorGenero,"Terror"); break;
                                case 4: strcpy(BusquedaPorGenero,"Comedia"); break;
                                default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 4 "<<endl;
                            }                            
                        }while(opc<1 || opc>4);
                        BuscarPeliculasPorGenero(raiz);break;}
            case 4: fracasostaquilleros(raiz); break;            
            case 5:{ cout<<"Mostrando Contenido En PRE - Orden "<<endl; mostrarPreOrden(raiz); break; }
            case 6:{ cout<<"Mostrando Contenido En IN - Orden "<<endl; mostrarInOrden(raiz); break; }
            case 7:{ cout<<"Mostrando Contenido En POST - Orden "<<endl; mostrarPostOrden(raiz); break; }
            case 8:{
                       strcpy(BusquedaPorNombre,"");
                       cout<<"Ingrese el Nombre De la Pelicula A Buscar "<<endl;
                       cin.ignore();
                       cin.getline(BusquedaPorNombre, 50);  // Leer una línea completa, hasta 50 caracteres
                       eliminarPelicula(); break;} 
        };
    }while(opcion!=9);
}