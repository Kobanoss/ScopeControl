#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QString>
#include <QPainter>
#include <QSvgRenderer>


class PainterWidget : public QWidget {
    Q_OBJECT

public:
    explicit PainterWidget(QString _scope_path, QWidget *parent = nullptr);

private:
    int center_crosshair_size;
    QString path;
    qreal offset_x;
    qreal offset_y;
    qreal scope_scale;
    qreal image_angle;

    void resizeEvent(QResizeEvent*);

protected:
    void paintEvent(QPaintEvent*);

public slots:
    void updateScopeColor(QString scope_path);
    void updateScopeGeometry(qreal offset_h, qreal _offset_v, qreal angle);
};

#endif // PAINTERWIDGET_H
