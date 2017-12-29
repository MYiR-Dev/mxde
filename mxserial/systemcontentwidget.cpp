/******************************************************************************
* Copyright (C), 2016-2017, Sunny.Guo
* FileName:
* Author: Sunny.Guo
* Version: 1.0
* Date:
* Description:
*
* History:
*  <author>  	<time>   	<version >   	<desc>
*  Sunny.Guo   	19/01/2017      1.0     	create this moudle
*
* Licensed under GPLv2 or later, see file LICENSE in this source tree.
*******************************************************************************/
#include "systemcontentwidget.h"
#include "mxde.h"
#include "constant.h"
#include "mxapplication.h"

#include <QObject>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSignalMapper>
#include <QDirIterator>
#include <QStringList>
#include <QPalette>

SystemContentWidget::SystemContentWidget(QWidget *parent, MxApplication *obj, int width , int height )
            :BaseWidget(parent,obj)
{
    openFlag = false;

    m_width = width;
    if(m_width <=0){
        m_width = DEFAULT_SCREEN_WIDTH;
    }
    m_height = height;
    if(m_height <= 0){
        m_height = DEFAULT_SCREEN_HEIGHT;
    }

    this->setFixedSize(m_width, m_height);

    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);
}

SystemContentWidget::~SystemContentWidget()
{
    m_mxde->callCloseSerialPort(m_serial_fd);

}

void SystemContentWidget::SerialPortInit()
{

    QString str = m_mxde->callGetSerialList();
    if((str!=NULL) &&(str.length() < 2)){
        return;
    }

    QStringList list = str.split("\n");
    m_serial_num = list.count()-1;
    qDebug() << "m_serial_num: " << m_serial_num ;


    for(int i=0;i<m_serial_num;i++)
    {


       m_serial_name[i] = strdup(list.at(i).toLocal8Bit().data());

       qDebug("%s",m_serial_name[i]);
       mSerialPortComboBox->addItem(QString(m_serial_name[i]));
    }
}


void SystemContentWidget::createSettingGroupBox()
{
    m_SettingGroup = new QGroupBox(tr("Settings"));
    m_SettingLayout = new QGridLayout(m_SettingGroup);
    mSerialPort = new QLabel(m_SettingGroup);
    mSerialPort->setText(tr("Port:"));
    mSerialPortComboBox = new QComboBox(m_SettingGroup);
    QHBoxLayout *hLayout1 = new QHBoxLayout(m_SettingGroup);
    hLayout1->addWidget(mSerialPort);
    hLayout1->addWidget(mSerialPortComboBox);

    mSerialBaudRate = new QLabel(m_SettingGroup);
    mSerialBaudRate->setText(tr("Baud:"));
    mSerialBaudRateComboBox =  new QComboBox(m_SettingGroup);
    mSerialBaudRateComboBox->insertItems(0,QStringList() \
          <<"300"<<"600"<<"1200"<< "2400" \
          <<"4800"<<"9600"<<"19200"<<"38400" \
          <<"57600"<<"115200") ;
    QHBoxLayout *hLayout2 = new QHBoxLayout(m_SettingGroup);
    hLayout2->addWidget(mSerialBaudRate);
    hLayout2->addWidget(mSerialBaudRateComboBox);

    mSerialCheckBit = new QLabel(m_SettingGroup);
    mSerialCheckBit->setText(tr("Check:"));
    mSerialCheckBitComboBox =  new QComboBox(m_SettingGroup);
    mSerialCheckBitComboBox->insertItems(0,QStringList()<<tr("NONE")<<tr("EVENT")<<tr("ODD"));
    QHBoxLayout *hLayout3 = new QHBoxLayout(m_SettingGroup);
    hLayout3->addWidget(mSerialCheckBit);
    hLayout3->addWidget(mSerialCheckBitComboBox);

    mSerialDataBit = new QLabel(m_SettingGroup);
    mSerialDataBit->setText(tr("Data:"));
    mSerialDataBitComboBox =  new QComboBox(m_SettingGroup);
    mSerialDataBitComboBox->insertItems(0,QStringList()<<"8"<<"7"<<"6");
    QHBoxLayout *hLayout4 = new QHBoxLayout(m_SettingGroup);
    hLayout4->addWidget(mSerialDataBit);
    hLayout4->addWidget(mSerialDataBitComboBox);

    mSerialStopBit = new QLabel(m_SettingGroup);
    mSerialStopBit->setText(tr("Stop:"));
    mSerialStopBitComboBox =  new QComboBox(m_SettingGroup);
    mSerialStopBitComboBox->insertItems(0,QStringList()<<"1"<<"2");
    QHBoxLayout *hLayout5 = new QHBoxLayout(m_SettingGroup);
    hLayout5->addWidget(mSerialStopBit);
    hLayout5->addWidget(mSerialStopBitComboBox);

    QHBoxLayout *hLayout6 = new QHBoxLayout(m_SettingGroup);
    mSerialOpenButton = new QPushButton;
    mSerialOpenButton->setText(tr("Open"));
    hLayout6->addWidget(mSerialOpenButton);
    if(m_width < DEFAULT_SCREEN_WIDTH){
        m_SettingLayout->addLayout(hLayout1,0,0,1,1);
        m_SettingLayout->addLayout(hLayout2,1,0,1,1);
        m_SettingLayout->addLayout(hLayout3,2,0,1,1);
        m_SettingLayout->addLayout(hLayout4,3,0,1,1);
        m_SettingLayout->addLayout(hLayout5,4,0,1,1);
        m_SettingLayout->addLayout(hLayout6,5,0,1,1);
    }
    else
    {
    m_SettingLayout->addLayout(hLayout1,0,0,1,1);
    m_SettingLayout->addLayout(hLayout2,0,1,1,1);
    m_SettingLayout->addLayout(hLayout3,0,2,1,1);
    m_SettingLayout->addLayout(hLayout4,0,3,1,1);
    m_SettingLayout->addLayout(hLayout5,0,4,1,1);
    m_SettingLayout->addLayout(hLayout6,1,0,1,1);
    }

    m_SettingGroup->setLayout(m_SettingLayout);
}

