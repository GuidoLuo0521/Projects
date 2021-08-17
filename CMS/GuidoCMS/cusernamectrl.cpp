#include "cusernamectrl.h"
#include <QMessageBox>

CUserNameCtrl::CUserNameCtrl(QWidget *parent):
    QLineEdit(parent)
{
    this->initData();
    this->initConnect();
    this->initDisplay();
}

CUserNameCtrl::~CUserNameCtrl()
{

}

void CUserNameCtrl::initData()
{
    mainLayout = new QHBoxLayout;
    layout = new QHBoxLayout;
    m_label = new QLabel();
    m_combo = new QComboBox();
    m_combo->setEditable(true);
    _bTime = false;
    m_comPleter = nullptr;
}

void CUserNameCtrl::initConnect()
{
    connect(m_combo,SIGNAL(currentTextChanged(const QString &)),this,SLOT(slot_TextChanged(const QString &)));
}

void CUserNameCtrl::initDisplay()
{
    mainLayout->addWidget(m_label);
    layout->addWidget(m_combo);
    mainLayout->addLayout(layout);
    mainLayout->setStretch(0,0);
    mainLayout->setStretch(1,1);

    setTextMargins(60,0,0,0);
    setContentsMargins(0,0,0,0);
    setLayout(mainLayout);

    m_combo->setCursor(Qt::PointingHandCursor);
}

void CUserNameCtrl::setTipInfo(QString sTip)
{
    m_label->setText(sTip);
}

void CUserNameCtrl::setUserList(QStringList list)
{
    m_combo->addItems(list);
    if(nullptr != m_comPleter)
    {
        delete m_comPleter;
        m_comPleter = nullptr;
    }
    m_comPleter = new QCompleter(list, this);
    m_comPleter->setCaseSensitivity(Qt::CaseInsensitive);//补齐大小写不敏感
    m_comPleter->setModelSorting(QCompleter::CaseInsensitivelySortedModel);//大小写不敏感排序
    m_combo->setCompleter(m_comPleter);
}

void CUserNameCtrl::setCurText(QString sText)
{
    if(-1 == m_combo->findText(sText))//当前没有该用户
    {
        QStringList list;
        list.clear();
        m_combo->addItem(sText);
    }

    m_combo->setCurrentText(sText);
}

QString CUserNameCtrl::curText()
{
    return m_combo->currentText();
}

void CUserNameCtrl::slot_TextChanged(const QString &text)
{
    if(text.length() > NameMaxLen)
    {
        m_combo->setCurrentText(text.left(NameMaxLen));
        return ;
    }
    emit sig_TextChanged(text);
}

