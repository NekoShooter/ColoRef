#include <iostream>
#include "base_RGB/Convertir_a_RGB.h"

using namespace std;

int main()
{
    //pruevas de Convertir_a_RGB
    char Hexadecimal[8];
    char CSS[5];
    long a = 1247;
    if (Convertir_RGB_A_CSS(125,74,255,CSS)==-1)
        cout <<"ERROR"<<endl;
    else
        cout << CSS << endl;
    Convertir_CSS_A_Hexadecimal(CSS,Hexadecimal);
    cout << Hexadecimal << endl;
    a = Convertir_Hexadecimal_A_EnteroPuro(Hexadecimal);
    short r,g,b;
    Convertir_Entero_A_RGB(&r,&g,&b,a);
    cout <<r<<" "<<g<<" "<<b<<endl;
    return 0;
}
