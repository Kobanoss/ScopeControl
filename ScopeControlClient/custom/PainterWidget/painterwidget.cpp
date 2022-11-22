#include "headers/painterwidget.h"
#include "config/conf.h"


PainterWidget::PainterWidget(QString _scope_path, QWidget *parent) : QWidget(parent) {
    image_angle = BASE_ANGLE;
    offset_x = BASE_OFFSET_X;
    offset_y = BASE_OFFSET_Y;

    center_crosshair_size = CENTER_CROSSHAIR_SIZE;
    path = _scope_path;
    scope_scale = BASE_SCOPE_SCALE;
}


void PainterWidget::paintEvent(QPaintEvent*) {

    auto painter = QPainter(this);
    painter.setPen(QPen((Qt::GlobalColor)CENTER_CROSSHAIR_COLOR, CENTER_CROSSHAIR_THICKNESS, Qt::SolidLine, Qt::FlatCap));

    painter.translate(geometry().center());
    painter.drawLine(0,0, center_crosshair_size, 0);
    painter.drawLine(0,0, -center_crosshair_size, 0);
    painter.drawLine(0,0, 0, center_crosshair_size);
    painter.drawLine(0,0, 0, -center_crosshair_size);
    painter.translate(-geometry().center());

    qreal abs_offset_x = offset_x * width()/2;
    qreal abs_offset_y = offset_y * height()/2;

    scope_scale = SCOPE_ANGLE_TO_THND/(image_angle/(qreal(360)/6000));

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
