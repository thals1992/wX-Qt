// https://wiki.qt.io/Clickable_QLabel

#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <functional>
#include <QLabel>
#include <Qt>

using std::function;

class ClickableLabel : public QLabel {

    Q_OBJECT 

public:
    explicit ClickableLabel(QWidget * parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    void connect(const function<void()>&);
    void setToWidth(const QByteArray&, int);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent* event) override;

private:
    QWidget * parent;
};

#endif  // CLICKABLELABEL_H
