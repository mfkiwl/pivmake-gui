#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QObject>
#include <pds/pdsra.h>
#include <QPen>

class mythread : public QThread
{
    Q_OBJECT
public:
    QList<QString> ImageFilePathList;
    QList<PdsRegionRect> RegionRectList;
    QString output_filename_pattern;
    QString output_directory;
    QPen RegionPen;
    QString output_file_format;

    explicit mythread(QObject *parent=0);

    bool set_listfilesdat(QList<QString> ImagePathList);
    bool set_listregionsdat(QList<PdsRegionRect> RegionList);
    bool set_output_filename_pattern(QString pattern);
    bool set_output_directory(QString directory);
    bool set_pen(QPen regionpen);
    bool set_output_file_format(QString ext);



    QString get_listregionsdat_output_filename(QString ,QString ,int );
    QColor get_qcolor_from(double min,double max,double val);
    bool drawVerticalColorBar(QString filepath,unsigned int W,unsigned int H,double dmin,double dmax );


    bool save_region_list(QString ,QList<PdsRegionRect> );
    bool save_image_region_list(QString inputfilepath,QString outputfilepath, QList<PdsRegionRect> InputRegionList,bool ENABLE_TEXT);

    bool save_image_region_list_distance( QString ImagePath,
                                          QString directory,
                                          QString pattern,
                                          QList<PdsRegionRect> RegionListInit,
                                          QList<PdsRegionRect> RegionListEnd);

    bool save_region_list_plot( QString directory,
                                QString output_filename_pattern,
                                QList< QList<PdsRegionRect> > RegionListList);

    bool save_image_region_list_pcolor(   QString ImagePath,
                                          QString directory,
                                          QString pattern,
                                          QList<PdsRegionRect> RegionListInit,
                                          QList<PdsRegionRect> RegionListEnd,
                                          bool ENABLE_TEXT);

    PdsMatrix *matrix_from_image_filepath(QString filepath);

signals:
    void signal_mythread_progress(int imageid,int regionid,int imageM,int regionN);
    void signal_mythread_workended(void);
    void signal_mythread_message(QString msg);
    void signal_mythread_message_red(QString msg);
    void signal_mythread_message_blue(QString msg);
    void signal_mythread_workinit(void);

protected:
    void run();
};

#endif // MYTHREAD_H
