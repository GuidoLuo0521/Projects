

#include "logindialog.h"
#include "ui_logindialog.h"
#include "common/staffinfo.h"
#include "common/commonapi.h"
#include "common/filedownloader.h"

#include <QFile>
#include <QStyledItemDelegate>

const QString gk_ProfileUrl = "http://www.millet.fun/GuidoCMS/Profile";

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent)
    , ui(new Ui::LoginDialog)
    , m_pCMSDatabase(nullptr)
{
    ui->setupUi(this);
    this->setFixedSize(360, 450);

    QStyledItemDelegate *delegate = new QStyledItemDelegate(this);
    ui->cbUserName->setItemDelegate(delegate);
    ui->cbUserName->setStyleSheet("QComboBox QAbstractItemView::item {min-height: 30px;}");
    //ui->cbUserName->setIconSize(QSize(30,30));
    ui->cbUserName->setLineEdit(ui->leUserName);

    QString strDefaultProfile = QApplication::applicationDirPath() + QString("/Profile/000000.png");
    QString strUrl = gk_ProfileUrl + "/000000.png";

    m_pFileDownloader = new FileDownloader(this);
    connect(m_pFileDownloader, SIGNAL(signalDownLoaded(QString, bool)),
            this, SLOT(slotUpdateDownLoadProfile(QString, bool)));

    if(QFile::exists(strDefaultProfile) == false)
    {
        m_pFileDownloader->DownLoadFile(strUrl, strDefaultProfile);
    }

    slotShowMainWindow();
}

LoginDialog::~LoginDialog()
{
    Clear();
    delete ui;
}

QString LoginDialog::GetUserID()
{
    return ui->leUserName->text();
}

QString LoginDialog::GetPassWord()
{
    return ui->lePassword->text();
}

void LoginDialog::slotShowMainWindow()
{
    Clear();

    CMSDatabase * pDB = CMSDatabaseSingleton::GetInstance();

    QString strErrorText = pDB ? "网络已连接。\n" : "网络未连接。\n";
    if( pDB )
    {
        if(!pDB->WDB_IsOpen())
            strErrorText += "WebDatabase Not Open。\n";

        if(!pDB->LDB_IsOpen())
            strErrorText += "LocalDatabase Not Open。\n";
    }

    ui->labelInfo->setText(strErrorText);

    m_nSelectStaffIndex = -1;
    m_nCurrentStaffIndex = -1;
    m_pCMSDatabase = pDB;
    LoadLocalStaffInfo();
    UpdateCombox();

    if( m_listLoginStaffs.count() > 0 && m_nSelectStaffIndex != -1)
    {
        ui->cbUserName->setCurrentIndex(m_nSelectStaffIndex);
        if(m_listLoginStaffs[m_nSelectStaffIndex].bAutoLogin)
        {
            //on_btnLogin_clicked();
        }
    }

    this->show();
}

void LoginDialog::slotUpdateDownLoadProfile(QString strPath, bool bSuccess)
{
    if(bSuccess)
    {
        QString strProfile = strPath;
        if(QFile::exists(strProfile) == false)
            strProfile = QApplication::applicationDirPath() + QString("/Profile/000000.png");

        ui->labelProfile->setPixmap(QPixmap(strProfile));
    }
}

