#include "texteditdelegate.h"

TextEditDelegate::TextEditDelegate(TextType tt, QObject * parent) :
    QItemDelegate(parent),
    m_TextType(tt)
{

}


QWidget *TextEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QTextEdit * pEditor = new QTextEdit(parent);

    // 安装事件过滤器，使得 ComboxDelegate 能够捕获 QComboBox 的事件
    pEditor->installEventFilter(const_cast<TextEditDelegate*>(this));

    return pEditor;
}

void TextEditDelegate::setEditorData(QWidget *pEditor, const QModelIndex &index) const
{
    // 获取指定箱的数据，并转为 string
    QString strDate = index.model()->data(index).toString();
    QTextEdit *pEdit = static_cast<QTextEdit*>(pEditor);

    switch (m_TextType) {
    case TT_Html: pEdit->setHtml(strDate); return;
    //case TT_MarkDown: pEdit->setMarkdown(strDate); return;
    default:
        pEdit->setPlainText(strDate); return;
    }
}

void TextEditDelegate::setModelData(QWidget *pEditor, QAbstractItemModel *pModel, const QModelIndex &index) const
{
    QTextEdit *pEdit = static_cast<QTextEdit*>(pEditor);

    switch (m_TextType) {
    case TT_Html: pModel->setData(index, pEdit->toHtml()); return;
    //case TT_MarkDown: pModel->setData(index, pEdit->toMarkdown()); return;
    default:pModel->setData(index, pEdit->toPlainText()); return;
    }
}

void TextEditDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
