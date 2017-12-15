#include <QObject>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>

#include "mxleddialog.h"
#include "mxledindicator.h"
#include "mxde.h"

char *led_name[5];
char *led_statu[5];

MxLedDialog::MxLedDialog(QObject *obj, QWidget *parent):QDialog(parent)
{
    m_mxde = new MxDE(this);

    loadLeds();

    createHorizontalGroupBox();

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(horizontalGroupBox);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    setWindowTitle(tr("Basic Layouts"));
    QDesktopWidget *desk = QApplication::desktop();
    QRect deskRect = desk->availableGeometry();
    this->resize(QSize(800,480));
    this->move((deskRect.width()-this->width())/2, (deskRect.height()-this->height())/2);

    connect(this, SIGNAL(click_Button(int)), this, SLOT(on_click_Button(int)));

}
//! [5]
void MxLedDialog::getLedNameAndStatus()
{
    QString led_list = m_mxde->callGetLedList();

    qDebug() << led_list;

    m_ledList = led_list.split("\n");
    m_ledNum = m_ledList.count()-1;
    qDebug("led_num:%d",m_ledNum);


    for(int i=0;i<m_ledNum;i++)
    {

         QStringList strstrlist=m_ledList.at(i).split(" ");
         for(int j=0;j<strstrlist.count();)
         {

          led_name[i] = strdup(strstrlist.at(j++).toLocal8Bit().data());
          led_statu[i] = strdup(strstrlist.at(j++).toLocal8Bit().data());
          qDebug("%s %s",led_name[i],led_statu[i]);
         }
    }
}
void MxLedDialog::loadLeds()
{
    getLedNameAndStatus();
    for (int i = 0; i < m_ledNum; ++i){
        MxLedIndicator *led = new MxLedIndicator(this);
        QString ledName = QString(led_name[i]);
        led->setLedSize(30);
        led->setLedName(ledName);
        QString str = led_statu[i];
        if( str.toInt() > 1)
        {
            led->setState(0);
            m_mxde->callSetLedBrightness(ledName,0);
        }
        else
        {
            led->setState(str.toInt());
        }
        leds.append(led);
    }
}


void MxLedDialog::createHorizontalGroupBox()
{
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    horizontalGroupBox = new QGroupBox(tr("LED TEST"));
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < leds.size(); ++i) {
 //      buttons[i] = new QPushButton(leds.at(i)->getLedName());
        QVBoxLayout *ledLayout = new QVBoxLayout();
        QPushButton *ledButton = new QPushButton();
        ledButton->setText(leds.at(i)->getLedName());
        connect(ledButton, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(ledButton, QString::number(i, 10));

        ledLayout->addWidget(leds.at(i),0,Qt::AlignHCenter);
        ledLayout->addWidget(ledButton);

        layout->addLayout(ledLayout);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchSelectedLedButtoIndex(QString)));
    horizontalGroupBox->setLayout(layout);
}

void MxLedDialog::switchSelectedLedButtoIndex(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);

    emit click_Button(current_index);
}

void MxLedDialog::on_click_Button(int index)
{
    qDebug() << "clicked " << index << endl;
    MxLedIndicator *led = leds.at(index);
    QString ledName = QString(led_name[index]);

//    leds.at(index)->toggle();
    if(led->getState() == true){
       //m_bus->callGetLedList("{\"request\":\"led\",\"operation\": \"set\",\"param\":{\"name\": \"myd:green:user3\", \"value\": 0 }}");

        m_mxde->callSetLedBrightness(ledName,0);

        //ledbus->Method();
        led->setState(false);
    }
    else
    {

        //m_bus->callGetLedList("{\"request\":\"led\",\"operation\": \"set\",\"param\":{\"name\": \"myd:green:user3\", \"value\": 1 }}");
         m_mxde->callSetLedBrightness(ledName,1);
        //ledbus->Method();
        led->setState(true);

    }
}

void MxLedDialog::onLedBrightnessChanged(QString &message)
{
    qDebug() << "onLedBrightnessChanged " << message << "\n" << endl;
}
