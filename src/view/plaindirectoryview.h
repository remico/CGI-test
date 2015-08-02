#ifndef PLAINDIRECTORYVIEW_H
#define PLAINDIRECTORYVIEW_H

#include "directoryview.h"

class PlainDirectoryView : public DirectoryView
{
public:
    PlainDirectoryView(Directory *pDir);
    QString makeHtmlPage(PageMaker *pPagemaker) const;
};

#endif // PLAINDIRECTORYVIEW_H
