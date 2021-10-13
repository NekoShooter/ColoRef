#include "SuperColor.h"
#include "Algoritmo_RGB.h"
#include "MACROS.h"
//#include <iostream>
using namespace SuperColorStd;

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
    hay_gamas       = false; Gamas     = nullptr;
    es_todo         = false;

    Que_color_Es   = NINGUNO;
    ColorMonocromo = NINGUNO;
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


void SuperColor::operator=(RGB &Color){
    Cambiar(Color);}


void SuperColor::operator=(long decimal){
    Cambiar(decimal);}


void SuperColor::operator=(const std::string &html){
    Cambiar(html);}


SuperColor::~SuperColor(){
    limpiar();}


void SuperColor::Cambiar(RGB &Color){
    if(Color.EstaVacio()) return;
    reiniciar();
    Original = new RGB(Color);
    hay_original = true;
    estaVacio = false;
    ConstruirColores();}



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



void SuperColor::reiniciar(){
    if(estaVacio) return;

    if(hay_original && Original != nullptr){
        delete Original;
        //std::cout<<"Orginal liberado"<<std::endl;
        Original = nullptr;}

    if(hay_opuesto && Opuesto != nullptr){
        delete Opuesto;
        //std::cout<<"Opuesto liberado"<<std::endl;
        Opuesto = nullptr;}

    if(hay_contiguo_A && ContiguoA != nullptr){
        //std::cout<<"ContiguoA liberado"<<std::endl;
        delete ContiguoA; ContiguoA = nullptr;}

    if(hay_contiguo_B && ContiguoB != nullptr){
        //std::cout<<"ContiguoB liberado"<<std::endl;
        delete ContiguoB; ContiguoB = nullptr;}

    if(hay_triangulo_A && Punta_A != nullptr){
        //std::cout<<"Punta_A liberado"<<std::endl;
        delete Punta_A; Punta_A = nullptr;}

    if(hay_triangulo_B && Punta_B != nullptr){
        //std::cout<<"Punta_B liberado"<<std::endl;
        delete Punta_B; Punta_B = nullptr;}

    if(hay_monocromo && Luz != nullptr){
        delete Luz;
        //std::cout<<"Luz liberado"<<std::endl;
        Luz = nullptr;}

    if(hay_monocromo && Sombra != nullptr){
        delete Sombra;
        //std::cout<<"Sombra liberado"<<std::endl;
        Sombra = nullptr;}

    if(hay_gamas && Gamas != nullptr){
        for(short i = 1; i < 13; i += 2)
            delete Gamas[i];
            //std::cout<<"Gamas["<<i<<"]"<<std::endl;
        delete [] Gamas;
        //std::cout<<"Gamas liberadas"<<std::endl;
        Gamas = nullptr;}}


void SuperColor::CreaColores(short eleccion,short extra){
    if(estaVacio|| eleccion < 0 || eleccion > TODO ) return;

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

    if(eleccion & GAMA)
        hay_gamas = true;

    if(extra == MONOCROMO){
        ColorMonocromo = eleccion;
        hay_monocromo = true;}

    if(extra != INTRAQUEABLE){
        Que_color_Es = eleccion;
        ConstruirColores();}}


void SuperColor::ConstruirColores(){
    if(estaVacio)return;

    if(hay_opuesto && Opuesto == nullptr){
        Opuesto = new RGB;
        *Opuesto = Nivelacion_Complementaria(Original->id_Color);}

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
        *ContiguoA =Nivelacion_Complementaria(Punta_B->id_Color);}

    if(hay_contiguo_B && ContiguoB == nullptr){
        ContiguoB = new RGB;
        *ContiguoB = Nivelacion_Complementaria(Punta_A->id_Color);}

    if(hay_monocromo){
        long brillo, oscuro;
        respaldo = Color_selecionado(ColorMonocromo);
        if(!respaldo || Brillo_y_Sombra(respaldo->id_Color,&brillo,&oscuro,.50,.25) == ERROR)
            return;
        if(Luz == nullptr)
            Luz = new RGB;
        if(Sombra == nullptr)
            Sombra = new RGB;
        *Luz = brillo;
        *Sombra = oscuro;}

    if(hay_gamas && Gamas == nullptr){
        ConstruirGamas();}}


void SuperColor::ConstruirGamas(){
    if(Gamas != nullptr) return;
    Gamas = new RGB*[13];
    CreaColores(TODO - GAMA,INTRAQUEABLE);
    ConstruirColores();
    Gamas[0] = Opuesto;
    Gamas[2] = Punta_B;
    Gamas[4] = ContiguoB;
    Gamas[6] = Original;
    Gamas[8] = ContiguoA;
    Gamas[10] = Punta_A;
    Gamas[12] = Opuesto;
    for(short i = 5,j = 11; i > 0; i -= 2 ,j -=2){
        respaldo = new RGB;
        *respaldo =Suma_deColor(Gamas[i+1]->id_Color,Gamas[i-1]->id_Color,IZQUIERDA);
        Gamas[j] = respaldo;}
    for(short i = 7,j = 1; i < 13; i += 2, j += 2){
        respaldo = new RGB;
        *respaldo = Suma_deColor(Gamas[i-1]->id_Color,Gamas[i+1]->id_Color,DERECHA);
        Gamas[j] = respaldo;}}


