#include <keypresslineedit.h>


KeypressLineEdit::KeypressLineEdit(QWidget* parent) : QLineEdit(parent)
{
}

void KeypressLineEdit::keyPressEvent(QKeyEvent* event)
{
    QString keyName = QKeySequence(event->key()).toString();
    setText(keyName);
    m_KeyCode = event->key();

    QLineEdit::keyPressEvent(event);
}
