#ifndef SIMPLEFACTORY_H
#define SIMPLEFACTORY_H

#include <exception>
#include "archivereader.h"
#include "archiveview.h"
#include "fileview.h"
#include "directoryview.h"

#if defined (Q_OS_WIN)
#define _NOTHROW
#else
#define _NOTHROW _GLIBCXX_USE_NOEXCEPT
#endif

class NonRigisteredTypeError : public std::exception
{
public:
    explicit NonRigisteredTypeError(const QString &error)
    { m_error = error; }

    const char *what() const _NOTHROW
    { return m_error.toUtf8().constData(); }

private:
    QString m_error;
};

class SimpleFactory
{
public:
    enum Type {
        ArchiveType_NonCompressed = 0x00,
        ArchiveViewType_Plain     = 0x10,
        FileViewType_PlainTxt     = 0x20,
        DirectoryViewType_Plain   = 0x30
    };

    static SimpleFactory *instance();

    virtual ~SimpleFactory() {}

    virtual ArchiveReader *createArchiveReader(Directory *pDir);
    virtual ArchiveView *createArchiveView(ArchiveReader *pReader);
    virtual FileView *createFileView(ArchiveReader *pReader);
    virtual DirectoryView *createDirectoryView(Directory *pDir);

protected:
    SimpleFactory(Type arcReaderType,
                  Type arcViewType,
                  Type fileViewType,
                  Type dirViewType);

private:
    Type m_arcReaderType;
    Type m_arcViewType;
    Type m_fileViewType;
    Type m_dirViewType;
};

#endif // SIMPLEFACTORY_H
