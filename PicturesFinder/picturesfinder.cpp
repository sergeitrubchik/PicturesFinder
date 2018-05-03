#include "picturesfinder.h"
#include "ui_picturesfinder.h"
#include <QFileDialog>
#include <QDirIterator>
#include <QMessageBox>

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

    QVBoxLayout* layout = new QVBoxLayout;
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout(layout);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setWidget(scrollAreaContent);

    QDirIterator* dirIter = new QDirIterator(directoryName, QStringList() << "*.jpg" << "*.JPG", QDir::Files,QDirIterator::Subdirectories);
    // iterate over all '.jpg' files
    while(dirIter->hasNext())
    {
        // get full path to image
        auto filename = dirIter->next();
        if (!filename.isEmpty())
        {
            // try to load image
            QImage image(filename);
            if (!image.isNull())
            {
                // create pixmap
                QPixmap pixmap = QPixmap::fromImage(image);

                // create label and set pixmap
                QLabel *imageLabel = new QLabel;
                imageLabel->setPixmap(pixmap);
                imageLabel->setScaledContents(true);
                imageLabel->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);

                // add this label widget to layout
                layout->addWidget(imageLabel);
            }
            //TODO: add logs window
            //else
            //{

            //    QMessageBox::information(this, tr("PicturesFinder"),
            //                             tr("Cannot load %1.").arg(filename));
            //}
        }
    }
}
