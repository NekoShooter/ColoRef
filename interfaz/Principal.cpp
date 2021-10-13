#include "Principal.h"
#include "base_RGB/SuperColor.h"
#include <QPushButton>
#include <QColor>
#include <QPixmap>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
//#include <QSplashScreen>

#define ALTURA 420
#define LARGO 600

using namespace SuperColorStd;


VentanaPrincipal::VentanaPrincipal()
{
    Pantalla_de_Bievenida();
    iniciar();
    Maquetado_Principal();
    Conectores_Principales();
    Temas();}

void VentanaPrincipal::Arrancar(){
    Seguro = true;
    imagen->clear();
    info->setHidden(true);
    Bloquear(false);}



void VentanaPrincipal::Conectores_Principales(){
        QObject::connect(Menu,SIGNAL(clicked()),this,SLOT(Acerca_De()));
        QObject::connect(Complemento,SIGNAL(clicked()),this,SLOT(Complementar()));
        QObject::connect(Analogos,SIGNAL(clicked()),this,SLOT(Analogar()));
        QObject::connect(Triada,SIGNAL(clicked()),this,SLOT(Triangular()));
        QObject::connect(Gamas,SIGNAL(clicked()),this,SLOT(Gamificar()));
        QObject::connect(Monocroma,SIGNAL(clicked()),this,SLOT(Monocromatizar()));
        QObject::connect(Todo,SIGNAL(clicked()),this,SLOT(Muestra_todo()));
        QObject::connect(Entrada_de_color,SIGNAL(editingFinished()),this,SLOT(EntradaTexto()));
        QObject::connect(&Entrada_RGB[0],SIGNAL(valueChanged(int)),this,SLOT(EntradaR(int)));
        QObject::connect(&Entrada_RGB[1],SIGNAL(valueChanged(int)),this,SLOT(EntradaG(int)));
        QObject::connect(&Entrada_RGB[2],SIGNAL(valueChanged(int)),this,SLOT(EntradaB(int)));
        QObject::connect(Agregar,&QPushButton::clicked,this,[&](){
            SuperColor COLOR(verificacion->toStdString());
            Actualizar(&COLOR);});
        clickeador();
}

#define _L 90
#define _A 70
QPushButton *boton(QVBoxLayout **vertical,QMainWindow **ventanaPrincipal){
    QPushButton *BOTON;
    BOTON = new QPushButton(ventanaPrincipal[0]);
    vertical[0]->addWidget(BOTON);
    BOTON->show();
    return BOTON;
}
void VentanaPrincipal::Maquetado_Principal(){
    Menu->setGeometry(530,350,70,_A);
    Menu->show();
    Complemento->setGeometry(0,0,_L,_A);
    Complemento->show();
    Analogos->setGeometry(0,1*_A,_L,_A);
    Analogos->show();
    Triada->setGeometry(0,2*_A,_L,_A);
    Triada->show();
    Gamas->setGeometry(0,3*_A,_L,_A);
    Gamas->show();
    Monocroma->setGeometry(0,4*_A,_L,_A);
    Monocroma->show();
    Todo->setGeometry(0,5*_A,_L,_A);
    Todo->show();
    foter->setGeometry(90,350,520,70);
    foter->show();
    Lateral->setGeometry(0,0,90,420);
    Etiqueta_HTML->setText("HEXADECIMAL");
    Etiqueta_HTML->setGeometry(170,365,70,20);
    Etiqueta_HTML->setAlignment(Qt::AlignHCenter);
    Entrada_de_color->setGeometry(170,385,70,20);
    Entrada_de_color->setAlignment(Qt::AlignHCenter);
    Etiqueta_CSS->setText("CSS");
    Etiqueta_CSS->setGeometry(255,365,70,20);
    Etiqueta_CSS->setAlignment(Qt::AlignHCenter);
    Salida_en_CSS->setGeometry(255,385,70,20);
    Salida_en_CSS->setReadOnly(true);
    Salida_en_CSS->setAlignment(Qt::AlignHCenter);
    contorno->setGeometry(110,366,39,39);
    Salida->setGeometry(112,368,35,35);
    Sombreador->setHidden(true);
    indicador->setHidden(true);
    contorno->show();
    Salida->show();
    Etiqueta_RGB[0].setText("R");
    Etiqueta_RGB[1].setText("G");
    Etiqueta_RGB[2].setText("B");
    for(short i= 0; i <3; ++i){
        Etiqueta_RGB[i].setGeometry((i*50+(i*15))+340,365,50,20);
        Etiqueta_RGB[i].setAlignment(Qt::AlignHCenter);
        Entrada_RGB[i].setGeometry((i*50+(i*15))+340,385,50,20);
        Entrada_RGB[i].setMaximum(255);
        Etiqueta_RGB[i].setAlignment(Qt::AlignHCenter);
        Entrada_RGB[i].setAlignment(Qt::AlignHCenter);
        Etiqueta_RGB[i].show();
        Entrada_RGB[i].show();}
    Agregar->setGeometry(110,366,39,39);
    Agregar->setHidden(true);
    Etiqueta_CSS->show();
    Etiqueta_HTML->show();
    Bloquear(true);
}

