#include "plaintxtfileview.h"

PlainTxtFileView::PlainTxtFileView(ArchiveReader *pReader, const char *encoding)
    : FileView(pReader, encoding)
{}

PlainTxtFileView::~PlainTxtFileView()
{}

QString PlainTxtFileView::makeHtmlPage(PageMaker *pPagemaker,
                                       const QString &arcname,
                                       const QString &filename)
{
    QByteArray content = m_pReader->getFileContent(arcname, filename);

    pPagemaker->addHeader_ContentType("text/plain");
    pPagemaker->addEmptyString();
    pPagemaker->addPageContent(content);

    return pPagemaker->getResult();
}

