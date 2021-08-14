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

void PreferencesDialog::savePreferences()
{
    int cycles = m_CyclesSpinBox->value();
    int wrapMode = m_WrapModeComboBox->currentIndex();
    std::vector<std::string> keyMapping;
    for(auto keyEdit : m_KeyEdits) {
        keyMapping.push_back(keyEdit->text().toStdString());
    }
    Preferences preferences(cycles, wrapMode, keyMapping);

    emit saved(preferences);

    close();
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
   m_CyclesSpinBox = new QSpinBox();
   cyclesLabel->setBuddy(m_CyclesSpinBox);
   m_CyclesSpinBox->setRange(0, 9999);

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
   generalGridLayout->addWidget(m_CyclesSpinBox, 0, 1);
   generalGridLayout->addWidget(wrapModeLabel, 1, 0);
   generalGridLayout->addWidget(m_WrapModeComboBox, 1, 1);
   m_GeneralGroupBox->setLayout(generalGridLayout);
}

void PreferencesDialog::setupBtnGroupBox()
{
   m_BtnGroupBox = new QFrame();

   QPushButton* okBtn = new QPushButton("OK");
   QPushButton* cancelBtn = new QPushButton("Cancel");

   connect(cancelBtn, &QPushButton::clicked, this, &PreferencesDialog::close);
   connect(okBtn, &QPushButton::clicked, this, &PreferencesDialog::savePreferences);

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

    std::vector<char> keyNames{'1', '2', '3', 'C', '4', '5', '6', 'D', '7', '8', '9', 'E', 'A', '0', 'B', 'F'};
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
           std::string keyName = std::string(1, keyNames[i * 4 + j]) + " = ";
           QLabel* label = new QLabel(keyName.c_str());
           KeypressLineEdit* keyEdit = new KeypressLineEdit();
           keyEdit->setReadOnly(true);
           label->setBuddy(keyEdit);

           keyMappingGridLayout->addWidget(label, i, 2 * j);
           keyMappingGridLayout->addWidget(keyEdit, i, 2 * j + 1);

           m_KeyEdits.push_back(keyEdit);
        }
    }
}

void PreferencesDialog::setCycles(int cycles)
{
    m_CyclesSpinBox->setValue(cycles);
}

void PreferencesDialog::setWrapMode(int wrapModeIndex)
{
    m_WrapModeComboBox->setCurrentIndex(wrapModeIndex);
}

void PreferencesDialog::setKeyMapping(std::vector<std::string> keyMapping)
{
    for(int i = 0; i < 16; i++) {
        KeypressLineEdit* keyEdit = m_KeyEdits[i];
        keyEdit->setText(keyMapping[i].c_str());
    }
}