void VentanaPrincipal::iniciar(){
    foter= new QLabel(this);
    Lateral = new QLabel(this);
    Sombreador = new QLabel(this);
    indicador =  new QLabel(this);
    contorno = new QLabel(this);
    Etiqueta_CSS = new QLabel(this);
    Etiqueta_HTML = new QLabel(this);
    Etiqueta_RGB = new QLabel[3];
    Menu = new QPushButton(this);
    Complemento = new QPushButton(this);
    Gamas= new QPushButton(this);
    Analogos = new QPushButton(this);
    Triada = new QPushButton(this);
    Monocroma= new QPushButton(this);
    Todo = new QPushButton(this);
    Entrada_de_color = new QLineEdit(this);
    Salida_en_CSS = new QLineEdit(this);
    Salida = new QLabel(this);
    verificacion = new QString;
    //info = new QSplashScreen(this);
    Agregar = new QPushButton(this);
    R = new int;
    G = new int;
    B = new int;
    Colores = new QColor[14];
    CSS = new QString[14];
    Entrada_RGB = new QSpinBox[3];
    for(short i= 0; i <3; ++i){
        Etiqueta_RGB[i].setParent(this);
        Entrada_RGB[i].setParent(this);}
    anular();}




void VentanaPrincipal::hipercreador(short L, short A, short X,short Y,short indice){
    C[indice]->setGeometry(X,Y,L,A);
    C[indice]->show();}


void VentanaPrincipal::mostrarSalida(int i, bool limpiar){
    if(i == 6)Agregar->setHidden(true);
    else if(Agregar->isHidden()) Agregar->show();
    if(limpiar){
        Salida_en_CSS->clear();
        Entrada_de_color->clear();
        Entrada_RGB[0].clear();
        Entrada_RGB[1].clear();
        Entrada_RGB[2].clear();   }
    *verificacion = Colores[i].name();
    Entrada_de_color->setText(Colores[i].name());
    Salida->setStyleSheet("background-color:" + Colores[i].name()+";");
    indicador->setStyleSheet("background-color:" + Colores[i].name()+";");
    int r,g,b;
    Colores[i].getRgb(&r,&g,&b);
    cambiarR(r);
    cambiarG(g);
    cambiarB(b);
    Entrada_RGB[0].setValue(r);
    Entrada_RGB[1].setValue(g);
    Entrada_RGB[2].setValue(b);
    Salida_en_CSS->setText(CSS[i]);}

//no es la mejor forma pero funciona
void VentanaPrincipal::clickeador(){
    QObject::connect(C[0],&QPushButton::clicked,this,[&](){mostrarSalida(0);});
    QObject::connect(C[1],&QPushButton::clicked,this,[&](){mostrarSalida(1);});
    QObject::connect(C[2],&QPushButton::clicked,this,[&](){mostrarSalida(2);});
    QObject::connect(C[3],&QPushButton::clicked,this,[&](){mostrarSalida(3);});
    QObject::connect(C[4],&QPushButton::clicked,this,[&](){mostrarSalida(4);});
    QObject::connect(C[5],&QPushButton::clicked,this,[&](){mostrarSalida(5);});
    QObject::connect(C[6],&QPushButton::clicked,this,[&](){mostrarSalida(6);});
    QObject::connect(C[7],&QPushButton::clicked,this,[&](){mostrarSalida(7);});
    QObject::connect(C[8],&QPushButton::clicked,this,[&](){mostrarSalida(8);});
    QObject::connect(C[9],&QPushButton::clicked,this,[&](){mostrarSalida(9);});
    QObject::connect(C[10],&QPushButton::clicked,this,[&](){mostrarSalida(10);});
    QObject::connect(C[11],&QPushButton::clicked,this,[&](){mostrarSalida(11);});
    QObject::connect(C[12],&QPushButton::clicked,this,[&](){mostrarSalida(12);});
    QObject::connect(C[13],&QPushButton::clicked,this,[&](){mostrarSalida(13);});}

