#include "SuperColor.h"
#include "Algoritmo_RGB.h"
#include "MACROS.h"

void SuperColor::iniciar(){
    estaVacio     = true;
    tiene_alfa    = false; Alfa = -1;

    hay_original  = false; Original  = nullptr;
    hay_opuesto   = false; Opuesto   = nullptr;
    hay_contiguos = false; ContiguoA = nullptr;
                           ContiguoB = nullptr;
    hay_triangulo = false; Punta_A   = nullptr;
                           Punta_B   = nullptr;

    hay_gamas     = false; Luz       = nullptr;
                           Sombra    = nullptr;

    ColoreSelecionados = 0;
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

    if(hay_contiguos){
        if(ContiguoA != nullptr){
            std::cout<<"ContiguoA liberado"<<std::endl;
            delete ContiguoA; ContiguoA = nullptr;}

        if(ContiguoB != nullptr){
            std::cout<<"ContiguoB liberado"<<std::endl;
            delete ContiguoB; ContiguoB = nullptr;}}

    if(hay_triangulo){
        if(Punta_A != nullptr){
            std::cout<<"Punta_A liberado"<<std::endl;
            delete Punta_A; Punta_A = nullptr;}

        if(Punta_B != nullptr){
            std::cout<<"Punta_B liberado"<<std::endl;
            delete Punta_B; Punta_B = nullptr;}}

    if(hay_gamas && Luz != nullptr){
        delete Luz;
        std::cout<<"Luz liberado"<<std::endl;
        Luz = nullptr;}

    if(hay_gamas && Sombra != nullptr){
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

    if(hay_triangulo){
        if (Punta_A == nullptr){
            Punta_A = new RGB;
            *Punta_A = *Original;
            Punta_A->Desplazar_RGB_Izq();
            Punta_A->actualizar_RGB();}
        if(Punta_B == nullptr){
            Punta_B = new RGB;
            *Punta_B = *Original;
            Punta_B->Desplazar_RGB_Der();
            Punta_B->actualizar_RGB();}}

    if(hay_contiguos){
        if(ContiguoA == nullptr){
            ContiguoA = new RGB;
            *ContiguoA = BLANCO - Punta_B->id_Color;}
        if(ContiguoB == nullptr){
            ContiguoB = new RGB;
            *ContiguoB = BLANCO - Punta_A->id_Color;}}

    if(hay_gamas){
        if(Luz == nullptr)
            Luz = new RGB;
        if(Sombra == nullptr)
            Sombra = new RGB;
        long brillo, oscuro;
        Brillo_y_Sombra(Original->id_Color,&brillo,&oscuro,.50,.25);
        *Luz = brillo;
        *Sombra = oscuro;}}


void SuperColor::limpiar(){
    reiniciar();
    iniciar();}

std::string SuperColor::Obterner(const short &Tono, const short &Modo){
    if(estaVacio) return "";
    switch(Tono){
        case ORIGINAL:
            return Original->obtenerHEX(Modo);

        case COMPLEMENTO:
            hay_opuesto = true;
            ConstruirColores();
            return Opuesto->obtenerHEX(Modo);

        case ANALOGO_A:
            hay_triangulo = true;
            hay_contiguos = true;
            ConstruirColores();
            return ContiguoA->obtenerHEX(Modo);
        case ANALOGO_B:
            hay_triangulo = true;
            hay_contiguos = true;
            ConstruirColores();
            return ContiguoB->obtenerHEX(Modo);

        case TRIANGULO_A:
            hay_triangulo = true;
            ConstruirColores();
            return Punta_A->obtenerHEX(Modo);

        case TRIANGULO_B:
            hay_triangulo = true;
            ConstruirColores();
            return Punta_B->obtenerHEX(Modo);

        case BRILLO:
            hay_gamas = true;
            ConstruirColores();
            return Luz->obtenerHEX(Modo);
        case SOMBRA:
            hay_gamas = true;
            ConstruirColores();
            return Sombra->obtenerHEX(Modo);

        default:
            return "";}}


void SuperColor::CreaColores(short eleccion){
    if(estaVacio|| eleccion < 1 || eleccion > 15) return;
    ColoreSelecionados = eleccion;

    if(eleccion & COMPLEMENTO)
        hay_opuesto   = true;

    if(eleccion & ANALOGO){
        hay_contiguos = true;
        hay_triangulo = true;}

    if(eleccion & TRIADA)
        hay_triangulo = true;

    if(eleccion & GAMAS)
        hay_gamas= true;

    ConstruirColores();}

std::ostream &operator<<(std::ostream &o, SuperColor &c){
    if(c.estaVacio) return o<<"Color inexistente";
    o<<"___color_____css___html____R____G____B___"<<std::endl;
    o<<"  Original  "<<*c.Original;

    if((c.ColoreSelecionados & c.GAMAS) && c.hay_gamas){
        o<<"   Brillo   "<<*c.Luz;
        o<<"   Sombra   "<<*c.Sombra;}

    if((c.ColoreSelecionados & c.COMPLEMENTO) && c.hay_opuesto)
        o<<"Complemento "<<*c.Opuesto;

    if((c.ColoreSelecionados & c.ANALOGO) && c.hay_contiguos){
        o<<"Adyasente A "<<*c.ContiguoA;
        o<<"  - - -   B "<<*c.ContiguoB;}

    if((c.ColoreSelecionados & c.TRIADA) && c.hay_triangulo){
        o<<"  Triada  A "<<*c.Punta_A;
        o<<"  - - -   B "<<*c.Punta_B;}

    return o;}
