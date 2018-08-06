#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPalette>
// #include <QDir>
#include <QFileDialog>

// #include <QDebug>
// #include <QScrollBar>
// #include <pds/pdsdatafunc.h>


void MainWindow::on_checkBox_enable_filename_pattern_clicked(bool checked)
{
    ui->lineEdit_output_filename_pattern->setEnabled(checked);
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
        launchMessageBox(tr("No directory was selected"),true);
    }
    else
    {
        ui->lineEdit_output_directory->setText(outputdir);
    }
}

void MainWindow::on_lineEdit_output_directory_editingFinished()
{
    QPalette palette;
    palette.setColor(QPalette::Base,Qt::white);
    ui->lineEdit_output_directory->setPalette(palette);
}
