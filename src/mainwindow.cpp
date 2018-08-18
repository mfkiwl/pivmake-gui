#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    this->progdir=pds_get_absolute_dirname ();
}

MainWindow::~MainWindow()
{
    delete ui;
}
