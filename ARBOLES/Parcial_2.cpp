#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>  // Necesario para SetConsoleOutputCP
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

bool existeAno(cinemania* raiz, int ano) {
    if (raiz == NULL) return false;

    if (ano == raiz->ano_realizado) {
        return true;
    } else if (ano < raiz->ano_realizado) {
        return existeAno(raiz->izq, ano);
    } else {
        return existeAno(raiz->der, ano);
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

    if (existeAno(raiz, aux->ano_realizado)) {
        cout << "Ya existe una película registrada con ese año. No se permite duplicados.\n";
        free(aux);  // Liberar memoria si no se usará
        return 0;   // Cancelar el registro
    }
    
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
        cout<<"Año De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;        
        mostrarPreOrden(nuevaraiz->izq);
        mostrarPreOrden(nuevaraiz->der);
    }
}

int mostrarPostOrden(struct cinemania *nuevaraiz){
    if(nuevaraiz!=NULL){        
        mostrarPostOrden(nuevaraiz->izq);
        mostrarPostOrden(nuevaraiz->der);
        cout<<"Nombre Pelicula = "<<nuevaraiz->nombre_pelicula<<endl;
        cout<<"Año De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;
    }
}

int mostrarInOrden(struct cinemania *nuevaraiz){
    if(nuevaraiz!=NULL){        
        mostrarInOrden(nuevaraiz->izq);
        cout<<"Nombre Pelicula = "<<nuevaraiz->nombre_pelicula<<endl;
        cout<<"Año De Estreno = "<<nuevaraiz->ano_realizado<<endl<<endl;
        mostrarInOrden(nuevaraiz->der);
    }
}

int BuscarNombrePelicula(struct cinemania *buscar_raiz){                
    if(buscar_raiz!=NULL){
        if(strcmp(BusquedaPorNombre, buscar_raiz->nombre_pelicula) == 0){
            cout<<"Nombre Pelicula = "<<buscar_raiz->nombre_pelicula<<endl;
            cout<<"Año De Estreno = "<<buscar_raiz->ano_realizado<<endl<<endl;
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
            cout<<"Año De Estreno = "<<buscar_raiz->ano_realizado<<endl;
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

cinemania* buscarConPadre(cinemania *nuevaRaiz, char*eliminarP, cinemania **padre) {
    if (nuevaRaiz == NULL) return NULL;

    if (strcmp(eliminarP, nuevaRaiz->nombre_pelicula) == 0) {
            aux = nuevaRaiz;            
            return aux;
        }
    
    // Buscar en el hijo izquierdo
    *padre = nuevaRaiz;
    cinemania* encontrado = buscarConPadre(nuevaRaiz->izq, eliminarP, padre);
    if (encontrado != NULL) return encontrado;

    // Buscar en el hijo derecho
    *padre = nuevaRaiz;
    return buscarConPadre(nuevaRaiz->der, eliminarP, padre);    
}

cinemania* encontrarHijo(cinemania* aux2){
  while(aux2->izq!= NULL){
     aux2 = aux2->izq;
  }
  return aux2;
}

void eliminarPelicula() {
    if (raiz == NULL) {
        cout << "No Hay Peliculas Registradas En EL Sistema.\n";
        return;
    }

    char eliminarP[50];
    cout << "Digite el Nombre De Pelicula a Eliminar: ";
    cin.ignore();
    cin.getline(eliminarP, 50);
    
    cinemania *padre = NULL;
    cinemania *aux = buscarConPadre(raiz, eliminarP, &padre);

    if (aux == NULL) {
        cout << "La Pelicula Con Nombre " << eliminarP << " No Se Ha Encontrado.\n";
        return;
    }

    // Caso de dos hijos: no implementado
    if (aux->izq != NULL && aux->der != NULL) {
        cinemania* sucesor = encontrarHijo(aux->der);

        strcpy(aux->nombre_pelicula,sucesor->nombre_pelicula);
        aux->ano_realizado = sucesor->ano_realizado;
        strcpy(aux->genero,sucesor->genero);
        aux->dinero_recaudado = sucesor->dinero_recaudado;

        cinemania *padreSucesor = aux;
        cinemania *actual = aux->der;
        while(actual->izq !=NULL){
           padreSucesor = actual;
           actual = actual->izq;
        }
        if (padreSucesor->izq == actual)
            padreSucesor->izq = (actual->der != NULL) ? actual->der : NULL;
        else
            padreSucesor->der = (actual->der != NULL) ? actual->der : NULL;

        free(actual);

        cout << "La Pelicula Fue Eliminada Correctamente Del Arbol.\n"<<endl<<endl;
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
    cout << "Pelicula Eliminada Correctamente.\n";
}

int main(){
    SetConsoleOutputCP(CP_UTF8);  // Configura la consola para UTF-8
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
            case 8:{ eliminarPelicula(); break;} 
        };
    }while(opcion!=9);
}