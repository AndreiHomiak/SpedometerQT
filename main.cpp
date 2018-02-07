#include "speedometer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Speedometer w;
    w.show();
    w.turnArrow(60);
    w.setTitleText("x1");
    w.setLblText("GAS");
    w.paint();
    w.setCountLine(6);
    w.setCountText(6);
    w.setMaxValue(60);
    w.turnArrow(20);

    return a.exec();
}
