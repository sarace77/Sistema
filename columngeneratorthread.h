#ifndef COLUMNGENERATORTHREAD_H
#define COLUMNGENERATORTHREAD_H

#include <QThread>

class ColumnGeneratorThread : public QThread
{
    Q_OBJECT
public:
    explicit ColumnGeneratorThread(QObject *parent = 0);

    int     overallColumnsCount();

signals:
    void    generatorErrorSignal( QString );
    void    processedColumnsSignal( int );

public slots:
    void    updateNumbers( QList<quint8> vNums );

private:
    QList<quint8>   vNumbers;

private slots:

};

#endif // COLUMNGENERATORTHREAD_H
