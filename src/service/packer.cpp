#include "packer.h"
#include <QFile>
#include <QDir>
#include <QDataStream>
#include <QFileInfo>
#include <QDebug>

Packer::Packer(const QString &srcDir, const QString &dstDir, const char *encoding)
    : m_pCodec(QTextCodec::codecForName(encoding))
    , m_srcDir(srcDir)
    , m_dstDir(dstDir)
{}

void Packer::setNameFilters(const QStringList &filters)
{ m_nameFilters = filters; }

bool Packer::packFiles(const QString &arcName)
{
    QDir srcdir(m_srcDir);
    if (!srcdir.exists()) {
        qDebug() << QString("Cannot find the '%1' directory").arg(m_srcDir);
        return false;
    }
    srcdir.setFilter(QDir::Files);
    srcdir.setSorting(QDir::Name|QDir::IgnoreCase);
    if (!m_nameFilters.isEmpty())
        srcdir.setNameFilters(m_nameFilters);
    QFileInfoList fileInfos = srcdir.entryInfoList();

    QDir dstdir(m_dstDir);
    if (!dstdir.exists()) {
        if (!dstdir.mkdir(m_dstDir)) {
            qDebug() << QString("Cannot create the '%1' directory").arg(m_dstDir);
            return false;
        }
    }

    QString outfilename(m_dstDir + QDir::separator() + arcName);
    QFile outfile(outfilename);
    if (!outfile.open(QFile::WriteOnly)) {
        qDebug() << QString("Cannot open the file '%1'").arg(outfilename);
        return false;
    }

    QDataStream outstream;
    outstream.setByteOrder(QDataStream::LittleEndian);
    outstream.setDevice(&outfile);

    foreach (QFileInfo finfo, fileInfos) {
        QFile infile(finfo.filePath());
        if (!infile.open(QFile::ReadOnly)) {
            qDebug() << QString("Cannot open the file '%1'").arg(finfo.filePath());
            return false;
        }
        QByteArray infileName = m_pCodec->fromUnicode(finfo.fileName());
        QByteArray infileContent = infile.readAll();
        outstream.writeRawData(infileName.constData(), infileName.size() + 1);
        outstream << static_cast<quint32>(finfo.size());
        outstream.writeRawData(infileContent.constData(), infileContent.size());
    }

    return true;
}
