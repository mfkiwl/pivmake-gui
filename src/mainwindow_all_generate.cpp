#include "mainwindow.h"
#include "ui_mainwindow.h"

// #include <QProcess>
// #include <QDir>
// #include <QFileDialog>

#include <QDebug>
#include <QScrollBar>
// #include <QScrollBar>
// #include <pds/pdsdatafunc.h>

#include "mythread.h"

void MainWindow::on_pushButton_generate_outfiles_clicked()
{
    if(check_listfilesdat_value()==true)
    if(check_listregionsdat_value()==true)
    {
        // deshabilito el boton GENERATE
        enable_generate_all_widgets(false);

        // Limpiar el listwidget
        ui->listWidget->clear();
        ui->progressBar->reset();

        // Creo el hilo
        hilo = new mythread(this);
        hilo->set_pen(pen_region);
        hilo->set_listfilesdat(ImageFilePathList);
        hilo->set_listregionsdat(RegionRectList);
        hilo->set_output_filename_pattern(ui->lineEdit_output_filename_pattern->text());
        hilo->set_output_directory(ui->lineEdit_output_directory->text());
        hilo->set_output_enable_text(ui->checkBox_show_region_id->isChecked());
        if(ui->comboBox_output_image_type->currentIndex()==0)
            hilo->set_output_file_format(".png");
        else
            hilo->set_output_file_format(".bmp");

        hilo->start(QThread::HighPriority);

        connect(hilo,SIGNAL(signal_mythread_progress(int,int,int,int)),this,SLOT(manual_hilo_progress(int,int,int,int)) );
        connect(hilo,SIGNAL(signal_mythread_workended())              ,this,SLOT(manual_hilo_workended()) );
        connect(hilo,SIGNAL(signal_mythread_workinit())               ,this,SLOT(manual_hilo_workinit()) );
        connect(hilo,SIGNAL(signal_mythread_message(QString))         ,this,SLOT(manual_hilo_message(QString)) );
        connect(hilo,SIGNAL(signal_mythread_message_red(QString))     ,this,SLOT(manual_hilo_message_red(QString)) );
        connect(hilo,SIGNAL(signal_mythread_message_blue(QString))    ,this,SLOT(manual_hilo_message_blue(QString)) );
    }
}

void MainWindow::manual_hilo_progress(int i,int j,int M,int N)
{
    QString msg(tr("Analyzed image ")+QString::number(i+1)+tr(" of ")+QString::number(M)+
                tr(" :: Region ")+QString::number(j+1)+tr(" of ")+QString::number(N));

    set_message_in_listwidget(msg,Qt::black);

    ui->progressBar->setValue((((i-1)*N+j+1)*100)/((M-1)*N));

    //qInfo(msg.toUtf8());
}

void MainWindow:: manual_hilo_message(QString msg)
{
    set_message_in_listwidget(msg,Qt::black);
    //qInfo(msg.toUtf8());
}

void MainWindow:: manual_hilo_message_red(QString msg)
{
    set_message_in_listwidget(msg,Qt::red);
    //qInfo(msg.toUtf8());
}

void MainWindow:: manual_hilo_message_blue(QString msg)
{
    set_message_in_listwidget(msg,Qt::blue);
    //qInfo(msg.toUtf8());
}
void MainWindow::manual_hilo_workended(void)
{
    QString msg(tr("Work finalized"));
    enable_generate_all_widgets(true);

    launchMessageBox(msg);
    ui->progressBar->setValue(0);

    //qInfo(msg.toUtf8());
}

void MainWindow::manual_hilo_workinit(void)
{
    QString msg(tr("Work Initialized"));

    ui->pushButton_generate_outfiles->setEnabled(false);
    set_message_in_listwidget(msg,Qt::black);
    ui->progressBar->setValue(0);

    //qInfo(msg.toUtf8());
}



void MainWindow::enable_listregions_widgets(bool dat)
{
    ui->lineEdit_listregionsdat->setEnabled(dat);
    ui->pushButton_choose_listregionsdat->setEnabled(dat);
    if(ENABLE_PROGLISTREGIONS==true) ui->pushButton_create_listregionsdat->setEnabled(dat);
}
void MainWindow::enable_listfiles_widgets(bool dat)
{
    ui->lineEdit_listfilesdat->setEnabled(dat);
    ui->pushButton_choose_listfilesdat->setEnabled(dat);
    if(ENABLE_PROGLISTFILES==true) ui->pushButton_create_listfilesdat->setEnabled(dat);
}
void MainWindow::enable_pattern_widgets(bool dat)
{
    ui->lineEdit_output_filename_pattern->setEnabled(false);
    ui->checkBox_enable_filename_pattern->setChecked(false);

    ui->checkBox_enable_filename_pattern->setEnabled(dat);
}
void MainWindow::enable_outdir_widgets(bool dat)
{
    ui->lineEdit_output_directory->setEnabled(dat);
    ui->pushButton_choose_output_directory->setEnabled(dat);
}
void MainWindow::enable_generate_all_widgets(bool dat)
{
    ui->pushButton_generate_outfiles->setEnabled(dat);
    enable_pattern_widgets(dat);
    enable_listregions_widgets(dat);
    enable_listfiles_widgets(dat);
    enable_outdir_widgets(dat);
}
