#include <stdio.h>
#include <malloc.h>

//Declaracion Nodo
struct nodo {
    int valor;
    struct nodo *sig;//NULL
};
struct nodo *top, *aux, *aux2;

int crearNodo(){    
    aux = ((struct nodo *) malloc(sizeof(struct nodo)));
    printf("Registre el valor: ");
    scanf("%d", &aux->valor);
    
    if(top==NULL){
        top = aux;
        top->sig = NULL;
    } else {
        aux->sig = top;
        top = aux;
    }
    aux = NULL;
    free(aux);
}

int mostrarNodos(){
    for(aux=top; aux!=NULL; aux=aux->sig){
        printf("Nodo: %d\n", aux->valor);        
    }
}

int eliminarNodo(){
    if(top==NULL){
      printf("No Hay Nodos A Eliminar:\n");
    }else{
        aux2 = top;
        top = top->sig;
        printf("Se ha Eliminado el Nodo: %d\n", aux2->valor); 
        free(aux2);
    }
    
}

int main(){
    int opc;
    do {
        printf("1. Registrar Nodo\n");
        printf("2. Mostrar Nodos\n");
        printf("3. Eliminar Nodos\n");
        printf("4. Salir\n");
        scanf("%d", &opc);
        switch (opc)
        {
            case 1: crearNodo(); break;
            case 2: mostrarNodos(); break;
            case 3: eliminarNodo(); break;
        }
    }while(opc!=4);
}