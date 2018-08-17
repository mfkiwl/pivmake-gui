#include "mythread.h"
#include <stdio.h>
#include <pds/pdsra.h>
#include <pds/pdsdic.h>
#include <QDir>
#include <QImage>
#include <QPainter>
#include <QTextStream>
#include <QFont>
#include <math.h>

mythread::mythread(QObject *parent):QThread(parent)
{
    ImageFilePathList.clear();
    RegionRectList.clear();
    output_filename_pattern.clear();
    output_directory.clear();
    enable_text=true;
    output_file_format=QString(".png");
}

void mythread::run()
{
    QList<PdsRegionRect> InputRegionList;
    QList<PdsRegionRect> OutputRegionList;

    if(ImageFilePathList.length()>1)
    if(RegionRectList.length()>0)
    if(output_filename_pattern.length()>0)
    if(output_directory.length()>0)
    {
        emit signal_mythread_workinit();

        int M=ImageFilePathList.length();
        int N=RegionRectList.length();

        OutputRegionList=RegionRectList;

        QString imagepath=ImageFilePathList.at(0);
        PdsMatrix *Mat0=matrix_from_image_filepath(imagepath);
        if(Mat0!=NULL)  emit signal_mythread_message_blue(QString(tr("\nLoaded the image:: "))+imagepath);
        else            emit signal_mythread_message_red(QString(tr("\nERROR Loaded the image:: "))+imagepath);

        PdsDic2D *DIC=pds_dic2d_new_from_matrices(Mat0,Mat0);
        if(DIC!=NULL)   emit signal_mythread_message(tr("Written the image in the DIC structure."));
        else            emit signal_mythread_message_red(tr("ERROR writing the image in the DIC structure."));


        pds_dic2d_set_no_moved_threshold(DIC,0.98);

        QString outfilepath=get_listregionsdat_output_filename(output_directory,output_filename_pattern,1);
        save_region_list(outfilepath,OutputRegionList);
        save_image_region_list(imagepath,outfilepath,OutputRegionList);

        emit signal_mythread_message_blue(QString(tr("Writing the regions in the file: "))+outfilepath);

        for(int i=1;i<M;i++)
        {
            InputRegionList=OutputRegionList;

            imagepath=ImageFilePathList.at(i);
            PdsMatrix *Mat=matrix_from_image_filepath(imagepath);
            if(Mat!=NULL)   emit signal_mythread_message_blue(QString(tr("\nLoaded the image:: "))+imagepath);
            else            emit signal_mythread_message_red(QString(tr("\nERROR Loaded the image:: "))+imagepath);

            if(pds_dic2d_push_matrix(DIC,Mat)==PDS_OK)
            {
                emit signal_mythread_message(tr("Written the image in the DIC structure."));

                for(int j=0;j<N;j++)
                {
                    PdsRegionRect Rout=pds_region_rect(0,0,0,0);
                    PdsRegionRect Rin=InputRegionList.at(j);

                    int ID=pds_dic2d_tracking_region(DIC,Rin,&Rout);
                    if(ID==PDS_DIC2D_ERROR)
                    {
                        emit signal_mythread_message_red(tr("Memory ERROR tracking the region."));
                        break;
                    }
                    else
                    {
                        OutputRegionList.replace(j,Rout);
                        emit signal_mythread_progress(i,j,M,N);
                    }
                }
                QString outfilepath=get_listregionsdat_output_filename(output_directory,output_filename_pattern,i+1);
                save_region_list(outfilepath,OutputRegionList);
                save_image_region_list(imagepath,outfilepath,OutputRegionList);
                emit signal_mythread_message_blue(QString(tr("Writing the regions in the file: "))+outfilepath);
            }
            else
            {
                emit signal_mythread_message_red(tr("ERROR writing the image in the DIC structure."));
            }

            pds_matrix_free(Mat);
        }

        save_image_region_list_distance(ImageFilePathList.at(0),output_directory,output_filename_pattern,RegionRectList,OutputRegionList);
        save_image_region_list_pcolor(ImageFilePathList.at(0),output_directory,output_filename_pattern,RegionRectList,OutputRegionList,false);


        emit signal_mythread_workended();
        pds_dic2d_free(DIC);
    }
}

bool mythread::set_pen(QPen regionpen)
{
    RegionPen=regionpen;
    return true;
}

bool mythread::set_output_enable_text(bool dat)
{
    enable_text=dat;
    return true;
}

bool mythread::set_output_file_format(QString ext)
{
    output_file_format=ext;
    return true;
}

