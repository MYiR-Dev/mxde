#include "systemcontentwidget.h"

#include <QDebug>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QVBoxLayout>
#include <QLabel>
#include <QStandardItemModel>
#include "mxde.h"
#include "systemcontentwidget.h"
#include "mxde.h"
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

    //this->setFixedSize(800, 480);
   // OTHER_CONTENT_HEIGHT();
    m_info_label = new QLabel(this);
    m_info_label->adjustSize();
    m_info_label->setGeometry(130,0,m_width-130,m_height);
    m_info_label->setWordWrap(true);
    m_info_label->setAlignment(Qt::AlignTop);

    m_category_widget = new QListWidget(this);
    m_category_widget->setFixedSize(130, m_height);
    m_category_widget->setFocusPolicy(Qt::NoFocus);
    m_category_widget->setObjectName("infoList");

    m_category_widget->setIconSize(QSize(16, 16));//设置QListWidget中的单元项的图片大小
    m_category_widget->setResizeMode(QListView::Adjust);
    m_category_widget->setViewMode(QListView::ListMode);   //设置QListWidget的显示模式
    m_category_widget->setMovement(QListView::Static);//设置QListWidget中的单元项不可被拖动


    QStringList type_list,icon_list;
    type_list << tr("System")  << tr("CPU") << tr("Memory") << tr("Storage");
    icon_list << "system.png" << "cpu.png" << "memory.png" << "storage.png";

    for(int i = 0;i < type_list.length();i ++) {
        QIcon icon;
        icon.addFile(":/res/hardware/" + icon_list.at(i), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *item = new QListWidgetItem(type_list.at(i), m_category_widget);
        item->setSizeHint(QSize(120,36));
        item->setIcon(icon);
    }

    connect(m_category_widget,SIGNAL(currentRowChanged(int)),this,SLOT(changeInfoPage(int)));

    m_category_widget->setCurrentRow(0);


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

void SystemContentWidget::setDbusProxy(MxDE *mxde)
{
    m_mxde = mxde;
}

void SystemContentWidget::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}

void SystemContentWidget::changeInfoPage(int row) {

    switch(row){

        case 0:{
            QString SystemInfo = m_mxde->callgetSystemInfo();
            m_info_label->setText(SystemInfo);
            break;
        }
        case 1:{
            QString CpuInfo = m_mxde->callgetCpuInfo();
            m_info_label->setText(CpuInfo);
            break;
        }
        case 2:{
            QString MemoryInfo = m_mxde->callgetMemoryInfo();
            m_info_label->setText(MemoryInfo);
            break;
        }
         case 3:{
            QString StorageInfo = m_mxde->callgetStorageInfo();
            m_info_label->setText(StorageInfo);
            break;
        }
        default:
            break;
    }
}
