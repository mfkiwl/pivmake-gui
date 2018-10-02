#include "myplot.h"

#include <QImage>
#include <QPainter>
#include <QPen>

MyPlot::MyPlot()
{
    this->W=800;
    this->H=600;


}

void MyPlot::SetData(QList<double> X,QList<double> Y)
{
    this->X=X;
    this->Y=Y;
}

void MyPlot::Save(QString filepath)
{
    int zeroPixelX=(int)(this->W*0.1);
    int endPixelX=(int)(this->W*0.9);

    int zeroPixelY=(int)(this->H*0.9);
    int endPixelY=(int)(this->H*0.1);

    int TextAxesSizeH=(int)(this->H*0.05);
    int TextAxesSizeW=(int)(this->H*0.05*0.75);

    QImage image(this->W,this->H,QImage::Format_RGB32);
    image.fill(qRgba(255, 255, 255, 0));

    int Nx=(this->X).size();

    QPainter painter( &image );

    // Draw Axes lines
    painter.setPen  (qRgba(0, 0, 0, 0));
    painter.setBrush(Qt::NoBrush);
    painter.drawLine(zeroPixelX,zeroPixelY,zeroPixelX,endPixelY);
    painter.drawLine(zeroPixelX,zeroPixelY,endPixelX,zeroPixelY);
    // Draw X text
    for(int i=0;i<Nx;i++)
    painter.drawText(x,y,H*0.05,H*0.05,Qt::AlignCenter,QString::number((this->X).at(i), 'f', 1));


    painter.end();
    image.save( filepath,NULL,100 );
}