RGB *SuperColor::Color_selecionado(short color){
    if(estaVacio) return nullptr;
    es_todo = false;
    switch(color){
        case ORIGINAL:    return Original;
        case COMPLEMENTO: return Opuesto;
        case ANALOGO_A:   return ContiguoA;
        case ANALOGO_B:   return ContiguoB;
        case TRIANGULO_A: return Punta_A;
        case TRIANGULO_B: return Punta_B;

        default: es_todo = true;
                return nullptr;}}


bool SuperColor:: Eleccion(short eleccion){
    if(eleccion < NEGRO) return false;
    respaldo = Color_selecionado(eleccion);
    if(es_todo) return false;
    if(respaldo == nullptr){
        CreaColores(eleccion,INTRAQUEABLE);
        ConstruirColores();
        respaldo = Color_selecionado(eleccion);}
    return true;}


short recorredor(short dimencion, short indice){
    if(dimencion < 0) return 0;
    dimencion -= 1;
    if(indice < 0){
        dimencion += indice + 1;
        if(dimencion < 0)
            return 0;
        return  dimencion;}

    if(indice > dimencion) return dimencion;
    return indice;}


void SuperColor::limpiar(){
    reiniciar();
    iniciar();}


void SuperColor::Re_Asignar(short eleccion){
    if(!Eleccion(eleccion))return;
    Cambiar(respaldo->id_Color);}


void SuperColor::Restableser(){
    reiniciar();
    ConstruirColores();}


bool SuperColor::Luminicencia(short seleccion,short nivel,bool aplicar){
    if(!Eleccion(seleccion))return false;
    *respaldo = Nivel_de_Luminicencia(respaldo->id_Color,nivel);
    if(aplicar) Cambiar(*respaldo);
    return true;}


void SuperColor::AplicarCambios(){
    if(respaldo == nullptr)return;
    Cambiar(*respaldo);}


std::string SuperColor::Obterner(const short &Tono, const short &Modo,const short &indice){
    if(estaVacio || Tono == TODO) return "";

    if(Eleccion(Tono)){
        return respaldo->obtenerHEX(Modo);}

    if(Tono == GAMA){
        short i = recorredor(12,indice);
        hay_gamas = true;
        ConstruirColores();
        return Gamas[i]->obtenerHEX(Modo);}

    if(Tono >= MONOCROMO && Tono < ILUMINAR){
        short res;
        if(Tono < SOMBRA){
            res = Que_color_Es;
            CreaColores(Tono - BRILLO,MONOCROMO);
            Que_color_Es = res;
            return Luz->obtenerHEX(Modo);}

        if(Tono <= SOMBRA + TRIANGULO_B){
            res = Que_color_Es;
            CreaColores(Tono - SOMBRA,MONOCROMO);
            Que_color_Es = res;
            return Sombra->obtenerHEX(Modo);}
        return "";}

    if(Tono >= ILUMINAR){
        if(!Luminicencia(Tono - ILUMINAR,indice)) return "";
        return respaldo->obtenerHEX(Modo);}
    return "";}


long SuperColor::id(short eleccion)
{
    if(!Eleccion(eleccion))return  ERROR;
    return respaldo->id_Color;
}


bool SuperColor::operator==(SuperColor C){
    if(estaVacio == C.estaVacio) return true;
    if(estaVacio != C.estaVacio) return false;
    return *Original == *C.Original;}
bool SuperColor::operator!=(SuperColor C){
    return !(*this == C);}


std::string SuperColor::Q_style(const short &Tono, const short &Modo, const short &indice)
{
    std::string Qt_styleSheet;
    Qt_styleSheet = "background-color:";
    Qt_styleSheet += Obterner(Tono, Modo,indice);
    return Qt_styleSheet+=";";
}

std::ostream &operator<<(std::ostream &o, SuperColor &c){
    if(c.estaVacio) return o<<"Color inexistente"<<std::endl;
    o<<"___color_____css___html____R____G____B___"<<std::endl;
    o<<"  Original  "<<*c.Original;

    if(c.hay_monocromo && c.Luz)
        o<<"   Brillo   "<<*c.Luz;

    if(c.hay_monocromo && c.Sombra)
        o<<"   Sombra   "<<*c.Sombra;

    if((c.Que_color_Es & COMPLEMENTO) && c.hay_opuesto)
        o<<"Complemento "<<*c.Opuesto;

    if((c.Que_color_Es & ANALOGO_A) && c.hay_contiguo_A)
        o<<"Adyasente A "<<*c.ContiguoA;

    if((c.Que_color_Es & ANALOGO_B) && c.hay_contiguo_B)
        o<<"Adyasente B "<<*c.ContiguoB;

    if((c.Que_color_Es & TRIANGULO_A) && c.hay_triangulo_A)
        o<<"  Triada  A "<<*c.Punta_A;

    if((c.Que_color_Es & TRIANGULO_B) && c.hay_triangulo_B)
        o<<"  Triada  B "<<*c.Punta_B;

    if((c.Que_color_Es & GAMA) && c.hay_gamas && c.Gamas != nullptr){
        o<<std::endl<<"___gamas_____css___html____R____G____B___"<<std::endl;
        for(short i = 0; i < 6; ++i)
            o<<"     ^^     "<<*c.Gamas[i];
        o<<"  Original  "<<*c.Gamas[6];
        for(short i = 7; i < 13; ++i)
            o<<"     vv     "<<*c.Gamas[i];}

    return o;}
