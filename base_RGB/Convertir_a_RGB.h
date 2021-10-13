/*                           - ColoRef -
                    Software de la teoría del color

      Este programa es un software libre; puedes redistribuirlo y/o
     modificarlo bajo los términos de la Licencia Pública General GNU
según lo publicado por la Free Software Foundation; versión 3 de la Licencia.

      Este programa se distribuye con la esperanza de que sea útil,
    pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
     COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver la
       Licencia pública general GNU para obtener más detalles.          */

#ifndef CONVERTIR_A_RGB_H
#define CONVERTIR_A_RGB_H

#ifdef __cplusplus
extern "C"
{
#endif

short seccionar_aBytes(long *decimal,short nBytes);

char De_int_a_letra(short valor,unsigned char invertir);
short  De_letra_a_int(char letra);

short Convertir_Entero_A_HexaPuro(long decimal,char *Hexadecimal, short dimencion);
long Convertir_Hexadecimal_A_EnteroPuro(const char *hex);

long Convertir_RGB_A_Entero(long r,int g,short b);
short Convertir_RGB_A_Hexadecimal(short r,short g,short b,char *Hexadecimal, short dimencion);

short Convertir_Entero_A_RGB(short *r,short *g,short *b,long Valor);
short Convertir_Hexadecimal_A_RGB(short *r,short *g,short *b,const char *Hexadecimal);

short Convertir_RGB_A_CSS(short r,short g,short b,char *CSS);
short Convertir_Entero_A_CSS(char *CSS, long Valor);
short Convertir_Hexadecimal_A_CSS(const char *Hexadecimal, char *CSS);

long Convertir_CSS_A_Entero(const char *CSS);
short Convertir_CSS_A_RGB(short *r,short *g,short *b,const char *CSS);
short Convertir_CSS_A_Hexadecimal(const char *CSS,char *Hexadecimal);

#ifdef __cplusplus
}
#endif
#endif // CONVERTIR_A_RGB_H
