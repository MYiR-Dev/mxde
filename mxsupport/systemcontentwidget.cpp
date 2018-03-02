#include "systemcontentwidget.h"

#include <QDebug>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QVBoxLayout>
#include <QLabel>
#include <QSettings>
#include "systemcontentwidget.h"

#include "constant.h"
#include "mxapplication.h"
SystemContentWidget::SystemContentWidget(QWidget *parent, MxApplication *obj, int width , int height )
            :BaseWidget(parent,obj)
{


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
   // m_mxde->callCloseSerialPort(m_serial_fd);

}
void SystemContentWidget::initUI()
{

    m_support_info_label = new QLabel(this);
    m_support_info_label->setGeometry(0,0,m_width,m_height);
    QFont ft;
    ft.setPointSize(30);
    m_support_info_label->setFont(ft);
    m_support_info_label->setWordWrap(true);
    m_support_info_label->setAlignment(Qt::AlignCenter);

    QSettings           *m_Settings = NULL;
    QString             m_current_language="en";

    m_Settings = new QSettings(QString(MXDE_SETTING_FILE_PATH), QSettings::IniFormat);

    m_Settings->beginGroup("LANGUAGE");
    m_current_language = m_Settings->value("language").toString();
    if(m_current_language.isEmpty()){
        m_current_language = "en";
    }
    m_Settings->endGroup();
    m_Settings->sync();

    QString rs;
    if(m_current_language == "zh_CN"){
        rs.append(tr("Website")).append(": www.myirtech.com<br>");
        rs.append(tr("Sales Email")).append(": sales@myirtech.com<br>");
        rs.append(tr("Support Email")).append(": support.cn@myirtech.com<br>");
        rs.append(tr("Support Phone")).append(": 027-59621648<br>");
        rs.append(tr("Phone")).append(": +86-755-22984836<br>");
        rs.append(tr("Fax")).append(": +86-755-25532724<br>");
        rs.append(tr("Address: zh"));
    }
    else
    {
        rs.append(tr("Website")).append(": www.myirtech.com<br>");
        rs.append(tr("Support Email")).append(": support@myirtech.com<br>");
        rs.append(tr("Sales Email")).append(": sales@myirtech.com<br>");
        rs.append(tr("Phone")).append(": +86-755-22984836<br>");
        rs.append(tr("Fax")).append(": +86-755-25532724<br>");
        rs.append(tr("Address: Room 04, 6th Floor, Building No.2, Fada Road, Yunli Smart Park,Bantian, Longgang District, Shenzhen,Guangdong, China 518129<br>"));

    }

    m_support_info_label->setText(rs);
}

void SystemContentWidget::initConnection()
{

}

void SystemContentWidget::display()
{

}
void SystemContentWidget::setApplication(MxApplication *app)
{
    m_app = app;
}


void SystemContentWidget::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}

