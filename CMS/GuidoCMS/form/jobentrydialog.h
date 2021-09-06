#ifndef JOBENTRYDIALOG_H
#define JOBENTRYDIALOG_H

#include "entryadddialog.h"

class JobEntryDialog : public EntryAddDialog
{
public:
    JobEntryDialog(QWidget *parent = 0);
    ~JobEntryDialog();

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
