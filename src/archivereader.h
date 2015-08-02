#ifndef ARCHIVEREADER
#define ARCHIVEREADER

#include <QString>
#include <QTextCodec>
#include "constants.h"
#include "directory.h"

class ArchiveReader
{
public:
    explicit ArchiveReader(Directory *pDir, const char *encoding = DEFAULT_ENCODING)
        : m_pCodec(QTextCodec::codecForName(encoding))
        , m_pDirectory(pDir)
    {}
    virtual ~ArchiveReader() {}

    virtual QStringList getArchiveContent(const QString &arcname) = 0;
    virtual QByteArray getFileContent(const QString &arcname, const QString &filename) = 0;

protected:
    QTextCodec *m_pCodec;
    Directory *m_pDirectory;
};

#endif // ARCHIVEREADER

