#ifndef ROLEENTRYDIALOG_H
#define ROLEENTRYDIALOG_H

#include "entryadddialog.h"

class RoleEntryDialog : public EntryAddDialog
{
public:
    RoleEntryDialog(QWidget *parent = 0);
    ~RoleEntryDialog();

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
