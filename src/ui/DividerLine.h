#ifndef OBJECTDIVIDERLINE_H
#define OBJECTDIVIDERLINE_H

#include <QFrame>

class DividerLine {
public:
    explicit DividerLine(QWidget *);
    QFrame * get();

private:
    QFrame * line;
};

#endif  // OBJECTDIVIDERLINE_H
