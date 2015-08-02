#include "directory.h"
#include <QDir>
#include <QDebug>

void Directory::setNameFilters(const QStringList &nameFilters)
{
    if (!nameFilters.isEmpty())
        m_nameFilters = nameFilters;
}

bool Directory::searchArchives()
{
    QDir dir(m_dirPath);
    if (!dir.exists()) {
        qDebug() << QString("Cannot find the '%1' directory").arg(m_dirPath);
        return false;
    }
    dir.setFilter(QDir::Files);
    dir.setSorting(QDir::Name|QDir::IgnoreCase);
    if (!m_nameFilters.isEmpty())
        dir.setNameFilters(m_nameFilters);
    m_archives = dir.entryList();
    return true;
}

QStringList Directory::getArchivesList() const
{
    return m_archives;
}

QString Directory::getArchivesPath() const
{
    return m_dirPath + QDir::separator();
}
