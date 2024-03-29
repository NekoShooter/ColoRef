#include <sstream>
#include "RGB.h"
#include "Convertir_a_RGB.h"
#include "Algoritmo_RGB.h"
#include "MACROS.h"

void RGB::limpiar(){
    R = G = B = NEGRO;
    r = g = b = -1;

    id_Color = -1;

    Hexadecimal.clear();
    _CSS.clear();
    vacio = true;      }


RGB::RGB() {
    limpiar();}

RGB::RGB(const std::string &html){
    limpiar();
    cambiar(html);}

RGB::RGB(long decimal){
    limpiar();
    cambiar(decimal);}

RGB::RGB(const short &rojo,const short &verde,
         const short &azul){
    limpiar();
    if((rojo > 255 || verde > 255 || azul > 255)||
       (rojo < 0   || verde < 0   || azul < 0)){
        return;}
    cambiar(rojo,verde,azul);}

void RGB::operator =(const std::string &html){
    cambiar(html);}

void RGB::operator =(long decimal){
    cambiar(decimal);}



void RGB::cambiar(const long &decimal){
    if(Convertir_Entero_A_HexaPuro(decimal,Hexa,8) == ERROR)
        return;

    if(vacio) Hexadecimal = Hexa;
    else {
        limpiar();
        Hexadecimal = Hexa;}
    id_Color = decimal;
    Convertir_Entero_A_RGB(&R,&G,&B,decimal);
    Convertir_RGB_A_CSS(R,G,B,css);
    _CSS = css;
    vacio = false;}



void RGB::cambiar(short rojo,short verde,short azul){
    if(Convertir_RGB_A_Hexadecimal(rojo,verde,azul,Hexa,8)==ERROR)
        return;
    limpiar();
    Hexadecimal = Hexa;
    R = rojo;
    G = verde;
    B = azul;
    Convertir_RGB_A_CSS(R,G,B,css);
    _CSS = css;
    id_Color = Convertir_RGB_A_Entero(R,G,B);
    vacio = false;}



void RGB::cambiar(const std::string &html){
    if(html.empty() || html.size() < 3 || html.size() > 7)
        return;

    long valor;

    if(html.size() <= 4){
        if(html.size() == 4 && html[0] != '#') return;
        valor = Convertir_CSS_A_Entero(html.c_str());
        if(valor == ERROR)
            return;
        cambiar(valor); }

    if(html.size() > 5){
        if(html.size() == 7 && html[0] != '#') return;
        valor = Convertir_Hexadecimal_A_EnteroPuro(html.c_str());
        if(valor == ERROR)
            return;
        cambiar(valor);}}



void RGB::cambiar(RGB & rgb){
    if(rgb.vacio)return;
    R = rgb.R;
    G = rgb.G;
    B = rgb.B;
    id_Color = rgb.id_Color;
    Hexadecimal = rgb.Hexadecimal;
    _CSS = rgb._CSS;}



void RGB::invertir(){
    respaldar_RGB();
    cambiar(r,g,b);}


short RGB::obtenerRGB(short elemento){
    if(vacio) return -1;
    switch(elemento){
        case ROJO:  return R;
        case VERDE: return G;
        case AZUL:  return B;
        default:    return -1;}}



std::string RGB::obtenerHEX(short elemento){
    if(vacio) return "";
    switch (elemento) {
        case HTML: return Hexadecimal;
        case CSS:  return _CSS;
        default: return "";}}



bool RGB::operator !=(const RGB &A){
    if(*this == A)
        return false;
    return true;}



bool RGB::operator ==(const RGB &A){
    if(A.vacio && vacio) return true;
    if(A.vacio != vacio) return false;
    return((A.R == R)&&(A.G == G)&&(A.B == B));}




std::string RGB::informacion(bool completa){
    if(vacio) return "<   RGB inexistente   >";
    std::ostringstream o;
    o<<_CSS<<" "<<Hexadecimal<<"  "<<R;

    if(R >  99)      o<<"  ";
    else if(R >= 10) o<<"   ";
    else             o<<"    ";

    o<<G;

    if(G > 99)       o<<"  ";
    else if(G >= 10) o<<"   ";
    else             o<<"    ";
    o<<B;
    if(!completa){
        o<<std::endl;
        return o.str();}
    if(B > 99)       o<<"  ";
    else if(B >= 10) o<<"   ";
    else             o<<"    ";
    o<<std::endl;
    return o.str();

    }
std::ostream &operator <<(std::ostream &o,RGB &C){
    if(C.vacio)
        return o<<"<   RGB inexistente   >"<<std::endl;
    return o<<C.informacion(true);}