void LoginDialog::on_btnLogin_clicked()
{
    if(m_pCMSDatabase == nullptr)
        return;

    int nRetInput = VerifyInput();
    if(nRetInput == 1)
    {
        QString strUserID = GetUserID();
        QString strPassWord = GetPassWord();

        int nRet = m_pCMSDatabase->WDB_VerifyLogin(strUserID, strPassWord);
        if(nRet == 1)
        {
            UpdateStaffInfo(strPassWord, ui->checkBoxRmbPW->isChecked(), ui->checkBoxAutoLogin->isChecked(), true);

            QString strProfile = QApplication::applicationDirPath() + QString("/Profile/%1.png").arg(strUserID);;
            if(QFile::exists(strProfile) == false)
            {
                QString strUrl = QString("%1/%2.png").arg(gk_ProfileUrl).arg(strUserID);
                m_pFileDownloader->DownLoadFile(strUrl, strProfile);
            }

            StaffInfoSingleton::SetInstance(GetStaffInfo(strUserID));

            LoadLocalStaffInfo();

            emit signalShowMainWindow();
            close();
        }
        else if(nRet == -1)
        {
            QMessageBox::warning(this, "警告", "暂无此用户！");

            ui->lePassword->clear();
            ui->leUserName->setFocus();
        }
        else if( nRet == 0)
        {
            QMessageBox::warning(this, "警告", "密码错误！");

            UpdateStaffInfo("", false, false, true);

            ui->lePassword->clear();
            ui->lePassword->setFocus();
        }
    }
    else if(nRetInput == -1)
    {
        QMessageBox::warning(this, "警告", "用户名不能为空！");
    }
    else if(nRetInput == 0)
    {
        QMessageBox::warning(this, "警告", "密码不能为空！");
    }
}

int LoginDialog::VerifyInput()
{
    QString strUserID = GetUserID();
    QString strPassWord = GetPassWord();
    if(strUserID.isEmpty())
    {
        return -1;
    }
    if(strPassWord.isEmpty())
    {
        return  0;
    }

    return  1;
}

void LoginDialog::UpdateCombox()
{
    ui->cbUserName->clear();

    for( int i = 0; i < m_listLoginStaffs.size(); ++i )
    {
        LoginStaff& staff = m_listLoginStaffs[i];
        if(staff.bActiveState == true )
        {
            //QString strProfile = QString("Profile/%1.png").arg(staff.strStaffID);
            //QIcon icon = QIcon(strProfile);

            ui->cbUserName->insertItem(i, staff.strStaffID);
        }
    }
}

int LoginDialog::UpdateStaffInfo(const QString &strPassWord, const bool bRemenmberPW, const bool bAutoLogin, const bool bActiveState)
{
    QString strQuery = "";
    QString strUserID = GetUserID();

    strQuery = QString("UPDATE StaffInfo SET SelectState = '%1'").arg(false);
    m_pCMSDatabase->m_LocalDatabase.exec(strQuery);

    if(CheckExistStaffInLocalDB(strUserID))
    {
        LoginStaff& staff = m_listLoginStaffs[m_nCurrentStaffIndex];
        staff.strPassword = strPassWord;
        staff.bRemenmberPW = bRemenmberPW;
        staff.bAutoLogin = bAutoLogin;
        staff.bActiveState = bActiveState;

        strQuery = QString("UPDATE StaffInfo SET "
                           "StaffPassword = '%2', "
                           "RemenmberPW = %3 ,"
                           "AutoLogin = %4 ,"
                           "ActiveState = %5 ,"
                           "SelectState = %6 "
                           "WHERE StaffID = '%1'")
                       .arg(staff.strStaffID).arg(staff.strPassword).arg(bRemenmberPW).arg(bAutoLogin).arg(bActiveState).arg(true);
    }
    else
    {
        bool bActiveState = true;
        strQuery = QString("INSERT INTO StaffInfo(StaffID, StaffPassword, RemenmberPW, AutoLogin, ActiveState, SelectState) "
                                   "VALUES('%1', '%2', %3, %4, %5, %6)")
                .arg(strUserID).arg(strPassWord).arg(bRemenmberPW).arg(bAutoLogin).arg(bActiveState).arg(true);

        LoginStaff staff;
        staff.strStaffID = strUserID;
        staff.strPassword = strPassWord;
        staff.bRemenmberPW = bRemenmberPW;
        staff.bAutoLogin = bAutoLogin;
        staff.bActiveState = bActiveState;
        m_listLoginStaffs.push_back(staff);

        UpdateCombox();
        ui->cbUserName->setCurrentIndex(ui->cbUserName->count() - 1);
    }

    m_pCMSDatabase->m_LocalDatabase.exec(strQuery);

    return 1;
}

