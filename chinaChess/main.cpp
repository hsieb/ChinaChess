#include "logindialog.h"
#include "modechange.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ModeChange w;
    w.show();

    return a.exec();
}
