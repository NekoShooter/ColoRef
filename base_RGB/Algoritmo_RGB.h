#ifndef ALGORITMO_RGB_H
#define ALGORITMO_RGB_H

#ifdef __cplusplus
extern "C"
{
#endif

short dividir_tono (short Tono, short *Claro, short *Oscuro, double Nivel_Brillo, double Nivel_Oscuro);
short Brillo_y_Sombra(long Color,long *Brillo, long *Sombra, double Nivel_Brillo, double Nivel_Oscuro);

#ifdef __cplusplus
}
#endif
#endif // ALGORITMO_RGB_H
