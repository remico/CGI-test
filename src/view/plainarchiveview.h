#ifndef PLAINARCHIVEVIEW_H
#define PLAINARCHIVEVIEW_H

#include "archiveview.h"
#include "constants.h"

class PlainArchiveView : public ArchiveView
{
public:
    explicit PlainArchiveView(ArchiveReader *pReader, const char *encoding = DEFAULT_ENCODING);
    ~PlainArchiveView();

    QString makeHtmlPage(PageMaker *pPagemaker, const QString &arcname);
};

#endif // PLAINARCHIVEVIEW_H
