#include "SuperColor.h"
#include "Algoritmo_RGB.h"
#include "MACROS.h"

void SuperColor::iniciar(){
    estaVacio       = true;
    tiene_alfa      = false; Alfa = -1;

    hay_original    = false; Original  = nullptr;
    hay_opuesto     = false; Opuesto   = nullptr;

    hay_contiguo_A  = false; ContiguoA = nullptr;
    hay_contiguo_B  = false; ContiguoB = nullptr;

    hay_triangulo_A = false; Punta_A   = nullptr;
    hay_triangulo_B = false; Punta_B   = nullptr;

    hay_monocromo   = false; Luz       = nullptr;
                             Sombra    = nullptr;
    hay_gamas       = false;

    Que_color_Es = 0;
    respaldo = nullptr;}


SuperColor::SuperColor(){
    iniciar();}

SuperColor::SuperColor(RGB &Color){
    iniciar();
    Cambiar(Color);}

SuperColor::SuperColor(long decimal){
    iniciar();
    Cambiar(decimal);}

SuperColor::SuperColor(const std::string &html){
    iniciar();
    Cambiar(html);}

SuperColor::SuperColor(const short &rojo,const short &verde,
                       const short &azul,const short alfa){
    iniciar();
    if(alfa < 0 || alfa > 255) return;
    Cambiar(rojo,verde,azul);}

void SuperColor::operator=(const std::string &html){
    Cambiar(html);}

void SuperColor::operator=(RGB &Color){
    Cambiar(Color);}

void SuperColor::operator=(long decimal){
    Cambiar(decimal);}

SuperColor::~SuperColor(){
    limpiar();}

void SuperColor::reiniciar(){
    if(estaVacio) return;

    if(hay_original && Original != nullptr){
        delete Original;
        std::cout<<"Orginal liberado"<<std::endl;
        Original = nullptr;}

    if(hay_opuesto && Opuesto != nullptr){
        delete Opuesto;
        std::cout<<"Opuesto liberado"<<std::endl;
        Opuesto = nullptr;}

    if(hay_contiguo_A && ContiguoA != nullptr){
        std::cout<<"ContiguoA liberado"<<std::endl;
        delete ContiguoA; ContiguoA = nullptr;}

    if(hay_contiguo_B && ContiguoB != nullptr){
        std::cout<<"ContiguoB liberado"<<std::endl;
        delete ContiguoB; ContiguoB = nullptr;}

    if(hay_triangulo_A && Punta_A != nullptr){
        std::cout<<"Punta_A liberado"<<std::endl;
        delete Punta_A; Punta_A = nullptr;}

    if(hay_triangulo_B && Punta_B != nullptr){
        std::cout<<"Punta_B liberado"<<std::endl;
        delete Punta_B; Punta_B = nullptr;}

    if(hay_monocromo && Luz != nullptr){
        delete Luz;
        std::cout<<"Luz liberado"<<std::endl;
        Luz = nullptr;}

    if(hay_monocromo && Sombra != nullptr){
        delete Sombra;
        std::cout<<"Sombra liberado"<<std::endl;
        Sombra = nullptr;}}



void SuperColor::Cambiar(RGB &Color){
    if(Color.EstaVacio()) return;
    reiniciar();
    Original = new RGB(Color);
    hay_original = true;
    estaVacio = false;
    ConstruirColores();}

void SuperColor::Cambiar(const std::string &html){
    respaldo = new RGB(html);

    if(respaldo->EstaVacio()){
        delete respaldo;
        return;    }
    else{
        reiniciar();
        Original = respaldo;
        hay_original = true;
        estaVacio = false;
        ConstruirColores();}}

void SuperColor::Cambiar(const short &rojo,const short &verde,
                         const short &azul,const short alfa){
    respaldo = new RGB(rojo,verde,azul);
    if(respaldo->EstaVacio()){
        delete respaldo;
        return;}
    else{
        reiniciar();
        Original = respaldo;
        hay_original = true;
        estaVacio = false;
        ConstruirColores();
        Alfa = alfa;
        if(alfa != 255)
            tiene_alfa = true;}}

void SuperColor::Cambiar(long decimal){
    respaldo = new RGB(decimal);
    if(respaldo->EstaVacio()){
        delete respaldo;
        return;}
    reiniciar();
    Original = respaldo;
    Alfa = 255;
    hay_original = true;
    estaVacio = false;
    ConstruirColores();}

