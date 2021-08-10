#ifndef RANDOMPARAMS_H
#define RANDOMPARAMS_H

#include <QDebug>

#include <QTime>       //使用了QTime函数
#include <QtGlobal>    //qsrand和qrand这两个函数在这里面

QStringList g_strList={"0","1","2","3","4","5","6","7","8","9",
                       "a","b","c","d","e","f","g","h","i","g",
                       "k","l","m","n","o","p","q","r","s","t",
                       "u","v","w","x","y","z"};

const int g_nStrListSize = g_strList.size();

int GetRandomNumber()
{
    static int nrand = QTime(0,0,0).secsTo(QTime::currentTime());
    qsrand(nrand);
    nrand = qrand();

    return nrand;
}

QString GetRandomString(int nMax, int nFrom = 0, int nEnd = g_nStrListSize - 1)
{
    if(nMax > g_nStrListSize || nEnd < nFrom ||
            nFrom < 0 || nFrom > g_nStrListSize - 1 ||
            nEnd < 0  || nEnd > g_nStrListSize - 1)
        return "";

    if( nFrom != 0 || nEnd != g_nStrListSize - 1)
    {
        QStringList strTempList;
        for( int i = nFrom; i <= nEnd; ++i)
        {
            strTempList.append(g_strList[i]);
        }

        if( nMax <= strTempList.size() )
            return strTempList[ GetRandomNumber() % nMax];
        else
            return "";
    }

    return g_strList[ GetRandomNumber() % nMax];
}

QString GetRandomPassword()
{
    return QString("%1%2%3%4%5%6")
            .arg(GetRandomString(g_nStrListSize))
            .arg(GetRandomString(g_nStrListSize))
            .arg(GetRandomString(g_nStrListSize))
            .arg(GetRandomString(g_nStrListSize))
            .arg(GetRandomString(g_nStrListSize))
            .arg(GetRandomString(g_nStrListSize));
}

int GetRandomSex()
{
    return QString("%1").arg(GetRandomString(3)).toInt();
}

QString GetRandomTime()
{
    int timeBegin,timeNow,t;
    QString str;
    QDateTime time = QDateTime::currentDateTime();//获取当前时间
    QDateTime timeFinal;
    timeNow = time.toTime_t();//时间转换为时间戳
    timeBegin = 778434765;//https://tool.lu/timestamp/这个时间戳转换网站 这边默认开始时间固定，也可以随时指定，加在函数变量中即可
    t = rand() % ( timeNow - timeBegin ); //获取一个随机数
    t = timeNow - t;//当前时间减去随机数得到目标随机时间的时间戳
    timeFinal = QDateTime::fromTime_t( t );//时间戳转为时间
    str = timeFinal.toString("yyyy-MM-dd hh:mm:ss");//时间输出的格式化

    return str;
}

QString GetRandomBirthday()
{
    //return GetRandomTime();
    QString param1, param2, param3, param4, param5, param6, param7, param8;

    param1 = GetRandomString(2, 1, 2);
    if(param1== "1")
    {
        param2 = "9";
        param3 = GetRandomString(2, 7, 9);
        param4 = GetRandomString(9);
    }
    else
    {
        param2 = "0";
        param3 = GetRandomString(3);
        param4 = GetRandomString(param3 == "2" ? 2 : 9);
    }

    param5 = GetRandomString(2);
    param6 = GetRandomString(param5 == "1" ? 2 : 9);
    if(param5 == "0" && param5 == param6)
        param6 = "1";

    param7 = GetRandomString(4);
    param8 = GetRandomString(param7 == "3" ? 2 : 9);
    if(param7 == "3" && param7 == param8)
        param7 = "1";

    return  QString("%1%2%3%4-%5%6-%7%8")
            .arg(param1)
            .arg(param2)
            .arg(param3)
            .arg(param4)
            .arg(param5)
            .arg(param6)
            .arg(param7)
            .arg(param8);
}



#endif // RANDOMPARAMS_H
