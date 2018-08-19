#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <pds/pdsdatafunc.h>

#include <QDebug>

QString MainWindow::get_program_listfiles(QString programpath)
{

    if(programpath.length()==0)
    {
        ////////////////////////////////
        /// Busco en el path del sistema
        #if defined(Q_OS_LINUX)
        programpath="listfiles";
        #else
        programpath="listfiles.exe";
        #endif
        if(get_program_response(programpath," --help")==true)    return programpath;

        //////////////////////////////////////
        /// Defino directorio de busqueda al directrio del programa
        char * absdir=pds_get_absolute_dirname();
        if(absdir==NULL)    return QString("");
        #if defined(Q_OS_LINUX)
        programpath=QString(absdir)+QDir::separator()+"listfiles";
        #else
        programpath=QString(absdir)+QDir::separator()+"listfiles.exe";
        #endif
        free(absdir);

    }

    if(get_program_response(programpath," --help")==true)    return programpath;
    else                                                     return QString("");

}

///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

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

        if(get_program_response(programpath," --help")==true)    return programpath;

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

    if(get_program_response(programpath," --help")==true)    return programpath;
    else                                               return QString("");
}


///////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////

#include <QProcess>

bool MainWindow::get_program_response(QString programpath,QString param)
{
    if(programpath.length()==0)
    {
        return false;
    }
    else
    {
        QProcess program;

        #if defined(Q_OS_LINUX)
        QString commandToStart= programpath + " "+param;
        #else
        QString commandToStart= "\""+programpath+"\""+ " "+param;
        #endif
        //QStringList environment = program.systemEnvironment();
        program.start(commandToStart.toUtf8().data());

        //qDebug() <<"get_program_response()"<<commandToStart.toUtf8().data();
        bool started = program.waitForStarted();
        if (!program.waitForFinished(10000)) // 10 Second timeout
            program.kill();

        int exitCode = program.exitCode();
        //QString stdOutput = QString::fromLocal8Bit(program.readAllStandardOutput());
        //qDebug() <<"stdOutput"<<stdOutput;
        //QString stdError = QString::fromLocal8Bit(program.readAllStandardError());
        //qDebug() <<"stdError"<<stdError;

        if((started==true)&&(exitCode==EXIT_SUCCESS))
        {
            return true;
        }
        else    return false;

    }
}


