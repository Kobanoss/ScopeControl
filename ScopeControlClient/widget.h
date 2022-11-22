#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QThread>
#include <QTimer>
#include <QMap>
#include <udpreceiver.h>
#include <painterwidget.h>

#define LISTENING_PORT 50000
#define FIXED_AR qreal(0.75)

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
} QT_END_NAMESPACE

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    qreal angle = 2;
    qreal offset_v{};
    qreal offset_h{}; 

    QThread* rec_thread;
    UdpReceiver* receiver;

    PainterWidget* painter_widget;
    QMap<quint8, QString> stylesheet_map;
    QMap<quint8, QString> scope_path_map;

    void getDatagram(QByteArray datagram);

    void setLabels();

    void calculateScopeGeometry();

    void resizeEvent(QResizeEvent*);

    Ui::Widget *ui;

signals:
    void _killReceiver();
    void changeScopeColor(QString path);
    void changeScopeGeometry(qreal offset_h, qreal offset_v, qreal angle);

private slots:
    void on_comboBox_crosshair_color_activated(int index);
    void on_comboBox_background_activated(int index);
};

#endif // WIDGET_H
