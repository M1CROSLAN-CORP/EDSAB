// ESTUDIANTE * ANTHONY CAICEDO CONGOLINO

#include <iostream>
using namespace std;

//Declaracion Estructura JUGADORES
struct jugadores {
    int id_cedula,edad;
    char nombre[50];
    char deporte[50], genero;
    struct jugadores *sig;//NULL
};

struct jugadores *cab, *aux, *ultimo;

int RegistrarJugador(){    
    aux = ((struct jugadores *) malloc(sizeof(struct jugadores)));
    cout<<"Registre Numero De Cedula Del Jugador: ";
    cin>>aux->id_cedula;
    
    cout<<"Registre El Nombre Completo Del Jugador: ";
    cin>>aux->nombre;     

    cout<<"Registre El Tipo De Sexo"<<endl;
    int opc;
    do {
        cout<<"Marque 1 Sexo Femenino"<<endl;
        cout<<"Marque 2 Sexo Masculino"<<endl;
        cin>>opc;
        if(opc==1){
         aux->genero = 'F';
        }else if (opc==2){
         aux->genero = 'M';
        }else{
            cout<<"Marcacion Incorrecta"<<endl;
        }       
    }while(opc<1 || opc>2);

    cout<<"Registre La Edad Del Jugador "<<endl;
    cin>>aux->edad;

    cout<<"Registre El Deporte a Participar ";
    cin>>aux->deporte;
    /*
    do {
        cout<<"1. Futbol "<<endl;
        cout<<"2. Baloncesto "<<endl;
        cout<<"3. Atletismo"<<endl;
        cout<<"4. Patinaje"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: aux->deporte = "Futbol"; break;
            case 2: aux->deporte = "Baloncesto"; break;
            case 3: aux->deporte = "Atletismo"; break;
            case 4: aux->deporte = "Patinaje"; break;
            default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 4 "<<endl;
        }
        
    }while(opc<1 || opc>4);
    */

    aux->sig = NULL;
    if(cab==NULL){
        cab = aux;
    } else {
        ultimo = cab;
        while(ultimo->sig!=NULL){
            ultimo = ultimo->sig;
        }
        ultimo->sig = aux;
        ultimo = NULL;
        free(ultimo);
    }    
    aux = NULL;
    free(aux);
}

int MostrarJugadores(){
    int cont=1;
    for(aux=cab; aux!=NULL; aux=aux->sig){
        cout<< "                Jugadores Inscritos  # "<< cont <<endl;
        cout<< "#######################################################################"<<endl;
        cout<< " Cedula Del Jugador: = " <<aux->id_cedula << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Nombre Del Jugador: = " <<aux->nombre << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Edad Del Jugador: = " <<aux->edad << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Genero Del jugador: = " <<aux->genero << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Su Deporte Es: = " <<aux->deporte << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< "#######################################################################"<<endl;
        cont++;       
    }
    
}

int main(){
    int opc;
    do {
        cout<<"1. Agregar Jugador a Cola "<<endl;
        cout<<"2. Mostrar Jugadores En Espera "<<endl;
        cout<<"3. Contar Jugadores En Espera "<<endl;
        cout<<"4. Permitir participacion del siguiente jugador "<<endl;
        cout<<"5. Mostrar Historial De Participacion "<<endl;
        cout<<"6. Deshacer Ultima Participacion"<<endl;
        cout<<"7. Salir"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: RegistrarJugador(); break;
            case 2: MostrarJugadores(); break;
            case 3: ; break;
            case 4: ; break;
            case 5: ; break;
            case 6: ; break;
            //default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 6 "<<endl;
        }
    }while(opc!=7);
}