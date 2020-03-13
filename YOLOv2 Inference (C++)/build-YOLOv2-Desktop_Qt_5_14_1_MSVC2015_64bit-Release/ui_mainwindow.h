/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *imageLabel;
    QPushButton *selectImage_button;
    QLabel *labelVersion;
    QLabel *labelDeviceName_;
    QLabel *labelVersion_;
    QLabel *labelDeviceName;
    QLineEdit *imagePath_lineEdit;
    QLabel *labelPathToImage;
    QPushButton *selectModel_button;
    QLabel *labelPathToModel;
    QLineEdit *modelPath_lineEdit;
    QSlider *horizontalSlider;
    QSlider *NMSThreshold_slider;
    QDoubleSpinBox *doubleSpinBox;
    QDoubleSpinBox *doubleSpinBox_2;
    QLabel *labelObjectThreshold;
    QLabel *NMSThreshold_l;
    QPushButton *update_button;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(529, 790);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imageLabel = new QLabel(centralWidget);
        imageLabel->setObjectName(QString::fromUtf8("imageLabel"));
        imageLabel->setGeometry(QRect(10, 270, 511, 511));
        selectImage_button = new QPushButton(centralWidget);
        selectImage_button->setObjectName(QString::fromUtf8("selectImage_button"));
        selectImage_button->setGeometry(QRect(490, 140, 31, 23));
        labelVersion = new QLabel(centralWidget);
        labelVersion->setObjectName(QString::fromUtf8("labelVersion"));
        labelVersion->setGeometry(QRect(10, 30, 71, 21));
        labelVersion->setFrameShape(QFrame::Panel);
        labelVersion->setFrameShadow(QFrame::Sunken);
        labelDeviceName_ = new QLabel(centralWidget);
        labelDeviceName_->setObjectName(QString::fromUtf8("labelDeviceName_"));
        labelDeviceName_->setGeometry(QRect(130, 10, 91, 16));
        labelVersion_ = new QLabel(centralWidget);
        labelVersion_->setObjectName(QString::fromUtf8("labelVersion_"));
        labelVersion_->setGeometry(QRect(10, 10, 101, 16));
        labelDeviceName = new QLabel(centralWidget);
        labelDeviceName->setObjectName(QString::fromUtf8("labelDeviceName"));
        labelDeviceName->setGeometry(QRect(130, 30, 161, 21));
        labelDeviceName->setFrameShape(QFrame::Panel);
        labelDeviceName->setFrameShadow(QFrame::Sunken);
        imagePath_lineEdit = new QLineEdit(centralWidget);
        imagePath_lineEdit->setObjectName(QString::fromUtf8("imagePath_lineEdit"));
        imagePath_lineEdit->setGeometry(QRect(9, 142, 471, 20));
        imagePath_lineEdit->setReadOnly(true);
        labelPathToImage = new QLabel(centralWidget);
        labelPathToImage->setObjectName(QString::fromUtf8("labelPathToImage"));
        labelPathToImage->setGeometry(QRect(9, 122, 101, 16));
        selectModel_button = new QPushButton(centralWidget);
        selectModel_button->setObjectName(QString::fromUtf8("selectModel_button"));
        selectModel_button->setGeometry(QRect(490, 90, 31, 23));
        labelPathToModel = new QLabel(centralWidget);
        labelPathToModel->setObjectName(QString::fromUtf8("labelPathToModel"));
        labelPathToModel->setGeometry(QRect(9, 72, 101, 16));
        modelPath_lineEdit = new QLineEdit(centralWidget);
        modelPath_lineEdit->setObjectName(QString::fromUtf8("modelPath_lineEdit"));
        modelPath_lineEdit->setEnabled(true);
        modelPath_lineEdit->setGeometry(QRect(9, 92, 471, 20));
        modelPath_lineEdit->setReadOnly(true);
        modelPath_lineEdit->setClearButtonEnabled(false);
        horizontalSlider = new QSlider(centralWidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(110, 190, 160, 19));
        horizontalSlider->setOrientation(Qt::Horizontal);
        NMSThreshold_slider = new QSlider(centralWidget);
        NMSThreshold_slider->setObjectName(QString::fromUtf8("NMSThreshold_slider"));
        NMSThreshold_slider->setGeometry(QRect(110, 240, 160, 19));
        NMSThreshold_slider->setOrientation(Qt::Horizontal);
        doubleSpinBox = new QDoubleSpinBox(centralWidget);
        doubleSpinBox->setObjectName(QString::fromUtf8("doubleSpinBox"));
        doubleSpinBox->setGeometry(QRect(280, 188, 51, 22));
        doubleSpinBox_2 = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_2->setObjectName(QString::fromUtf8("doubleSpinBox_2"));
        doubleSpinBox_2->setGeometry(QRect(280, 237, 51, 22));
        labelObjectThreshold = new QLabel(centralWidget);
        labelObjectThreshold->setObjectName(QString::fromUtf8("labelObjectThreshold"));
        labelObjectThreshold->setGeometry(QRect(110, 170, 101, 16));
        NMSThreshold_l = new QLabel(centralWidget);
        NMSThreshold_l->setObjectName(QString::fromUtf8("NMSThreshold_l"));
        NMSThreshold_l->setGeometry(QRect(110, 220, 101, 16));
        update_button = new QPushButton(centralWidget);
        update_button->setObjectName(QString::fromUtf8("update_button"));
        update_button->setGeometry(QRect(10, 200, 75, 31));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        imageLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        selectImage_button->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        labelVersion->setText(QString());
        labelDeviceName_->setText(QCoreApplication::translate("MainWindow", "Device Name", nullptr));
        labelVersion_->setText(QCoreApplication::translate("MainWindow", "TensorFlow Version", nullptr));
        labelDeviceName->setText(QString());
        labelPathToImage->setText(QCoreApplication::translate("MainWindow", "Path to Image", nullptr));
        selectModel_button->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        labelPathToModel->setText(QCoreApplication::translate("MainWindow", "Path to Model", nullptr));
        labelObjectThreshold->setText(QCoreApplication::translate("MainWindow", "Object Threshold", nullptr));
        NMSThreshold_l->setText(QCoreApplication::translate("MainWindow", "NMS Threshold", nullptr));
        update_button->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
