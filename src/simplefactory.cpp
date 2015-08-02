#include "simplefactory.h"

#include "noncompressedarchivereader.h"
#include "plainarchiveview.h"
#include "plaintxtfileview.h"
#include "plaindirectoryview.h"

SimpleFactory::SimpleFactory(SimpleFactory::Type arcReaderType,
                             SimpleFactory::Type arcViewType,
                             SimpleFactory::Type fileViewType,
                             SimpleFactory::Type dirViewType)
    : m_arcReaderType(arcReaderType)
    , m_arcViewType(arcViewType)
    , m_fileViewType(fileViewType)
    , m_dirViewType(dirViewType)
{}

SimpleFactory *SimpleFactory::instance()
{
    static SimpleFactory instance(ARC_READER_TYPE, ARC_VIEW_TYPE, FILE_VIEW_TYPE, DIR_VIEW_TYPE);
    return &instance;
}

ArchiveReader *SimpleFactory::createArchiveReader(Directory *pDir)
{
    switch (m_arcReaderType) {
    case ArchiveType_NonCompressed:
        return new NonCompressedArchiveReader(pDir);
    default:
        throw NonRigisteredTypeError(QString("Non-registered archive type '%1'")
                                     .arg(m_arcReaderType));
    }
}

ArchiveView *SimpleFactory::createArchiveView(ArchiveReader *pReader)
{
    switch (m_arcViewType) {
    case ArchiveViewType_Plain:
        return new PlainArchiveView(pReader);
    default:
        throw NonRigisteredTypeError(QString("Non-registered archive view type '%1'")
                                     .arg(m_arcViewType));
    }
}

FileView *SimpleFactory::createFileView(ArchiveReader *pReader)
{
    switch (m_fileViewType) {
    case FileViewType_PlainTxt:
        return new PlainTxtFileView(pReader);
    default:
        throw NonRigisteredTypeError(QString("Non-registered file view type '%1'")
                                     .arg(m_fileViewType));
    }
}

DirectoryView *SimpleFactory::createDirectoryView(Directory *pDir)
{
    switch (m_dirViewType) {
    case DirectoryViewType_Plain:
        return new PlainDirectoryView(pDir);
    default:
        throw NonRigisteredTypeError(QString("Non-registered directory view type '%1'")
                                     .arg(m_dirViewType));
    }
}