void VentanaPrincipal::desbloquear(){
    for(short i = 0; i < 14; ++i){
        if(C[i]->isEnabled())
            C[i]->setEnabled(false);}}

void VentanaPrincipal::Area_de_seleccion(short i)
{
    CambiarIndicador(i);
    i -= 1;
    if(indicador->isHidden()){
        indicador->show();
        Sombreador->show();}
    indicador->setGeometry(0,i*70,3,70);
    Sombreador->setGeometry(0,i*70,90,70);
}

void VentanaPrincipal::Original(){
    indice_dela_arquitectura = 0;
    imagen->clear();
    if(regresar){ Acerca_De(); return;}
    ocultar();
    imagen->setGeometry(230,50,200,200);
    imagen->setStyleSheet("Background-color:"+Colores[6].name()+";");
    imagen->show();
    imagenCargada = false;
    indicador->setHidden(true);
    Sombreador->setHidden(true);}

void VentanaPrincipal::Complementar(){
    Area_de_seleccion(1);
    if(regresar){ Acerca_De(); return;}
    ocultar();
    hipercreador(200,98,230,50,6);
    hipercreador(200,98,230,152,0);}

void VentanaPrincipal::Analogar(){
    Area_de_seleccion(2);
    if(regresar){ Acerca_De(); return;}
    ocultar();
    hipercreador(100,100,280,170,6);
    hipercreador(100,100,210,35,4);
    hipercreador(100,100,350,35,8);}

void VentanaPrincipal::Triangular(){
    Area_de_seleccion(3);
    if(regresar){ Acerca_De(); return;}
    ocultar();
    hipercreador(100,100,280,35,6);
    hipercreador(100,100,210,170,2);
    hipercreador(100,100,350,170,10);}

void VentanaPrincipal::Monocromatizar()
{
    Area_de_seleccion(5);
    if(regresar){ Acerca_De(); return;}
    ocultar();
    hipercreador(100,100,292,120,6);
    hipercreador(100,100,187,120,12);
    hipercreador(100,100,397,120,13);}

void VentanaPrincipal::Gamificar(){

    Area_de_seleccion(4);
    if(regresar){ Acerca_De(); return;}
    ocultar();
    for(short i = 1,j = 0; i <12; i +=2,++j){
        hipercreador(60,100,(65*j)+120,120,i);
        if(i == 5){++j; ++i;
        hipercreador(60,100,(65*j)+120,120,i);--i;}}}



void VentanaPrincipal::Muestra_todo()
{   Area_de_seleccion(6);
    if(regresar){ Acerca_De(); return;}
    if(!imagen->isHidden()) imagen->setHidden(true);
    short a = 55;
    short b = 35;
    short c = 35;
    hipercreador(a,b,312,c+(b*6),0);
    hipercreador(a,b,257,c+(b*5),1);
    hipercreador(a,b,202,c+(b*4),2);
    hipercreador(a,b,147,c+(b*3),3);
    hipercreador(a,b,202,c+(b*2),4);
    hipercreador(a,b,257,c+(b*1),5);
    hipercreador(a,b,312,c,6);
    hipercreador(a,b,367,c+(b*1),7);
    hipercreador(a,b,422,c+(b*2),8);
    hipercreador(a,b,477,c+(b*3),9);
    hipercreador(a,b,422,c+(b*4),10);
    hipercreador(a,b,367,c+(b*5),11);
    hipercreador(a,b,147,c,12);
    hipercreador(a,b,477,c,13);}



void VentanaPrincipal::Pantalla_de_Bievenida()
{
    this->resize(LARGO,ALTURA);
    this->setMinimumSize(LARGO,ALTURA);
    this->setMaximumSize(LARGO,ALTURA);
    imagen = new QLabel(this);
    info = new QLabel(this);
    info->setAlignment(Qt::AlignHCenter);
    Seguro = false;
    imagenCargada = false;
    regresar = false;
    portada();}

void VentanaPrincipal::portada()
{
    if(regresar){
        Acerca_De();
        return;}
    if(imagen->isHidden())imagen->setHidden(false);
    if(info->isHidden())info->setHidden(false);
    CambiarIndicador(7);
    QPixmap inicio(":/imagenes/bokqet bienvenida.png");
    imagen->setPixmap(inicio);
    info->setText("¿Con que Color Comenzamos?");
    //imache->resize(contenedor->width(),contenedor->height());
    imagen->setGeometry(255,35,inicio.width(),inicio.height());
    info->setGeometry(265,290,150,20);
    cambioElTexto = true;
    imagenCargada = false;
}

