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
        mb.setText("Directory '" + directoryName + "' doesn't exist. Check path.");
        mb.exec();
    }

    QVBoxLayout* flowLayout = new QVBoxLayout;
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );
    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );

    QDirIterator* dirIter = new QDirIterator(directoryName, QStringList() << "*.jpg" << "*.JPG", QDir::Files,QDirIterator::Subdirectories);
    while(dirIter->hasNext())
    {
        auto next = dirIter->next();
        QLabel *imageLabel = new QLabel;
        imageLabel->setPixmap(QPixmap::fromImage(QImage(next)));
        flowLayout->addWidget(imageLabel);
    }
}
