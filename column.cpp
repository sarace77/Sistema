#include "column.h"
#include "Defs.h"

#include <QDebug>

Column::Column(QList<quint8> vNum ) {
    if ( _COLUMN_SIZE == vNum.count() ) {
        vValues = vNum;
    } else {
        qFatal("Invalid Column Size!");
    }
}
