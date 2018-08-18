#include "mainwindow.h"
#include "ui_mainwindow.h"


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
