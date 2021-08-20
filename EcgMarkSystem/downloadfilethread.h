#ifndef DOWNLOADFILETHREAD_H
#define DOWNLOADFILETHREAD_H

#include <QThread>
#include "downloadprocess.h"

class DownLoadFileThread : public QThread
{
public:
    DownLoadFileThread(const QString& strUrl, const QString& strSavePath);

    void run() override;

private:
    DownLoadProcess * m_pDownLoadProcess;
    QString m_strUrl;
    QString m_strSavePath;
};

#endif // DOWNLOADFILETHREAD_H
