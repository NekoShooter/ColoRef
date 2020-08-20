#include "Algoritmo_RGB.h"
#include "Convertir_a_RGB.h"
#include "MACROS.h"

short dividir_tono(short Tono, short *Claro, short *Oscuro,double Nivel_Brillo, double Nivel_Oscuro){
    if(Tono < 0 || Claro == INVALIDO || Oscuro == INVALIDO|| Nivel_Brillo < 0 || Nivel_Oscuro < 0)
        return  ERROR;
    //unidad del 1% del color
    #define Unidad 2.55
    double PropocionTonoClaro = (255.0 - (double)Tono)/Unidad;
    *Claro = (((double)Tono) + ((PropocionTonoClaro * Nivel_Brillo)*Unidad))+.5;

    if(*Claro > 255) *Claro = 255;

    double PropocionTonoOscuro =  (((double)Tono) / Unidad);
    *Oscuro = (((double)Tono) - (PropocionTonoOscuro *Nivel_Oscuro)*Unidad)+.5;

    if(*Oscuro < 0) *Oscuro = 0;
    return OK;}




short Brillo_y_Sombra(long Color, long *Brillo,long *Sombra,double Nivel_Brillo, double Nivel_Oscuro){
    short RGB_Original[3], i,
          RGB_Brillo  [3],
          RGB_Sombra  [3];

    if(Convertir_Entero_A_RGB(&RGB_Original[0],&RGB_Original[1],&RGB_Original[2],Color)==ERROR)
        return ERROR;

    for(i = 0; i < 3; ++i){
        if(dividir_tono(RGB_Original[i],&RGB_Brillo[i],&RGB_Sombra[i],Nivel_Brillo,Nivel_Oscuro) == ERROR)
            return  ERROR;}

    *Brillo = Convertir_RGB_A_Entero(RGB_Brillo[0],RGB_Brillo[1],RGB_Brillo[2]);
    *Sombra = Convertir_RGB_A_Entero(RGB_Sombra[0],RGB_Sombra[1],RGB_Sombra[2]);
    return  OK;}