bool mythread::set_listfilesdat(QList<QString> ImagePathList)
{
    ImageFilePathList=ImagePathList;
    return true;
}
bool mythread::set_listregionsdat(QList<PdsRegionRect> InputRegionList)
{
    RegionRectList=InputRegionList;
    return true;
}
bool mythread::set_output_filename_pattern(QString pattern)
{
    output_filename_pattern=pattern;
    return true;
}
bool mythread::set_output_directory(QString directory)
{
    output_directory=directory;
    return true;
}

QString mythread::get_listregionsdat_output_filename(QString directory, QString filename_pattern,int id)
{
    QString path;

    QDir pathDir(directory);
    if (pathDir.exists()==false)
    {
        if(QDir().mkdir(directory)==false)
        {
            emit signal_mythread_message_red(tr("ERROR creating the directory:: ")+directory);
        }
    }
    path=directory+QDir::separator()+filename_pattern+QString::number(id)+".listregions";
    return path;
}

QColor mythread::get_qcolor_from(double min, double max, double val)
{
    QColor color;
    int id;
    if(min==max)    return Qt::black;
    id=255.0*(val-min)/(max-min);
    color.setRed(PDS_COLORMAP_JET[id][0]);
    color.setGreen(PDS_COLORMAP_JET[id][1]);
    color.setBlue(PDS_COLORMAP_JET[id][2]);

    return color;
}

bool mythread::save_image_region_list(QString inputfilepath,QString outputtextfilepath, QList<PdsRegionRect> InputRegionList)
{
    QImage image;
    image.load(inputfilepath);
    if(image.isNull())  return false;

    int H=image.height();
    int W=image.width();
    if((H==0)||(W==0))  return false;

    image = image.convertToFormat(QImage::Format_RGB32);
    //if(image.format()==QImage::Format_Indexed8)
    //{
    //    image = image.convertToFormat(QImage::Format_RGB32);
    //}

    QPainter painter( &image );
    painter.setPen(RegionPen);

    painter.setBrush(Qt::NoBrush);
    QFont font = painter.font();


    for(int i=0;i<InputRegionList.length();i++)
    {
        int x=InputRegionList.at(i).C0;
        int y=InputRegionList.at(i).L0;
        int width=(int)InputRegionList.at(i).Ncol;
        int height=(int)InputRegionList.at(i).Nlin;
        if((width>0) && (height>0) &&(x>=0)&& (y>=0) && ((x+width-1)<W)&& ((y+height-1)<H))
        {
            painter.drawRect(x,y,width,height);
            if(enable_text==true)
            {
                font.setPixelSize(std::min(height,width)*1/2);
                painter.setFont(font);
                painter.drawText(x,y,width,height,Qt::AlignCenter,QString::number(i+1));
            }
        }
    }

    painter.end();
    image.save( outputtextfilepath+output_file_format,NULL,100 );

    return true;
}


bool mythread::save_image_region_list_distance( QString ImagePath,
                                                QString directory,
                                                QString pattern,
                                                QList<PdsRegionRect> RegionListInit,
                                                QList<PdsRegionRect> RegionListEnd)
{
    QImage image;
    image.load(ImagePath);
    if(image.isNull())  return false;

    int H=image.height();
    int W=image.width();
    if((H==0)||(W==0))  return false;

    image = image.convertToFormat(QImage::Format_RGB32);

    QPainter painter( &image );
    painter.setPen(RegionPen);

    painter.setBrush(Qt::NoBrush);
    QFont font = painter.font();

    QList<double> d;
    for(int i=0;i<RegionListInit.length();i++)
    {   d.append(-1.0);
        if( (RegionListEnd.at(i).Nlin>0)&&
            (RegionListEnd.at(i).Ncol>0)&&
            (RegionListInit.at(i).Nlin>0)&&
            (RegionListInit.at(i).Ncol>0) )
        {
            int dx=RegionListEnd.at(i).C0-RegionListInit.at(i).C0;
            int dy=RegionListEnd.at(i).L0-RegionListInit.at(i).L0;
            d.replace(i,sqrt(dx*dx+dy*dy));
        }
    }


    for(int i=0;i<RegionListInit.length();i++)
    {
        int x=RegionListInit.at(i).C0;
        int y=RegionListInit.at(i).L0;
        int width=(int)RegionListInit.at(i).Ncol;
        int height=(int)RegionListInit.at(i).Nlin;
        if((width>0) && (height>0) &&(x>=0)&& (y>=0) && ((x+width-1)<W)&& ((y+height-1)<H))
        {
            painter.drawRect(x,y,width,height);
            //if((enable_text==true)&&(d.at(i)>=0))
            if(d.at(i)>=0)
            {
                font.setPixelSize(std::min(height,width)*1/3);
                painter.setFont(font);
                painter.drawText(x,y,width,height,Qt::AlignCenter,QString::number(d.at(i), 'f', 1));
            }

            painter.drawLine(RegionListInit.at(i).C0,RegionListInit.at(i).L0,x,y);
        }
    }

    painter.end();
    image.save( directory+QDir::separator()+pattern+"_dist.listregions"+output_file_format,NULL,100 );

    return true;
}


