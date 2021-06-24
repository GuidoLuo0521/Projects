#include "cgerberstructure.h"

CGerberStructure::CGerberStructure()
{

}

void CGerberStructure::PushSymbol(CSymbol *pSymbol)
{
    if(pSymbol == nullptr)
        return;

    m_listSymbols.push_back(pSymbol);
}
