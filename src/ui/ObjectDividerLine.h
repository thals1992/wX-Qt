#ifndef OBJECTDIVIDERLINE_H
#define OBJECTDIVIDERLINE_H

#include <QFrame>

class ObjectDividerLine {
public:
    explicit ObjectDividerLine(QWidget *);
    QFrame * get();

private:
    QFrame * line;
};

#endif  // OBJECTDIVIDERLINE_H
