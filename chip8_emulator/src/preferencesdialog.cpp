#include <preferencesdialog.h>

const char* PreferencesDialog::WRAP_MODES[] = {"NO_WRAP", "WRAP", "WRAP_PART", "WRAP_CIRCULAR"};

PreferencesDialog::PreferencesDialog(QWidget* parent) : QDialog(parent)
{
    setMinimumWidth(480);
    setWindowTitle(tr("Preferences"));
    setupUI();
}

void PreferencesDialog::showEvent(QShowEvent* event)
{
    QRect parentRect( parentWidget()->mapToGlobal( QPoint( 0, 0 ) ),
    parentWidget()->size());
    move( QStyle::alignedRect( Qt::LeftToRight, Qt::AlignCenter, size(), parentRect ).topLeft() );
    QDialog::showEvent(event);
}

void PreferencesDialog::setupUI()
{
   QVBoxLayout* mainLayout = new QVBoxLayout();

   setupGeneralGroupBox();
   setupKeyMappingGroupBox();
   setupBtnGroupBox();

   mainLayout->addWidget(m_GeneralGroupBox);
   mainLayout->addWidget(m_KeyMappingGroupBox);
   mainLayout->addStretch();
   mainLayout->addWidget(m_BtnGroupBox);

   setLayout(mainLayout);
}

void PreferencesDialog::setupGeneralGroupBox()
{
   m_GeneralGroupBox = new QGroupBox(tr("General"));

   QLabel* cyclesLabel = new QLabel(tr("Cycles"));
   QSpinBox* cyclesSpinBox = new QSpinBox();
   cyclesLabel->setBuddy(cyclesSpinBox);
   cyclesSpinBox->setRange(0, 9999);

   QLabel* wrapModeLabel = new QLabel(tr("Wrap mode"));
   m_WrapModeComboBox = new QComboBox();
   wrapModeLabel->setBuddy(m_WrapModeComboBox);

   for(int i = 0; i < 4; i++) {
       m_WrapModeComboBox->addItem(WRAP_MODES[i]);
   }

   QGridLayout* generalGridLayout = new QGridLayout();
   generalGridLayout->setColumnStretch(0, 0);
   generalGridLayout->setColumnStretch(1, 1);
   generalGridLayout->addWidget(cyclesLabel, 0, 0);
   generalGridLayout->addWidget(cyclesSpinBox, 0, 1);
   generalGridLayout->addWidget(wrapModeLabel, 1, 0);
   generalGridLayout->addWidget(m_WrapModeComboBox, 1, 1);
   m_GeneralGroupBox->setLayout(generalGridLayout);
}

void PreferencesDialog::setupBtnGroupBox()
{
   m_BtnGroupBox = new QFrame();

   QPushButton* okBtn = new QPushButton("OK");
   QPushButton* cancelBtn = new QPushButton("Cancel");

   QHBoxLayout* btnBoxLayout = new QHBoxLayout();
   btnBoxLayout->addStretch();
   btnBoxLayout->addWidget(cancelBtn);
   btnBoxLayout->addWidget(okBtn);
   m_BtnGroupBox->setLayout(btnBoxLayout);
}

void PreferencesDialog::setupKeyMappingGroupBox()
{
    m_KeyMappingGroupBox = new QGroupBox(tr("Key Mapping"));
    QGridLayout* keyMappingGridLayout = new QGridLayout();
    m_KeyMappingGroupBox->setLayout(keyMappingGridLayout);
}
