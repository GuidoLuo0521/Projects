#ifndef RANDOMPARAMS_H
#define RANDOMPARAMS_H

#include <QDebug>

#include <QTime>       //使用了QTime函数
#include <QtGlobal>    //qsrand和qrand这两个函数在这里面

QStringList g_strList={"0","1","2","3","4","5","6","7","8","9",
                       "a","b","c","d","e","f","g","h","i","g",
                       "k","l","m","n","o","p","q","r","s","t",
                       "u","v","w","x","y","z"};

QStringList g_strListDepartment = {
    "董事部",
    "秘书科",
    "总务部",
    "会计部",
    "财务部",
    "业务部",
    "人事部",
    "劳务部",
    "企划部",
    "管理部",
    "法律部",
    "设计部",
    "生产部",
    "质检部",
    "研发部",
    };


/// <summary> 获取随机数 </sumamry>
/// 因为按时间s来说，种子数差别不大，导致随机数也一样。
/// 所以，每次记录上次的随机数，然后以此作为随机种子。
int GetRandomNumber()
{
    static int nrand = QTime(0,0,0).secsTo(QTime::currentTime());
    qsrand(nrand);
    nrand = qrand();

    return nrand;
}

/// <summary> 随机字符 左闭右闭 </sumamry>
/// <param name = "nMax"> 范围的最大值 </param>
/// <param name = "nFrom"> 开始字符 </param>
/// <param name = "nEnd"> 结束字符 </param>
QString GetRandomString(const QStringList& strList, int nStop, int nFrom = 0, int nEnd = -1)
{
    int nListSize = strList.size();
    if(nStop > nListSize || nEnd > nListSize ||
            nFrom < 0 || nFrom > nListSize - 1 ||
            nEnd > nListSize - 1)
        return "";

    if( nFrom == 0 && nEnd == -1)
        return strList[ GetRandomNumber() % nStop];
    else
    {
        QStringList strTempList;
        for( int i = nFrom; i <= nEnd; ++i)
        {
            strTempList.append(strList[i]);
        }

        if( nStop <= strTempList.size() )
            return strTempList[ GetRandomNumber() % nStop];
        else
            return "";
    }
}

/// <summary> 随机密码 </sumamry>
QString GetRandomPassword()
{
    return QString("%1%2%3%4%5%6")
            .arg(GetRandomString(g_strList, g_strList.size()))
            .arg(GetRandomString(g_strList, g_strList.size()))
            .arg(GetRandomString(g_strList, g_strList.size()))
            .arg(GetRandomString(g_strList, g_strList.size()))
            .arg(GetRandomString(g_strList, g_strList.size()))
            .arg(GetRandomString(g_strList, g_strList.size()));
}

/// <summary> 随机性别 </sumamry>
int GetRandomSex()
{
    return QString("%1").arg(GetRandomString(g_strList, 3)).toInt();
}

/// <summary> 随机时间 </sumamry>
/// 这个时间差别太小了
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

/// <summary> 随机出生日期 </sumamry>
QString GetRandomBirthday()
{
    //return GetRandomTime();
    QString param1, param2, param3, param4, param5, param6, param7, param8;

    param1 = GetRandomString(g_strList, 2, 1, 2);
    if(param1== "1")
    {
        param2 = "9";
        param3 = GetRandomString(g_strList, 2, 7, 9);
        param4 = GetRandomString(g_strList, 9);
    }
    else
    {
        param2 = "0";
        param3 = GetRandomString(g_strList, 3);
        param4 = GetRandomString(g_strList, param3 == "2" ? 2 : 9);
    }

    param5 = GetRandomString(g_strList, 2);
    param6 = GetRandomString(g_strList, param5 == "1" ? 2 : 9);
    if(param5 == "0" && param5 == param6)
        param6 = "1";

    param7 = GetRandomString(g_strList, 4);
    param8 = GetRandomString(g_strList, param7 == "3" ? 2 : 9);
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

/// <summary> 随机部门 </sumamry>
QString GetRandomDepartent()
{
    return GetRandomString(g_strListDepartment, g_strListDepartment.size());
}

/// <summary> 随机工资 </sumamry>
float GetRandomWage()
{
    return GetRandomNumber() % 9999;
}

/// <summary> 随机工龄 </sumamry>
float GetRandomWorkingAge()
{
    return GetRandomNumber() % 20;
}




#endif // RANDOMPARAMS_H
