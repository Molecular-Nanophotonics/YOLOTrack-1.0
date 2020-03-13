#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../TF DLL/TF.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QImageReader>
#include <QPainter>

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

    bool loadFile(const QString &);
    void setImage(const QImage &newImage);
};

#endif // MAINWINDOW_H
