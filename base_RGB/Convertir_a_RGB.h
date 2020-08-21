/*
ColoRef - Color Theory Software

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
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
