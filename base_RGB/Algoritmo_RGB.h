/*                           - ColoRef -
                    Software de la teoría del color

      Este programa es un software libre; puedes redistribuirlo y/o
     modificarlo bajo los términos de la Licencia Pública General GNU
según lo publicado por la Free Software Foundation; versión 3 de la Licencia.

      Este programa se distribuye con la esperanza de que sea útil,
    pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
     COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver la
       Licencia pública general GNU para obtener más detalles.          */


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
