#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    enum SearchTableType
    {
        STT_STAFF,
        STT_DEPARTMENT,
        STT_JOB,
        STT_ROLE
    };

    enum FilterIndex
    {
        FILTER_NAME,
        FILTER_SEX,
        FILTER_DEPARTMENT,
        FILTER_JOB,
        FILTER_WAGE_L,
        FILTER_WAGE_H,
        FILTER_STATE
    };

public:
    explicit SearchDialog(QDialog *parent = nullptr);
    ~SearchDialog();

    void SetSearchMode(SearchTableType mode);
    SearchTableType SearchMode();

signals:
    void signalFilterChange(QStringList listFilter);

private slots:
    void on_btnClear_clicked();

    void on_leName_textChanged(const QString &arg1);
    void on_sbLower_valueChanged(double arg1);
    void on_sbHigher_valueChanged(double arg1);

    void on_cbSex_currentTextChanged(const QString &arg1);
    void on_cbDepartment_currentTextChanged(const QString &arg1);
    void on_cbJob_currentTextChanged(const QString &arg1);
    void on_cbState_currentTextChanged(const QString &arg1);

private:
    void Clear();

    QStringList GetFilter();
    void InitLayout();
    void HideAll(bool hide);

    void ShowJob();
    void ShowRole();
    void ShowStaff();
    void ShowDepartment();

    Ui::SearchDialog *ui;
    SearchTableType m_SearchTableType;
    bool m_bInitOver;

};

#endif // SEARCHDIALOG_H
