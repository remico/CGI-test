#ifndef PACKER_H
#define PACKER_H

#include <QStringList>
#include <QTextCodec>
#include "constants.h"

class Packer
{
public:
    Packer(const QString &srcDir, const QString &dstDir, const char *encoding = DEFAULT_ENCODING);
    void setNameFilters(const QStringList &filters);
    bool packFiles(const QString &arcName);

private:
    QTextCodec *m_pCodec;
    QString m_srcDir;
    QString m_dstDir;
    QStringList m_nameFilters;
};

#endif // PACKER_H
