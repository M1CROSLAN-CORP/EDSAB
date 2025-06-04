#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits> // Para numeric_limits
#include <iomanip> // Para setprecision
#include <windows.h>  // Necesario para SetConsoleOutputCP

using namespace std;

// --- Estructura del Nodo Pelicula (Ahora también nodo AVL) ---
struct Pelicula {
    string nombre;
    int year;
    string genero;
    float recaudacion;
    Pelicula *izquierda;
    Pelicula *derecha;
    int altura; // Altura del nodo para el balance AVL

    // Constructor actualizado para inicializar la altura
    Pelicula(string n, int y, string g, float r) :
        nombre(n), year(y), genero(g), recaudacion(r),
        izquierda(nullptr), derecha(nullptr), altura(1) {} // Una hoja tiene altura 1
};

// --- Funciones Auxiliares para AVL ---

// Obtiene la altura de un nodo (o 0 si es nulo)
int obtenerAltura(Pelicula* peli) {
    if (peli == nullptr) {
        return 0;
    }
    return peli->altura;
}

// Retorna el máximo de dos enteros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Actualiza la altura de un nodo después de una operación
void actualizarAltura(Pelicula* peli) {
    if (peli != nullptr) {
        peli->altura = 1 + max(obtenerAltura(peli->izquierda), obtenerAltura(peli->derecha));
    }
}

// Calcula el factor de balance de un nodo
// FB = Altura(derecha) - Altura(izquierda)
int obtenerFactorBalance(Pelicula* peli) {
    if (peli == nullptr) {
        return 0;
    }
    return obtenerAltura(peli->derecha) - obtenerAltura(peli->izquierda);
}

// --- Rotaciones AVL ---

// Rotación simple a la derecha (z es el nodo desequilibrado)
Pelicula* rotarDerecha(Pelicula* z) {
    Pelicula* y = z->izquierda;
    Pelicula* T3 = y->derecha;

    // Realizar la rotación
    y->derecha = z;
    z->izquierda = T3;

    // Actualizar alturas (¡importante el orden!)
    actualizarAltura(z);
    actualizarAltura(y);

    return y; // Retorna la nueva raíz del subárbol rotado
}

// Rotación simple a la izquierda (z es el nodo desequilibrado)
Pelicula* rotarIzquierda(Pelicula* z) {
    Pelicula* y = z->derecha;
    Pelicula* T2 = y->izquierda;

    // Realizar la rotación
    y->izquierda = z;
    z->derecha = T2;

    // Actualizar alturas (¡importante el orden!)
    actualizarAltura(z);
    actualizarAltura(y);

    return y; // Retorna la nueva raíz del subárbol rotado
}

// --- Función para crear un nuevo nodo de película (ahora con altura inicial) ---
Pelicula* crearNodo(string nombre, int year, string genero, float recaudacion) {
    return new Pelicula(nombre, year, genero, recaudacion);
}

// --- Función para insertar un nodo en el árbol AVL ---
Pelicula* insertar(Pelicula* raiz, string nombre, int year, string genero, float recaudacion) {
    // 1. Inserción normal de un Árbol Binario de Búsqueda (ABB)
    if (raiz == nullptr) {
        return crearNodo(nombre, year, genero, recaudacion);
    }

    if (year < raiz->year) {
        raiz->izquierda = insertar(raiz->izquierda, nombre, year, genero, recaudacion);
    } else if (year > raiz->year) {
        raiz->derecha = insertar(raiz->derecha, nombre, year, genero, recaudacion);
    } else {
        // Condición: Si el año ya existe, no se inserta
        // Esto mantiene el AVL ordenado por año y evita duplicados en la clave de ordenamiento.
        cout << "Error: Ya existe una película con el año " << year << ". No se puede insertar '" << nombre << "'." << endl;
        return raiz; // No se insertó, retornar el nodo actual
    }

    // 2. Actualizar altura del nodo actual
    actualizarAltura(raiz);

    // 3. Obtener el factor de balance y verificar desequilibrio
    int factorBalance = obtenerFactorBalance(raiz);

    // 4. Realizar rotaciones si está desequilibrado

    // Caso LL (Left Left)
    if (factorBalance < -1 && year < raiz->izquierda->year) {
        return rotarDerecha(raiz);
    }

    // Caso RR (Right Right)
    if (factorBalance > 1 && year > raiz->derecha->year) {
        return rotarIzquierda(raiz);
    }

    // Caso LR (Left Right)
    if (factorBalance < -1 && year > raiz->izquierda->year) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    // Caso RL (Right Left)
    if (factorBalance > 1 && year < raiz->derecha->year) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz; // Retorna el nodo actual (sin cambios si está balanceado)
}

// Función para encontrar el nodo con el valor mínimo (para eliminación)
Pelicula* encontrarMinimo(Pelicula* nodo) {
    Pelicula* actual = nodo;
    while (actual && actual->izquierda != nullptr) {
        actual = actual->izquierda;
    }
    return actual;
}


// --- Otras funciones (reordenadas) ---

