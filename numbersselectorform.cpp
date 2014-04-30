#include "numbersselectorform.h"
#include "ui_numbersselectorform.h"

#include "Defs.h"

#define _EMIT_UPDATE     emit numSelectionChangedSignal(getSelectedNumbers());

NumbersSelectorForm::NumbersSelectorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumbersSelectorForm)
{
    ui->setupUi(this);

    pCheckBoxAll = new QCheckBox(this);

    pColMapper = new QSignalMapper(this);
    pNumMapper = new QSignalMapper(this);
    pRowMapper = new QSignalMapper(this);

    pColSelector.reserve(_COL_SELECTOR_SIZE);
    pNumSelector.reserve(_NUM_SELECTOR_SIZE);
    pRowSelector.reserve(_ROW_SELECTOR_SIZE);

    ui->mainLayout->addWidget(pCheckBoxAll, 0, 0);

    for ( int i = 0 ; i < _COL_SELECTOR_SIZE ; i++ ) {
        QCheckBox *pCheckBox = new QCheckBox(QString("C%1").arg(i), this);
        pCheckBox->setTristate(true);
        pColSelector.append(pCheckBox);
        connect(pCheckBox, SIGNAL(stateChanged(int)), pColMapper, SLOT(map()));
        pColMapper->setMapping(pCheckBox, i);
        ui->mainLayout->addWidget(pCheckBox, 0, i + 1);
    }

    for ( int i = 0 ; i < _NUM_SELECTOR_SIZE ; i++ ) {
        QCheckBox *pCheckBox = new QCheckBox(QString("%1").arg(i + 1), this);
        pCheckBox->setTristate(false);
        pNumSelector.append(pCheckBox);
        connect(pCheckBox, SIGNAL(stateChanged(int)), pNumMapper, SLOT(map()));
        pNumMapper->setMapping(pCheckBox, i);
        ui->mainLayout->addWidget(pCheckBox, i / _COL_SELECTOR_SIZE + 1, i % _COL_SELECTOR_SIZE +1);
    }

    for ( int i = 0 ; i < _ROW_SELECTOR_SIZE ; i++ ) {
        QCheckBox *pCheckBox = new QCheckBox(QString("R%1").arg(i), this);
        pCheckBox->setTristate(true);
        pRowSelector.append(pCheckBox);
        connect(pCheckBox, SIGNAL(stateChanged(int)), pRowMapper, SLOT(map()));
        pRowMapper->setMapping(pCheckBox, i);
        ui->mainLayout->addWidget(pCheckBox, i + 1, 0);
    }

    connectSignals();
}

NumbersSelectorForm::~NumbersSelectorForm()
{
    delete ui;
}

void NumbersSelectorForm::connectSignals() {
    connect(pCheckBoxAll, SIGNAL(stateChanged(int)), this, SLOT(selectAll(int)));
    connect(pColMapper, SIGNAL(mapped(int)), this, SLOT(selectCol(int)));
    connect(pNumMapper, SIGNAL(mapped(int)), this, SLOT(selectNum(int)));
    connect(pRowMapper, SIGNAL(mapped(int)), this, SLOT(selectRow(int)));
}

void NumbersSelectorForm::disconnectSignals() {
    pCheckBoxAll->disconnect(pCheckBoxAll, 0, 0, 0);
    pColMapper->disconnect(pColMapper, 0, 0, 0);
    pNumMapper->disconnect(pNumMapper, 0, 0, 0);
    pRowMapper->disconnect(pRowMapper, 0, 0, 0);
}

QList<quint8> NumbersSelectorForm::getSelectedNumbers() {
    QList<quint8> vRes;
    vRes.reserve(_NUM_SELECTOR_SIZE);

    for ( int  i = 0 ; i < _NUM_SELECTOR_SIZE ; i ++ ) {
        QCheckBox *pCheckBox = pNumSelector.at(i);
        if ( pCheckBox->checkState() == Qt::Checked ) {
            vRes.append( i + 1);
        }
    }

    return vRes;
}

void NumbersSelectorForm::selectAll(int eState) {
    disconnectSignals();

    for ( int i = 0 ; i < _COL_SELECTOR_SIZE ;  i++ ) {
        QCheckBox *pCheckBox = pColSelector.at(i);
        switch( eState ) {
        case Qt::Checked:
        case Qt::Unchecked:
            pCheckBox->setCheckState((Qt::CheckState) eState);
            break;
        default:
            break;
        }
    }

    for ( int i = 0 ; i < _NUM_SELECTOR_SIZE ;  i++ ) {
        QCheckBox *pCheckBox = pNumSelector.at(i);
        switch( eState ) {
        case Qt::Checked:
        case Qt::Unchecked:
            pCheckBox->setCheckState((Qt::CheckState) eState);
            break;
        default:
            break;
        }
    }

    for ( int i = 0; i < _ROW_SELECTOR_SIZE ;  i++ ) {
        QCheckBox *pCheckBox = pRowSelector.at(i);
        switch( eState ) {
        case Qt::Checked:
        case Qt::Unchecked:
            pCheckBox->setCheckState((Qt::CheckState) eState);
            break;
        default:
            break;
        }
    }

    connectSignals();
    _EMIT_UPDATE
}

