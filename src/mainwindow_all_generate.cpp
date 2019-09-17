#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QScrollBar>

#include "mythread.h"

void MainWindow::on_pushButton_generate_outfiles_clicked()
{
    if(check_listfilesdat_value()==false)
        set_message_in_listwidget(QString(tr("check_listfilesdat_value==false")),Qt::red);
    else if(check_listregionsdat_value()==false)
        set_message_in_listwidget(QString(tr("check_listregionsdat_value==false")),Qt::red);
    else
    {
        set_message_in_listwidget(QString(tr("Working please wait.")),Qt::black);

        // deshabilito el boton GENERATE
        enable_generate_all_widgets(false);

        // Limpiar el listwidget y progressbar
        ui->listWidget->clear();
        ui->progressBar->reset();

        // Creo el hilo
        hilo = new mythread(this);
        hilo->set_pen(pen_region);
        hilo->set_listfilesdat(ImageFilePathList);
        hilo->set_listregionsdat(RegionRectList);
        hilo->set_output_filename_pattern(ui->lineEdit_output_filename_pattern->text());
        hilo->set_output_directory(ui->lineEdit_output_directory->text());
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
}

void MainWindow:: manual_hilo_message(QString msg)
{
    set_message_in_listwidget(msg,Qt::black);
}

void MainWindow:: manual_hilo_message_red(QString msg)
{
    set_message_in_listwidget(msg,Qt::red);
}

void MainWindow:: manual_hilo_message_blue(QString msg)
{
    set_message_in_listwidget(msg,Qt::blue);
}

void MainWindow::manual_hilo_workended(void)
{
    QString msg(tr("Work finalized"));
    enable_generate_all_widgets(true);

    launchMessageBox(msg);
    ui->progressBar->setValue(0);
}

void MainWindow::manual_hilo_workinit(void)
{
    QString msg(tr("Work Initialized"));

    ui->pushButton_generate_outfiles->setEnabled(false);
    set_message_in_listwidget(msg,Qt::black);
    ui->progressBar->setValue(0);
}