void SuperColor::ConstruirColores(){
    if(estaVacio)return;

    if(hay_opuesto && Opuesto == nullptr){
        Opuesto = new RGB;
        *Opuesto = BLANCO - Original->id_Color;}

    if (hay_triangulo_A && Punta_A == nullptr){
        Punta_A = new RGB;
        *Punta_A = *Original;
        Punta_A->Desplazar_RGB_Izq();
        Punta_A->actualizar_RGB();}

    if (hay_triangulo_B && Punta_B == nullptr){
        Punta_B = new RGB;
        *Punta_B = *Original;
        Punta_B->Desplazar_RGB_Der();
        Punta_B->actualizar_RGB();}

    if(hay_contiguo_A && ContiguoA == nullptr){
        ContiguoA = new RGB;
        *ContiguoA = BLANCO - Punta_B->id_Color;}

    if(hay_contiguo_B && ContiguoB == nullptr){
        ContiguoB = new RGB;
        *ContiguoB = BLANCO - Punta_A->id_Color;}

    if(hay_monocromo){
        long brillo, oscuro;
        respaldo =Color_selecionado(Que_color_Es);
        if(!respaldo || Brillo_y_Sombra(respaldo->id_Color,&brillo,&oscuro,.50,.25) == ERROR)
            return;
        if(Luz == nullptr)
            Luz = new RGB;
        if(Sombra == nullptr)
            Sombra = new RGB;
        *Luz = brillo;
        *Sombra = oscuro;}}

RGB *SuperColor::Color_selecionado(short color){
    if(estaVacio) return nullptr;

    switch(color){
        case ORIGINAL:
            return Original;

        case COMPLEMENTO:
            return Opuesto;

        case ANALOGO_A:
            return ContiguoA;

        case ANALOGO_B:
            return ContiguoB;

        case TRIANGULO_A:
            return Punta_A;

        case TRIANGULO_B:
            return Punta_B;

        default: return nullptr;}}


void SuperColor::limpiar(){
    reiniciar();
    iniciar();}

std::string SuperColor::Obterner(const short &Tono, const short &Modo){
    if(estaVacio) return "";
    respaldo = Color_selecionado(Tono);
    if(respaldo)
        return respaldo->obtenerHEX(Modo);
    return "";}


void SuperColor::CreaColores(short eleccion,short extra){
    if(estaVacio|| eleccion < 0 || eleccion > 31 ) return;

    Que_color_Es = eleccion;

    if(eleccion & COMPLEMENTO)
        hay_opuesto   = true;

    if(eleccion & ANALOGO_A){
        hay_contiguo_A = true;
        hay_triangulo_B = true;}

    if(eleccion & ANALOGO_B){
        hay_contiguo_B = true;
        hay_triangulo_A = true;}

    if(eleccion & TRIANGULO_A)
        hay_triangulo_A = true;

    if(eleccion & TRIANGULO_B)
        hay_triangulo_B = true;

    if(extra == MONOCROMO)
        hay_monocromo = true;
    ConstruirColores();}

std::ostream &operator<<(std::ostream &o, SuperColor &c){
    if(c.estaVacio) return o<<"Color inexistente"<<std::endl;
    o<<"___color_____css___html____R____G____B___"<<std::endl;
    o<<"  Original  "<<*c.Original;

    if(c.hay_monocromo && c.Luz)
        o<<"   Brillo   "<<*c.Luz;

    if(c.hay_monocromo && c.Sombra)
        o<<"   Sombra   "<<*c.Sombra;

    if((c.Que_color_Es & c.COMPLEMENTO) && c.hay_opuesto)
        o<<"Complemento "<<*c.Opuesto;

    if((c.Que_color_Es & c.ANALOGO_A) && c.hay_contiguo_A)
        o<<"Adyasente A "<<*c.ContiguoA;

    if((c.Que_color_Es & c.ANALOGO_B) && c.hay_contiguo_B)
        o<<"Adyasente B "<<*c.ContiguoB;

    if((c.Que_color_Es & c.TRIANGULO_A) && c.hay_triangulo_A)
        o<<"  Triada  A "<<*c.Punta_A;

    if((c.Que_color_Es & c.TRIANGULO_B) && c.hay_triangulo_B)
        o<<"  Triada  B "<<*c.Punta_B;

    return o;}
