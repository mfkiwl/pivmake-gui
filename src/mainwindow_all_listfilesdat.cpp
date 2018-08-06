#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDir>
#include <QFileDialog>

// #include <QDebug>
#include <QPalette>
#include <pds/pdsdatafunc.h>


void MainWindow::on_pushButton_choose_listfilesdat_clicked()
{
    QString  listfilesdat;
    QString  sourcedir;

    if(ui->lineEdit_listfilesdat->text().length()==0)
    {
        if(ui->lineEdit_listregionsdat->text().length()==0)
            sourcedir=QDir::currentPath();
        else
            sourcedir=QFileInfo(ui->lineEdit_listregionsdat->text()).absoluteDir().absolutePath();
    }
    else    sourcedir=ui->lineEdit_listfilesdat->text();

    listfilesdat =  QFileDialog::getOpenFileName(this,
                                                     tr("Select the listfiles dat file"),
                                                     sourcedir,
                                                     tr("Listfiles dat file (*.listfiles);;Generic dat file (*.dat);;Any file (*)"));

    if(listfilesdat.length()==0)
    {
        launchMessageBox(tr("No listfiles dat file was selected"),true);
    }
    else
    {
        ui->lineEdit_listfilesdat->setText(listfilesdat);
        on_lineEdit_listfilesdat_editingFinished();
    }
}



void MainWindow::on_pushButton_create_listfilesdat_clicked()
{
    QString  listfilesdat;
    QString  search_dir_listfiles;

    if(ui->lineEdit_program_listfiles->text().length()==0) return;

    if(ui->lineEdit_listfilesdat->text().length()==0)
    {
        listfilesdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listfiles dat file"),
                                                       QDir::currentPath()+QDir::separator()+ QString("listfilesdata.listfiles"),
                                                       tr("Listfiles dat file (*.listfiles);;Generic dat file (*.dat);;Any file (*)"));

        //Codigo para obter search_dir_listfiles
        QString tmp=listfilesdat;
        QByteArray ba = tmp.toUtf8();
        const char *c_str2 = ba.data();
        if(pds_get_number_of_significative_lines(c_str2)<2)
        {
            QFileInfo fileInfo1(listfilesdat);
            search_dir_listfiles=fileInfo1.dir().path();
            qInfo("pds_get_number_of_significative_lines(c_str2)<2");
        }
        else
        {
            QFileInfo fileInfo1(pds_string_new_significative_line_of_file(c_str2,1));
            search_dir_listfiles=fileInfo1.dir().path();
        }

    }
    else
    {
        listfilesdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listfiles dat file"),
                                                       ui->lineEdit_listfilesdat->text(),
                                                       tr("Listfiles dat file (*.listfiles);;Generic dat file (*.dat);;Any file (*)"));

        //Codigo para obter search_dir_listfiles
        QString tmp=ui->lineEdit_listfilesdat->text();
        QByteArray ba = tmp.toUtf8();
        const char *c_str2 = ba.data();
        char *line=pds_string_new_significative_line_of_file (c_str2,1);
        if(line!=NULL)
        {
            QFileInfo fileInfo1(line);
            search_dir_listfiles=fileInfo1.dir().path();
        }
        else search_dir_listfiles=QString("");
        //qInfo("ui->lineEdit_listfilesdat->text().length()!=0");
    }


    if(listfilesdat.length()==0)
    {
        launchMessageBox(tr("No listfiles dat file was selected"),true);
    }
    else
    {
        ui->lineEdit_listfilesdat->setText(listfilesdat);

        QProcess *myProcess = new QProcess(this);
        QStringList arguments;
        arguments << "--filter" <<"*.bmp"<<
                     "--outfile"<<listfilesdat<<
                     "--rootdir"<<search_dir_listfiles<<"--en-rootdir";
        myProcess->start(ui->lineEdit_program_listfiles->text(),arguments);

    }

    on_lineEdit_listfilesdat_editingFinished();
}


void MainWindow::on_lineEdit_listfilesdat_editingFinished()
{
    if(ui->lineEdit_listfilesdat->text().length()!=0)
    if(ui->lineEdit_output_directory->text().length()==0)
    {
        QString tmp=ui->lineEdit_listfilesdat->text();
        QByteArray ba = tmp.toUtf8();
        const char *c_str2 = ba.data();
        char *cad=pds_get_dirname(c_str2);
        ui->lineEdit_output_directory->setText(QString(cad)+QDir::separator()+QString("output"));
        free(cad);
    }

}

void MainWindow::on_lineEdit_listfilesdat_textChanged(const QString &arg1)
{
    QString lfilesdat=arg1;
    QString lregionsdat=ui->lineEdit_listregionsdat->text();
    QString outdir=ui->lineEdit_output_directory->text();

    if((is_subdirectory(lfilesdat,outdir)==false)&&
       (is_subdirectory(lregionsdat,outdir)==false)&&
       (lfilesdat.length()>0||lregionsdat.length()>0))
    {
        QPalette palette;
        palette.setColor(QPalette::Base,QColor(255, 160, 160));
        ui->lineEdit_output_directory->setPalette(palette);
    }
    else
    {
        QPalette palette;
        palette.setColor(QPalette::Base,Qt::white);
        ui->lineEdit_output_directory->setPalette(palette);
    }
}
