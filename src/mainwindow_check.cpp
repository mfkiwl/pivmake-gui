#include "mainwindow.h"
#include "ui_mainwindow.h"

// #include <QProcess>
#include <QFile>
// #include <QFileDialog>
#include <QMessageBox>

// #include <QDebug>
// #include <QScrollBar>
#include <pds/pdsdatafunc.h>
#include <pds/pdsra.h>
#include <stdlib.h>

bool MainWindow::check_listregionsdat_value(void)
{
    if(ui->lineEdit_listregionsdat->text().length()==0)
    {
        launchMessageBox(tr("Region list no defined."),true);
        return false;
    }

    QString listregionsdat=ui->lineEdit_listregionsdat->text();
    QByteArray ba = listregionsdat.toLocal8Bit();
    const char *strchar = ba.data();

    int N=pds_get_number_of_significative_lines(strchar);
    if(N<1)
    {
        launchMessageBox(tr("The region list dat file dont have elements. The minimum is 1."),true);
        return false;
    }

    PdsRaNatural nl,nc;
    FILE *fd=fopen(strchar,"r");
    pds_ratools_load_number_of_columns_and_lines (fd,&nc,&nl);
    fclose(fd);

    if(N!=(int)nl)   return false;
    if(4!=nc)   return false;

    RegionRectList.clear();

    PdsRegionRect R;
    fd=fopen(strchar,"r");
    while(feof(fd)==0)
    {
        int ID=pds_region_rect_next_nospace_fscanf(fd,&R);
        if(ID==PDS_OK)  RegionRectList.append(R);
        else
        {
            RegionRectList.clear();
            return false;
        }
    }
    fclose(fd);

    return true;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

bool MainWindow::check_listfilesdat_value(void)
{
    if(ui->lineEdit_listfilesdat->text().length()==0)
    {
        launchMessageBox(tr("Images list no defined."),true);
        return false;
    }

    QString listfilesdat=ui->lineEdit_listfilesdat->text();
    QByteArray ba = listfilesdat.toLocal8Bit();
    const char *strchar = ba.data();

    int N=pds_get_number_of_significative_lines(strchar);
    if(N<2)
    {
        launchMessageBox(tr("The images list dat file dont have elements. The minimum is 2."),true);

        return false;
    }

    ImageFilePathList.clear();

    QFile inputFile(listfilesdat);
    if ( inputFile.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
       while (!inputFile.atEnd())
       {
          // Returns a string that has whitespace removed from the start and the end.
          QString imagePath = inputFile.readLine().trimmed();

          if(imagePath.length()>0)
          {
              if(fileExists(imagePath)==true)
              {
                  ImageFilePathList.append(imagePath);
              }
              else
              {
                  launchMessageBox(tr("The image <<")+imagePath+tr(">> No exist"),true);
                  ImageFilePathList.clear();
                  return false;
              }
          }
       }
       inputFile.close();
    }
    else return false;

    return true;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

bool MainWindow::check_output_directory_value(void)
{
    if(ui->lineEdit_output_directory->text().length()==0)
        return false;

    return true;
}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

bool MainWindow::check_output_filename_pattern_value(void)
{
    if(ui->lineEdit_output_filename_pattern->text().length()==0)
        return false;

    return true;
}
