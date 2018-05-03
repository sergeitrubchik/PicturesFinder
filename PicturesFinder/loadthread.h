#ifndef LOADTHREAD_H
#define LOADTHREAD_H

#include <QtCore>
#include <QLayout>

class LoadThread : public QRunnable
{
    // TODO: what are main differences between QThread and QRunnable?
public:
    LoadThread(QMutex* mutex, QDirIterator* dirIter, QList<QPixmap*>& pixmaps, QString name);

protected:
    void run();

private:
    QMutex* mutex_;
    QDirIterator* dirIter_;
    QList<QPixmap*>& pixmaps_;
    QString name_;
};

#endif // LOADTHREAD_H
