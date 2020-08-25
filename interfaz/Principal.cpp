#include "Principal.h"
#include "base_RGB/SuperColor.h"

#include "stdlib.h"
#include "windows.h"
#include "time.h"
#include "pthread.h"

#include <iostream>
#include <string>

using namespace std;
void mostrar(char *controlador)
{
    pthread_t vista;
    pthread_t coloreado;
    controlador[0] = 0;
    if(pthread_create(&vista,NULL,menu,controlador)==-1)
        return;
    if(pthread_create(&coloreado,NULL,colorea,controlador)==-1)
        return;

    pthread_join(vista,NULL);
    pthread_join(coloreado,NULL);
    if(*controlador != '3')
        interfaz(controlador);
    agradecer();
}

void gama(){
    string gama[15];
    gama[0] = "color 01";
    gama[1] = "color 02";
    gama[2] = "color 03";
    gama[3] = "color 04";
    gama[4] = "color 05";
    gama[5] = "color 06";
    gama[6] = "color 07";
    gama[7] = "color 08";
    gama[8] = "color 09";
    gama[9] = "color 0A";
    gama[10] = "color 0B";
    gama[11] = "color 0C";
    gama[12] = "color 0D";
    gama[13] = "color 0F";
    srand(time(NULL));
    short i = rand()%13;
    system(gama[i].c_str());
}

void *colorea(void *valor){
    char *controlador =(char*)valor;
    struct timespec tiempo {1,10};
    while(*controlador != '3'&&*controlador != '1'){
        gama();
        pthread_delay_np(&tiempo);}}

void *menu(void *valor){
    char *controlador =(char*)valor;
    while(*controlador != '3'){
        POS(23,0);
        cout<<"ColoRef";
        POS(15,3);
        printf("PARA INICIAR presiona[1]");
        POS(15,6);
        printf("INFORMACION presiona[2]");
        POS(18,9);
        printf("SAlIR presiona[3]\n\n");
        struct timespec tiempo {1,0};
        scanf("%s",controlador);
        if(*controlador < '1' || *controlador > '3'){
            printf("intenta de nuevo");
            pthread_delay_np(&tiempo);
            system("cls");}
        else if(*controlador == '2'){
            system("cls");
            licencia();}
        else{
            system("cls");
            break; }}}

void interfaz(char *controlador){
    system("color 0F");
    while(true){
        printf("ingresa la notacion html o css del color\n");
        string color;
        cin>>color;
        SuperColor ColordelUsuario = color;
        if(!ColordelUsuario.EstaVacio()){
            printf("obtener brillo y sombras[1]\n");
            printf("obtener complemento[2]\n");
            printf("obtener adyasentes[3]\n");
            printf("obtener la triada[4]\n");
            printf("obtener todo[5]\n");
            scanf("%s",controlador);
            switch (*controlador) {
                case '1': ColordelUsuario.CreaColores(SuperColor::TODO,SuperColor::MONOCROMO);
                        break;
                case '2': ColordelUsuario.CreaColores(SuperColor::COMPLEMENTO);
                        break;
                case '3': ColordelUsuario.CreaColores(SuperColor::ANALOGO);
                        break;
                case '4': ColordelUsuario.CreaColores(SuperColor::TRIADA);
                        break;
                case '5': ColordelUsuario.CreaColores(SuperColor::TODO);
                        break;
                default:break;}}
        system("cls");
        cout<<ColordelUsuario<<endl;
        printf("agregar un nuevo color [1] salir [cualquier tecla]\n");
        scanf("%s",controlador);
        if(*controlador == '1' )
            system("cls");
        else{
            system("cls");
            break;}}}

void POS (short x, short y){
    COORD coor;
    coor.X = x;
    coor.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coor);}


void licencia(){
    POS(23,0);
    cout<<"ColoRef";
    POS(16,1);
    printf("version monocromo 0.0");
    POS(13,4);
    printf("GNU: GENERAL PUBLIC LICENSE");
    POS(15,5);
    printf("Version 3, 29 June 2007");
    POS(16,7);
    printf("autor <MARCO  ANTONIO>");
    printf("\n\n");
    system("pause");
    system("cls");}


void agradecer(){
    system("color 0F");
    printf("              _.. --- .._\n\
           .:`             `:_\n\
         .`                    :,\n\
        /                        :`\n\
       :`                     \\    :`\n\
      :`        \\ .  |`,  \\    \\     \\\n\
     /      |  / V\\  |  \\.`\\    \\     \\\n\
    /^.     ` /__. `.| --`  \\|        |\n\
      |    ^.V          ,==, |  ;\\  |\\|\n\
      |^.   \\ ,==,        `` | /^/  | `\n\
        |    | ``   `        |/-^  /\n\
        |^ ^.:,    /[\\--`  ,*--. /V\n\
          V   V`--/ `.\\--<`/    V\n\
                .|) |  |\\ / __  |\n\
               / \\_/^,/  \\<    /|\n\
              /    /|\\        / |\n\
              \\   / | \\      /  /\n\
               \\_:` |   `:__:` /\n\n");
    printf("gracias por usarme\n");
    while(true){
        Sleep(3000);
        break;};
}
