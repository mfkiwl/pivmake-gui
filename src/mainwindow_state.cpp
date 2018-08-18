#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>

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


bool MainWindow::is_subdirectory(QString filepath,QString dir)
{
    QFileInfo fileinf(filepath);
    QDir dirfile(fileinf.absoluteDir().absolutePath());

    QString relative=dirfile.relativeFilePath(dir);

    //qInfo(absdir.toUtf8());

   if(relative.contains(".."))  return false;
   else                         return true;
}


