#ifndef PICTURESFINDER_H
#define PICTURESFINDER_H

#include <QMainWindow>

namespace Ui {
class PicturesFinder;
}

class PicturesFinder : public QMainWindow
{
    Q_OBJECT

public:
    explicit PicturesFinder(QWidget *parent = 0);
    ~PicturesFinder();

private slots:
    void on_browseButton_clicked();

    void on_startButton_clicked();

private:
    Ui::PicturesFinder *ui;
};

#endif // PICTURESFINDER_H