bool mythread::drawVerticalColorBar(QString filepath,unsigned int W,unsigned int H,double dmin,double dmax )
{
    QImage image(W, H, QImage::Format_RGB32);
    QColor color;
    double factor=0.4;

    QPainter painter( &image );
    unsigned int lineW=W/32;
    if(lineW==0)lineW=1;

    QPen pen;
    unsigned int i;
    unsigned int delta=round(H/6);
    unsigned int textH=round(H/6);


    if(delta<8) return false;

    QBrush brush(Qt::white);
    painter.setBrush(brush);
    painter.drawRect(0,0,W-1,H-1);

    painter.setBrush(Qt::NoBrush);

    for(i=0;i<H;i++)
    {
        color=get_qcolor_from(0, H, i*1.0);
        pen.setColor(color);
        painter.setPen(pen);// color de linea
        painter.drawLine(round(lineW/2),H-1-i,(1.0-factor)*W,H-1-i);
    }

    color.setRgb(0,0,0);
    pen.setColor(color);
    pen.setWidth(lineW);

    painter.setPen(pen);// color de linea
    painter.drawRect(round(lineW/2),round(lineW/2),(1.0-factor)*W-round(lineW/2),H-1-round(lineW/2));

    QFont font = painter.font() ;
    font.setPointSize(font.pointSize()* 1.5);
    painter.setFont(font);

    for(i=0;i<H;i=i+delta)
    {
        unsigned int x=(1.0-factor)*W;
        unsigned int y=H-1-i;
        unsigned int w=factor*W;
        unsigned int h=round(std::min(textH*1.0,factor*W));
        painter.drawLine(x*0.75,y,x,y);
        //painter.drawRect(x,y-h,w,h);

        painter.drawText(x,y-h,w,h,Qt::AlignBottom|Qt::AlignHCenter,QString::number((i*(dmax-dmin))/H+dmin, 'f', 2));
    }

    image.save( filepath,NULL,100 );

    return true;
}

#include <complex>
void drawVectorInit(QPainter& painter,PdsRegionRect Rinit,PdsRegionRect Rend,double dmax,double pixelmax)//Rinit.Nlin*0.8
{

    std::complex<double> vec (Rend.L0-Rinit.L0,Rend.C0-Rinit.C0);

    double d=sqrt(pow(Rend.L0-Rinit.L0,2)+ pow(Rend.C0-Rinit.C0,2));
    double C0=Rinit.C0+Rinit.Ncol/2.0;
    double L0=Rinit.L0+Rinit.Nlin/2.0;

    std::complex<double> pd2(+0.00,+0.50);//(L,C)
    std::complex<double> pd1(+0.00,-0.50);//(L,C)

    std::complex<double> pa2(+0.00,+0.50);//(L,C)
    std::complex<double> pa1(+0.25,+0.25);//(L,C)

    std::complex<double> pb2(+0.00,+0.50);//(L,C)
    std::complex<double> pb1(-0.25,+0.25);//(L,C)

    std::complex<double> factor=vec/(pd2-pd1);
    factor=factor/std::abs(factor);

    pd2=factor*(pixelmax)*pd2*d/dmax;
    pd1=factor*(pixelmax)*pd1*d/dmax;

    pa2=factor*(pixelmax)*pa2*d/dmax;
    pa1=factor*(pixelmax)*pa1*d/dmax;

    pb2=factor*(pixelmax)*pb2*d/dmax;
    pb1=factor*(pixelmax)*pb1*d/dmax;


    QPen pen_arrow   =QPen(Qt::black);
    pen_arrow.setWidth(3);
    painter.setPen(pen_arrow);// color de linea
    painter.drawLine(std::imag(pd1)+C0,std::real(pd1)+L0,std::imag(pd2)+C0,std::real(pd2)+L0);
    painter.drawLine(std::imag(pa1)+C0,std::real(pa1)+L0,std::imag(pa2)+C0,std::real(pa2)+L0);
    painter.drawLine(std::imag(pb1)+C0,std::real(pb1)+L0,std::imag(pb2)+C0,std::real(pb2)+L0);

    painter.setPen(Qt::NoPen);// color de linea

    //painter.drawLine(RegionListInit.at(i).C0,RegionListInit.at(i).L0,x,y);
}

