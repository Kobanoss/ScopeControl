#include <QApplication>
#include "widget/headers/widget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Widget window;
    window.show();
    return app.exec();
}
