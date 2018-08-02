#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>

#include <pds/pdsdatafunc.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString program_listfiles  =get_program_listfiles("");
    QString program_listregions=get_program_listregions("");

    if(program_listfiles.length()!=0)   ui->lineEdit_program_listfiles->setText(program_listfiles);
    if(program_listregions.length()!=0) ui->lineEdit_program_listregions->setText(program_listregions);

    //qInfo("program_listfiles:"+program_listfiles.toLatin1()+"\n");
    //qInfo("program_listregions:"+program_listregions.toLatin1()+"\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::launch_program(QString programpath,QString param)
{
    if(programpath.length()==0)
    {
        return false;
    }
    else
    {
        QProcess program;

        QString commandToStart= programpath + " "+param;
        //QStringList environment = program.systemEnvironment();
        program.start(commandToStart);

        bool started = program.waitForStarted();
        if (!program.waitForFinished(10000)) // 10 Second timeout
            program.kill();

        int exitCode = program.exitCode();
        //QString stdOutput = QString::fromLocal8Bit(program.readAllStandardOutput());
        //QString stdError = QString::fromLocal8Bit(program.readAllStandardError());

        if((started==true)&&(exitCode==EXIT_SUCCESS))
        {
            //qInfo("OK ejecutado programa:" +programpath.toLatin1()+"\n");
            return true;
        }
        else    return false;

    }
}


QString MainWindow::get_program_listfiles(QString programpath)
{

    if(programpath.length()==0)
    {
        ////////////////////////////////
        /// Busco en el ath del sistema
        #if defined(Q_OS_LINUX)
        programpath="listfiles";
        #else
        programpath="listfiles.exe";
        #endif

        if(launch_program(programpath," --help")==true)    return programpath;

        //////////////////////////////////////
        /// Busco en eldirectrio del programa
        char * absdir=pds_get_absolute_dirname();
        if(absdir==NULL)    return QString("");

        #if defined(Q_OS_LINUX)
        programpath=QString(absdir)+QDir::separator()+"listfiles";
        #else
        programpath=QString(absdir)+QDir::separator()+"listfiles.exe";
        #endif

        free(absdir);

    }

    if(launch_program(programpath," --help")==true)    return programpath;
    else                                               return QString("");

}

QString MainWindow::get_program_listregions(QString programpath)
{

    if(programpath.length()==0)
    {
        ////////////////////////////////
        /// Busco en el ath del sistema
        #if defined(Q_OS_LINUX)
        programpath="listregions";
        #else
        programpath="listregions.exe";
        #endif

        if(launch_program(programpath," --help")==true)    return programpath;

        //////////////////////////////////////
        /// Busco en eldirectrio del programa
        char * absdir=pds_get_absolute_dirname();
        if(absdir==NULL)    return QString("");

        #if defined(Q_OS_LINUX)
        programpath=QString(absdir)+QDir::separator()+"listregions";
        #else
        programpath=QString(absdir)+QDir::separator()+"listregions.exe";
        #endif

        free(absdir);

    }

    if(launch_program(programpath," --help")==true)    return programpath;
    else                                               return QString("");
}

void MainWindow::on_checkBox_enable_filename_pattern_clicked(bool checked)
{
    ui->lineEdit_output_filename_pattern->setEnabled(checked);
}