void SystemContentWidget::createSendGroupBox()
{
    m_SendGroup = new QGroupBox(tr("Send"));
    m_SendLayout = new QGridLayout(m_SendGroup);

    m_SendTextEdit1 = new QTextEdit(m_SendGroup);
    m_SendPushButton = new QPushButton(m_SendGroup);
    m_SendPushButton->setText(tr("Send"));

    QVBoxLayout *vLayout = new QVBoxLayout(m_SendGroup);
    vLayout->addWidget(m_SendPushButton);

    m_SendLayout->addWidget(m_SendTextEdit1,0,0,2,99);
    m_SendLayout->addLayout(vLayout,1,100,1,1,Qt::AlignBottom);
    m_SendLayout->setColumnMinimumWidth(100,80);

    m_SendGroup->setLayout(m_SendLayout);
}

void SystemContentWidget::createRecvGroupBox()
{
    m_RecvGroup = new QGroupBox(tr("Received"));
    m_RecvLayout = new QGridLayout(m_RecvGroup);

    m_ClearPushButton = new QPushButton(m_RecvGroup);
    m_ClearPushButton->setText(tr("Clear"));
    m_RecvTextEdit1 = new QTextEdit(m_RecvGroup);
    QVBoxLayout *vLayout = new QVBoxLayout(m_RecvGroup);
    vLayout->addWidget(m_ClearPushButton);

    m_RecvLayout->addWidget(m_RecvTextEdit1,0,0,2,99);
    m_RecvLayout->addLayout(vLayout,1,100,1,1,Qt::AlignBottom);
    m_RecvLayout->setColumnMinimumWidth(100,80);
    m_RecvGroup->setLayout(m_RecvLayout);

}

