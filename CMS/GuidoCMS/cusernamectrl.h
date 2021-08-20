#ifndef CUSERNAMECTRL_H
#define CUSERNAMECTRL_H

#include <QLineEdit>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QComboBox>
#include <QCompleter>

#define NameMaxLen 20 //限制用户名的最大输入长度，可根据自己需要设置

class CUserNameCtrl : public QLineEdit
{
    Q_OBJECT
signals:
    void sig_TextChanged(const QString &sName);//当用户名数据有变化时发出的信号，内容为当前的用户名数据

public:
    explicit CUserNameCtrl(QWidget *parent = nullptr);
    ~CUserNameCtrl();

public:
    void setTipInfo(QString sTip);//设置“用户名”字样
    void setUserList(QStringList list);//设置历史记忆的多个QComboBox用户名数据
    void setCurText(QString sText);//设置当前的用户名，若用户存在则直接设置，不存在先插入QComboBox再设置
    QString curText();//获取当前设置的用户名

private slots:
    void slot_TextChanged(const QString &text);

private:
    void initData();
    void initConnect();
    void initDisplay();

private:
    QLabel *m_label;
    QComboBox *m_combo;
    QHBoxLayout *mainLayout;
    QHBoxLayout *layout;
    QCompleter *m_comPleter;

private:
    bool _bTime;
};

#endif // CUSERNAMECTRL_H
