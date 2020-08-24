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
#ifndef SUPERCOLOR_H
#define SUPERCOLOR_H
#include "RGB.h"

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

        std::string Obterner(const short &Tono = ORIGINAL,
                             const short &Modo = HTML);

        void Cambiar(RGB &Color);
        void Cambiar(const std::string &html);
        void Cambiar(const short &rojo,const short &verde,
                     const short &azul,const short alfa = 255);
        void Cambiar(long decimal);

        void CreaColores(short eleccion = TODO,short extra = 0);
        void limpiar();
        enum Seleccion{ORIGINAL    = 0,     TRIADA  = 24,
                       COMPLEMENTO = 1,     ANALOGO = 6,

                       ANALOGO_A = 2,       TODO = 31,
                       ANALOGO_B = 4,       HTML, CSS,

                       TRIANGULO_A = 8,     SOMBRA,
                       TRIANGULO_B = 16,    BRILLO};

        enum Opciones{ NONE,MONOCROMO,GAMA
           };

        bool EstaVacio(){return estaVacio;}
        friend std::ostream &operator<<(std::ostream &o, SuperColor &c);

    private:
        RGB * Color_selecionado(short color);
        void ConstruirColores();
        void iniciar();
        void reiniciar();
        RGB *Original,  *Opuesto,
            *ContiguoA, *ContiguoB,
            *Punta_A,   *Punta_B,
            *Luz,       *Sombra,
            *respaldo;

        short Alfa,Que_color_Es;

        bool estaVacio,  hay_original,
             tiene_alfa, hay_opuesto,

        hay_contiguo_A,  hay_triangulo_A,
        hay_contiguo_B,  hay_triangulo_B,

                         hay_gamas,
                         hay_monocromo;
};

#endif // SUPERCOLOR_H
