#include "Convertir_a_RGB.h"

#define true 1
#define false 0
#define INVALIDO 0
#define OK 1
#define ERROR -1


short seccionar_aBytes(long *decimal,short nBytes){
    long saliente = (*decimal >> nBytes)<<nBytes;
    short numero = *decimal ^ saliente;
    *decimal = saliente >> nBytes;
    return numero;}



char De_int_a_letra (short valor,unsigned char invertir){
    if(15 < valor || 0 > valor) return INVALIDO;
    if (!invertir){
        const char * Binario = "0123456789abcdef";
        return Binario[valor];}
    else{
        const char * Binario = "fedcba9876543210";
        return Binario[valor];}}



short De_letra_a_int(char letra){
    if(letra >= '0' && letra <= '9')
        return(short)letra - 48;
    else if(letra >= 'A' && letra <= 'F')
        return(short)letra - 55;
    else if(letra >= 'a' && letra <= 'f')
        return(short)letra - 87;
    else
         return ERROR;}



short Convertir_Entero_A_HexaPuro(long decimal,char *Hexadecimal,short dimencion){
    if(Hexadecimal == INVALIDO || decimal < 0) return INVALIDO;

    short valor;
    short i = dimencion - 2;
    Hexadecimal[0] = '#';
    Hexadecimal[dimencion - 1] = 0;

    while(i > 0){
        valor = seccionar_aBytes(&decimal,4);
        Hexadecimal[i]= De_int_a_letra(valor,false);
        if(Hexadecimal[i]== INVALIDO)
            return  ERROR;
        --i;}

    if(decimal) return ERROR;
    else        return OK;}



long Convertir_Hexadecimal_A_EnteroPuro(const char *Hexadecimal){
        if(Hexadecimal == INVALIDO) return ERROR;

        short dimencion,i = 0,
                        j = 0;

        long intPuro = 0,
             resultado;

        for(dimencion = 1; Hexadecimal[dimencion];++dimencion);
        for(i = dimencion - 1; i > -1; --i){

            if(Hexadecimal[i] == '#'&& i != 0) return ERROR;
            else if(Hexadecimal[i] == '#')break;

            resultado = De_letra_a_int(Hexadecimal[i]);
            if(resultado != ERROR){
                intPuro +=(resultado << j);
                j += 4;}
            else
                return ERROR;}
        return intPuro;}



long Convertir_RGB_A_Entero(long r,int g,short b){
    return b + (g << 8)+(r << 16);}



short Convertir_RGB_A_Hexadecimal(short r,short g,short b,char *Hexadecimal, short dimencion){
    return Convertir_Entero_A_HexaPuro(Convertir_RGB_A_Entero(r,g,b),Hexadecimal,dimencion);}

short Convertir_Entero_A_RGB(short *r,short *g,short *b,long Valor){
    if(Valor < 0) return ERROR;
    *b = seccionar_aBytes(&Valor,8);
    *g = seccionar_aBytes(&Valor,8);
    *r = seccionar_aBytes(&Valor,8);
    return  OK;}

short Convertir_Hexadecimal_A_RGB(short *r,short *g,short *b,char *Hexadecimal){
    long Valor = Convertir_Hexadecimal_A_EnteroPuro(Hexadecimal);
    if(Valor == ERROR) return ERROR;
    return Convertir_Entero_A_RGB(r,g,b,Valor);}


#define RGBaCSS(rgb) rgb * 15/255
short Convertir_RGB_A_CSS(short r,short g,short b,char *CSS){
    if(CSS == INVALIDO) return ERROR;
    short rgb[3];
    rgb[0] = RGBaCSS(r)+.5;
    rgb[1] = RGBaCSS(g)+.5;
    rgb[2] = RGBaCSS(b)+.5;
    CSS[0] = '#';
    for(short i = 0; i < 3; ++i){
        CSS[i + 1] = De_int_a_letra(rgb[i],false);
        if(CSS[i + 1] == INVALIDO)
            return ERROR;}
    CSS[4] = '\0';
    return OK;}


short Convertir_CSS_A_Hexadecimal(const char *CSS,char *Hexadecimal){
    if(CSS==INVALIDO||(Hexadecimal==INVALIDO))return ERROR;
    unsigned short j = 0,
                   i = 1;

    if(CSS[0]== '#')j = 1;
    Hexadecimal[0] = '#';
    Hexadecimal[7] = '\0';

    while(i < 7){
        if(De_letra_a_int(CSS[j]) == ERROR)
            return ERROR;
        Hexadecimal[i] = CSS[j];
        Hexadecimal[i + 1]  = CSS[j];

        i += 2;   ++j;}

    return  OK;}