void VentanaPrincipal::anular(){
    *verificacion = "";
    *R=*G=*B=0;
    for(short i = 0;i < 14; ++i)
        C[i]= nullptr;}


void VentanaPrincipal::ocultar(){
    if(!info->isHidden()) info->setHidden(true);
    if(!imagen->isHidden()) imagen->setHidden(true);
    for(short i = 0; i < 14; ++i){
        if(!C[i]->isHidden())
        C[i]->setHidden(true);}
    if(!imagen->isHidden())
        imagen->setHidden(true);}


void VentanaPrincipal::Bloquear(bool ver){
    Complemento->setEnabled(!ver);
    Analogos->setEnabled(!ver);
    Gamas->setEnabled(!ver);
    Triada->setEnabled(!ver);
    Monocroma->setEnabled(!ver);
    Todo->setEnabled(!ver);}




void VentanaPrincipal::Temas(){
    QPalette fondo;
    fondo.setColor(QPalette::Background,QColor("#eeeeee"));
    this->setPalette(fondo);
    this->setAutoFillBackground(true);
    //info->setPixmap(QPixmap("C:/Users/Marco/Pictures/giti_mini.png"));
    fondo.setColor(QPalette::ButtonText,QColor("#fafafa"));
    fondo.setColor(QPalette::WindowText,QColor("#fafafa"));
    foter->setStyleSheet("background-color:#5c5c5c;");
    Lateral->setStyleSheet("background-color:#5c5c5c;");
    Sombreador->setStyleSheet("background-color:#454545;");
    contorno->setStyleSheet("background-color:#dddddd;");
    Etiqueta_CSS->setPalette(fondo);
    Etiqueta_HTML->setPalette(fondo);
    Menu->setFlat(true);
    Complemento->setFlat(true);
    Gamas->setFlat(true);
    Analogos->setFlat(true);
    Triada->setFlat(true);
    Monocroma->setFlat(true);
    Todo->setFlat(true);
    Agregar->setFlat(true);
    Complemento->setIcon(QIcon(":/iconos/complemento.png"));
    //Complemento->setFixedSize(70,70);
    Complemento->setIconSize(QSize(37,37));
    Complemento->setToolTip("Complemento");
    Menu->setIcon(QIcon(":/iconos/menu.png"));
    Menu->setIconSize(QSize(35,35));
    Menu->setToolTip("Acerca de");
    Gamas->setIcon(QIcon(":/iconos/Gama.png"));
    Gamas->setIconSize(QSize(35,35));
    Gamas->setToolTip("Gamas");
    Monocroma->setIcon(QIcon(":/iconos/monocromo.png"));
    Monocroma->setIconSize(QSize(50,50));
    Analogos->setIcon(QIcon(":/iconos/Analogos.png"));
    Analogos->setIconSize(QSize(37,37));
    Analogos->setToolTip("Analogos");
    Triada->setIcon(QIcon(":/iconos/triada.png"));
    Triada->setIconSize(QSize(30,30));
    Triada->setToolTip("Triada");
    Todo->setIcon(QIcon(":/iconos/todo.png"));
    Todo->setIconSize(QSize(30,30));
    Todo->setToolTip("Paleta Completa");
    Entrada_de_color->setStyleSheet("background-color:#eeeeee;");
    Salida_en_CSS->setStyleSheet("background-color:#eeeeee;");
    Agregar->setIcon(QIcon(":/iconos/agregar.png"));
    Agregar->setIconSize(QSize(20,20));
    Agregar->setToolTip("Agregar Color");
    for(short i= 0; i <3; ++i){
        Etiqueta_RGB[i].setPalette(fondo);
        Entrada_RGB[i].setStyleSheet("background-color:#eeeeee;");}
}

void VentanaPrincipal::Actualizar(SuperColor *COLOR){

    if(COLOR->EstaVacio()){
        Entrada_de_color->clear();
        return;}
    cargarColores(COLOR);
    if(!Seguro) Arrancar();
    mostrarSalida(6,false);
    Original();}



void VentanaPrincipal::EntradaTexto(){
    if(*verificacion == Entrada_de_color->displayText())return;
    SuperColor COLOR = Entrada_de_color->displayText().toStdString();
    Actualizar(&COLOR);}

