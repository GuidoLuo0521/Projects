#include "comboboxdelegate.h"

ComboboxDelegate::ComboboxDelegate(QObject * parent)
    : QItemDelegate(parent)
{

}

ComboboxDelegate::~ComboboxDelegate()
{
    m_listItems.clear();
}

QWidget *ComboboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox * pEditor = new QComboBox(parent);
    for(int i = 0; i < m_listItems.count(); ++i)
    {
        pEditor->addItem(m_listItems[i]);
    }

    // 安装事件过滤器，使得 ComboxDelegate 能够捕获 QComboBox 的事件
    pEditor->installEventFilter(const_cast<ComboboxDelegate*>(this));

    return pEditor;
}

void ComboboxDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const
{
    // 获取指定箱的数据，并转为 string
    QString strDate = index.model()->data(index).toString();
    QComboBox *pBox = static_cast<QComboBox*>(pEditor);
    pBox->setCurrentIndex(pBox->findText(strDate));
}

void ComboboxDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const
{
    QComboBox *pBox = static_cast<QComboBox*>(pEditor);
    pModel->setData(index, pBox->currentText());
}

void ComboboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void ComboboxDelegate::PushItem(QString strItem)
{
    m_listItems.push_back(strItem);
}
