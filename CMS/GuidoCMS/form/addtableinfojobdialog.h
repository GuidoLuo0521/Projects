#ifndef ADDTABLEINFOJOBDIALOG_H
#define ADDTABLEINFOJOBDIALOG_H

#include "addtableinfodialog.h"

class AddTableInfoJobDialog : public AddTableInfoDialog
{
public:
    AddTableInfoJobDialog(QWidget *parent = 0);
    ~AddTableInfoJobDialog();

protected slots:
    virtual void slotAdd() override;
    virtual void slotClear() override;

protected:
    virtual void InitLayout() override;

private:
    void InitDelegate();
    bool CheckParams();

private:
    StanderLineEdit * m_pLineEditName;
    StanderLineEdit * m_pLineEditBaseWage;
    StanderComboBox * m_pComboBoxState;
    StanderPlainTextEdit * m_pPlainTextEditDesc;

};

#endif // ADDTABLEINFOJOBDIALOG_H
