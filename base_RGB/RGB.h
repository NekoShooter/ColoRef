/*                           - ColoRef -
                    Software de la teoría del color

      Este programa es un software libre; puedes redistribuirlo y/o
     modificarlo bajo los términos de la Licencia Pública General GNU
según lo publicado por la Free Software Foundation; versión 3 de la Licencia.

      Este programa se distribuye con la esperanza de que sea útil,
    pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
     COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver la
       Licencia pública general GNU para obtener más detalles.          */

#ifndef RGB_H
#define RGB_H
#include <iostream>


class RGB
{
    public:
        RGB();
        RGB(long decimal);
        RGB(const std::string &html);
        RGB(const short &rojo,const short &verde,const short &azul);

        void invertir();
        void operator =(const std::string &html);
        void operator =(long decimal);

        bool operator ==(const RGB &A);
        bool operator !=(const RGB &A);

        std::string informacion(bool completa = false);
        void cambiar(const long &decimal);
        void cambiar(RGB & rgb);
        void cambiar(const std::string &html);
        void cambiar(short rojo,short verde,short azul);

        enum Eleccion{ROJO, VERDE, AZUL, HTML = 5, CSS = 6};

        short obtenerRGB(short elemento = ROJO);
        std::string obtenerHEX(short elemento = HTML);
        inline long obtenerID(){return id_Color;}

        inline bool EstaVacio(){return vacio;}
        void limpiar();

        friend class SuperColor;
        friend std::ostream &operator <<(std::ostream &o,RGB &Color);

    protected:
        char Hexa[8],css[5];
        short r,g,b;

        inline void Desplazar_RGB_Izq(){r = G;  g = B;  b = R;}
        inline void Desplazar_RGB_Der(){r = B;  g = R;  b = G;}
        inline void Girar_RGB()        {r = B;  g = G;  b = R;}
        inline void asignar_a_RGB()    {R = r;  G = g;  B = b;}
        inline void respaldar_RGB()    {r = R;  g = G;  b = B;}

        inline void actualizar_HEX(){cambiar(Hexa);}
        inline void actualizar_RGB(){cambiar(r,g,b);}

    private:
        long id_Color;
        short R,G,B;
        std::string Hexadecimal;
        std::string _CSS;
        bool vacio;
};

std::ostream &operator <<(std::ostream &o,const RGB &Color);

#endif // RGB_H
