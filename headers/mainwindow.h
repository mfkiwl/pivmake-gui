#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPen>
#include <QColor>

#include <pds/pdsra.h>

class mythread;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



public:


    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    char *progdir;

    mythread *hilo; // Hilo donde se hace el metodo PIV, todo lo demas aqui
                    // son solo ayudas para la interfaz de usuario


    QColor color_region;
    QPen pen_region;


    // lista de imagenes , y regiones a analizar
    // estas variables contienen la entrada de datos.
    QList<QString>       ImageFilePathList;
    QList<PdsRegionRect> RegionRectList;


    // Metodos y variables para verificar si los programas de ayuda
    // listfiles y listregions.
    bool    ENABLE_PROGLISTFILES;   // Indica si fue encontrado el programa listfiles
    bool    ENABLE_PROGLISTREGIONS; // Indica si fue encontrado el programa listregions
    QString get_program_listfiles(QString programpath);     // Intenta encontrar la direccion del programa listfiles
    QString get_program_listregions(QString programpath);   // Intenta encontrar la direccion del programa listregions
    bool    get_program_response(QString programpath,QString param);    //instenta ver si el programa responde.

    // Verifica si los datos fueron completados en la GUI.
    bool check_listregionsdat_value(void);          // (Input) Verifica el archivo de datos de las regiones
    bool check_listfilesdat_value(void);            // (Input) Verifica el archivo de datos de los archivos
    bool check_output_directory_value(void);        // (Output)verifica el directorio de salida
    bool check_output_filename_pattern_value(void); // (Output)verifica el patron de nombre de los archivos de salida


    // funciones de estado
    bool fileExists(QString path);
    bool is_subdirectory(QString filepath,QString dir);


    // funciones para emitir mensajes de salida de datos
    void launchMessageBox(QString str,bool warning=false);
    void set_message_in_listwidget(QString msg,QColor col);


    // funciones de habilitacion y deshabilitacion de widgets.
    void enable_listregions_widgets(bool dat);
    void enable_listfiles_widgets(bool dat);
    void enable_pattern_widgets(bool dat);
    void enable_outdir_widgets(bool dat);
    void enable_generate_all_widgets(bool dat);


private slots:

    /////////////////////////////////////////////////////////////////
    /// slots que son llamados por sinales emitidas por la GUI.
    ///
    void on_checkBox_enable_filename_pattern_clicked(bool checked);

    void on_pushButton_choose_listfilesdat_clicked();

    void on_pushButton_choose_listregionsdat_clicked();

    void on_pushButton_choose_output_directory_clicked();

    void on_pushButton_find_program_listfiles_clicked();

    void on_pushButton_find_program_listregions_clicked();

    void on_lineEdit_program_listfiles_editingFinished();

    void on_lineEdit_program_listregions_editingFinished();

    void on_pushButton_create_listfilesdat_clicked();

    void on_pushButton_create_listregionsdat_clicked();

    void on_lineEdit_listfilesdat_editingFinished();

    void on_lineEdit_listregionsdat_editingFinished();

    void on_pushButton_generate_outfiles_clicked();

    void on_pushButton_color_region_clicked();

    void on_lineEdit_output_directory_editingFinished();

    void on_lineEdit_listfilesdat_textChanged(const QString &arg1);

    void on_lineEdit_listregionsdat_textChanged(const QString &arg1);

    /////////////////////////////////////////////////////////////////
    /// slots que son llamados por sinales emitidas por el hilo.
    ///
    void manual_hilo_progress(int,int,int,int);
    void manual_hilo_workended(void);
    void manual_hilo_workinit(void);
    void manual_hilo_message(QString);
    void manual_hilo_message_red(QString);
    void manual_hilo_message_blue(QString);


    void on_actionAbout_triggered();

    void on_actionDocumentation_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
