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
    ui->pathTextEdit->setPlainText(str);
}

void PicturesFinder::on_startButton_clicked()
{
    auto directoryName = ui->pathTextEdit->toPlainText();
    QDir dir(directoryName);
    if(!dir.exists())
    {
        QMessageBox mb;
        mb.setText("Directory '" + directoryName + "' doesn't exist. Check path.");
        mb.exec();
    }

    QDirIterator* dirIter = new QDirIterator(directoryName, QStringList() << "*.jpg" << "*.JPG", QDir::Files);
    //ui->tableWidget->setRowCount(10);
    //ui->tableWidget->setColumnCount(1);
    int row = 0;
    std::vector<QLabel*> labels;


    QVBoxLayout* flowLayout = new QVBoxLayout;
    QWidget* scrollAreaContent = new QWidget;
    scrollAreaContent->setLayout( flowLayout );
    //QScrollArea* scrollArea = new QScrollArea;
    ui->scrollArea->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
    ui->scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAsNeeded );
    ui->scrollArea->setWidgetResizable( true );
    ui->scrollArea->setWidget( scrollAreaContent );

    // add your buttons the flowLayout ....

    while(dirIter->hasNext())
    {
        auto next = dirIter->next();
        QLabel *imageLabel = new QLabel;
        imageLabel->setPixmap(QPixmap::fromImage(QImage(next)));

        flowLayout->addWidget(imageLabel);
        QLabel *imageLabel1 = new QLabel;
        imageLabel1->setText(next);

        labels.push_back(imageLabel);

        //QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(pow(row, 1)));
        //newItem->setData(Qt::DecorationRole, QPixmap::fromImage(QImage(next)));
        //ui->tableWidget->setItem(row, 1, newItem);
        row++;
        //ui->verticalLayout_2->addWidget(imageLabel);
    }

}
