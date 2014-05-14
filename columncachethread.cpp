#include "columncachethread.h"

#include "Defs.h"

#define ERROR( ERRORSTRING ) emit cacheErrorSignal( QString("ColumnCacheThread: ") + ERRORSTRING );

ColumnCacheThread::ColumnCacheThread(QObject *parent) :
    QThread(parent)
{
    cCache.reserve(_MAX_COL_CACHE_SIZE);
}


void ColumnCacheThread::enqueue(Column col) {
    if ( _MAX_COL_CACHE_SIZE <= cCache.count() ) {
        storeCache();
    }
    if ( mCacheMutex.tryLock(50) ) {
        cCache.enqueue(col);
        mCacheMutex.unlock();
    } else {
        ERROR(QString("(enqueue): Unable to Lock Mutex"));
    }
}

void ColumnCacheThread::storeCache() {
    if ( mCacheMutex.tryLock(50) ) {
        cCache.clear();
        mCacheMutex.unlock();
    } else {
        ERROR(QString("(storeCache): Unable to Lock Mutex"));
    }
}
