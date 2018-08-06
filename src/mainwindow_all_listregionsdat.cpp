#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDir>
#include <QFileDialog>

// #include <QDebug>
// #include <QScrollBar>
#include <pds/pdsdatafunc.h>

void MainWindow::on_pushButton_choose_listregionsdat_clicked()
{
    QString  listregionsdat;
    QString  sourcedir;

    if(ui->lineEdit_listregionsdat->text().length()==0)
    {
        if(ui->lineEdit_listfilesdat->text().length()==0)
            sourcedir=QDir::currentPath();
        else
            sourcedir=QFileInfo(ui->lineEdit_listfilesdat->text()).absoluteDir().absolutePath();
    }
    else    sourcedir=ui->lineEdit_listregionsdat->text();

    listregionsdat =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listregions dat file"),
                                                       sourcedir,
                                                       tr("Listregions dat file (*.listregions);;Generic dat file (*.dat);;Any file (*)"));

    if(listregionsdat.length()==0)
    {
        launchMessageBox(tr("No listregions dat file was selected"),true);
    }
    else
    {
        ui->lineEdit_listregionsdat->setText(listregionsdat);
        on_lineEdit_listregionsdat_editingFinished();
    }
}

void MainWindow::on_pushButton_create_listregionsdat_clicked()
{
    QString  listregionsdat;
    QString  rootlistregionsimage;

    if(ui->lineEdit_program_listregions->text().length()==0) return;

    if(ui->lineEdit_listregionsdat->text().length()==0)
    {
        QFileInfo basedir(ui->lineEdit_listfilesdat->text());

        listregionsdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listregions dat file"),
                                                       basedir.dir().path()+QDir::separator()+ QString("listregionsdata.listregions"),
                                                       tr("Listregions dat file (*.listregions);;Generic dat file (*.dat);;Any file (*)"));
    }
    else
    {
        listregionsdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listregions dat file"),
                                                       ui->lineEdit_listregionsdat->text(),
                                                       tr("listregions dat file (*.listregions);;Generic dat file (*.dat);;Any file (*)"));

    }

    if(ui->lineEdit_listfilesdat->text().length()==0)
    {
        rootlistregionsimage=QString("");
    }
    else
    {
        QString tmp=ui->lineEdit_listfilesdat->text();
        QByteArray ba = tmp.toUtf8();
        const char *c_str2 = ba.data();

        char *line=pds_string_new_significative_line_of_file (c_str2,1);
        if(line!=NULL)  rootlistregionsimage=QString(line);
        else            rootlistregionsimage=QString("");
    }


    if(listregionsdat.length()==0)
    {
        launchMessageBox(tr("No listregions dat file was selected"),true);
    }
    else
    {
        ui->lineEdit_listregionsdat->setText(listregionsdat);

        QProcess *myProcess = new QProcess(this);
        QStringList arguments;
        arguments << "--outfile"<<listregionsdat<<
                     "--rootimage"<<rootlistregionsimage<<"--en-rootimage";
        myProcess->start(ui->lineEdit_program_listregions->text(),arguments);
        //qInfo("<<"+rootlistregionsimage.toUtf8()+">>");
        //qInfo("<<"+listregionsdat.toUtf8()+">>");

    }

    on_lineEdit_listregionsdat_editingFinished();
}

void MainWindow::on_lineEdit_listregionsdat_editingFinished()
{
    if(ui->lineEdit_listregionsdat->text().length()!=0)
    if(ui->lineEdit_output_directory->text().length()==0)
    {
        QString tmp=ui->lineEdit_listregionsdat->text();
        QByteArray ba = tmp.toUtf8();
        const char *c_str2 = ba.data();
        char *cad=pds_get_dirname(c_str2);
        ui->lineEdit_output_directory->setText(QString(cad)+QDir::separator()+QString("output"));
        free(cad);
    }
}

void MainWindow::on_lineEdit_listregionsdat_textChanged(const QString &arg1)
{
    QString lfilesdat=ui->lineEdit_listfilesdat->text();
    QString lregionsdat=arg1;
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
