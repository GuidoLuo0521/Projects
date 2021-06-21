#ifndef CGERBERSTRUCTURE_H
#define CGERBERSTRUCTURE_H

#include <QList>

#include "csymbol.h"

class CGerberStructure
{
public:
    CGerberStructure();

    void PushSymbol(CSymbol * pSymbol);

protected:

    // 存储所有的图形
    QList<CSymbol*> m_listSymbols;

};

#endif // CGERBERSTRUCTURE_H
