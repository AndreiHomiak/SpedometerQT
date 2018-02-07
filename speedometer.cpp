#include "speedometer.h"
#include "ui_speedometer.h"

Speedometer::Speedometer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Speedometer)
{
    ui->setupUi(this);

    midle.setX(this->width() / 2);
    this->resize(this->width(), this->width() * 0.6);
    midle.setY(this->width() / 2);
    radius = (int)this->width() / 2; //приведение

    clrBackGround = Qt::white;
    countLine = 24;
    dangerZona = false;

    lblSize = QSize(30, 20);

    lblSizeTitle = QSize(radius*0.2, radius*0.2);
    lblTitle = new QLabel(this);
    setFontTitle("Arial", 12);
    lblTitle->setText("x1");
    lblTitle->resize(lblSizeTitle);
    lblTitle->move(radius - lblSizeTitle.width()*0.5, radius*0.5 - lblSizeTitle.height()*0.5);

    widthArrow = 4;
    angleArrow = angle180;
    minValue = 0;

    lblSizeTxt = QSize(40,20);
    lblText = new QLabel(this);
    lblText->setFont(QFont("Arial", 12));
    lblText->setText("Test");
    lblTxt = "Test";
    lblText->resize(lblSizeTxt);
    lblText->move(radius - lblText->width()*0.5, radius*0.75 - lblText->height()*0.5);


    countText = 8;
    maxValue = 360;

    for(int i = 0; i <= countText; i++)
        lbl[i] = new QLabel(this);

//    listDangerAreas = new QList<DangerArea>();
    //for debug;
    dangerZona = true;
    listDangerAreas.push_back(DangerArea(10,20, Qt::yellow));
    listDangerAreas.push_back(DangerArea(0,10, Qt::red));
    //---------

    repaint();
}

Speedometer::~Speedometer()
{
    delete ui;
    //delete lbl;
}

