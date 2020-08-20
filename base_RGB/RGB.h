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
        RGB operator +(RGB &A);
        RGB operator -(RGB &A);
        void cambiar(const long &decimal);
        void cambiar(RGB & rgb);
        void cambiar(const std::string &html);
        void cambiar(short rojo,short verde,short azul);

        enum Eleccion{ROJO, VERDE, AZUL, HTML, _CSS};

        const short obtenerRGB(short elemento = ROJO);
        std::string obtenerHEX(short elemento = HTML);

        inline const bool EstaVacio(){return vacio;}
        void limpiar();
        std::string informacion();



        friend class SuperColor;
        friend RGB SumaDeRGB(RGB &A,RGB &B);
        friend RGB sumaBasica(RGB &A,RGB &B);
        friend RGB sumaCruzada(RGB &A,RGB &B);
        friend RGB sumaCompuesta(RGB &A,RGB &B,const char *r_R,const char *r_G,const char*r_B);
        friend RGB RestaDeRGB(RGB &A,RGB &B);
        friend short ConfirmarColor(RGB &C);
        friend std::ostream &operator <<(std::ostream &o,RGB &Color);

    protected:
        char Hexa[8],css[5];
        short r,g,b;

        inline void Desplazar_RGB_Izq(){r = G;  g = B;  b = R;}
        inline void Desplazar_RGB_Der(){r = B;  g = R;  b = G;}
        inline void Girar_RGB(){r = B;  g = G;  b = R;}
        inline void actualizar_HEX(){cambiar(Hexa);}
        inline void asignar_a_RGB(){R = r; G = g; B = b;}
        inline void actualizar_RGB(){cambiar(r,g,b);}
        inline void respaldar_RGB(){r = R;  g = G;  b = B;}

    private:

        void crear_RBG();
        void crear_HEX(bool invertir = false);
        void Identificar_tipo();
        short familia;
        short composicion;
        long id_Color;
        short R,G,B;
        std::string Hexadecimal;
        std::string CSS;
        std::string Notacion_html;
        bool vacio,Color_valido;
};

std::ostream &operator <<(std::ostream &o,const RGB &Color);

#endif // RGB_H
