#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <QStringList>
#include "pagemaker.h"

class Directory
{
public:
    Directory(const QString &path) : m_dirPath(path) {}

    void setNameFilters(const QStringList &nameFilters);    // e.g. QStringList() << "*.ext1" << "*.ext2";
    bool searchArchives();

    QStringList getArchivesList() const;
    QString getArchivesPath() const;

private:
    QStringList m_archives;
    QStringList m_nameFilters;
    QString m_dirPath;
};

#endif // DIRECTORY_H
