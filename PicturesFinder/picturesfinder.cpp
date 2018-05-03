#include "picturesfinder.h"
#include "ui_picturesfinder.h"
#include <QFileDialog>
#include <QDirIterator>
#include <QMessageBox>
#include <QtGui>
#include <QDebug>
#include "loadthread.h"

PicturesFinder::PicturesFinder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PicturesFinder)
{
    ui->setupUi(this);
}

PicturesFinder::~PicturesFinder()
{
    delete ui;
}

void PicturesFinder::on_browseButton_clicked()
{
    // open file dialog and get path to directory
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "");
    ui->lineEdit->setText(str);
}

void PicturesFinder::on_startButton_clicked()
{
    auto directoryName = ui->lineEdit->text();
    QDir dir(directoryName);
    if(!dir.exists())
    {
        QMessageBox mb;
        mb.setText("Directory '" + directoryName + "' doesn't exist. Please check path's correctness.");
        mb.exec();
        return;
    }

    // load images
    QDirIterator* dirIter = new QDirIterator(directoryName, QStringList() << "*.jpg" << "*.JPG", QDir::Files,QDirIterator::Subdirectories);

    QMutex* m = new QMutex();
    QList<QPixmap *> pixmaps;
    LoadThread* thread1 = new LoadThread(m, dirIter, pixmaps, "Thread1");
    LoadThread* thread2 = new LoadThread(m, dirIter, pixmaps, "Thread2");

    // TODO: how to prevent 'Not responding' problem ?
    QThreadPool::globalInstance()->start(thread1);
    QThreadPool::globalInstance()->start(thread2);

    // TODO: is it just loop while(!thread.finished()) in case of threads ?
    QThreadPool::globalInstance()->waitForDone();
    qDebug() << "Loadind finished.";

    // setup scrol area and layouts
    QVBoxLayout* layout = new QVBoxLayout;
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(layout);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollAreaContent);

    // TODO: is it possible to make it in parallel?
    // probably we can do addind widgets in parallel
    for(auto pixmap : pixmaps)
    {
        // create label and set pixmap
        QLabel *imageLabel = new QLabel;
        imageLabel->setPixmap(*pixmap);
        imageLabel->setScaledContents(true);
        imageLabel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

        // add this label widget to layout
        layout->addWidget(imageLabel);

        // TODO: good or bad ?
        //QCoreApplication::processEvents();
    }
}
