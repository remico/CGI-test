#ifndef PLAINTXTFILEVIEW_H
#define PLAINTXTFILEVIEW_H

#include "constants.h"
#include "fileview.h"

class PlainTxtFileView : public FileView
{
public:
    explicit PlainTxtFileView(ArchiveReader *pReader, const char *encoding = DEFAULT_ENCODING);
    ~PlainTxtFileView();

    QString makeHtmlPage(PageMaker *pPagemaker, const QString &arcname, const QString &filename);
};

#endif // PLAINTXTFILEVIEW_H
