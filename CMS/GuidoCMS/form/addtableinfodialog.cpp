﻿#include "addtableinfodialog.h"
#include <QGridLayout>

AddTableInfoDialog::AddTableInfoDialog(QWidget *parent) :
    QWidget(parent),
    m_pCMSDatabase(nullptr)
{
    m_pCMSDatabase = CMSDatabaseSingleton::GetInstance();

    m_pButtonLayout = new QHBoxLayout;
    m_pButtonAdd = new QPushButton("增加");
    m_pButtonClear = new QPushButton("清除");
    //m_pButtonLayout->addStretch();
    m_pButtonLayout->addWidget(m_pButtonAdd);
    m_pButtonLayout->addWidget(m_pButtonClear);

    connect(m_pButtonAdd, &QPushButton::clicked, this, &AddTableInfoDialog::slotAdd);
    connect(m_pButtonClear, &QPushButton::clicked, this, &AddTableInfoDialog::slotClear);
    connect(this, &AddTableInfoDialog::signalAddSuccess, this, &AddTableInfoDialog::slotClear);
}

AddTableInfoDialog::~AddTableInfoDialog()
{

}

QStringList AddTableInfoDialog::GetDepartmentList()
{
    QString strQuery = "SELECT DepartmentName FROM department";
    QSqlQuery query = CMSDatabaseSingleton::GetInstance()->WDB_Exec(strQuery);

    QStringList strList;
    while (query.next())
    {
        strList.push_back( query.value("DepartmentName").toString());
    }

    return  strList;
}

QStringList AddTableInfoDialog::GetSpecialtyList()
{
    QString strQuery = "SELECT Name FROM Specialty";
    QSqlQuery query = CMSDatabaseSingleton::GetInstance()->WDB_Exec(strQuery);

    QStringList strList;
    while (query.next())
    {
        strList.push_back( query.value("Name").toString());
    }

    return  strList;
}

QStringList AddTableInfoDialog::GetEducationList()
{
    QString strQuery = "SELECT Name FROM education";
    QSqlQuery query = CMSDatabaseSingleton::GetInstance()->WDB_Exec(strQuery);

    QStringList strList;
    while (query.next())
    {
        strList.push_back( query.value("Name").toString());
    }

    return  strList;
}

QStringList AddTableInfoDialog::GetPlaceList()
{
    QString strQuery = "SELECT Province, City FROM place";
    QSqlQuery query = CMSDatabaseSingleton::GetInstance()->WDB_Exec(strQuery);

    QStringList strList;
    while (query.next())
    {
        QString province = query.value("Province").toString();
        QString city = query.value("City").toString();
        strList.push_back( province + city);
    }

    return  strList;
}

QStringList AddTableInfoDialog::GetJobList()
{
    QString strQuery = "SELECT JobName FROM job";
    QSqlQuery query = CMSDatabaseSingleton::GetInstance()->WDB_Exec(strQuery);

    QStringList strList;
    while (query.next())
    {
        strList.push_back( query.value("JobName").toString());
    }

    return  strList;
}

QStringList AddTableInfoDialog::GetStateList()
{
    return {"正常", "撤销"};
}

QStringList AddTableInfoDialog::GetSexList()
{
    return {"男性", "女性", "未知"};
}

void AddTableInfoDialog::InitLayout()
{

}

void AddTableInfoDialog::slotAdd()
{
    emit signalAddSuccess(true);
}

void AddTableInfoDialog::slotClear()
{

}
