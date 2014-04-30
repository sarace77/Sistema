#ifndef NUMBERSSELECTORFORM_H
#define NUMBERSSELECTORFORM_H

#include <QWidget>
#include <QCheckBox>
#include <QSignalMapper>


namespace Ui {
class NumbersSelectorForm;
}

class NumbersSelectorForm : public QWidget
{
    Q_OBJECT

public:
    explicit NumbersSelectorForm(QWidget *parent = 0);
    ~NumbersSelectorForm();

    QList<quint8>       getSelectedNumbers();
private:
    Ui::NumbersSelectorForm *ui;

    QSignalMapper           *pColMapper, *pNumMapper, *pRowMapper;
    QCheckBox               *pCheckBoxAll;
    QList<QCheckBox *>      pColSelector, pNumSelector, pRowSelector;

protected slots:
    void                    selectAll( int eState );
    void                    selectCol( int index );
    void                    selectNum( int index );
    void                    selectRow( int index );

signals:
    void                    numSelectionChangedSignal( QList<quint8> );


private:
    void                connectSignals();
    void                disconnectSignals();
};

#endif // NUMBERSSELECTORFORM_H
