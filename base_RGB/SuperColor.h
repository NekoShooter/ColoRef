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

        void CreaColores(short eleccion = TODO);
        void limpiar();
        enum Seleccion{ORIGINAL    = 0, TRIADA  = 4,
                       COMPLEMENTO = 1, ANALOGO = 2,
                                        GAMAS   = 8,
                                        TODO    = 15,

                       ANALOGO_A,       HTML, CSS,
                       ANALOGO_B,

                       TRIANGULO_A,     SOMBRA,
                       TRIANGULO_B,     BRILLO,};

        bool EstaVacio(){return estaVacio;}
        friend std::ostream &operator<<(std::ostream &o, SuperColor &c);

    private:
        void ConstruirColores();
        void iniciar();
        void reiniciar();
        RGB *Original,  *Opuesto,
            *ContiguoA, *ContiguoB,
            *Punta_A,   *Punta_B,
            *Luz,       *Sombra,
            *respaldo;

        short Alfa,ColoreSelecionados;

        bool estaVacio,  hay_original,
             tiene_alfa, hay_opuesto,
                         hay_contiguos,
                         hay_gamas,
                         hay_triangulo;
};

#endif // SUPERCOLOR_H
