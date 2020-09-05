#include <QApplication>
#include "interfaz/Principal.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);
    //a.setStyle("fusion");
    VentanaPrincipal v;
    v.show();
    return a.exec();
}

