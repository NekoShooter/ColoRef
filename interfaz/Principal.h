/*                           - ColoRef -
                    Software de la teoría del color

      Este programa es un software libre; puedes redistribuirlo y/o
     modificarlo bajo los términos de la Licencia Pública General GNU
según lo publicado por la Free Software Foundation; versión 3 de la Licencia.

      Este programa se distribuye con la esperanza de que sea útil,
    pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
     COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver la
       Licencia pública general GNU para obtener más detalles.          */

#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QMainWindow>

class SuperColor;
class QPushButton;
class QPixmap;
class QLineEdit;
class QLabel;
class QGridLayout;
class QSpinBox;
//class QSplashScreen;

class VentanaPrincipal : public QMainWindow{
        Q_OBJECT
       // Q_PROPERTY(SuperColor COLOR READ COLOR WRITE setColor NOTIFY color_changed)
        Q_PROPERTY(int R_ READ R_ WRITE cambiarR NOTIFY remplazarRGB)
        Q_PROPERTY(int G_ READ G_ WRITE cambiarG NOTIFY remplazarRGB)
        Q_PROPERTY(int B_ READ B_ WRITE cambiarB NOTIFY remplazarRGB)
        Q_PROPERTY(int Indicador READ Indicador WRITE CambiarIndicador NOTIFY remplazarRGB)
    public:
        VentanaPrincipal();
        ~VentanaPrincipal();
        /*
        SuperColor COLOR()const {
            return Color;}
        void setColor(SuperColor);*/
        int R_()const{return *R;}
        int G_()const{return *G;}
        int B_()const{return *B;}
        int Indicador()const{return indice_dela_arquitectura;}
        void CambiarIndicador(int i){
            if(indice_dela_arquitectura == i)return;
            indice_dela_arquitectura = i;
            emit remplazarRGB(i);
        }
        void cambiarR(int r){
            if(*R == r)return;
            *R = r;
            emit remplazarRGB(*R);}
        void cambiarG(int g){
            if(*G == g)return;
            *G = g;
            emit remplazarRGB(*G);}
        void cambiarB(int b){
            if(*B == b)return;
            *B = b;
            emit remplazarRGB(*B);}
    signals:
        void remplazarRGB(int);
    private slots:
        void Original();
        void Complementar();
        void Analogar();
        void Triangular();
        void Gamificar();
        void Monocromatizar();
        void Muestra_todo();
        void Arrancar();
        void EntradaTexto();
        void EntradaR(int);
        void EntradaG(int);
        void EntradaB(int);
        void Acerca_De();

    private:

        QPushButton *Agregar,  *Complemento,  *Gamas,
                    *Analogos, *Monocroma,    *Triada,
                    *Todo,*Menu;
        QLabel *imagen,*info;
        QLineEdit *Entrada_de_color;
        QLineEdit *Salida_en_CSS;
        QLabel *Salida,*foter,*Lateral,
               *indicador,*Sombreador,*contorno,
               *Etiqueta_HTML,*Etiqueta_CSS,*Etiqueta_RGB;
        QGridLayout *pie;
        QColor *Colores;
        QPushButton *C[14];
        QString *CSS,*verificacion;
        bool Seguro;
        bool regresar;
        bool imagenCargada;
        bool cambioElTexto;
        QSpinBox* Entrada_RGB;
        int indice_dela_arquitectura;
        //QSplashScreen *info;
        int *R,*G,*B;
        void Pantalla_de_Bievenida();
        void Conectores_Principales();
        void Temas();
        void Maquetado_Principal();
        void iniciar();
        void anular();
        void ocultar();
        void Bloquear(bool);
        void cargarColores(SuperColor*);
        void hipercreador(short L,short A, short X, short Y,short indice = 6);
        void mostrarSalida(int i,bool limpiar = true);
        void clickeador();
        void desbloquear();
        void Area_de_seleccion(short i);
        void Actualizar(SuperColor*);
        void portada();
};
#endif //PRINCIPAL_H
