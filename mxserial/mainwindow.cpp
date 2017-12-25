#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <errno.h>
#include <QString>
#include "mxde.h"
#define DBUS_SERVICE_NAME "com.myirtech.mxde"
#define DBUS_SERVICE_PATH "/com/myirtech/mxde"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openFlag = false;
    timerFlag = false;
    autosendFlag = false;
    recvNum = 0;
    sendNum = 0;


    timer = new QTimer;
    label = new QLabel;
    systemLabel = new QLabel;
    systemTimer = new QTimer;
    sendLable = new QLabel;
    recvLable = new QLabel;

    m_mxde = new MxDE(this);
    systemTimer->setInterval(1000);

    //QObject::connect(mxde_session_iface,SIGNAL(sigSerialRecv(int,const QString,int)),this,SLOT(serial_recv_data(int,const QString,int)));
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(timeOutEvent()));
    QObject::connect(systemTimer, SIGNAL(timeout()), this, SLOT(systemTimeUpdate()));
    QObject::connect(ui->recvTextEdit, SIGNAL(textChanged()), this, SLOT(autoScroll()));
    QObject::connect(ui->rateComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    QObject::connect(ui->checkBitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    QObject::connect(ui->dataBitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));
    QObject::connect(ui->stopBitComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(reLoadSerialPort()));


    SerialPortInit();

    label->setText(QString::fromUtf8("     串口状态：　关闭"));
    ui->statusBar->addWidget(label);

    recvLable->setText(QString::fromUtf8("\t接收：") + QString::number(recvNum));
    ui->statusBar->addWidget(recvLable);

    sendLable->setText(QString::fromUtf8("\t发送：") + QString::number(sendNum));
    ui->statusBar->addWidget(sendLable);

    systemLabel->setText(QString::fromUtf8("\t当前时间：") + QTime::currentTime().toString());
    ui->statusBar->addWidget(systemLabel);

    systemTimer->start();

}

MainWindow::~MainWindow()
{

    systemTimer->stop();
    delete ui;

    delete timer;
    delete label;
    delete systemLabel;
    delete systemTimer;
    delete recvLable;
    delete sendLable;
}

void MainWindow::systemTimeUpdate()
{
    recvLable->setText(QString::fromUtf8("\t接收：") + QString::number(recvNum));
    sendLable->setText(QString::fromUtf8("\t发送：") + QString::number(sendNum));
    systemLabel->setText(QString::fromUtf8("\t当前时间：") + QTime::currentTime().toString());
}

void MainWindow::reLoadSerialPort()
{
    if(openFlag)
    {
        on_openPushButton_clicked();
    }
}

// 接收区自动滚屏
void MainWindow::autoScroll()
{
    QTextCursor cursor =  ui->recvTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->recvTextEdit->setTextCursor(cursor);
}

// 显示收到的数据的槽
void MainWindow::showInRecvText(QString str)
{
    recvNum += str.length();
    if(0)
    {
        bool ok = true;
        QString result = QString::number(str.toInt(&ok, 10),16);
        if(ok)
        {
            ui->recvTextEdit->insertPlainText(result.toUtf8());
        }
        else
        {
            result = "";
            for(int i = 0; i < str.length(); ++i)
            {
                result += QString::number(str[i].toLatin1());
            }
            ui->recvTextEdit->insertPlainText(result.toUtf8());
        }
    }
    else
    {
        ui->recvTextEdit->insertPlainText(str.toUtf8());
    }
}

//  初始化槽，用于动态加载当前的串口到combobox
void MainWindow::SerialPortInitSlots()
{
    SerialPortInit();
}

//　初始化函数，获取当前的所有串口
void MainWindow::SerialPortInit()
{

    QString str = m_mxde->callGetSerialList();

    QStringList list = str.split("\n");
    m_serial_num = list.count()-1;
    qDebug() << "m_serial_num: " << m_serial_num ;


    for(int i=0;i<m_serial_num;i++)
    {


       m_serial_name[i] = strdup(list.at(i).toLocal8Bit().data());

       qDebug("%s",m_serial_name[i]);
       ui->serialPortComboBox->addItem(QString(m_serial_name[i]).mid(5));
    }

}

