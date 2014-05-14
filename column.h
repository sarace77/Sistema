#ifndef COLUMN_H
#define COLUMN_H

#include <QObject>

class Column
{
public:
    explicit Column( QList<quint8> vNum );

private:
    QList<quint8>   vValues;
};

#endif // COLUMN_H
