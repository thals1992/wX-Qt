#include "ui/ObjectDividerLine.h"
#include <QRect>

ObjectDividerLine::ObjectDividerLine(QWidget * parent) {
    line = new QFrame(parent);
    line->setGeometry(QRect(320, 150, 118, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
}

QFrame * ObjectDividerLine::get() {
    return line;
}
