#ifndef PREFERENCES_DIALOG_H
#define PREFERENCES_DIALOG_H

#include <iostream>

#include <QDialog>
#include <QWidget>
#include <QStyle>
#include <QGroupBox>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QEvent>
#include <QKeyEvent>

#include <keypresslineedit.h>
#include <models/preferences.h>

class PreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PreferencesDialog(QWidget *parent = nullptr);
protected:
    void showEvent(QShowEvent* event) override;
private slots:
    void closeDialog();
signals:
    void saved(Preferences preferences);
private:
    void setupUI();
    void setupGeneralGroupBox();
    void setupBtnGroupBox();
    void setupKeyMappingGroupBox();

    const static char* WRAP_MODES[];

    QGroupBox* m_GeneralGroupBox;
    QGroupBox* m_KeyMappingGroupBox;
    QFrame* m_BtnGroupBox;
    QComboBox* m_WrapModeComboBox;
    std::vector<KeypressLineEdit*> m_KeyEdits;
};

#endif // PREFERENCES_DIALOG_H
