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


struct Participacion {
    int id_cedula_P,edad_P;
    char nombre_P[50];
    char deporte_P[50], genero_P;
    struct Participacion *sig;//NULL
};
struct Participacion *toP, *auxP, *aux2P;

int CantidadJugadores=0,contarP=0,contarJ=0;

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

    cout<<"## El  Jugador "<< aux->nombre <<" Registrado Correctamente "<<endl<<endl;
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
    CantidadJugadores++;
    contarJ++;
}

int MostrarCantidadJugadores(){
    if(CantidadJugadores==0){
      cout<<"Lo Sentimos En EL Momento No Hay Jugadores A lA Espera De Participar "<<endl<<endl;
    }else{
      cout<<"En El Momento Tenemos A la Espera " << CantidadJugadores <<" Por participar "<<endl<<endl;
    }
}

int MostrarJugadores(){
     if(contarJ!=0){ 
        int cont=1;
        for(aux=cab; aux!=NULL; aux=aux->sig){
            cout<< "      Jugadores Inscritos  # "  << cont   <<endl;
            cout<< "###################################################"<<endl;
            cout<< " Cedula Del Jugador: = " <<aux->id_cedula <<endl;
            cout<< " Nombre Del Jugador: = " <<aux->nombre    <<endl;
            cout<< " Edad Del Jugador: = " <<aux->edad        <<endl;
            cout<< " Genero Del jugador: = " <<aux->genero    <<endl;
            cout<< " Su Deporte Es: = " <<aux->deporte        <<endl;
            cout<< "####################################################"<<endl;
            cont++;       
        }
    }else{
        cout<< " No Se ha Registrado Jugadores En La Base De Datos "<<endl<<endl;
    }
    
}

int MostrarHistorial(){
    if(CantidadJugadores!=0){
        for(auxP=toP; auxP!=NULL; auxP=auxP->sig){
            cout<< "                Historial Participacion Jugadores  # "<< CantidadJugadores <<endl;
            cout<< "#######################################################################"<<endl;
            cout<< " Cedula Del Jugador: = " <<auxP->id_cedula_P << " = Ubicacion En Memoria = "<< auxP <<endl;
            cout<< " Nombre Del Jugador: = " <<auxP->nombre_P << " = Ubicacion En Memoria = "<< auxP <<endl;
            cout<< " Edad Del Jugador: = " <<auxP->edad_P << " = Ubicacion En Memoria = "<< auxP <<endl;
            cout<< " Genero Del jugador: = " <<auxP->genero_P << " = Ubicacion En Memoria = "<< auxP <<endl;
            cout<< " Su Deporte Es: = " <<auxP->deporte_P << " = Ubicacion En Memoria = "<< auxP <<endl;
            cout<< "#######################################################################"<<endl;
            contarP++;       
        }
    }else{
        cout<< " No Se ha Registrado Participacion De Jugadores Al Momento "<<endl<<endl;
    }
}

int Participacion(){
   auxP = ((struct Participacion *) malloc(sizeof(struct Participacion)));
   for(aux=cab; aux!=NULL; aux=aux->sig){
        if(aux!=NULL){
            if(aux->edad>15){
                auxP->id_cedula_P = aux->id_cedula;
                //auxP->nombre_P = aux->nombre;
                auxP->edad_P = aux->edad;
                auxP->genero_P = aux->genero;
                //auxP->deporte_P = aux->deporte;
             cout<< " El Jugador Ha Quedado Registrado Para participar "<<endl<<endl;
             CantidadJugadores--;
             contarP++;
           }else{
              cout<<" No Cumple Con La Edad Debe Tener Mas De 15 Años "<<endl<<endl;
           }
        }
    }
    if(toP==NULL){
        toP = auxP;
        toP->sig = NULL;
    } else {
        auxP->sig = toP;
        toP = auxP;
    }
    auxP = NULL;
    free(auxP);
    
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
            case 3: MostrarCantidadJugadores(); break;
            case 4: Participacion(); break;
            case 5: MostrarHistorial(); break;
            case 6: ; break;
            //default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 6 "<<endl;
        }
    }while(opc!=7);
}