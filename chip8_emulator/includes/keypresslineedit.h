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

    const int& key_code() const { return m_KeyCode; }
    void key_code(int keyCode) { m_KeyCode = keyCode; }
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    int m_KeyCode;
};

#endif // KEYPRESS_LINE_EDIT_H
