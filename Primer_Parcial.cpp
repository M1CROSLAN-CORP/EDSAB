// ESTUDIANTE * ANTHONY CAICEDO CONGOLINO

#include <iostream>
#include <string.h>
using namespace std;

//Declaracion Estructura JUGADORES TIPO FIFO
struct jugadores {
    int id_cedula,edad;
    char nombre[50];
    char deporte[50], genero;
    struct jugadores *sig;//NULL
};
struct jugadores *cab, *aux, *ultimo, *temp;
// FIN DE LA ESTRUCTURA

//DECLARACION ESTRUCTURA PARTICIPACION TIPO LIFO
struct Participacion {
    int id_cedula_P,edad_P;
    char nombre_P[50];
    char deporte_P[50], genero_P;
    struct Participacion *sig;//NULL
};
struct Participacion *toP, *auxP, *aux2P;
//FIN DE LA ESTRUCTURA

int CantidadJugadores=0, contarP=0, contarJ=0;

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
            cout<<"Marcacion Incorrecta"<<endl<<endl;
        }       
    }while(opc<1 || opc>2);

    cout<<"Registre La Edad Del Jugador "<<endl;
    cin>>aux->edad;

    cout<<"Registre El Deporte a Participar "<<endl;
   
    do {
        cout<<"1. Futbol "<<endl;
        cout<<"2. Baloncesto "<<endl;
        cout<<"3. Atletismo"<<endl;
        cout<<"4. Patinaje"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: strcpy(aux->deporte,"Futbol"); break;
            case 2: strcpy(aux->deporte,"Baloncesto"); break;
            case 3: strcpy(aux->deporte,"Atletismo"); break;
            case 4: strcpy(aux->deporte,"Patinaje"); break;
            default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 4 "<<endl;
        }
        
    }while(opc<1 || opc>4);
    
    cout<<"## El  Jugador "<< aux->nombre <<" Registrado Correctamente "<<endl<<endl;

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
     if(contarJ>0){ 
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
    if(contarP>0){
        for(auxP=toP; auxP!=NULL; auxP=auxP->sig){
            cout<< "    Historial Participacion Jugadores  # "<< contarP <<endl;
            cout<< "####################################################"<<endl;
            cout<< " Cedula Del Jugador: = " << auxP->id_cedula_P   <<endl;
            cout<< " Nombre Del Jugador: = " << auxP->nombre_P      <<endl;
            cout<< " Edad Del Jugador: = " << auxP->edad_P          <<endl;
            cout<< " Genero Del jugador: = "<<  auxP->genero_P      <<endl;
            cout<< " Su Deporte Es: = " << auxP->deporte_P          <<endl;
            cout<< "#####################################################"<<endl;      
        }
    }else{
        cout<< " No Se ha Registrado Participacion De Jugadores Al Momento "<<endl<<endl;
    }
}

int Participacion(){   
   int opc=0;
   for(aux=cab; aux!=NULL; aux=aux->sig){
        if(aux==cab && opc==0){
            if(aux->edad>15){
                auxP = ((struct Participacion *) malloc(sizeof(struct Participacion)));
                strcpy(auxP->nombre_P, aux->nombre);
                strcpy(auxP->deporte_P, aux->deporte);
                auxP->id_cedula_P = aux->id_cedula;
                auxP->edad_P = aux->edad;
                auxP->genero_P = aux->genero;
             cout<< " El Jugador " << aux->nombre <<" Ha Quedado Registrado Para participar "<<endl<<endl;
             CantidadJugadores--;
             contarP++;
             contarJ--;
              if(toP==NULL){
                toP = auxP;
                toP->sig = NULL;
              } else {
                        auxP->sig = toP;
                        toP = auxP;
                    }
                auxP = NULL;
                free(auxP);

             //Desencolar De En La Lista FiFO EL JUGADOR QUE ENTRO A PARTICIPAR
             temp = cab;
             cab = cab->sig;
             free(temp);     
             opc=1;
           }else{
              cout<<" No Cumple Con La Edad Debe Tener Mas De 15 A\u00F1os "<<endl<<endl;
              cout<<" Se Eliminara Este Jugador De La Lista FIFO ? "<<endl;
              cout<<" 1: SI "<<endl;
              cout<<" 2: NO "<<endl;
              cin>>opc;

              if(opc==1){
                 cout<<" EL Jugador De Nombre " << aux->nombre << " Quedo Eliminado Por Tener " << aux->edad << " Años "<<endl;
                 //Desencolar De En La Lista FIFO POR SER MENOR DE EDAD
                 temp = cab;
                 cab = cab->sig;
                 free(temp);
                 CantidadJugadores--;
                 contarP--;
              }else{
                 cout<<" No Se Elimino El Jugador "<<endl;
                 opc=1;
              }
           }
        }
    }   
}

int deshacerParticipacion(){
    if (toP==NULL) {
        cout<<" No Hay Participaciones Para Deshacer "<<endl;
    }else{
        aux2P = toP;
        toP = toP->sig;        
        contarP--;        
              
        cout<< aux2P->id_cedula_P << aux2P->nombre_P << aux2P->edad_P << aux2P->genero_P << aux2P->deporte_P <<endl;

        aux = ((struct jugadores *) malloc(sizeof(struct jugadores)));            
            strcpy(aux->nombre, aux2P->nombre_P);
            strcpy(aux->deporte, aux2P->deporte_P);
            aux->id_cedula = aux2P->id_cedula_P;
            aux->edad = aux2P->edad_P;
            aux->genero = aux2P->genero_P;
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
            cout<<" La participacion Del Jugador "<< aux2P->nombre_P << " A Sido Eliminada y Queda En La Cola De Espera FIFO"<<endl;
            free(aux2P);
    }
}

int main(){
    int opc;
    do {
        cout<<"1. Agregar Jugador a Cola "<<endl;
        cout<<"2. Mostrar Jugadores En Espera "<<endl;
        cout<<"3. Contar Jugadores En Espera "<<endl;
        cout<<"4. Permitir participacion Segun El Orden En La Fila "<<endl;
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
            case 6: deshacerParticipacion(); break;
            //default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 6 "<<endl;
        }
    }while(opc!=7);
}