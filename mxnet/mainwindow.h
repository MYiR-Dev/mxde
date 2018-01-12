#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMetaType>
#include <QtDBus/QDBusReply>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtNetwork/QHostAddress>
namespace Ui {
class MainWindow;
}
struct arrayElement
{
  QDBusObjectPath objpath;
  QMap<QString,QVariant> objmap;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QList<arrayElement>   services_list;
    QDBusObjectPath objpath;
    QMap<QString,QVariant> objmap;
    QMap<QString,QVariant> ipv4map;
    QStringList sl_ipv4_method;
    void netPortInit();
    void test();
    void changeConnection();
    void setNetPort();
    void getServices();
    void setNetPortComboBox();
    QString getDeviceName(const QDBusObjectPath& objpath);
    bool extractMapData(QMap<QString,QVariant>& r_map, const QVariant& r_var);
    bool getArray(QList<arrayElement>& r_list, const QDBusMessage& r_msg );
    void getServiceDetails(int index);
    void updateDisplayWidgets();
    QDBusMessage::MessageType processReply(const QDBusMessage& reply);
    QDBusInterface* con_manager;
private slots:
    void dbsServicesChanged(QList<QVariant>, QList<QDBusObjectPath>, QDBusMessage);
    void dbsServicePropertyChanged(QString, QDBusVariant, QDBusMessage);
    void updateConfiguration();
    void ipv4Method(int idx);
    void netPortMethod(int idx);
    void pingTest();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