void SystemContentWidget::initUI()
{
    createSettingGroupBox();
    createSendGroupBox();
    createRecvGroupBox();

    mainLayout = new QGridLayout;
    if(m_width < DEFAULT_SCREEN_WIDTH){
        m_SettingGroup->setObjectName("microGroupBox");
        m_SendGroup->setObjectName("microGroupBox");
        m_RecvGroup->setObjectName("microGroupBox");
        m_SendPushButton->setObjectName("microButton");
        m_ClearPushButton->setObjectName("microButton");
        mSerialPort->setObjectName("microblackLabel");
        mSerialBaudRate->setObjectName("microblackLabel");
        mSerialCheckBit->setObjectName("microblackLabel");
        mSerialDataBit->setObjectName("microblackLabel");
        mSerialStopBit->setObjectName("microblackLabel");
        mSerialPortComboBox->setObjectName("microComboBox");
        mSerialBaudRateComboBox->setObjectName("microComboBox");
        mSerialCheckBitComboBox->setObjectName("microComboBox");
        mSerialDataBitComboBox->setObjectName("microComboBox");
        mSerialStopBitComboBox->setObjectName("microComboBox");
        m_SendLayout->setColumnMinimumWidth(100,50);
        m_RecvLayout->setColumnMinimumWidth(100,50);
        m_SettingGroup->setMaximumWidth(150);
        mainLayout->addWidget(m_SettingGroup, 0,0,2,1);
        mainLayout->addWidget(m_SendGroup,0,1,1,4);
        mainLayout->addWidget(m_RecvGroup,1,1,1,4);
    }
    else
    {
        mainLayout->addWidget(m_SettingGroup, 0,0);
        mainLayout->addWidget(m_SendGroup,1,0);
        mainLayout->addWidget(m_RecvGroup, 2,0);
    }

    SerialPortInit();
    this->setLayout(mainLayout);
}
void SystemContentWidget::setApplication(MxApplication *app)
{
    m_app = app;
}

void SystemContentWidget::setDbusProxy(MxDE *mxde)
{
    m_mxde = mxde;
}

void SystemContentWidget::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}


