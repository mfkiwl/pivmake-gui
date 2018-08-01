#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString get_program_listfiles(QString programpath);
    QString get_program_listregions(QString programpath);
    bool launch_program(QString programpath,QString param);


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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