void Speedometer::paintEvent(QPaintEvent *event)
{
    for(int i = 0; i <= countText; i++)
        delete lbl[i];

    delete lblTitle;
    delete lblText;

    //корректировка координат
    midle.setX(this->width() / 2);
    this->resize(this->width(), this->width() * 0.6);
    midle.setY(this->width() / 2);
    radius = (int)this->width() / 2; //приведение

    //полукруг и черточки
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //отрисовка поля
    painter.setPen(QPen(Qt::black, 1, Qt::NoPen, Qt::RoundCap, Qt::BevelJoin));
    painter.setBrush(QBrush(clrFrame, Qt::SolidPattern));
    painter.drawPie(0,0, radius*2, radius*2, 16*0, 16*180);
  //  painter.drawRect(0, radius, this->width(), this->width()*0.1);
    painter.setBrush(QBrush(clrBackGround, Qt::SolidPattern));
    painter.drawPie(radius*0.02, radius*0.02, radius*2*0.98, radius*2*0.98, 16*0, 16*180);
    painter.drawRect(radius*0.02, radius*0.99, this->width()*0.98, this->width()*0.1*0.99);


    if(dangerZona)
    {
        //опасные зоны
        float k =  -180 / (float)maxValue;
        float b = 180;

        if(!listDangerAreas.empty())
        {
            float angleBegin, angleEnd;

            for(int i = 0; i < listDangerAreas.length(); i++)
            {
                angleBegin = k * listDangerAreas[i].getBeginValue() + b;
                angleEnd = k * listDangerAreas[i].getEndValue() + b;
                painter.setBrush(QBrush(listDangerAreas[i].getColor(), Qt::SolidPattern));
                painter.drawPie(radius*0.02, radius*0.02, radius*2*0.98, radius*2*0.98, 16*angleEnd, 16*(angleBegin - angleEnd));
                painter.setBrush(QBrush(clrBackGround, Qt::SolidPattern));
                painter.drawPie(radius*0.09, radius*0.09, radius*2*0.91, radius*2*0.91, 16*0, 16*180);
            }

        }
    }

    painter.setBrush(QBrush(clrBackGround, Qt::SolidPattern));
    painter.drawRect(radius*0.02, radius*0.99, this->width()*0.98, this->width()*0.1*0.99);

    //отрисовка надписиси
    QImage img("d:/gaz.png");
    lblTitle = new QLabel(this);
    setFontTitle(fontTitle);
   // lblTitle->setText(titleText);
    lblTitle->resize(lblSizeTitle);
    lblTitle->move(radius - lblSizeTitle.width()*0.5, radius*0.5 - lblSizeTitle.height()*0.5);
    lblTitle->setPixmap(QPixmap::fromImage(img.scaled(lblTitle->width(), lblTitle->height())));
    lblTitle->show();

    lblText = new QLabel(this);
    lblText->setFont(fontLlbTxt);
    lblText->setText(lblTxt);
    lblText->resize(lblSizeTxt);
    lblText->move(radius - lblText->width()*0.5, radius*0.75 - lblText->height()*0.5);
    lblText->show();


    painter.setFont(font);
    float alpha = angle180 / countLine;
    float beta;
    char symbols[5];
    QPointF pBegin, pEnd, pText;
    int koef = countLine / countText;
    int partVal = maxValue / countText;

    for(int i = 0; i <= countLine; i++)
    {
        beta = alpha*i;
        QPen pen1(QBrush(clrLine, Qt::SolidPattern), 1, Qt::SolidLine, Qt::RoundCap,Qt::BevelJoin);
        painter.setPen(pen1);
        pBegin.setX((float)radius*0.99f*cos(angle180+beta) + midle.rx());
        pBegin.setY((float)radius*0.99f*sin(angle180+beta) + midle.ry());
        pEnd.setX((float)radius*0.9f*cos(angle180+beta) + midle.rx());
        pEnd.setY((float)radius*0.9f*sin(angle180+beta) + midle.ry());
        pText.setX((float)radius*0.7f*cos(angle180+beta) + midle.rx());
        pText.setY((float)radius*0.7f*sin(angle180+beta) + midle.ry());
        if(i%koef == 0)
        {
            pEnd.setX((float)radius*0.85f*cos(angle180+beta) + midle.rx());
            pEnd.setY((float)radius*0.85f*sin(angle180+beta) + midle.ry());

            QPen pen2(QBrush(clrLine, Qt::SolidPattern), 5, Qt::SolidLine, Qt::RoundCap,Qt::BevelJoin);
            painter.setPen(pen2);
            sprintf(symbols, "%d", i*partVal/koef);
            painter.drawText((int)(pText.rx() - lblSize.width()/2), (int)(pText.ry() - lblSize.height()/2), lblSize.width(), lblSize.height(), Qt::AlignCenter, symbols);

            lbl[i/koef] = new QLabel(this);
         /*   lbl[i/koef]->resize(lblSize);
            // !!!!!!!!!!!!!!!!!!!!!!!!!
            QFont font("Liberation Sans Narrow", 12);
            lbl[i/koef]->setFont(font);
            lbl[i/koef]->setText(symbols);
            int x = lbl[i/koef]->width()/2;
            int y = lbl[i/koef]->height()/2;

            lbl[i/koef]->move(pText.rx() - y, pText.ry() - x);
            lbl[i/koef]->show();*/
        }

        painter.drawLine(pBegin, pEnd);

    }

    //стрелочка
 /*   QPointF arrow;
    painter.setBrush(QBrush(clrArrow, Qt::SolidPattern));
    painter.drawEllipse(midle, radius*0.05, radius*0.05);
    arrow.setX((float)radius*0.8*cos(angleArrow) + midle.rx());
    arrow.setY((float)radius*0.8*sin(angleArrow) + midle.ry());
    painter.setPen(QPen(clrArrow, widthArrow, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    painter.drawLine(arrow, midle);*/
    //------------------------

    //стрелочка v2
  /*  QPolygonF triangle;
    QPointF arrow[3];
    arrow[0].setX(radius);      arrow[0].setY(radius*0.95);
    arrow[1].setX(radius);      arrow[1].setY(radius*1.05);
    arrow[2].setX(radius*0.1);  arrow[2].setY(radius);
    for(int i = 0; i < 3; i++)
    {
        float x = (arrow[i].rx() - midle.rx())*cos(angleArrow + angle180) - (arrow[i].ry() - midle.ry())*sin(angleArrow + angle180) + midle.rx();
        float y = (arrow[i].rx() - midle.rx())*sin(angleArrow + angle180) + (arrow[i].ry() - midle.ry())*cos(angleArrow + angle180) + midle.ry();
        triangle<<QPointF(x,y);
    }

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
    QLinearGradient gradient(arrow[2], midle);
    gradient.setColorAt(0, QColor(255, 0, 0, 125));
    gradient.setColorAt(0.5, QColor(255, 0, 0, 255));
    gradient.setColorAt(1, QColor(255, 0, 0, 175));
    painter.setBrush(gradient);
    painter.drawPolygon(triangle);*/
    //end стрелочка v2

    //стрелочка v3
    QPolygonF triangle1, triangle2;
    QPointF arrow[4];

    arrow[0].setX(radius*0.05);      arrow[0].setY(midle.ry());
    arrow[1].setX(radius*0.15);      arrow[1].setY(midle.ry() + radius*0.02);
    arrow[2].setX(radius*0.95);      arrow[2].setY(midle.ry() + radius*0.04);
    arrow[3].setX(radius);          arrow[3].setY(midle.ry());
    for(int i = 0; i < 4; i++)
    {
        float x = (arrow[i].rx() - midle.rx())*cos(angleArrow + angle180) - (arrow[i].ry() - midle.ry())*sin(angleArrow + angle180) + midle.rx();
        float y = (arrow[i].rx() - midle.rx())*sin(angleArrow + angle180) + (arrow[i].ry() - midle.ry())*cos(angleArrow + angle180) + midle.ry();
        triangle1<<QPointF(x,y);
    }

    arrow[0].setX(radius*0.05);      arrow[0].setY(midle.ry());
    arrow[1].setX(radius*0.15);      arrow[1].setY(midle.ry() - radius*0.02);
    arrow[2].setX(radius*0.95);      arrow[2].setY(midle.ry() - radius*0.04);
    arrow[3].setX(radius);          arrow[3].setY(midle.ry());
    for(int i = 0; i < 4; i++)
    {
        float x = (arrow[i].rx() - midle.rx())*cos(angleArrow + angle180) - (arrow[i].ry() - midle.ry())*sin(angleArrow + angle180) + midle.rx();
        float y = (arrow[i].rx() - midle.rx())*sin(angleArrow + angle180) + (arrow[i].ry() - midle.ry())*cos(angleArrow + angle180) + midle.ry();
        triangle2<<QPointF(x,y);
    }

    painter.setPen(QPen(Qt::black, 1, Qt::NoPen, Qt::SquareCap, Qt::BevelJoin));
    QLinearGradient gradient(arrow[0], midle);
    gradient.setColorAt(0, QColor(255, 0, 0, 255));
    gradient.setColorAt(0.7, QColor(255, 0, 0, 255));
    gradient.setColorAt(1, QColor(255, 0, 0, 255));
    painter.setBrush(QBrush(Qt::darkRed, Qt::SolidPattern));
//    painter.setBrush(gradient);
    painter.drawPolygon(triangle1);
    painter.setBrush(QBrush(Qt::red, Qt::SolidPattern));
    painter.drawPolygon(triangle2);
    //end стрелочка v3

    painter.end();
}