// Función para imprimir los detalles de una película (auxiliar)
void imprimirDetallesPelicula(Pelicula* peli) {
    cout << "Nombre: " << peli->nombre
         << ", Año: " << peli->year
         << ", Género: " << peli->genero
         << ", Recaudación: " << fixed << setprecision(2) << peli->recaudacion << " millones"
         << " (Altura: " << peli->altura
         << ", FB: " << obtenerFactorBalance(peli) << ")" << endl;
}

// Función auxiliar para contar el número total de nodos
void contarNodos(Pelicula* nodo, int& count) {
    if (nodo != nullptr) {
        contarNodos(nodo->izquierda, count);
        count++;
        contarNodos(nodo->derecha, count);
    }
}

// Función para recolectar todas las películas en un vector (para sorting, etc.)
void recolectarPeliculas(Pelicula* raiz, vector<Pelicula*>& peliculas) {
    if (raiz != nullptr) {
        recolectarPeliculas(raiz->izquierda, peliculas);
        peliculas.push_back(raiz);
        recolectarPeliculas(raiz->derecha, peliculas);
    }
}

// Función de comparación para ordenar películas por recaudación (ascendente)
bool compararRecaudacion(const Pelicula* a, const Pelicula* b) {
    return a->recaudacion < b->recaudacion;
}


// --- Recorridos del árbol ---

void inorden(Pelicula* raiz) {
    if (raiz != nullptr) {
        inorden(raiz->izquierda);
        imprimirDetallesPelicula(raiz);
        inorden(raiz->derecha);
    }
}

void preorden(Pelicula* raiz) {
    if (raiz != nullptr) {
        imprimirDetallesPelicula(raiz);
        preorden(raiz->izquierda);
        preorden(raiz->derecha);
    }
}

void posorden(Pelicula* raiz) {
    if (raiz != nullptr) {
        posorden(raiz->izquierda);
        posorden(raiz->derecha);
        imprimirDetallesPelicula(raiz);
    }
}

// --- Eliminación (manteniendo el orden por año y AVL) ---
Pelicula* eliminarPelicula(Pelicula* raiz, int yearEliminar) {
    // 1. Eliminación normal de ABB
    if (raiz == nullptr) {
        return raiz;
    }

    if (yearEliminar < raiz->year) {
        raiz->izquierda = eliminarPelicula(raiz->izquierda, yearEliminar);
    } else if (yearEliminar > raiz->year) {
        raiz->derecha = eliminarPelicula(raiz->derecha, yearEliminar);
    } else {
        // Nodo con el año a eliminar encontrado

        // Caso 1: Nodo hoja o con un solo hijo
        if (raiz->izquierda == nullptr) {
            Pelicula* temp = raiz->derecha;
            delete raiz;
            return temp; // Regresa el subárbol derecho (o nullptr si era una hoja)
        } else if (raiz->derecha == nullptr) {
            Pelicula* temp = raiz->izquierda;
            delete raiz;
            return temp; // Regresa el subárbol izquierdo
        }

        // Caso 2: Nodo con dos hijos
        // Encontrar el sucesor inorden (el menor en el subárbol derecho)
        Pelicula* temp = encontrarMinimo(raiz->derecha);

        // Copiar los datos del sucesor al nodo actual
        raiz->nombre = temp->nombre;
        raiz->year = temp->year;
        raiz->genero = temp->genero;
        raiz->recaudacion = temp->recaudacion;

        // Eliminar el sucesor recursivamente
        raiz->derecha = eliminarPelicula(raiz->derecha, temp->year);
    }

    // Si el árbol solo tenía un nodo antes de la eliminación, ahora es nulo
    if (raiz == nullptr) {
        return raiz;
    }

    // 2. Actualizar altura del nodo actual
    actualizarAltura(raiz);

    // 3. Obtener el factor de balance
    int factorBalance = obtenerFactorBalance(raiz);

    // 4. Rebalancear el nodo si es necesario

    // Caso LL (Left Left)
    if (factorBalance < -1 && obtenerFactorBalance(raiz->izquierda) <= 0) {
        return rotarDerecha(raiz);
    }

    // Caso LR (Left Right)
    if (factorBalance < -1 && obtenerFactorBalance(raiz->izquierda) > 0) {
        raiz->izquierda = rotarIzquierda(raiz->izquierda);
        return rotarDerecha(raiz);
    }

    // Caso RR (Right Right)
    if (factorBalance > 1 && obtenerFactorBalance(raiz->derecha) >= 0) {
        return rotarIzquierda(raiz);
    }

    // Caso RL (Right Left)
    if (factorBalance > 1 && obtenerFactorBalance(raiz->derecha) < 0) {
        raiz->derecha = rotarDerecha(raiz->derecha);
        return rotarIzquierda(raiz);
    }

    return raiz;
}
// --- Resto de funciones (sin cambios mayores) ---
// La búsqueda por nombre es ineficiente en este AVL, ya que está ordenado por año.
// Para búsquedas eficientes por nombre, necesitarías otro árbol o una tabla hash.
void buscarPelicula(Pelicula* raiz, string nombreBuscar) {
    if (raiz == nullptr) {
        cout << "Película '" << nombreBuscar << "' no encontrada." << endl;
        return;
    }

    // Se realiza un recorrido completo porque el árbol está ordenado por año, no por nombre
    bool encontrada = false;
    vector<Pelicula*> peliculas;
    recolectarPeliculas(raiz, peliculas); // Recolecta todas las películas

    for (Pelicula* peli : peliculas) {
        if (peli->nombre == nombreBuscar) {
            cout << "Película encontrada:" << endl;
            imprimirDetallesPelicula(peli);
            encontrada = true;
            break;
        }
    }

    if (!encontrada) {
        cout << "Película '" << nombreBuscar << "' no encontrada." << endl;
    }
}

