#include "painterwidget.h"

PainterWidget::PainterWidget(QString _scope_path, QWidget *parent) : QWidget(parent) {
    scope_size = size().height()/2;
    path = _scope_path;
    scope_scale = 1;
    image_angle = 2;
}


void PainterWidget::paintEvent(QPaintEvent*) {

    auto painter = QPainter(this);
    painter.setPen(QPen(Qt::green, 3, Qt::SolidLine, Qt::FlatCap));

    painter.translate(geometry().center());
    painter.drawLine(0,0, scope_size, 0);
    painter.drawLine(0,0, -scope_size, 0);
    painter.drawLine(0,0, 0, scope_size);
    painter.drawLine(0,0, 0, -scope_size);
    painter.translate(-geometry().center());

    qreal abs_offset_x = offset_x * width()/2;
    qreal abs_offset_y = offset_y * height()/2;

    scope_scale = THOUSANDS_IN_SCOPE/(image_angle/(qreal(360)/6000));
    qDebug() << scope_scale;

    painter.scale(scope_scale, scope_scale);
    painter.translate((1/scope_scale - 1) * width()/2, (1/scope_scale - 1) * height()/2);
    painter.translate(abs_offset_x/scope_scale, abs_offset_y/ scope_scale);

    QSvgRenderer svgr(path);
    svgr.render(&painter);
}

void PainterWidget::resizeEvent(QResizeEvent*) {
    repaint();
}

void PainterWidget::updateScopeColor(QString scope_path) {
    path = scope_path;
    repaint();
}

void PainterWidget::updateScopeGeometry(qreal offset_h, qreal offset_v, qreal angle) {
    offset_x = offset_h;
    offset_y = offset_v;
    image_angle = angle;
    repaint();
}
