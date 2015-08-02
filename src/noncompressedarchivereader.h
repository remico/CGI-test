#ifndef NONCOMPRESSEDARCHIVEREADER_H
#define NONCOMPRESSEDARCHIVEREADER_H

#include "archivereader.h"
#include "fileitem.h"
#include <QFile>

class NonCompressedArchiveReader : public ArchiveReader
{
    typedef QList<FileItem> FileItemList;

public:
    explicit NonCompressedArchiveReader(Directory *pDir, const char *encoding = DEFAULT_ENCODING);
    ~NonCompressedArchiveReader();

    QStringList getArchiveContent(const QString &arcname);
    QByteArray getFileContent(const QString &arcname, const QString &filename);

private:
    FileItemList parseArchive(QFile &f);
};

#endif // NONCOMPRESSEDARCHIVEREADER_H
