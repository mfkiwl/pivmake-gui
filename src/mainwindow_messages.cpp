#include "mainwindow.h"
#include "ui_mainwindow.h"

//#include <QScrollBar>
#include <QMessageBox>

void MainWindow::launchMessageBox(QString str,bool warning)
{
    QString msg(str);
    QMessageBox Msgbox;
    if(warning==true)   Msgbox.setIcon(QMessageBox::Warning);
    else                Msgbox.setIcon(QMessageBox::Information);
    Msgbox.setText(msg);
    Msgbox.exec();
}


void MainWindow::set_message_in_listwidget(QString msg,QColor col)
{
    // Agregar  novo menssagem
    ui->listWidget->addItem(msg);
    ui->listWidget->item(ui->listWidget->count()-1)->setForeground(col);

    //QScrollBar *vb = ui->listWidget->verticalScrollBar();
    //while(vb->value()< vb->maximum())
    //vb->setValue(vb->maximum()); // Scrolls to the bottom

    ui->listWidget->setCurrentRow(ui->listWidget->count()-1);
}
