#include "downloadfilethread.h"
#include <QApplication>
#include <QProcess>

DownLoadFileThread::DownLoadFileThread(const QString &strUrl, const QString &strSavePath)
    : m_strUrl(strUrl)
    , m_strSavePath(strSavePath)
{
    m_pDownLoadProcess = new DownLoadProcess(strUrl, strSavePath);
}

void DownLoadFileThread::run()
{
    m_pDownLoadProcess->show();
    m_pDownLoadProcess->exec();
}