bool mythread::save_image_region_list_pcolor( QString ImagePath,
                                                QString directory,
                                                QString pattern,
                                                QList<PdsRegionRect> RegionListInit,
                                                QList<PdsRegionRect> RegionListEnd,
                                                bool ENABLE_TEXT)
{
    QImage image;
    image.load(ImagePath);
    if(image.isNull())  return false;

    int H=image.height();
    int W=image.width();
    if((H==0)||(W==0))  return false;

    image = image.convertToFormat(QImage::Format_RGB32);

    QPainter painter( &image );
    painter.setPen(Qt::NoPen);// color de linea

    painter.setBrush(Qt::NoBrush);
    QFont font = painter.font();// color de fondo

    // Making d, dmin, dmax
    QList<double> d;
    double dmin=(double)std::max(W,H);
    double dmax=0;
    for(int i=0;i<RegionListInit.length();i++)
    {   d.append(-1.0);
        if( (RegionListEnd.at(i).Nlin>0)&&
            (RegionListEnd.at(i).Ncol>0)&&
            (RegionListInit.at(i).Nlin>0)&&
            (RegionListInit.at(i).Ncol>0) )
        {
            int dx=RegionListEnd.at(i).C0-RegionListInit.at(i).C0;
            int dy=RegionListEnd.at(i).L0-RegionListInit.at(i).L0;
            d.replace(i,sqrt(dx*dx+dy*dy));

            if(dmax<d.at(i))  dmax=d.at(i);
            if(dmin>d.at(i))  dmin=d.at(i);
        }
    }


    for(int i=0;i<RegionListInit.length();i++)
    {
        // The geometry of current region (x,y,width,height)
        int x=RegionListInit.at(i).C0;
        int y=RegionListInit.at(i).L0;
        int width=(int)RegionListInit.at(i).Ncol;
        int height=(int)RegionListInit.at(i).Nlin;

        // If the region is true
        if((width>0) && (height>0) &&(x>=0)&& (y>=0) && ((x+width-1)<W)&& ((y+height-1)<H))
        {
            // Painting the background of each region, to each pen and brush.
            QColor color=get_qcolor_from(dmin, dmax, d.at(i));
            painter.setBrush(QBrush(color));
            painter.drawRect(x,y,width,height);

            // Draw Vector
            drawVectorInit(painter,RegionListInit.at(i),RegionListEnd.at(i),dmax,height*0.7);

            // Set a new brush
            painter.setBrush(Qt::NoBrush);

            // Draw text
            if((ENABLE_TEXT==true)&&(d.at(i)>=0))
            {
                painter.setPen(Qt::black);
                font.setPixelSize(std::min(height,width)*1/3);
                painter.setFont(font);
                painter.drawText(x,y,width,height,Qt::AlignCenter,QString::number(d.at(i), 'f', 1));
                painter.setPen(RegionPen);
            }

        }
    }

    painter.end();
    image.save( directory+QDir::separator()+pattern+"_pcolor.listregions"+output_file_format,NULL,100 );
    drawVerticalColorBar(directory+QDir::separator()+pattern+"_pcolor.colorbar"+output_file_format,200,800,dmin,dmax);
    return true;
}

bool mythread::save_region_list(QString filepath, QList<PdsRegionRect> InputRegionList)
{
    int N=InputRegionList.length();
    QFile file(filepath);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream stream(&file);
        for(int i=0;i<N;i++)
        {
            stream << QString::number(InputRegionList.at(i).L0)+"\t"
                   << QString::number(InputRegionList.at(i).C0)+"\t"
                   << QString::number(InputRegionList.at(i).Nlin)+"\t"
                   << QString::number(InputRegionList.at(i).Ncol)<< endl;
        }


    }
    else return false;

    return true;
}

PdsMatrix *mythread::matrix_from_image_filepath(QString filepath)
{
    QImage image;
    image.load(filepath);

    int H=image.height();
    int W=image.width();

    if((H==0)||(W==0))  return NULL;

    QColor color;

    PdsMatrix *Mat=pds_matrix_new_rand(H,W);
    if(Mat==NULL)   return NULL;
    for(int i=0;i<H;i++)
    for(int j=0;j<W;j++)
    {
        color=image.pixel(j,i);
        Mat->M[i][j]=0.21*color.red()+0.72*color.green()+0.07*color.blue();
    }
    return Mat;
}
