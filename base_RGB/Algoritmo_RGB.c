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
    if(Color < NEGRO) return ERROR;

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



long Suma_deColor(long ColorA, long ColorB,short desplazamiento){
    if(ColorA < NEGRO || ColorB < NEGRO || desplazamiento < 0) return ERROR;
    short rgb_A[3], ra,ga,ba,
          rgb_B[3], rb,gb,bb,
          rgb_C[3];
    switch (desplazamiento) {
        case DERECHA:   ra = 2; ga = 0; ba = 1;
                        rb = 1; gb = 2; bb = 0; break;

        case IZQUIERDA: ra = 1; ga = 2; ba = 0;
                        rb = 2; gb = 0; bb = 1; break;

        case CENTRO:    return (ColorA + ColorB)/CONST_ARTE;
        default:        return  ERROR;}

    if(Convertir_Entero_A_RGB(&rgb_A[0],&rgb_A[1],&rgb_A[2],ColorA) == ERROR)
        return  ERROR;
    if(Convertir_Entero_A_RGB(&rgb_B[0],&rgb_B[1],&rgb_B[2],ColorB) == ERROR)
        return  ERROR;

    rgb_C[0] = (rgb_A[ra] + rgb_B[rb])/ CONST_ARTE;
    rgb_C[1] = (rgb_A[ga] + rgb_B[gb])/ CONST_ARTE;
    rgb_C[2] = (rgb_A[ba] + rgb_B[bb])/ CONST_ARTE;
    return (BLANCO - Convertir_RGB_A_Entero(rgb_C[0],rgb_C[1],rgb_C[2]));}



long Nivel_de_Luminicencia(long Color,short intencidad){
    if(Color < NEGRO) return ERROR;
    short r,g,b;
    if(Convertir_Entero_A_RGB(&r,&g,&b,Color)== ERROR)
        return ERROR;
    b += intencidad;
    g += intencidad;
    r += intencidad;

    if(r < 0) r = 0;
    if(g < 0) g = 0;
    if(b < 0) b = 0;

    if(r > 255) r = 255;
    if(g > 255) g = 255;
    if(b > 255) b = 255;
    return Convertir_RGB_A_Entero(r,g,b);}
