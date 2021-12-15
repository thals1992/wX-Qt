// https://wiki.qt.io/Clickable_QLabel

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <functional>
#include <QLabel>
#include <Qt>

class ClickableLabel : public QLabel {

    Q_OBJECT 

public:
    explicit ClickableLabel(QWidget * parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    void connect(std::function<void()>);
    void setToWidth(const QByteArray&, int);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event);

private:
    QWidget * parent;
};

#endif  // CLICKABLELABEL_H