void NumbersSelectorForm::selectCol(int index) {
    disconnectSignals();

    if ( Qt::PartiallyChecked == pColSelector.at(index)->checkState() ) {
        pColSelector.at(index)->setChecked(true);
    }
    int count = 0;
    for ( int i = 0 ; i < _ROW_SELECTOR_SIZE ; i ++ ) {
        pNumSelector.at( i * _COL_SELECTOR_SIZE + index )->setChecked( Qt::Checked == pColSelector.at(index)->checkState()  );
        count = 0;
        for ( int j = 0 ; j < _COL_SELECTOR_SIZE ; j++ ) {
            if ( pNumSelector.at( i * _COL_SELECTOR_SIZE + j )->isChecked() ) {
                ++count;
            }
        }
        switch ( count ) {
        case 0:
            pRowSelector.at(i)->setCheckState(Qt::Unchecked);
            break;
        case _COL_SELECTOR_SIZE:
            pRowSelector.at(i)->setCheckState(Qt::Checked);
            break;
        default:
            pRowSelector.at(i)->setCheckState(Qt::PartiallyChecked);
            break;
        }
    }

    count = 0;
    for ( int i = 0 ; i < _ROW_SELECTOR_SIZE ; i++ ) {
        for ( int j = 0 ; j < _COL_SELECTOR_SIZE ; j++ )
        if ( pNumSelector.at( i * _COL_SELECTOR_SIZE + j )->isChecked() ) {
            ++count;
        }
    }
    switch ( count ) {
    case 0:
        pCheckBoxAll->setCheckState(Qt::Unchecked);
        break;
    case _NUM_SELECTOR_SIZE:
        pCheckBoxAll->setCheckState(Qt::Checked);
        break;
    default:
        pCheckBoxAll->setCheckState(Qt::PartiallyChecked);
        break;
    }

    connectSignals();
    _EMIT_UPDATE
}

void NumbersSelectorForm::selectNum(int index) {
    disconnectSignals();

    int col = index % _COL_SELECTOR_SIZE;
    int row = index / _COL_SELECTOR_SIZE;

    int count = 0;
    for ( int i = 0 ; i < _ROW_SELECTOR_SIZE ; i++ ) {
        if ( pNumSelector.at( i * _COL_SELECTOR_SIZE + col)->isChecked() ) {
            ++count;
        }
    }
    switch ( count ) {
    case 0:
        pColSelector.at(col)->setCheckState(Qt::Unchecked);
        break;
    case _ROW_SELECTOR_SIZE:
        pColSelector.at(col)->setCheckState(Qt::Checked);
        break;
    default:
        pColSelector.at(col)->setCheckState(Qt::PartiallyChecked);
        break;
    }

    count = 0;
    for ( int i = 0 ; i < _COL_SELECTOR_SIZE ; i++ ) {
        if ( pNumSelector.at( row * _COL_SELECTOR_SIZE + i)->isChecked() ) {
            ++count;
        }
    }
    switch ( count ) {
    case 0:
        pRowSelector.at(row)->setCheckState(Qt::Unchecked);
        break;
    case _COL_SELECTOR_SIZE:
        pRowSelector.at(row)->setCheckState(Qt::Checked);
        break;
    default:
        pRowSelector.at(row)->setCheckState(Qt::PartiallyChecked);
        break;
    }

    count = 0;
    for ( int i = 0 ; i < _ROW_SELECTOR_SIZE ; i++ ) {
        for ( int j = 0 ; j < _COL_SELECTOR_SIZE ; j++ )
        if ( pNumSelector.at( i * _COL_SELECTOR_SIZE + j )->isChecked() ) {
            ++count;
        }
    }
    switch ( count ) {
    case 0:
        pCheckBoxAll->setCheckState(Qt::Unchecked);
        break;
    case _NUM_SELECTOR_SIZE:
        pCheckBoxAll->setCheckState(Qt::Checked);
        break;
    default:
        pCheckBoxAll->setCheckState(Qt::PartiallyChecked);
        break;
    }

    connectSignals();
    emit numSelectionChangedSignal(getSelectedNumbers());
}

void NumbersSelectorForm::selectRow(int index) {
    disconnectSignals();

    if ( Qt::PartiallyChecked == pRowSelector.at(index)->checkState() ) {
        pRowSelector.at(index)->setChecked(true);
    }

    int count = 0;
    for ( int i = 0 ; i < _COL_SELECTOR_SIZE ; i++ ) {
        pNumSelector.at( index * _COL_SELECTOR_SIZE + i )->setChecked( Qt::Checked == pRowSelector.at(index)->checkState() );
        count = 0;
        for ( int j = 0; j < _ROW_SELECTOR_SIZE ; j++ ) {
            if ( pNumSelector.at( j * _COL_SELECTOR_SIZE + i)->isChecked() ) {
                ++count;
            }
        }
        switch ( count ) {
        case 0:
            pColSelector.at(i)->setCheckState(Qt::Unchecked);
            break;
        case _ROW_SELECTOR_SIZE:
            pColSelector.at(i)->setCheckState(Qt::Checked);
            break;
        default:
            pColSelector.at(i)->setCheckState(Qt::PartiallyChecked);
            break;
        }
    }

    count = 0;
    for ( int i = 0 ; i < _ROW_SELECTOR_SIZE ; i++ ) {
        for ( int j = 0 ; j < _COL_SELECTOR_SIZE ; j++ )
        if ( pNumSelector.at( i * _COL_SELECTOR_SIZE + j )->isChecked() ) {
            ++count;
        }
    }
    switch ( count ) {
    case 0:
        pCheckBoxAll->setCheckState(Qt::Unchecked);
        break;
    case _NUM_SELECTOR_SIZE:
        pCheckBoxAll->setCheckState(Qt::Checked);
        break;
    default:
        pCheckBoxAll->setCheckState(Qt::PartiallyChecked);
        break;
    }

    connectSignals();

    _EMIT_UPDATE
}


