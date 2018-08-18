#include "mainwindow.h"
#include "ui_mainwindow.h"

// #include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QColorDialog>

// #include <QDebug>
// #include <QScrollBar>
// #include <pds/pdsdatafunc.h>

void MainWindow::on_pushButton_find_program_listfiles_clicked()
{
    QString  program_listfiles;
    if(ui->lineEdit_program_listfiles->text().length()==0)
        program_listfiles =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listfiles program"),
                                                       QDir::currentPath(),
                                                       #if defined(Q_OS_LINUX)
                                                       tr("listfiles program (listfiles)"));
                                                       #else
                                                       tr("listfiles program (listfiles.exe)"));
                                                       #endif
    else
        program_listfiles =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listfiles dat file"),
                                                       ui->lineEdit_program_listfiles->text(),
                                                       #if defined(Q_OS_LINUX)
                                                       tr("listfiles program (listfiles)"));
                                                       #else
                                                       tr("listfiles program (listfiles.exe)"));
                                                       #endif

    if(program_listfiles.length()==0)
    {
        launchMessageBox(tr("No listfiles program was selected"),true);
    }
    else
    {
        ui->lineEdit_program_listfiles->setText(program_listfiles);
    }
}


void MainWindow::on_pushButton_find_program_listregions_clicked()
{
    QString  program_listregions;
    if(ui->lineEdit_program_listregions->text().length()==0)
        program_listregions =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listregions program"),
                                                       QDir::currentPath(),
                                                       #if defined(Q_OS_LINUX)
                                                       tr("Listregions program (listregions)"));
                                                       #else
                                                       tr("Listregions program (listregions.exe)"));
                                                       #endif
    else
        program_listregions =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listregions dat file"),
                                                       ui->lineEdit_program_listregions->text(),
                                                       #if defined(Q_OS_LINUX)
                                                       tr("Listregions program (listregions)"));
                                                       #else
                                                       tr("Listregions program (listregions.exe)"));
                                                       #endif

    if(program_listregions.length()==0)
    {
        launchMessageBox(tr("No listregions program was selected"),true);
    }
    else
    {
        ui->lineEdit_program_listregions->setText(program_listregions);
    }
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////




void MainWindow::on_lineEdit_program_listfiles_editingFinished()
{
    if(ui->lineEdit_program_listfiles->text().length()==0)
    {
        ui->statusBar->showMessage(tr("WARNING: No listfiles program selected"),10000);
        //if(ui->lineEdit_program_listfiles->hasFocus()==false)
        //launchMessageBox(tr("WARNING: No listfiles program selected"),true);
        ENABLE_PROGLISTFILES=false;
        ui->pushButton_create_listfilesdat->setEnabled(false);
    }
    else if(get_program_response(ui->lineEdit_program_listfiles->text()," --help")==false)
    {
        launchMessageBox(tr("WARNING: The program ")+ui->lineEdit_program_listfiles->text()+tr(" is invalid listfiles program"),true);
        ui->lineEdit_program_listfiles->setText("");
        ENABLE_PROGLISTFILES=false;
        ui->pushButton_create_listfilesdat->setEnabled(false);
    }
    else
    {
        ENABLE_PROGLISTFILES=true;
        if(ui->pushButton_generate_outfiles->isEnabled())
        ui->pushButton_create_listfilesdat->setEnabled(true);
    }
}


void MainWindow::on_lineEdit_program_listregions_editingFinished()
{
    if(ui->lineEdit_program_listregions->text().length()==0)
    {
        ui->statusBar->showMessage(tr("WARNING: No listregions program selected"),10000);
        ENABLE_PROGLISTREGIONS=false;
        ui->pushButton_create_listregionsdat->setEnabled(false);
    }
    else if(get_program_response(ui->lineEdit_program_listregions->text()," --help")==false)
    {
        launchMessageBox(tr("WARNING: The program ")+ui->lineEdit_program_listregions->text()+tr(" is invalid listregions program"),true);
        ui->lineEdit_program_listregions->setText("");
        ENABLE_PROGLISTREGIONS=false;
        ui->pushButton_create_listregionsdat->setEnabled(false);
    }
    else
    {
        ENABLE_PROGLISTREGIONS=true;
        if(ui->pushButton_generate_outfiles->isEnabled())
        ui->pushButton_create_listregionsdat->setEnabled(true);
    }
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////



void MainWindow::on_pushButton_color_region_clicked()
{
    QColor color = QColorDialog::getColor(this->color_region, this );
    if( color.isValid() )
    {
        this->color_region=color;
        this->pen_region =QPen(this->color_region);


        QIcon *icop = new QIcon();
        QPixmap pmp=QPixmap(32,32); pmp.fill(this->color_region);
        icop->addPixmap(pmp,QIcon::Normal,QIcon::On);
        ui->pushButton_color_region->setIcon(*icop);

        QString tmp("("+QString::number(color.red())+","+QString::number(color.green())+","+QString::number(color.blue())+")");
        ui->pushButton_color_region->setText(tmp);
    }

}