// 打开串口，且开启线程读取串口
void MainWindow::on_openPushButton_clicked()
{
    if(!openFlag)
    {
        QString serialPortStr = ui->serialPortComboBox->currentText().isEmpty() ? "" : ui->serialPortComboBox->currentText();
        QString rateStr = ui->rateComboBox->currentText().isEmpty() ? "" : ui->rateComboBox->currentText();
        QString checkBitStr = ui->checkBitComboBox->currentText().isEmpty() ? "" : ui->checkBitComboBox->currentText();
        QString dataBitStr = ui->dataBitComboBox->currentText().isEmpty() ? "" : ui->dataBitComboBox->currentText();
        QString stopBbitStr = ui->stopBitComboBox->currentText().isEmpty() ? "" : ui->stopBitComboBox->currentText();

        qDebug() << "port: " << serialPortStr;
        qDebug() << "rate: " << rateStr;
        qDebug() << "check: " << checkBitStr;
        qDebug() << "data: " << dataBitStr;
        qDebug() << "stop: " << stopBbitStr;

        if(serialPortStr == "")
        {
            QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromUtf8("未找到串口"));
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
            QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromUtf8("串口异常"));
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
                QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromUtf8("请使用root权限"));
            }
            else
            {
                QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromUtf8("串口异常"));
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

            ui->openPushButton->setText(QString::fromUtf8("关闭串口"));
            openFlag = true;
            label->setText(QString::fromUtf8("     串口状态：　打开"));
            sendNum = 0;
            recvNum = 0;

        }
    }
    else    // 关闭串口
    {
        m_mxde->callCloseSerialPort(m_serial_fd);
        m_serial_fd = 0;
        ui->openPushButton->setText(QString::fromUtf8("打开串口"));
        openFlag = false;
        label->setText(QString::fromUtf8("     串口状态：　关闭"));

        autosendFlag = false;
        qDebug() << "closed ...";
    }
}

// 清空接收区
void MainWindow::on_clearRecvPushButton_clicked()
{
    ui->recvTextEdit->clear();
}

// 发送，清空发送区
void MainWindow::on_sendPushButton1_clicked()
{
    if(openFlag)
    {
        bool ok = true;
        QString sendStr;


        sendStr = ui->sendTextEdit1->toPlainText();

        if(ok)
        {
            sendNum += sendStr.length();
            m_mxde->callSerialWrite(m_serial_fd,sendStr,sendStr.length());

        }
        else
        {
            QString result;
            sendStr = ui->sendTextEdit1->toPlainText();
            for(int i = 0; i < sendStr.length(); ++i)
            {
                QString tmpStr = QString::number(sendStr[i].toLatin1(), 16);
                result += tmpStr;
            }
            sendNum += sendStr.length();
            m_mxde->callSerialWrite(m_serial_fd,sendStr
                                            ,sendStr.length());

        }
        ui->sendTextEdit1->clear();

    }
    else
    {
        QMessageBox::information(this, QString::fromUtf8("提示"), QString::fromUtf8("请打开串口"));
    }
}



void MainWindow::timeOutEvent()
{
    qDebug() << "time out ... ";
    on_sendPushButton1_clicked();
}


 void MainWindow::onSerialRecvData(int uart_fd, const QString &data, int size)
 {

    recvNum += data.length();
    if(0)
    {
        bool ok = true;
        QString result = QString::number(data.toInt(&ok, 10),16);
        if(ok)
        {
            ui->recvTextEdit->insertPlainText(result.toUtf8());
        }
        else
        {
            result = "";
            for(int i = 0; i < data.length(); ++i)
            {
                result += QString::number(data[i].toLatin1());
            }
            ui->recvTextEdit->insertPlainText(result.toUtf8());
        }
    }
    else
    {
        ui->recvTextEdit->insertPlainText(data.toUtf8());
    }
 }
