#include "picturesfinder.h"
#include "ui_picturesfinder.h"

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
