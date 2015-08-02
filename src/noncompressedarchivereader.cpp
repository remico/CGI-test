#include "noncompressedarchivereader.h"
#include <QDataStream>
#include <QDebug>

NonCompressedArchiveReader::NonCompressedArchiveReader(Directory *pDir, const char *encoding)
    : ArchiveReader(pDir, encoding)
{}

NonCompressedArchiveReader::~NonCompressedArchiveReader()
{}

QStringList NonCompressedArchiveReader::getArchiveContent(const QString &arcname)
{
    QString path = m_pDirectory->getArchivesPath() + arcname;
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) {
        qDebug() << QString("Cannot open the archive '%1'").arg(path);
        return QStringList();
    }

    QStringList files;
    foreach (FileItem i, parseArchive(f)) {
        files.append(i.name);
    }

    return files;
}

QByteArray NonCompressedArchiveReader::getFileContent(const QString &arcname, const QString &filename)
{
    QString path = m_pDirectory->getArchivesPath() + arcname;
    QFile f(path);
    if (!f.open(QFile::ReadOnly)) {
        qDebug() << QString("Cannot open the archive '%1'").arg(path);
        return QByteArray();
    }

    foreach (FileItem i, parseArchive(f)) {
        if (i.name == filename) {
            f.seek(i.contentPos);
            return f.read(i.contentLen);
        }
    }

    return QByteArray();
}

#ifdef Q_OS_WIN
#define le32toh // dirty hack for simplicity; we hope that Windows system always has LE format
#endif

NonCompressedArchiveReader::FileItemList NonCompressedArchiveReader::parseArchive(QFile &f)
{
    FileItemList items;
    long pos = 0;

    while (!f.atEnd()) {
        FileItem item;

        char encodedfilename[1000] = {0};  // hope that any filename can't be longer than the array len
        f.peek(encodedfilename, sizeof(encodedfilename));
        item.name = m_pCodec->toUnicode(encodedfilename);
        int filenamelen = qstrlen(encodedfilename) + 1;
        pos += filenamelen;
        f.seek(pos);

        char contentlen[sizeof(quint32)] = {0};
        f.read(contentlen, sizeof(quint32));
        item.contentLen = le32toh(*reinterpret_cast<quint32 *>(contentlen));
        pos += sizeof(quint32);

        item.contentPos = pos;
        pos += item.contentLen;
        f.seek(pos);

        items.append(item);
    }

    return items;
}
