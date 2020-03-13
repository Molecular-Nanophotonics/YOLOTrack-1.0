#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    graphicsView = new MyGraphicsView();
    ui->verticalLayout->addWidget(graphicsView);

    scene = new QGraphicsScene();
    graphicsView->setScene(scene);
    //graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    //graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    connect(ui->selectModel_button, &QPushButton::clicked, this,  &MainWindow::selectModelDialog);
    connect(ui->selectImage_button, &QPushButton::clicked, this,  &MainWindow::selectImageDialog);

    char tf_version[32];
    if (!getVersion(tf_version))
        ui->labelVersion->setText(QString(tf_version));
        char device_name[32];
        if (!getDeviceName(device_name))
            ui->labelDeviceName->setText(QString(device_name));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::selectModelDialog()
{
    //QFileDialog dialog(this, tr("Select Model"));
    //initializeImageFileDialog(dialog, QFileDialog::AcceptOpen);

    QString modelFileName = QFileDialog::getOpenFileName(this, "Open Model", "../../YOLOv2 Training (Python)", "Protocol Buffer File (*.pb)");

    qDebug() << modelFileName;

    QFileInfo info(modelFileName);
    QString iniFileName = info.path() + "/" + info.baseName() + ".ini";

    ui->modelPath_lineEdit->setText(modelFileName);

    qDebug() << iniFileName;

    QSettings settings(iniFileName, QSettings::IniFormat);

    char* file = _strdup(modelFileName.toStdString().c_str());

    int IMAGE_H = settings.value("IMAGE_H").toInt();
    int IMAGE_W = settings.value("IMAGE_W").toInt();
    int GRID_H = settings.value("GRID_H").toInt();
    int GRID_W = settings.value("GRID_W").toInt();
    int BOXES = settings.value("BOXES").toInt();
    int CLASSES = settings.value("CLASSES").toInt();
    QString INPUT_NODE_NAME = settings.value("INPUT_NODE_NAME").toString();
    QString OUTPUT_NODE_NAME = settings.value("OUTPUT_NODE_NAME").toString();

    int64_t in_shape[] = {1, IMAGE_W, IMAGE_H, 3};
    int in_dim = 4;
    char* in_name = _strdup(INPUT_NODE_NAME.toStdString().c_str());

    int64_t out_shape[] = {1, GRID_W, GRID_H, BOXES, 5 + CLASSES};
    int out_dim = 5;
    char* out_name = _strdup(OUTPUT_NODE_NAME.toStdString().c_str());

    /*
    QStringList ANCHORS = settings.value("ANCHORS").toStringList();
    float *anchors = (float *)malloc(sizeof(float)*ANCHORS.size());
    for (int i = 0; i < ANCHORS.size(); i++)
        anchors[i] = ANCHORS[i].toFloat();
    */

    qDebug() << setupTF(file, in_shape, in_dim, in_name, out_shape, out_dim, out_name);

    //qDebug() << (char*)file << in_shape << in_dim << (char*)in_name << out_shape << out_dim << (char*)out_name;
}

void MainWindow::selectImageDialog()
{
    QString imageFileName = QFileDialog::getOpenFileName(this, "Open Image", "../../YOLOv2 Training (Python)/images/test_images", "JPG Files (*.jpg)");
    loadFile(imageFileName);
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
    p->setCompositionMode(QPainter::CompositionMode_Clear);
    p->setPen(QPen(QColor(0, 255, 0,255), 1.5));
    p->drawRect(15, 15, 100, 100);


    /*
    QPixmap *pix = new QPixmap(500,500);
    QGraphicsPixmapItem* item(scene->addPixmap(*pix)); // Save the returned item
    QPainter *paint = new QPainter(pix);
    paint->setPen(*(new QColor(255,34,255,255)));
    paint->drawRect(15,15,100,100);
    item->setPixmap(*pix); // Added this line
    */

    // ui->imageLabel->setPixmap(pixmap.scaled(ui->imageLabel->width(), ui->imageLabel->height(), Qt::KeepAspectRatio));

    scene->addPixmap(pixmap); // .scaled(ui->imageLabel->width(), ui->imageLabel->height(), Qt::KeepAspectRatio)

    return true;
}
