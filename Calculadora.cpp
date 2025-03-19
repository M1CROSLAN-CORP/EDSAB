#include <iostream>
using namespace std;

int main()
{
   int a,b, resultado,opcion;
   std::cout << "1 Para Realizar la suma " << std::endl;
   std::cout << "2 Para Realizar la resta " << std::endl;
   std::cout << "3 Para Realizar la multiplicacion " << std::endl;
   std::cout << "4 Para Realizar la division " << std::endl;
   std::cin >> opcion;
   
   switch(opcion){
       case 1:
        std::cout << "ingresar el  primer valor" << std::endl;
        std::cin >> a;
        std::cout << " ingresar en segundo valor" << std::endl;
        std::cin >> b;
        resultado = a + b;
        std::cout << "El resultado es" << resultado <<std::endl;
       break;
       
       case 2:
        std::cout << "ingresar el  primer valor" << std::endl;
        std::cin >> a;
        std::cout << " ingresar en segundo valor" << std::endl;
        std::cin >> b;
        resultado = a - b;
        std::cout << "El resultado es" << resultado <<std::endl;
       break;
       
       case 3:
        std::cout << "ingresar el  primer valor" << std::endl;
        std::cin >> a;
        std::cout << " ingresar en segundo valor" << std::endl;
        std::cin >> b;
        resultado = a * b;
        std::cout << "El resultado es" << resultado <<std::endl;
       break;
       
       case 4:
        std::cout << "ingresar el  primer valor" << std::endl;
        std::cin >> a;
        std::cout << " ingresar en segundo valor" << std::endl;
        std::cin >> b;
        resultado = a / b;
        std::cout << "El resultado es" << resultado <<std::endl;
       break;
   }
    return 0;
}