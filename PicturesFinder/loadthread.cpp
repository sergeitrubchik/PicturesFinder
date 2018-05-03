#include "loadthread.h"
#include <QLabel>
#include <iostream>
#include <fstream>

LoadThread::LoadThread(QMutex* mutex, QDirIterator* dirIter, QList<QPixmap*>& pixmaps, QString name)
    :QRunnable(),
      mutex_(mutex),
      dirIter_(dirIter),
      pixmaps_(pixmaps),
      name_(name)
{

}

void LoadThread::run()
{
    mutex_->lock();
    bool hasNext = dirIter_->hasNext();

    // iterate over all '.jpg' files
    while(hasNext)
    {
        // get full path to image
        auto filename = dirIter_->next();
        qDebug() << filename << name_;
        mutex_->unlock();

        if (!filename.isEmpty())
        {
            // try to load image
            QImage image(filename);
            if (!image.isNull())
            {
                // create pixmap and add it to list
                QPixmap* pixmap = new QPixmap(QPixmap::fromImage(image));
                mutex_->lock();
                pixmaps_.append(pixmap);
                mutex_->unlock();
            }
            //TODO: add logs window "Cannot load %1.").arg(filename));
        }

        mutex_->lock();
        hasNext = dirIter_->hasNext();
    }

    mutex_->unlock();
    qDebug() << name_ << " done.";
}

