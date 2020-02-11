#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openFile, &QPushButton::clicked, this,  &MainWindow::open);

    //ui->label->setText(QString::number(add(8, 4)));
    char version[32];
    getVersion(version);
    ui->versionLabel->setText(QString(version));
    //ui->versionLabel->setText(version);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::open()
{
    QFileDialog dialog(this, tr("Open File"));
    //initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    while (dialog.exec() == QDialog::Accepted && !loadFile(dialog.selectedFiles().first())) {}
}


bool MainWindow::loadFile(const QString &fileName)
{
    QImageReader reader(fileName);
    reader.setAutoTransform(true);
    const QImage newImage = reader.read();
    if (newImage.isNull()) {
        QMessageBox::information(this, QGuiApplication::applicationDisplayName(), "...");
        return false;
    }

    QImage image = newImage;
    QPixmap pixmap = QPixmap::fromImage(image);

    // https://forum.qt.io/topic/61684/tinting-a-qpixmap-using-qpainter-compositionmode_overlay/3
    QPainter *p = new QPainter(&pixmap);
    //p->setRenderHint(QPainter::Antialiasing);
    p->setPen(QColor(0, 255, 0,255));
    p->drawRect(15, 15, 100, 100);


    /*
    QPixmap *pix = new QPixmap(500,500);
    QGraphicsPixmapItem* item(scene->addPixmap(*pix)); // Save the returned item
    QPainter *paint = new QPainter(pix);
    paint->setPen(*(new QColor(255,34,255,255)));
    paint->drawRect(15,15,100,100);
    item->setPixmap(*pix); // Added this line
    */

    ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width(), ui->imageLabel->height(), Qt::KeepAspectRatio));

    return true;
}
