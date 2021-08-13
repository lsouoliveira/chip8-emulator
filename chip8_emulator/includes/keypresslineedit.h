#ifndef KEYPRESS_LINE_EDIT_H
#define KEYPRESS_LINE_EDIT_H

#include <QLineEdit>
#include <QKeyEvent>
#include <QKeySequence>

class KeypressLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit KeypressLineEdit(QWidget *parent = nullptr);
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // KEYPRESS_LINE_EDIT_H
