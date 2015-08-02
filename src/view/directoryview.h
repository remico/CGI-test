#ifndef DIRECTORYVIEW_H
#define DIRECTORYVIEW_H

#include "directory.h"
#include "pagemaker.h"

class DirectoryView
{
public:
    DirectoryView(Directory *pDir) : m_pDir(pDir) {}
    virtual ~DirectoryView() {}

    virtual QString makeHtmlPage(PageMaker *pPagemaker) const = 0;

protected:
    Directory *m_pDir;
};

#endif // DIRECTORYVIEW_H
