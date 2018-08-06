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
    bool ENABLE_PROGLISTFILES;
    bool ENABLE_PROGLISTREGIONS;
    mythread *hilo;

    QList<QString> ImageFilePathList;
    QList<PdsRegionRect> RegionRectList;

    QColor color_region;
    QPen pen_region;

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString get_program_listfiles(QString programpath);
    QString get_program_listregions(QString programpath);
    bool get_program_response(QString programpath,QString param);

    bool check_listregionsdat_value(void);
    bool check_listfilesdat_value(void);
    bool check_output_directory_value(void);
    bool check_output_filename_pattern_value(void);

    bool fileExists(QString path);
    bool is_subdirectory(QString filepath,QString dir);

    void launchMessageBox(QString str,bool warning=false);
    void set_message_in_listwidget(QString msg,QColor col);


    void enable_listregions_widgets(bool dat);
    void enable_listfiles_widgets(bool dat);
    void enable_pattern_widgets(bool dat);
    void enable_outdir_widgets(bool dat);
    void enable_generate_all_widgets(bool dat);



private slots:
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

    ///////////////////////////////////////////////////////////
    void manual_hilo_progress(int,int,int,int);
    void manual_hilo_workended(void);
    void manual_hilo_workinit(void);
    void manual_hilo_message(QString);
    void manual_hilo_message_red(QString);
    void manual_hilo_message_blue(QString);

    void on_pushButton_color_region_clicked();

    void on_lineEdit_output_directory_editingFinished();

    void on_lineEdit_listfilesdat_textChanged(const QString &arg1);

    void on_lineEdit_listregionsdat_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
