#include "dangerarea.h"

DangerArea::DangerArea()
{
    this->beginValue = 0;
    this->endValue = 0;
    this->color = Qt::black;
}

DangerArea::DangerArea(int beginValue, int endValue, QColor color)
{
    this->beginValue = beginValue;
    this->endValue = endValue;
    this->color = color;
}

DangerArea::~DangerArea()
{

}

void DangerArea::setDangerArea(int beginValue, int endValue, QColor color)
{
    this->beginValue = beginValue;
    this->endValue = endValue;
    this->color = color;
}

void DangerArea::setBeginValue(int beginValue)
{
    this->beginValue = beginValue;
}

void DangerArea::setEndValue(int endValue)
{
    this->endValue = endValue;
}

void DangerArea::setColor(QColor color)
{
    this->color = color;
}

int DangerArea::getBeginValue()
{
    return this->beginValue;
}

int DangerArea::getEndValue()
{
    return this->endValue;
}

QColor DangerArea::getColor()
{
    return this->color;
}