void SystemContentWidget::initConnection()
{

//    connect(timer, SIGNAL(timeout()), this, SLOT(timeOutEvent()));
//    connect(systemTimer, SIGNAL(timeout()), this, SLOT(systemTimeUpdate()));
    connect(m_RecvTextEdit1, SIGNAL(textChanged()), this, SLOT(autoScroll()));
    connect(mSerialBaudRateComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    connect(mSerialCheckBitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    connect(mSerialDataBitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    connect(mSerialStopBitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    connect(mSerialOpenButton, SIGNAL(clicked()), this, SLOT(on_openPushButton_clicked()));
    connect(m_SendPushButton,SIGNAL(clicked()),this, SLOT(on_sendPushButton_clicked()));
    connect(m_ClearPushButton,SIGNAL(clicked()),this, SLOT(on_clearPushButton_clicked()));
}

void SystemContentWidget::display()
{

}

void SystemContentWidget::showInRecvText(QString str)
{
    recvNum += str.length();
    if(0)
    {
        bool ok = true;
        QString result = QString::number(str.toInt(&ok, 10),16);
        if(ok)
        {
            m_RecvTextEdit1->insertPlainText(result.toUtf8());
        }
        else
        {
            result = "";
            for(int i = 0; i < str.length(); ++i)
            {
                result += QString::number(str[i].toLatin1());
            }
            m_RecvTextEdit1->insertPlainText(result.toUtf8());
        }
    }
    else
    {
        m_RecvTextEdit1->insertPlainText(str.toUtf8());
    }
}

void SystemContentWidget::SerialPortInitSlots()
{
    SerialPortInit();
}

void SystemContentWidget::autoScroll()
{
    QTextCursor cursor = m_RecvTextEdit1->textCursor();
    cursor.movePosition(QTextCursor::End);
    m_RecvTextEdit1->setTextCursor(cursor);
}

void SystemContentWidget::reLoadSerialPort()
{
    if(openFlag)
    {
        on_openPushButton_clicked();
    }
}

void SystemContentWidget::on_openPushButton_clicked()
{
    if(!openFlag)
    {
        QString serialPortStr = mSerialPortComboBox->currentText().isEmpty() ? "" : mSerialPortComboBox->currentText();
        QString rateStr = mSerialBaudRateComboBox->currentText().isEmpty() ? "" : mSerialBaudRateComboBox->currentText();
        QString checkBitStr = mSerialCheckBitComboBox->currentText().isEmpty() ? "" : mSerialCheckBitComboBox->currentText();
        QString dataBitStr = mSerialDataBitComboBox->currentText().isEmpty() ? "" : mSerialDataBitComboBox->currentText();
        QString stopBbitStr = mSerialStopBitComboBox->currentText().isEmpty() ? "" : mSerialStopBitComboBox->currentText();

        qDebug() << "port: " << serialPortStr;
        qDebug() << "rate: " << rateStr;
        qDebug() << "check: " << checkBitStr;
        qDebug() << "data: " << dataBitStr;
        qDebug() << "stop: " << stopBbitStr;

        if(serialPortStr == "")
        {
            QMessageBox::information(this, tr("Warning"), tr("Do not find any serial port!"));
            return;
        }

        if(!rateStr.isNull() && !checkBitStr.isNull() && !dataBitStr.isNull() && !stopBbitStr.isNull())
        {
            bool rateOK = false;
            bool dataOK = false;
            bool stopOK = false;
            serialPortStr = "/dev/" + serialPortStr;

        }
        else
        {
            QMessageBox::information(this, tr("Error"), tr("Failed to open serial port!"));
            exit(0);
        }
        qDebug() << "serialPortStr: " << serialPortStr;
        m_serial_fd = m_mxde->callOpenSerialPort(serialPortStr);
        qDebug() << "open ret: " << m_serial_fd;
        if(-1 == m_serial_fd)
        {
            perror("open error");
            qDebug() << "open error errno: " <<  errno;
            if(errno == 13)
            {
                QMessageBox::information(this, tr("Error"), tr("Do not have access permission!"));
            }
            else
            {
                QMessageBox::information(this, tr("Error"), tr("Failed to open serial port!"));
            }
            m_mxde->callCloseSerialPort(m_serial_fd);
        }
        else
        {

            QString serial_param;
            int serial_mode = 0;
            int tty_flow = 0;
            QByteArray check = checkBitStr.toLatin1();

            serial_param.sprintf("%d %d %d %d %d %s %d",m_serial_fd,rateStr.toInt(),dataBitStr.toInt(), serial_mode, serial_mode,check.data(),stopBbitStr.toInt());
            m_mxde->callSetSerialPort(serial_param);

            mSerialOpenButton->setText(tr("Close"));
            openFlag = true;
//            label->setText(QString::fromUtf8("     串口状态：　打开"));
            sendNum = 0;
            recvNum = 0;

        }
    }
    else    // 关闭串口
    {
        m_mxde->callCloseSerialPort(m_serial_fd);
        m_serial_fd = 0;
        mSerialOpenButton->setText(tr("Open"));
        openFlag = false;
       // label->setText(QString::fromUtf8("     串口状态：　关闭"));

        //autosendFlag = false;
        qDebug() << "closed ...";
    }
}

void SystemContentWidget::on_clearPushButton_clicked()
{
    m_RecvTextEdit1->clear();
}

void SystemContentWidget::on_sendPushButton_clicked()
{
    if(openFlag)
    {
        bool ok = true;
        QString sendStr;


        sendStr =  m_SendTextEdit1->toPlainText();

        if(ok)
        {
            sendNum += sendStr.length();
            m_mxde->callSerialWrite(m_serial_fd,sendStr,sendStr.length());

        }
        else
        {
            QString result;
            sendStr =  m_SendTextEdit1->toPlainText();
            for(int i = 0; i < sendStr.length(); ++i)
            {
                QString tmpStr = QString::number(sendStr[i].toLatin1(), 16);
                result += tmpStr;
            }
            sendNum += sendStr.length();
            m_mxde->callSerialWrite(m_serial_fd,sendStr
                                            ,sendStr.length());

        }
        m_SendTextEdit1->clear();

    }
    else
    {
        QMessageBox::information(this, tr("Warning"), tr("Please open serial port first!"));
    }
}

void SystemContentWidget::timeOutEvent()
{

}

void SystemContentWidget::systemTimeUpdate()
{

}

void SystemContentWidget::onSerialRecvData(int uart_fd, const QString &data, int size)
{

    recvNum += data.length();
    if(0)
    {
        bool ok = true;
        QString result = QString::number(data.toInt(&ok, 10),16);
        if(ok)
        {
            m_RecvTextEdit1->insertPlainText(result.toUtf8());
        }
        else
        {
            result = "";
            for(int i = 0; i < data.length(); ++i)
            {
                result += QString::number(data[i].toLatin1());
            }
            m_RecvTextEdit1->insertPlainText(result.toUtf8());
        }
    }
    else
    {
        m_RecvTextEdit1->insertPlainText(data.toUtf8());
    }
}
