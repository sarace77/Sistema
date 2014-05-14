#include "columngeneratorthread.h"

#include "Defs.h"

#define ERROR(ERRORSTRING) emit generatorErrorSignal( QString("ColumnGeneratorThread: ") + ERRORSTRING );

#define _DENOMINATORE_BINOMIO_NEWTON    6*5*4*3*2

ColumnGeneratorThread::ColumnGeneratorThread(QObject *parent) :
    QThread(parent)
{
    vNumbers.reserve(_NUM_SELECTOR_SIZE);
}

int ColumnGeneratorThread::exec() {
    int count = 0;
    QList<quint8> vTmp;
    vTmp.reserve(_COLUMN_SIZE);
    for ( int a = 0 ; a < vNumbers.count() - _COLUMN_SIZE ; a++ ) {
        for ( int b = a + 1 ; b < vNumbers.count() - _COLUMN_SIZE + 1 ; b++ ) {
            for ( int c = b + 1 ; c < vNumbers.count() - _COLUMN_SIZE + 2 ; c++ ) {
                for ( int d = c + 1 ; d < vNumbers.count() - _COLUMN_SIZE + 3 ; d++ ) {
                    for ( int e = d + 1 ; e < vNumbers.count() - _COLUMN_SIZE + 4 ; e++ ) {
                        for ( int f =  e + 1 ; f < vNumbers.count() - _COLUMN_SIZE + 5 ; f++ ) {
                            vTmp << a << b << c << d << e << f;
                            Column tmpCol(vTmp);
                            emit newColumn(tmpCol);
                            emit processedColumnsSignal(++count);
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int ColumnGeneratorThread::overallColumnsCount() {

    int result = 1;
    if ( _COLUMN_SIZE > vNumbers.count() ) {
        ERROR(QString("Numero di valori errato\n Selezionati: %1 - Numero Minimo: %2").arg(vNumbers.count()).arg(_COLUMN_SIZE));
    }

    for ( int i = 0 ; i < _COLUMN_SIZE ; i++ ) {
        result *= (vNumbers.count() - i);
    }

    return result / _DENOMINATORE_BINOMIO_NEWTON;
}

void ColumnGeneratorThread::run() {
    if ( _COLUMN_SIZE > vNumbers.count() ) {
        ERROR(QString("Numero di valori Selezionati errato\n Selezionati: %1 - Numero Minimo: %2").arg(vNumbers.count()).arg(_COLUMN_SIZE));
    } else {
        exec();
    }
}

void ColumnGeneratorThread::updateNumbers(QList<quint8> vNums) {
    if ( _COLUMN_SIZE <= vNums.count() ) {
        vNumbers = vNums;
    } else {
        ERROR(QString("Numero di valori Selezionati errato\n Selezionati: %1 - Numero Minimo: %2").arg(vNums.count()).arg(_COLUMN_SIZE));
    }
}