void Speedometer::setColorBackground(QColor color)
{
    clrBackGround = color;
}

void Speedometer::setColorBackground(int red, int green, int blue)
{
    clrBackGround = QColor(red, green, blue, 255);
}

void Speedometer::setColorArrow(QColor color)
{
    clrArrow = color;
}

void Speedometer::setColorArrow(int red, int green, int blue)
{
    clrArrow = QColor(red, green, blue, 255);
}

void Speedometer::setColorLine(QColor color)
{
    clrLine = color;
}

void Speedometer::setColorLine(int red, int green, int blue)
{
    clrLine = QColor(red, green, blue, 255);
}

void Speedometer::setColorText(QColor color)
{
    clrTxt = color;
}

void Speedometer::setColorText(int red, int green, int blue)
{
    clrTxt = QColor(red, green, blue, 255);
}

void Speedometer::setColorFrame(QColor color)
{
    clrFrame = color;
}

void Speedometer::setColorFrame(int red, int green, int blue)
{
    clrFrame = QColor(red, green, blue, 255);
}

void Speedometer::setCountLine(int count)
{
    countLine = count;
}

void Speedometer::setCountText(int count)
{
    countText = count;
}

void Speedometer::setFont(QString nameFont, int kegl)
{
    font = QFont(nameFont, kegl);
}

void Speedometer::setFont(QFont font)
{
    this->font = font;
}

void Speedometer::setFontTitle(QString nameFont, int kegl)
{
    lblTitle->setFont(QFont(nameFont, kegl));
}

void Speedometer::setFontTitle(QFont font)
{
    fontTitle = font;
    lblTitle->setFont(font);
}

void Speedometer::setLabelSize(QSize size)
{
    lblSize = size;
}

void Speedometer::setLabelSize(int width, int height)
{
    lblSize = QSize(width, height);
}

void Speedometer::setLabelSizeTitle(QSize size)
{
    lblSizeTitle = size;
}

void Speedometer::setLabelSizeTitle(int width, int height)
{
    lblSizeTitle = QSize(width, height);
}

void Speedometer::setLabelTitleText(QString text)
{
    lblTitle->setText(text);
}

void Speedometer::setWidthArrow(int width)
{
    widthArrow = width;
}

void Speedometer::setTitleText(QString text)
{
    titleText = text;
    lblTitle->setText(titleText);
}

void Speedometer::setMaxValue(int val)
{
    maxValue = val;
}

void Speedometer::setFontLlbTxt(QString nameFont, int kegl)
{
    fontLlbTxt = QFont(nameFont, kegl);
    lblText->setFont(fontLlbTxt);
}

void Speedometer::setFontLblTxt(QFont font)
{
    fontLlbTxt = font;
    lblText->setFont(fontLlbTxt);
}

void Speedometer::setLblText(QString str)
{
    lblText->setText(str);
    lblTxt = str;
    repaint();
}

void Speedometer::AddDangerZone(int beginValue, int endValue, QColor color)
{
    listDangerAreas.push_back(DangerArea(beginValue, endValue, color));
}

void Speedometer::ClearListDangerZone()
{
    listDangerAreas.clear();
}

bool Speedometer::ListDangerZoneEmpty()
{
    return listDangerAreas.empty();
}

void Speedometer::ListDangerZoneDeleteItem(int i)
{
    listDangerAreas.removeAt(i);
}


void Speedometer::turnArrow(int value)
{
    float k =  (angle360 - angle180) / (maxValue - minValue);
    float b = angle360 - k * maxValue;

    angleArrow = k * value + b;

    repaint();
}

void Speedometer::paint()
{
    repaint();
}
