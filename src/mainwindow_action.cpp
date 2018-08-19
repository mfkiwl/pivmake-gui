#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopServices>
#include <QDir>
#include <QUrl>
#include <QDebug>

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

void MainWindow::on_actionAbout_triggered()
{
    std::stringstream about;

    about
    <<"<center><b> "<<APP_TARGET<<"</b></center><br>"
    <<"<b>version:</b> "<<APP_VERSION<<"<br>"
    <<"<b>license:</b> GPL<br>"
    <<"<b>homepage:</b> <a href='"<<APP_HOMEPAGE<<"'>"<<APP_HOMEPAGE<<"</a><br>"
    <<"<b>author:</b> Fernando Pujaico Rivera<br>"
    <<"<b>email:</b> fernando.pujaico.rivera@gmail.com<br>";

    QMessageBox::about(this,"About the program", QString::fromStdString(about.str()));
}

void MainWindow::on_actionDocumentation_triggered()
{
    QString strtemp=QString(this->progdir)+QDir::separator()+
                            ".."+QDir::separator()+
                            "share"+QDir::separator()+
                            "doc"+QDir::separator()+
                            APP_TARGET+QDir::separator()+
                            APP_TARGET+".pdf";
#if defined(_WINDOWS_) || defined(_WIN32) || defined(WIN32)
    strtemp="file:"+strtemp;
#endif
qDebug() <<"Opening:"<<strtemp;
    qDebug() << QDesktopServices::openUrl(QUrl(strtemp, QUrl::TolerantMode));
}

