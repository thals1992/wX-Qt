// https://wiki.qt.io/Clickable_QLabel

#include "ui/ClickableLabel.h"
#include "util/UtilityUI.h"

ClickableLabel::ClickableLabel(QWidget * parent, [[maybe_unused]] Qt::WindowFlags f) : QLabel(parent) {
    this->parent = parent;
}

void ClickableLabel::mousePressEvent([[maybe_unused]] QMouseEvent * event) {
    emit clicked();
}

void ClickableLabel::connect(std::function<void()> f) {
    QObject::connect(this, &ClickableLabel::clicked, parent, f);
}

void ClickableLabel::setToWidth(const QByteArray& ba, int width) {
    UtilityUI::updateImage(this, ba, width);
}
