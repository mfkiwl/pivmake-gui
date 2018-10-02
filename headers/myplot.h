#ifndef MYPLOT_H
#define MYPLOT_H

#include <QString>
#include <QList>
class MyPlot
{
public:
    int W;
    int H;
    QList<double> X;
    QList<double> Y;
public:
    MyPlot();
    void SetData(QList<double> X,QList<double> Y);

    void Save(QString filepath);
};

#endif // MYPLOT_H
