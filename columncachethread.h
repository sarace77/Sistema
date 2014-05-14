#ifndef COLUMNCACHETHREAD_H
#define COLUMNCACHETHREAD_H

#include "column.h"

#include <QMutex>
#include <QQueue>
#include <QThread>

class ColumnCacheThread : public QThread
{
    Q_OBJECT
public:
    explicit ColumnCacheThread(QObject *parent = 0);

signals:
    void            cacheErrorSignal(QString );

public slots:
    void            enqueue( Column col );

private:
    QQueue<Column>  cCache;
    QMutex          mCacheMutex;

    void            storeCache();
};

#endif // COLUMNCACHETHREAD_H
