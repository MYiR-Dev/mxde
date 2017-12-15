#ifndef MXLEDDIALOG_H
#define MXLEDDIALOG_H

#include <QDialog>
#include <QList>
#include <QListView>
#include <QVector>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QStringList>
#include <QDialogButtonBox>
#include <QGroupBox>
#include <QApplication>

#include "mxledindicator.h"
#include "mxde.h"

class MxLedDialog : public QDialog
{
    Q_OBJECT

public:
    MxLedDialog(QObject *obj = 0,QWidget *parent = 0);
    void loadLeds();

signals:
    void click_Button(int index);

public slots:
    void on_click_Button(int index);
    void switchSelectedLedButtoIndex(QString str);
    void onLedBrightnessChanged(QString &message);

private:
    void createMenu();
    void createHorizontalGroupBox();
    void createGridGroupBox();
    void createFormGroupBox();
    void getLedNameAndStatus();
    QDialogButtonBox *buttonBox;
    QGroupBox          *horizontalGroupBox;
    QList<MxLedIndicator *> leds;
    QStringList          m_ledList;
    int                  m_ledNum;

    MxDE                *m_mxde;
    QApplication        *m_app;
};

#endif // MXLEDDIALOG_H