void VentanaPrincipal::EntradaR(int r){
    if(*R == r) return;
    cambiarR(r);
    SuperColor COLOR(*R,*G,*B);
    Actualizar(&COLOR);}

void VentanaPrincipal::EntradaG(int g){
    if(*G == g)return;
    cambiarG(g);
    SuperColor COLOR(*R,*G,*B);
    Actualizar(&COLOR);}

void VentanaPrincipal::EntradaB(int b){
    if(*B == b)return;
    cambiarB(b);
    SuperColor COLOR(*R,*G,*B);
    Actualizar(&COLOR);}



void VentanaPrincipal::cargarColores(SuperColor*COLOR){
    for(short i = 0;i<12;++i){
        Colores[i].setNamedColor(COLOR->Obterner(GAMA,HTML,i).c_str());
        CSS[i] = COLOR->Obterner(GAMA,SuperColorStd::CSS,i).c_str();}
    Colores[12].setNamedColor(COLOR->Obterner(ORIGINAL+SOMBRA).c_str());
    Colores[13].setNamedColor(COLOR->Obterner(ORIGINAL+BRILLO).c_str());
    CSS[12] = COLOR->Obterner(ORIGINAL+SOMBRA,SuperColorStd::CSS).c_str();
    CSS[13] = COLOR->Obterner(ORIGINAL+BRILLO,SuperColorStd::CSS).c_str();
    if(C[0]== nullptr){
        for(short i = 0; i <14; ++i){
            C[i]=new QPushButton(this);}}
    if(!Seguro)
        clickeador();
    for(short i = 0; i <14; ++i)
        C[i]->setStyleSheet("background-color:" + Colores[i].name()+";");}


void VentanaPrincipal::Acerca_De()
{
    if(regresar){
        regresar = false;
        Menu->setIcon(QIcon(":/iconos/menu.png"));
        if(!imagen->isHidden())imagen->setHidden(true);
        if(!info->isHidden())info->setHidden(true);
        switch (indice_dela_arquitectura) {
            case 0: Original(); return;
            case 1: Complementar(); return;
            case 2: Analogar(); return;
            case 3: Triangular(); return;
            case 4: Gamificar(); return;
            case 5: Monocromatizar(); return;
            case 6: Muestra_todo(); return;
            default: portada(); return;}}
    if(Seguro)ocultar();
    if(cambioElTexto){
        info->setText("Soy ColoRef y me encantara poder ayudarte a elegir "
                      "uno o varios colores para tu proyecto\n"
                      "Mi Padre \"Marco Antonio\" creo mi algortimo usando "
                      "C y C++ y para la interfaz visual QT\n"
                      "\'Papá aun me sigue mejorando y aunque no estoy "
                      "completa espero poder ser te de utilidad\'\n\n"
                      "Estoy bajo la lincencia\n"
                      "GNU General Public License -version 3-\n"
                      "\nSi deseas colaborar o buscar actualizaciones me encuetras en\n"
                      "https://github.com/NekoShooter/ColorRef\n\n"
                      "ColoRef -- Version -- bokqet 1.0");
        info->setGeometry(115,200,460,200);
        cambioElTexto = false;}
    if(imagenCargada && indice_dela_arquitectura != 0){
        imagen->show();
        info->show();}
    else{
        imagen->clear();
        if(Seguro)imagen->setStyleSheet(nullptr);
        QPixmap nuevaimagen(":/imagenes/bokqet info.png");
        imagen->setPixmap(nuevaimagen);
        imagen->setGeometry(286,15,nuevaimagen.width(),nuevaimagen.height());
        imagen->show();
        info->show();}
    regresar = true;
    imagenCargada = true;
    Menu->setIcon(QIcon(":/iconos/regresar.png"));}


VentanaPrincipal::~VentanaPrincipal(){
    delete Agregar;
    delete verificacion;
    delete R;
    delete G;
    delete B;
    delete [] Etiqueta_RGB;
    delete []Entrada_RGB;
    delete Etiqueta_HTML;
    delete Etiqueta_CSS;
    delete contorno;
    delete Sombreador;
    delete indicador;
    delete foter;
    delete Lateral;
    delete Menu;
    delete Complemento;
    delete Gamas;
    delete Analogos;
    delete Triada;
    delete Todo;
    delete Monocroma;
    delete Entrada_de_color;
    delete Salida_en_CSS;
    delete [] Colores;
    delete [] CSS;
    delete  Salida;}

