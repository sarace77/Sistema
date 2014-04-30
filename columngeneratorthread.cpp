#include "columngeneratorthread.h"

#include "Defs.h"

#define ERROR(ERRORSTRING) emit generatorErrorSignal( ERRORSTRING);

#define _DENOMINATORE_BINOMIO_NEWTON    6*5*4*3*2

ColumnGeneratorThread::ColumnGeneratorThread(QObject *parent) :
    QThread(parent)
{
    vNumbers.reserve(_NUM_SELECTOR_SIZE);
}

int ColumnGeneratorThread::overallColumnsCount() {

    int result = 1;
    if ( _COLUMN_SIZE > vNumbers.count() ) {
        ERROR(QString("ColumnGeneratorThread: ") + \
              QString("Numero di valori errato\n Selezionati: %1 - Numero Minimo: %2").arg(vNumbers.count()).arg(_COLUMN_SIZE));
    }

    for ( int i = 0 ; i < _COLUMN_SIZE ; i++ ) {
        result *= (vNumbers.count() - i);
    }

    return result / _DENOMINATORE_BINOMIO_NEWTON;
}

void ColumnGeneratorThread::updateNumbers(QList<quint8> vNums) {
    if ( _COLUMN_SIZE <= vNums.count() ) {
        vNumbers = vNums;
        ERROR(QString())
    } else {
        ERROR(QString("ColumnGeneratorThread: ") + \
              QString("Numero di valori Selezionati errato\n Selezionati: %1 - Numero Minimo: %2").arg(vNums.count()).arg(_COLUMN_SIZE));
    }
}