int LoginDialog::LoadLocalStaffInfo()
{
    if(m_pCMSDatabase && m_pCMSDatabase->LDB_IsOpen())
    {
        QString strQuery = "SELECT * FROM StaffInfo ORDER BY SelectState";
        QSqlQuery query = m_pCMSDatabase->LDB_Exec(strQuery);

        int i = 0;
        while (query.next())
        {
            LoginStaff staff;
            if(query.value("ActiveState").toBool())
            {
                staff.strStaffID = query.value("StaffID").toString();
                staff.strPassword = query.value("StaffPassword").toString();
                staff.bRemenmberPW = query.value("RemenmberPW").toBool();
                staff.bAutoLogin = query.value("AutoLogin").toBool();
                staff.bSelectState = query.value("SelectState").toBool();
                staff.bActiveState = true;
                m_listLoginStaffs.push_back(staff);

                if(staff.bSelectState == true && m_nSelectStaffIndex == -1)
                {
                    m_nSelectStaffIndex = i;
                }

                ++i;
            }
        }

        return 1;
    }

    return -1;
}

void LoginDialog::Clear()
{
    m_pCMSDatabase = nullptr;
    m_listLoginStaffs.clear();
    ui->labelInfo->clear();

    ui->cbUserName->clear();

    ui->lePassword->clear();;
    ui->lePassword->clear();;
    ui->checkBoxRmbPW->setChecked(false);
    ui->checkBoxAutoLogin->setChecked(false);
}

bool LoginDialog::CheckExistStaffInLocalDB(const QString &strUID)
{
    QString strQuery = QString("SELECT StaffID "
                               "FROM StaffInfo "
                               "WHERE StaffID = '%1'").arg(strUID);
    QSqlQuery query = m_pCMSDatabase->m_LocalDatabase.exec(strQuery);

    return query.next();
}

int LoginDialog::CheckExistStaffInList(const QString &strUID)
{
    for(int i = 0 ; i < m_listLoginStaffs.size(); ++i)
    {
        if(strUID == m_listLoginStaffs[i].strStaffID)
            return i;
    }

    return  -1;
}

void LoginDialog::on_cbUserName_currentIndexChanged(int index)
{
    m_nCurrentStaffIndex = -1;

    if(index >= 0 && index < m_listLoginStaffs.count())
    {
        m_nCurrentStaffIndex = index;

        LoginStaff& staff = m_listLoginStaffs[index];
        ui->leUserName->setText(staff.strStaffID);
        ui->checkBoxAutoLogin->setChecked(staff.bAutoLogin);
        ui->checkBoxRmbPW->setChecked(staff.bRemenmberPW);
        if(staff.bRemenmberPW)
            ui->lePassword->setText(staff.strPassword);       

        QString strDefaultProfile = QApplication::applicationDirPath() + QString("/Profile/000000.png");
        QString strProfile = QApplication::applicationDirPath() + QString("/Profile/%1.png").arg(staff.strStaffID);

        if( QFile::exists(strProfile) == false)
        {
            strProfile = strDefaultProfile;
        }
        ui->labelProfile->setPixmap(QPixmap(strProfile));
    }
}

void LoginDialog::on_checkBoxAutoLogin_clicked(bool checked)
{
    if(checked)
        ui->checkBoxRmbPW->setChecked(true);
}

void LoginDialog::on_leUserName_textChanged(const QString &arg1)
{
    ui->lePassword->setText("");
    ui->checkBoxAutoLogin->setChecked(false);
    ui->checkBoxRmbPW->setChecked(false);

    QString strID = arg1;
    for(int i = 0; i < ui->cbUserName->count(); ++i)
    {
        if(ui->cbUserName->itemText(i) == strID)
        {
            ui->cbUserName->setCurrentIndex(i);
            return;
        }
    }

    QString strProfile = QApplication::applicationDirPath() + QString("/Profile/%1.png").arg(arg1);
    if(QFile::exists(strProfile) == false)
        strProfile = QApplication::applicationDirPath() + QString("/Profile/000000.png");

    ui->labelProfile->setPixmap(QPixmap(strProfile));
}

void LoginDialog::on_cbUserName_editTextChanged(const QString &arg1)
{
    qDebug() << arg1;
}
