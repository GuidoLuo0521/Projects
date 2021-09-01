#ifndef ADDTABLEINFOROLEDIALOG_H
#define ADDTABLEINFOROLEDIALOG_H

#include "addtableinfodialog.h"

class AddTableInfoRoleDialog : public AddTableInfoDialog
{
public:
    AddTableInfoRoleDialog(QWidget *parent = 0);
    ~AddTableInfoRoleDialog();

protected slots:
    virtual void slotAdd() override;
    virtual void slotClear() override;

protected:
    virtual void InitLayout() override;

private:
    bool CheckParams();

private:
    StanderLineEdit * m_pLineEditName;
    StanderComboBox * m_pComboBoxState;
    StanderPlainTextEdit * m_pPlainTextEditDesc;

};

#endif // ADDTABLEINFOROLEDIALOG_H
