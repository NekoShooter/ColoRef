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
#ifndef ALGORITMO_RGB_H
#define ALGORITMO_RGB_H

#ifdef __cplusplus
extern "C"
{
#endif

short dividir_tono (short Tono, short *Claro, short *Oscuro, double Nivel_Brillo, double Nivel_Oscuro);
short Brillo_y_Sombra(long Color,long *Brillo, long *Sombra, double Nivel_Brillo, double Nivel_Oscuro);

long Suma_deColor(long ColorA, long ColorB,short desplazamiento);
long Nivel_de_Luminicencia(long Color,short intencidad);
long Nivelacion_Complementaria(long ColorOriginal);
long Nivelacion_Luminica(long ColorA,long ColorB);

#ifdef __cplusplus
}
#endif
#endif // ALGORITMO_RGB_H
