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

    // �洢���е�ͼ��
    QList<CSymbol*> m_listSymbols;

};

#endif // CGERBERSTRUCTURE_H
