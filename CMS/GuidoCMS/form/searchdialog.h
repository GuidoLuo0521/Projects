#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

enum SearchTableType
{
    STT_NULL,
    STT_STAFF,
    STT_DEPARTMENT,
    STT_JOB,
    STT_ROLE
};

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr);
    ~SearchDialog();

    void SetSearchMode(SearchTableType mode);
    SearchTableType SearchMode();

signals:
    void signalNameChange(QString str);
    void signalSexChange(QString str);
    void signalDepartmentChange(QString str);
    void signalJobChange(QString str);
    void signalRangeChange(double lower, double higher);

    void signalClear();

private slots:
    void on_leName_textChanged(const QString &arg1);

    void on_cbSex_currentTextChanged(const QString &arg1);

    void on_cbDepartment_currentTextChanged(const QString &arg1);

    void on_sbLower_valueChanged(double arg1);

    void on_btnClear_clicked();

    void on_sbHigher_valueChanged(double arg1);

    void on_cbJob_currentTextChanged(const QString &arg1);

private:
    void InitLayout();
    void HideAll(bool hide);

    void ShowJob();
    void ShowStaff();
    void ShowDepartment();

    Ui::SearchDialog *ui;
    SearchTableType m_SearchTableType;
    bool m_bInitOver;

};

#endif // SEARCHDIALOG_H
