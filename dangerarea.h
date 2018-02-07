#ifndef DANGERAREA_H
#define DANGERAREA_H

#include <QColor>

class DangerArea
{
public:
    DangerArea();
    DangerArea(int beginValue, int endValue, QColor color);
    ~DangerArea();

    void setDangerArea(int beginValue, int endValue, QColor color);
    void setBeginValue(int beginValue);
    void setEndValue(int endValue);
    void setColor(QColor color);

    int getBeginValue();
    int getEndValue();
    QColor getColor();

private:
    int beginValue;
    int endValue;
    QColor color;
};


#endif // DANGERAREA_H
