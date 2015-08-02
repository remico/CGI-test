#ifndef ARCHIVEVIEW
#define ARCHIVEVIEW

#include "archivereader.h"
#include "constants.h"
#include "pagemaker.h"
#include <QTextCodec>

class ArchiveView
{
public:
    explicit ArchiveView(ArchiveReader *pReader, const char *encoding = DEFAULT_ENCODING)
        : m_pCodec(QTextCodec::codecForName(encoding)), m_pReader(pReader) {}
    virtual ~ArchiveView() {}

    virtual QString makeHtmlPage(PageMaker *pPagemaker, const QString &arcname) = 0;

protected:
    QTextCodec *m_pCodec;
    ArchiveReader *m_pReader;
};

#endif // ARCHIVEVIEW

