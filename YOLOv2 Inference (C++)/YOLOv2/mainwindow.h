#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../TF DLL/TF.h"
#include "../../YOLOv2 DLL/YOLOv2.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QImageReader>
#include <QPainter>
#include <QGraphicsView>
#include <QWheelEvent>


class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit MyGraphicsView(QWidget* parent = nullptr) : QGraphicsView(parent) {}

private:

    int m_originX, m_originY;

protected Q_SLOTS:

    void wheelEvent(QWheelEvent *event)
    {
    if(event->delta() > 0)
        scale(1.1, 1.1);
    else
        scale(0.9, 0.9);
    }

    /*
    void resizeEvent(QResizeEvent  *event)
    {
        fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
    }
    */

};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectModelDialog();
    void selectImageDialog();


private:
    Ui::MainWindow *ui;

    int IMAGE_W;
    int IMAGE_H;

    float* input_tensor;
    float* output_tensor;

    float* x_out;
    float* y_out;
    float* w_out;
    float* h_out;
    int* c_out;

    MyGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *item;

    bool loadFile(const QString &);
    void setImage(const QImage &newImage);
};

#endif // MAINWINDOW_H
