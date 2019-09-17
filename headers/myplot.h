#ifndef MYPLOT_H
#define MYPLOT_H

#include <QString>
#include <QList>
#include <QPainter>
#include <QPen>

class MyPlot
{
private:
    int W;
    int H;

    int zeroLin;
    int zeroCol;

    QImage image;
public:
    MyPlot(double W,double H);
private:
    int CurrentMaxX(void);
    int CurrentMaxY(void);

    void PlotLine(int x0,int y0,int x1,int y1,QPainter &painter, QPen &pen);
    void PlotText(QString text,int x0,int y0,int deltax,int deltay,QPainter &painter, QPen &pen);
    void PlotPoint(int x0,int y0,int r,QPainter &painter,QPen &pen);
    bool PlotAxes(int MaxX,int MaxY,QList<double> labelx,QList<double> labely, QPainter &painter, QPen &pen);
    bool PlotCurve(QList<double> X,QList<double> Y,QString labelX,QString labelY, QPainter &painter, QPen &penAxes, QPen &penCurve, QPen &penPoint);


    void SetZero(int lin0,int col0);
public:
    void Print(QString filepath,QList<double> X,QList<double> Y,QString labelX,QString labelY);
};

#endif // MYPLOT_H
