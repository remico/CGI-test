#ifndef FILEVIEW
#define FILEVIEW

#include "archivereader.h"
#include "constants.h"
#include "pagemaker.h"
#include <QTextCodec>

class FileView
{
public:
    explicit FileView(ArchiveReader *pReader, const char *encoding = DEFAULT_ENCODING)
        : m_pCodec(QTextCodec::codecForName(encoding)), m_pReader(pReader) {}
    virtual ~FileView() {}

    virtual QString makeHtmlPage(PageMaker *pPagemaker,
                                 const QString &arcname,
                                 const QString &filename) = 0;

protected:
    QTextCodec *m_pCodec;
    ArchiveReader *m_pReader;
};

#endif // FILEVIEW

