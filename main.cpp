#include "interfaz/Principal.h"
#include <QApplication>
#include <QWidget>
#include <QSplashScreen>
#include <QObject>
#include <QPushButton>

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    //a.setStyle("fusion");
    VentanaPrincipal v;
    v.show();
    return a.exec();
}

