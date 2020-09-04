/*ColoRef - Color Theory Software

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; version 3 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*/
#ifndef SUPERCOLOR_H
#define SUPERCOLOR_H
#include "RGB.h"


namespace SuperColorStd {
enum Seleccion{ORIGINAL    = 0,     TRIADA  = 24, GAMA = 32,
               COMPLEMENTO = 1,     ANALOGO = 6,  NINGUNO = 0,

               ANALOGO_A   = 2,     TODO = 63,    BRILLO = 64,
               ANALOGO_B   = 4,     HTML, CSS,    SOMBRA = 81,

               TRIANGULO_A = 8,     MONOCROMO = 64,
               TRIANGULO_B = 16,    ILUMINAR  = 98,
                                    INTRAQUEABLE};}


class SuperColor
{
    public:
        SuperColor();
        SuperColor(RGB &Color);
        SuperColor(long decimal);
        SuperColor(const std::string &html);
        SuperColor(const short &rojo,const short &verde,
                   const short &azul,const short alfa = 255);
        virtual ~SuperColor();

        void operator=(const std::string &html);
        void operator=(RGB &Color);
        void operator=(long decimal);
        bool operator==(SuperColor C);
        bool operator!=(SuperColor C);
        std::string Q_style(const short &Tono = SuperColorStd::ORIGINAL,
                            const short &Modo = SuperColorStd::HTML, const short &indice = 6);
        std::string Obterner(const short &Tono = SuperColorStd::ORIGINAL,
                             const short &Modo = SuperColorStd::HTML, const short &indice = 6);
        long id(short eleccion = SuperColorStd::ORIGINAL);

        void Cambiar(RGB &Color);
        void Cambiar(const std::string &html);
        void Cambiar(const short &rojo,const short &verde,
                     const short &azul,const short alfa = 255);
        void Cambiar(long decimal);
        void Restableser();

        void Re_Asignar(short eleccion);
        bool Luminicencia(short seleccion = SuperColorStd::ORIGINAL,short nivel = 3,bool aplicar = false);

        void CreaColores(short eleccion = SuperColorStd::TODO,short extra = SuperColorStd::NINGUNO);
        void limpiar();
        void AplicarCambios();

        bool EstaVacio(){return estaVacio;}
        friend std::ostream &operator<<(std::ostream &o, SuperColor &c);

    private:
        RGB * Color_selecionado(short color);
        void ConstruirColores();
        bool Eleccion(short eleccion);
        void ConstruirGamas();
        void iniciar();
        void reiniciar();

        RGB *Original,  *Opuesto,
            *ContiguoA, *ContiguoB,
            *Punta_A,   *Punta_B,
            *Luz,       *Sombra,
            *respaldo,  **Gamas;

        short Alfa,   Que_color_Es,  ColorMonocromo;

        bool estaVacio,       hay_original,
             tiene_alfa,      hay_opuesto,

             hay_contiguo_A,  hay_triangulo_A,
             hay_contiguo_B,  hay_triangulo_B,

             hay_gamas,       hay_monocromo,
             es_todo;
};

#endif // SUPERCOLOR_H
