#include "RGB.h"
#include "Convertir_a_RGB.h"
#include "Algoritmo_RGB.h"
#include "MACROS.h"

void RGB::limpiar(){
    R = G = B = 0;   familia = -1;
    r = g = b = -1;  composicion = -1;

    id_Color = 0;

    Color_valido = false;
    Hexadecimal.clear();
    CSS.clear();
    vacio = true;      }



RGB::RGB() {
    vacio = true;
    limpiar();}

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
    CSS = css;
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
    CSS = css;
    id_Color = Convertir_RGB_A_Entero(R,G,B);}


void RGB::cambiar(const std::string &html, bool invertir){
    if(html.size() == 3 || html.size() == 4){
        Hexa = Hex_a_CSS(html);
        if(Hexa.empty()){
            Color_valido = false;
            return;}
        Color_valido = true;}
    else if(html.size() == 7 && html[0] != '#'){
        Color_valido = false;
        return;}
    else if(html.size() != 6 && html.size() != 7){
        Color_valido = false;
        return;}

    if(html[0] != '#'&& !Color_valido)
        Hexa = '#' + html;
    else if(!Color_valido) Hexa = html;
    crear_RBG();



void RGB::cambiar(RGB & rgb){
    if(rgb.vacio)return;
    R = rgb.R;
    G = rgb.G;
    B = rgb.B;
    cambiar(R,G,B);}

RGB::RGB(const std::string &html){
    limpiar();
    cambiar(html,invertir);
    /*if(!Color_valido)
        limpiar();*/}
RGB::RGB(long decimal){
    limpiar();
    cambiar(decimal);}

RGB::RGB(const short &rojo,const short &verde,
         const short &azul, bool invertir){
    limpiar();
    if((rojo > 255 || verde > 255 || azul > 255)||
       (rojo < 0   || verde < 0   || azul < 0)){
        return;}
    cambiar(rojo,verde,azul,invertir);}

const short RGB::obtenerRGB(short elemento){
    if(vacio) return -1;
    switch(elemento){
        case ROJO:  return R;
        case VERDE: return G;
        case AZUL:  return B;
        default:    return -1;}}

std::string RGB::obtenerHEX(short elemento){
    if(vacio) return "";
    if(elemento == HTML)
        return Notacion_html;
    if(elemento == CSS)
        return Css;
    else return "";}




    if(Color_valido&&!invertir){
        asignar_a_RGB();//actualizarRGB
        Css = ConvertirA_CSSPuro(r,g,b);
        Notacion_html = Hexa;//crear_HEX(invertir);
        vacio = false;
        Identificar_tipo();}

    if(Color_valido && invertir){
        crear_HEX(invertir);
        crear_RBG();
        vacio = false;
        //Hexa = Notacion_html;
        //crear_RBG();
        asignar_a_RGB();//actualizarRGB
        Identificar_tipo();}}

void RGB::crear_RBG(){
    short valor_1 = 0, valor_2 = 0, i = 0;
    if(Hexa[0] == '#') ++i;
    short j = i;
          i = 0;
    while(Hexa[j] && Hexa[j+1]){
        valor_1 = Hex_a_int(Hexa[j],Color_valido);
            if(!Color_valido) break;
        valor_2 = Hex_a_int(Hexa[j+1],Color_valido);
            if(!Color_valido) break;
        j += 2;
        if(i == 0)
            r = valor_2|(valor_1 << 4);
        else if(i == 1)
            g = valor_2|(valor_1 << 4);
        else if(i == 2)
            b = valor_2|(valor_1 << 4);
        ++i;}
    if(i != 3)Color_valido = false;}

void RGB::crear_HEX(bool invertir){
    std::string html = "#";
    html += int_a_Hex(r,invertir);
    html += int_a_Hex(g,invertir);
    html += int_a_Hex(b,invertir);
    if(html.size() == 7){
        Css = ConvertirA_CSSPuro(r,g,b);
        Notacion_html = html;}}

void RGB::invertir(){
    respaldar_RGB();
    cambiar(r,g,b,true);}

RGB RGB::operator +(RGB &A){
    return SumaDeRGB(*this,A);}

RGB RGB::operator -(RGB &A){
    return RestaDeRGB(*this,A);}

bool RGB::operator !=(const RGB &A){
    if(*this == A)
        return false;
    return true;}

bool RGB::operator ==(const RGB &A){
    if(A.vacio && vacio) return true;
    if(A.vacio != vacio) return false;
    return((A.R == R)&&(A.G == G)&&(A.B == B));}

void RGB::Identificar_tipo(){
    familia = ConfirmarColor(*this);
    if(composicion == PRIMIGENIOS){
        switch(familia){
        case IIO: composicion = PRIMARIO;
                break;
        case OII: composicion = SECUNDARIO;
                break;
        case IOO: composicion = PRIMARIO;
                break;
        case OOI: composicion = PRIMARIO;
                break;
        case OIO: composicion = SECUNDARIO;
                break;
        case IOI: composicion = SECUNDARIO; }}}

std::string RGB::Familia(){
    switch(familia){
        case XXX: return "Monocromos[XXX] ";
        case OOO: return "Neutrales [OOO] ";
        case IIO: return "Amarillos [IIO] ";
        case OII: return "Violetas  [OII] ";
        case IOO: return "Rojos     [IOO] ";
        case OOI: return "Azules    [OOI] ";
        case OIO: return "Verdes    [OIO] ";
        case IOI: return "Magentas  [IOI] ";
        default:return " <Sin familia> ";}}
std::string RGB::Composicion(){
    switch(composicion){
        case NEGRO:      return "NEGRO     ";
        case BLANCO:     return "BLANCO    ";
        case PRIMARIO:   return "PRIMARIO  ";
        case SECUNDARIO: return "SECUNDARIO";
        case COMPUESTO:  return "COMPUESTOS";
        case COMBINADO:  return "COMBINADO ";
        case DERIVADOS:  return "DERIVADO  ";
        case INPURO:     return "INPURO    ";
        case EXTRAIDO:   return "EXTRAIDO  ";
        case DILUIDO:    return "DILUIDO   ";
        case CASI_PURO:  return "CASI_PURO ";
        default:return "< Sin composicion >";}}
std::string RGB::informacion(bool completa){
    if(vacio) return "<   RGB inexistente   >";
    std::ostringstream o;
    o<<Css<<" "<<Notacion_html<<"  "<<R;

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
    o<<Familia();
    o<<Composicion()<<std::endl;
    return o.str();

    }
std::ostream &operator <<(std::ostream &o,RGB &C){
    if(C.vacio)
        return o<<"<   RGB inexistente   >"<<std::endl;
    return o<<C.informacion(true);}