void mostrarPeliculasPorGenero(Pelicula* raiz, string generoBuscar) {
    if (raiz != nullptr) {
        mostrarPeliculasPorGenero(raiz->izquierda, generoBuscar);
        if (raiz->genero == generoBuscar) {
            imprimirDetallesPelicula(raiz);
        }
        mostrarPeliculasPorGenero(raiz->derecha, generoBuscar);
    }
}

void mostrarFracasosTaquilleros(Pelicula* raiz) {
    if (raiz == nullptr) {
        cout << "No hay películas en el sistema." << endl;
        return;
    }

    vector<Pelicula*> peliculas;
    recolectarPeliculas(raiz, peliculas);

    if (peliculas.size() < 3) {
        cout << "No hay suficientes películas para mostrar los 3 fracasos taquilleros (Se necesitan al menos 3 películas)." << endl;
        if (!peliculas.empty()) {
            cout << "Películas ingresadas: " << endl;
            for(Pelicula* p : peliculas) {
                imprimirDetallesPelicula(p);
            }
        }
        return;
    }

    sort(peliculas.begin(), peliculas.end(), compararRecaudacion);

    cout << "\nLos 3 fracasos taquilleros son:" << endl;
    for (int i = 0; i < min((size_t)3, peliculas.size()); ++i) {
        cout << i + 1 << ". ";
        imprimirDetallesPelicula(peliculas[i]);
    }
}

void liberarArbol(Pelicula* raiz) {
    if (raiz != nullptr) {
        liberarArbol(raiz->izquierda);
        liberarArbol(raiz->derecha);
        delete raiz;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);  // Configura la consola para UTF-8
    Pelicula* raiz = nullptr;
    int opcion;

    do {
        cout << "\n--- Menú ---" << endl;
        cout << "1. Ingresar nueva película" << endl;
        cout << "2. Mostrar recorrido Inorden" << endl;
        cout << "3. Mostrar recorrido Preorden" << endl;
        cout << "4. Mostrar recorrido Posorden" << endl;
        cout << "5. Buscar película por nombre" << endl;
        cout << "6. Mostrar películas por género" << endl;
        cout << "7. Mostrar los 3 fracasos taquilleros" << endl;
        cout << "8. Eliminar película por AÑO" << endl; // Cambiado a eliminar por año
        cout << "9. Mostrar todas las películas" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese su opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpiar el buffer del newline

        switch (opcion) {
            case 1: {
                string nombre;
                int year;
                string genero;
                float recaudacion;

                cout << "Ingrese el nombre de la película: ";
                getline(cin, nombre);

                cout << "Ingrese el año de realización: ";
                cin >> year;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "Ingrese el género de la película: ";
                getline(cin, genero);

                cout << "Ingrese la recaudación en millones de dólares: ";
                cin >> recaudacion;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                raiz = insertar(raiz, nombre, year, genero, recaudacion);
                break;
            }
            case 2:
                cout << "\nRecorrido Inorden:" << endl;
                inorden(raiz);
                break;
            case 3:
                cout << "\nRecorrido Preorden:" << endl;
                preorden(raiz);
                break;
            case 4:
                cout << "\nRecorrido Posorden:" << endl;
                posorden(raiz);
                break;
            case 5: {
                string nombreBuscar;
                cout << "Ingrese el nombre de la película a buscar: ";
                getline(cin, nombreBuscar);
                buscarPelicula(raiz, nombreBuscar);
                break;
            }
            case 6: {
                string generoBuscar;
                cout << "Ingrese el género a buscar: ";
                getline(cin, generoBuscar);
                cout << "\nPelículas del género '" << generoBuscar << "':" << endl;
                mostrarPeliculasPorGenero(raiz, generoBuscar);
                break;
            }
            case 7:
                mostrarFracasosTaquilleros(raiz);
                break;
            case 8: {
                int yearEliminar;
                cout << "Ingrese el AÑO de la película a eliminar: ";
                cin >> yearEliminar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                raiz = eliminarPelicula(raiz, yearEliminar);
                cout << "Película del año " << yearEliminar << " eliminada (si existía)." << endl;
                break;
            }
            case 9:
                cout << "\n--- Todas las películas ingresadas ---" << endl;
                inorden(raiz); // Inorden las muestra ordenadas por año
                cout << "--- Fin de la lista de películas ---" << endl;
                break;
            case 0:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opción inválida. Por favor, intente de nuevo." << endl;
        }
    } while (opcion != 0);

    // Liberar la memoria del árbol antes de salir
    liberarArbol(raiz);

    return 0;
}