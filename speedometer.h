#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QPainter>
#include <QFont>
#include <QLabel>

#include <iostream>
#include <dangerarea.h>

using namespace std;

namespace Ui {
class Speedometer;
}

class Speedometer : public QWidget
{
    Q_OBJECT

public:
    explicit Speedometer(QWidget *parent = 0);
    ~Speedometer();

protected:
    void paintEvent(QPaintEvent *event);

public:
    void setColorBackground(QColor color);
    void setColorBackground(int red, int green, int blue);
    void setColorArrow(QColor color);
    void setColorArrow(int red, int green, int blue);
    void setColorLine(QColor color);
    void setColorLine(int red, int green, int blue);
    void setColorText(QColor color);
    void setColorText(int red, int green, int blue);
    void setColorFrame(QColor color);
    void setColorFrame(int red, int green, int blue);
    void setCountLine(int count);
    void setCountText(int count);
    void setFont(QString nameFont, int kegl);
    void setFont(QFont font);
    void setFontTitle(QString nameFont, int kegl);
    void setFontTitle(QFont font);
    void setLabelSize(QSize size);
    void setLabelSize(int width, int height);
    void setLabelSizeTitle(QSize size);
    void setLabelSizeTitle(int width, int height);
    void setLabelTitleText(QString text);
    void setWidthArrow(int width);
    void setTitleText(QString text);
    void setMaxValue(int val);
    void setFontLlbTxt(QString nameFont, int kegl);
    void setFontLblTxt(QFont font);
    void setLblText(QString str);

    void AddDangerZone(int beginValue, int endValue, QColor color);
    void ClearListDangerZone();
    bool ListDangerZoneEmpty();
    void ListDangerZoneDeleteItem(int i);

    void turnArrow(int value);
    void paint();

private:
    Ui::Speedometer *ui;
    float radius;
    int countLine;
    int countText;
    int maxValue, minValue;
    QPointF midle;
    QColor clrBackGround, clrArrow, clrLine, clrTxt, clrFrame;
    QFont font, fontTitle, fontLlbTxt;
    QSize lblSize, lblSizeTitle, lblSizeTxt;
    QLabel *lbl[30];
    QLabel *lblTitle;
    QLabel *lblText;
    QString titleText, lblTxt;
    bool dangerZona;
    int widthArrow;
    float angleArrow;
    QImage gaz;

    QList<DangerArea> listDangerAreas;

    const float angle30 = 0.5236f;
    const float angle150 = 2.610f;
    const float angle180 = 3.1416f;
    const float angle360 = 6.2832f;
};

#endif // SPEEDOMETER_H