void MainWindow::on_pushButton_choose_listfilesdat_clicked()
{
    QString  listfilesdat;
    if(ui->lineEdit_listfilesdat->text().length()==0)
        listfilesdat =  QFileDialog::getOpenFileName(this,
                                                     tr("Select the listfiles dat file"),
                                                     QDir::currentPath(),
                                                     tr("Listfiles dat file (*.dat);;Listfiles dat file (*.listfiles);;Any file (*)"));
    else
        listfilesdat =  QFileDialog::getOpenFileName(this,
                                                     tr("Select the listfiles dat file"),
                                                     ui->lineEdit_listfilesdat->text(),
                                                     tr("Listfiles dat file (*.dat);;Listfiles dat file (*.listfiles);;Any file (*)"));

    if(listfilesdat.length()==0)
    {
        QString msg(tr("No listfiles dat file was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else
    {
        ui->lineEdit_listfilesdat->setText(listfilesdat);
    }
}

void MainWindow::on_pushButton_choose_listregionsdat_clicked()
{
    QString  listregionsdat;
    if(ui->lineEdit_listregionsdat->text().length()==0)
        listregionsdat =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listregions dat file"),
                                                       QDir::currentPath(),
                                                       tr("Listregions dat file (*.dat);;Listregions dat file (*.listregions);;Any file (*)"));
    else
        listregionsdat =  QFileDialog::getOpenFileName(this,
                                                       tr("Select the listregions dat file"),
                                                       ui->lineEdit_listregionsdat->text(),
                                                       tr("Listregions dat file (*.dat);;Listregions dat file (*.listregions);;Any file (*)"));

    if(listregionsdat.length()==0)
    {
        QString msg(tr("No listregions dat file was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else
    {
        ui->lineEdit_listregionsdat->setText(listregionsdat);
    }
}

void MainWindow::on_pushButton_choose_output_directory_clicked()
{
    QString  outputdir;
    if(ui->lineEdit_output_directory->text().length()==0)
    {
        if(ui->lineEdit_listregionsdat->text().length()!=0)
            outputdir =  QFileDialog::getExistingDirectory(this, tr("Select the output directory"), ui->lineEdit_listregionsdat->text());
        else if(ui->lineEdit_listfilesdat->text().length()!=0)
            outputdir =  QFileDialog::getExistingDirectory(this, tr("Select the output directory"), ui->lineEdit_listfilesdat->text());
        else
            outputdir =  QFileDialog::getExistingDirectory(this, tr("Select the output directory"), QDir::currentPath());

    }
    else
        outputdir =  QFileDialog::getExistingDirectory(this, tr("Select the output directory"), ui->lineEdit_output_directory->text());

    if(outputdir.length()==0)
    {
        QString msg(tr("No directory was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else
    {
        ui->lineEdit_output_directory->setText(outputdir);
    }
}

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
        QString msg(tr("No listfiles program was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
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
        QString msg(tr("No listregions program was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else
    {
        ui->lineEdit_program_listregions->setText(program_listregions);
    }
}

void MainWindow::on_lineEdit_program_listfiles_editingFinished()
{
    if(ui->lineEdit_program_listfiles->text().length()==0)
    {
        QString msg(tr("WARNING: No listfiles program selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }

    if(launch_program(ui->lineEdit_program_listfiles->text()," --help")==false)
    {
        QString msg(tr("WARNING: The program ")+ui->lineEdit_program_listfiles->text()+tr(" is invalid listfiles program"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
}

void MainWindow::on_lineEdit_program_listregions_editingFinished()
{
    if(ui->lineEdit_program_listregions->text().length()==0)
    {
        QString msg(tr("WARNING: No listregions program selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else if(launch_program(ui->lineEdit_program_listregions->text()," --help")==false)
    {
        QString msg(tr("WARNING: The program ")+ui->lineEdit_program_listregions->text()+tr(" is invalid listregions program"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
}

void MainWindow::on_pushButton_create_listfilesdat_clicked()
{
    QString  listfilesdat;
    QString  searchlistfilesdir;

    if(ui->lineEdit_listfilesdat->text().length()==0)
    {
        listfilesdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listfiles dat file"),
                                                       QDir::currentPath()+QDir::separator()+ QString("listfiles.dat"),
                                                       tr("listfiles dat file (*.dat);;listfiles dat file (*.listfiles);;Any file (*)"));
        QFileInfo fileInfo1(listfilesdat);
        searchlistfilesdir=fileInfo1.dir().path();
    }
    else
    {
        listfilesdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listfiles dat file"),
                                                       ui->lineEdit_listfilesdat->text(),
                                                       tr("listfiles dat file (*.dat);;listfiles dat file (*.listfiles);;Any file (*)"));
        QString tmp=ui->lineEdit_listfilesdat->text();
        QByteArray ba = tmp.toLatin1();
        const char *c_str2 = ba.data();

        char *line=pds_string_new_significative_line_of_file (c_str2,1);
        if(line!=NULL)
        {
            QFileInfo fileInfo1(line);
            searchlistfilesdir=fileInfo1.dir().path();
        }
        else searchlistfilesdir=QString("");
    }


    if(listfilesdat.length()==0)
    {
        QString msg(tr("No listfiles dat file was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else
    {
        ui->lineEdit_listfilesdat->setText(listfilesdat);

        QProcess *myProcess = new QProcess(this);
        QStringList arguments;
        arguments << "--filter" <<"*.bmp"<<
                     "--outfile"<<listfilesdat<<
                     "--rootdir"<<searchlistfilesdir<<"--en-rootdir";
        myProcess->start(ui->lineEdit_program_listfiles->text(),arguments);

    }


}

void MainWindow::on_pushButton_create_listregionsdat_clicked()
{
    QString  listregionsdat;
    QString  rootlistregionsimage;

    if(ui->lineEdit_listregionsdat->text().length()==0)
    {
        QFileInfo basedir(ui->lineEdit_listfilesdat->text());

        listregionsdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listregions dat file"),
                                                       basedir.dir().path()+QDir::separator()+ QString("listregions.dat"),
                                                       tr("listregions dat file (*.dat);;listregions dat file (*.listregions);;Any file (*)"));
    }
    else
    {
        listregionsdat =  QFileDialog::getSaveFileName(this,
                                                       tr("Save the listregions dat file"),
                                                       ui->lineEdit_listregionsdat->text(),
                                                       tr("listregions dat file (*.dat);;listregions dat file (*.listregions);;Any file (*)"));

    }

    if(ui->lineEdit_listfilesdat->text().length()==0)
    {
        rootlistregionsimage=QString("");
    }
    else
    {
        QString tmp=ui->lineEdit_listfilesdat->text();
        QByteArray ba = tmp.toLatin1();
        const char *c_str2 = ba.data();

        char *line=pds_string_new_significative_line_of_file (c_str2,1);
        if(line!=NULL)  rootlistregionsimage=QString(line);
        else            rootlistregionsimage=QString("");
    }


    if(listregionsdat.length()==0)
    {
        QString msg(tr("No listregions dat file was selected"));
        QMessageBox Msgbox;
        Msgbox.setText(msg);
        Msgbox.exec();
    }
    else
    {
        ui->lineEdit_listregionsdat->setText(listregionsdat);

        QProcess *myProcess = new QProcess(this);
        QStringList arguments;
        arguments << "--outfile"<<listregionsdat<<
                     "--rootimage"<<rootlistregionsimage<<"--en-rootimage";
        myProcess->start(ui->lineEdit_program_listregions->text(),arguments);

    }


}
