// ESTUDIANTE * ANTHONY CAICEDO CONGOLINO

#include <iostream>
using namespace std;

//Declaracion Nodo PRODUCTOS
struct Productos {
    int codigo,cantidad,precio,TotalCosto;
    char nombre;
    int valor;
    struct Productos *sig;//NULL
};
//Generar una funcion que permita determinar si existe un nodo con valor X. Y cuantos nodos tienen dicho valor
struct Productos *cab, *aux, *ultimo, *semaforo;

int mostrarNodos(){
    int cont=1;
    for(aux=cab; aux!=NULL; aux=aux->sig){
        cout<< "                PRODUCTO  # "<< cont <<endl;
        cout<< "############################################"<<endl;
        cout<< " Codigo Del Producto = " <<aux->codigo << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Nombre Del Producto = " <<aux->valor << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Cantidad Del Producto = " <<aux->cantidad << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Precio Del Producto = " <<aux->precio << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< " Valor De la Cantidad de Productos = " <<aux->TotalCosto << " = Ubicacion En Memoria = "<< aux <<endl;
        cout<< "############################################"<<endl;
        cont++;       
    }
    
}
int crearNodo(){    
    aux = ((struct Productos *) malloc(sizeof(struct Productos)));
    cout<<"Registre el Codigo Del Producto: ";
    cin>>aux->codigo;
    
    cout<<"Registre el Nombre Del Producto: ";
    cin>>aux->nombre;
     

    cout<<"Registre La Cantidad Disponible ";
    cin>>aux->cantidad;
    
    cout<<"Registre El Valor Por Unidad Del Producto ";
    cin>>aux->precio;
    aux->TotalCosto = aux->cantidad * aux->precio;

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

int realizarventa(){
    int vender;
    int contador=0;
    cout<<"Ingrese El Codigo Del Producto a Vender: ";
    cin>>vender;

    for(aux=cab; aux!=NULL; aux=aux->sig){        
        if(vender==aux->codigo){
           contador++;
           semaforo = aux;
           cout<<" 1) Realizar Una Venta  "<<endl;
           cout<<" 2) Cancelar Venta"<<endl;
           cin>>vender;
        }    
               if(semaforo==aux && vender==1){
                    cout<<"Cantidad De Productos a Vender : ";
                    cin>>vender;
                    if(vender>aux->cantidad){
                     cout<<"No Se Puede Realizar La Venta Cantidad Insuficiente"<<endl;
                    }else{
                        aux->cantidad = aux->cantidad - vender;
                        aux->TotalCosto = aux->cantidad * aux->precio;
                        cout<<"Venta Realizada Correctamente Disponible En Bodega Despues De la Venta: "<< aux->cantidad <<" Unidades "<<endl;
                    }
                    
               } 
               if(semaforo==aux && vender==2){
                cout<<"Venta Cancelada Correctamente : "<<endl;
              }                                   
    }
    if(contador==0){
        cout<<"El Producto Que Intenta Vender No Se Encuentra Registrado"<<endl;
    }    

}
int buscar(){
    int busqueda;
    int contador=0;
    cout<<"Ingrese El Codigo Del Producto a Buscar: ";
    cin>>busqueda;

    for(aux=cab; aux!=NULL; aux=aux->sig){
        if(busqueda==aux->codigo){
           contador++;
           semaforo = aux;
           cout<<" Que Desea Realizar Con Este Producto ? "<<endl;
           cout<<" 1) Adicionar Al Inventario Del Producto  "<<endl;
           cout<<" 2) Cancelar Operacion  "<<endl;
           cin>>busqueda;
        }    
                if(semaforo==aux && busqueda==1){
                    cout<<"Adiciones El Mas Cajas Disponibles Para El Producto : ";
                    cin>>busqueda;
                    aux->cantidad = aux->cantidad + busqueda;
                    aux->TotalCosto = aux->cantidad * aux->precio;
                }
                if(semaforo==aux && busqueda==2){
                    cout<<"Operacion Cancelada Correctamente : "<<endl;
               }                                            
    }
    if(contador==0){
        cout<<"El Producto Que Intenta Actualizar No Se Encuentra Registrado"<<endl;
    }    
}
int main(){
    int opc;
    do {
        cout<<"1. Registrar Productos"<<endl;
        cout<<"2. Mostrar Productos"<<endl;
        cout<<"3. Buscar y Actualizar Productos"<<endl;
        cout<<"4. Realizar Venta"<<endl;
        cout<<"5. Eliminar Productos Activos "<<endl;
        cout<<"6. Salir"<<endl;
        cin>>opc;
        switch (opc)
        {
            case 1: crearNodo(); break;
            case 2: mostrarNodos(); break;
            case 3: buscar(); break;
            case 4: realizarventa(); break;
            default: cout<<"Opcion Incorrecta Marque una Opcion De 1 Hasta 6 "<<endl;
        }
    }while(opc!=6);
}