#include "myplot.h"

#include <QImage>
#include <QPainter>
#include <QPen>
#include <QColor>

MyPlot::MyPlot(double W,double H)
{
    this->W=W;
    this->H=H;

    this->zeroLin=0.9*H;
    this->zeroCol=0.1*W;

    this->image=QImage(this->W,this->H,QImage::Format_RGB32);
    this->image.fill(qRgba(255, 255, 255, 0));
}

void MyPlot::SetZero(int lin0,int col0)
{
    this->zeroLin=lin0;
    this->zeroCol=col0;
}

int MyPlot::CurrentMaxX(void)
{
    return W-this->zeroCol;
}

int MyPlot::CurrentMaxY(void)
{
    return this->zeroLin;
}


void MyPlot::PlotLine(int x0,int y0,int x1,int y1,QPainter &painter, QPen &pen)
{
    painter.setPen  (pen);
    painter.setBrush(Qt::NoBrush);

    painter.drawLine(this->zeroCol+x0,this->zeroLin-y0,this->zeroCol+x1,this->zeroLin-y1);
}

void MyPlot::PlotPoint(int x0,int y0,int r,QPainter &painter,QPen &pen)
{
    painter.setPen  (pen);
    painter.setBrush(Qt::NoBrush);

    painter.drawEllipse(QPoint(this->zeroCol+x0,this->zeroLin-y0),r,r);
}

void MyPlot::PlotText(QString text,int x0,int y0,int deltax,int deltay,QPainter &painter, QPen &pen)
{
    painter.setPen  (pen);
    painter.setBrush(Qt::NoBrush);

    painter.drawText(this->zeroCol+x0,this->zeroLin-y0,deltax,deltay,Qt::AlignCenter,text);
}

bool MyPlot::PlotAxes(int MaxX,int MaxY,QList<double> labelx,QList<double> labely, QPainter &painter, QPen &pen)
{
    int TextBarSize=10;
    int TextHSize=20;
    int TextWSize=15;

    this->PlotLine(0,
                   0,
                   MaxX,
                   0,
                   painter,pen);

    this->PlotLine(0,
                   0,
                   0,
                   MaxY,
                   painter,pen);

    int Nx=labelx.size();
    if(Nx<=0)   return false;

    int Ny=labely.size();
    if(Ny<=0)   return false;

    int maxlabelx=labelx.at(0);
    int minlabelx=labelx.at(0);
    for(int i=0;i<Nx;i++)  if(maxlabelx<labelx.at(i)) maxlabelx=labelx.at(i);
    for(int i=0;i<Nx;i++)  if(minlabelx>labelx.at(i)) minlabelx=labelx.at(i);

    int maxlabely=labely.at(0);
    int minlabely=labely.at(0);
    for(int i=0;i<Ny;i++)  if(maxlabely<labely.at(i)) maxlabely=labely.at(i);
    for(int i=0;i<Ny;i++)  if(minlabely>labely.at(i)) minlabely=labely.at(i);

    for(int i=0;i<Nx;i++)
    {
        int pos=MaxX *(labelx.at(i)-minlabelx)/(maxlabelx-minlabelx);
        this->PlotLine(pos,0,pos,-TextBarSize,painter,pen);
        this->PlotText(QString::number(labelx.at(i), 'f', 1),pos-TextWSize,-TextBarSize,2*TextWSize,TextHSize,painter,pen);
    }


    for(int i=0;i<Ny;i++)
    {
        int pos=MaxY *(labely.at(i)-minlabely)/(maxlabely-minlabely);
        this->PlotLine(0,pos,-TextBarSize,pos,painter,pen);
        this->PlotText(QString::number(labely.at(i), 'f', 1),-2.5*TextWSize-TextBarSize,pos+TextHSize/2,2.5*TextWSize,TextHSize,painter,pen);
    }

    return true;
}

bool MyPlot::PlotCurve(QList<double> X,QList<double> Y,QString labelX,QString labelY, QPainter &painter, QPen &penAxes, QPen &penCurve, QPen &penPoint)
{
    QFont font;

    int Nx=X.size();
    if(Nx<=0)   return false;

    int Ny=Y.size();
    if(Ny<=0)   return false;

    if(Nx!=Ny)  return false;

    int N=Nx;

    int PointRad=5;

    int maxx=X.at(0);
    int minx=X.at(0);
    for(int i=0;i<N;i++)  if(maxx<X.at(i)) maxx=X.at(i);
    for(int i=0;i<N;i++)  if(minx>X.at(i)) minx=X.at(i);
    // maxx : maximo valor de x
    // minx : minimo valor de x

    int maxy=Y.at(0);
    int miny=Y.at(0);
    for(int i=0;i<N;i++)  if(maxy<Y.at(i)) maxy=Y.at(i);
    for(int i=0;i<N;i++)  if(miny>Y.at(i)) miny=Y.at(i);
    // maxy : maximo valor de y
    // miny : minimo valor de y

    font=painter.font() ;
    font.setPointSize ( 16 );//font.setWeight(QFont::DemiBold);
    painter.setFont(font);
    int MaxAxesX=this->CurrentMaxX()-0.05*W;
    int MaxAxesY=this->CurrentMaxY()-0.05*H;
    this->PlotAxes(MaxAxesX,MaxAxesY,X,Y,painter,penAxes);

    font=painter.font() ;
    font.setPointSize ( 20 );
    //font.setWeight(QFont::DemiBold);
    painter.setFont(font);
    this->PlotText(labelX,0,-0.05*H,MaxAxesX,0.05*H,painter, penAxes);

    font=painter.font() ;
    font.setPointSize ( 20 );
    //font.setWeight(QFont::DemiBold);
    painter.setFont(font);
    painter.rotate(-90);
    this->PlotText(labelY,-this->zeroLin-0.15*H,MaxAxesX-0.18*W,MaxAxesY,0.05*W,painter, penAxes);
    painter.rotate(+90);

    for(int i=1;i<N;i++)    this->PlotLine(MaxAxesX*(X.at(i-1)-minx)/(maxx-minx),
                                            MaxAxesY*(Y.at(i-1)-miny)/(maxy-miny),
                                            MaxAxesX*(X.at(i)-minx)/(maxx-minx),
                                            MaxAxesY*(Y.at(i)-miny)/(maxy-miny),painter,penCurve);

    for(int i=0;i<N;i++)    this->PlotPoint(MaxAxesX*(X.at(i)-minx)/(maxx-minx),MaxAxesY*(Y.at(i)-miny)/(maxy-miny),PointRad,painter,penPoint);

    return true;
}

void MyPlot::Print(QString filepath,QList<double> X,QList<double> Y,QString labelX,QString labelY)
{

    this->image.fill(qRgba(255, 255, 255, 0));

    QPainter painter( &(this->image) );

    QPen penAxes(qRgba(0, 0, 0, 0));
    QPen penCurve(qRgba(190, 190,190, 0));
    QPen penPoint(qRgba(255, 0, 0, 0));

    penAxes.setWidth(3);
    penCurve.setWidth(3);
    penPoint.setWidth(3);


    this->PlotCurve(X,Y, labelX, labelY, painter, penAxes,penCurve,penPoint);

    painter.end();

    this->image.save( filepath,NULL,100 );
}
