#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QProcess>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>
#include <QScrollBar>
#include <pds/pdsdatafunc.h>

#include "mythread.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ImageFilePathList.clear();
    RegionRectList.clear();

    this->color_region =QColor(255,  0,0);
    this->pen_region   =QPen(this->color_region);
    this->pen_region.setWidth(3);

    ENABLE_PROGLISTFILES=false;
    ENABLE_PROGLISTREGIONS=false;
    ui->pushButton_create_listfilesdat->setEnabled(false);
    ui->pushButton_create_listregionsdat->setEnabled(false);
    QString program_listfiles  =get_program_listfiles("");
    QString program_listregions=get_program_listregions("");

    if(program_listfiles.length()!=0)
    {
        ui->lineEdit_program_listfiles->setText(program_listfiles);
        ui->pushButton_create_listfilesdat->setEnabled(true);
    }
    if(program_listregions.length()!=0)
    {
        ui->lineEdit_program_listregions->setText(program_listregions);
        ui->pushButton_create_listregionsdat->setEnabled(true);
    }

    QIcon *icop = new QIcon();
    QPixmap pmp=QPixmap(32,32); pmp.fill(this->color_region);
    icop->addPixmap(pmp,QIcon::Normal,QIcon::On);
    ui->pushButton_color_region->setIcon(*icop);

    this->setWindowTitle(QString(APP_TARGET)+" "+QString(APP_VERSION));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchMessageBox(QString str,bool warning)
{
    QString msg(str);
    QMessageBox Msgbox;
    if(warning==true)   Msgbox.setIcon(QMessageBox::Warning);
    else                Msgbox.setIcon(QMessageBox::Information);
    Msgbox.setText(msg);
    Msgbox.exec();
}
bool MainWindow::fileExists(QString path)
{
    QFileInfo check_file(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (check_file.exists() && check_file.isFile()) {
        return true;
    } else {
        return false;
    }
}
///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

bool MainWindow::get_program_response(QString programpath,QString param)
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
            //qInfo("OK ejecutado programa:" +programpath.toUtf8()+"\n");
            return true;
        }
        else    return false;

    }
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

void MainWindow::set_message_in_listwidget(QString msg,QColor col)
{
    // Agregar  novo menssagem
    ui->listWidget->addItem(msg);
    ui->listWidget->item(ui->listWidget->count()-1)->setForeground(col);
    QScrollBar *vb = ui->listWidget->verticalScrollBar();
    while(vb->value()< vb->maximum())
    vb->setValue(vb->maximum()); // Scrolls to the bottom
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

bool MainWindow::is_subdirectory(QString filepath,QString dir)
{
    QFileInfo fileinf(filepath);
    QDir dirfile(fileinf.absoluteDir().absolutePath());

    QString relative=dirfile.relativeFilePath(dir);

    //qInfo(absdir.toUtf8());

   if(relative.contains(".."))  return false;
   else                         return true;
}



