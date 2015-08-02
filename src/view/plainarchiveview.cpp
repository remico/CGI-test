#include "plainarchiveview.h"

PlainArchiveView::PlainArchiveView(ArchiveReader *pReader, const char *encoding)
    : ArchiveView(pReader, encoding)
{}

PlainArchiveView::~PlainArchiveView()
{}

QString PlainArchiveView::makeHtmlPage(PageMaker *pPagemaker, const QString &arcname)
{
    QString linktag_vw("<a href=\"%1?file_vw=%2&arc=%3\">%2</a>");
    QString linktag_dl("<a href=\"%1?file_dl=%2&arc=%3\">Download</a>");
    QString linkslist;

    foreach (QString s, m_pReader->getArchiveContent(arcname)) {
        linkslist.append(linktag_vw.arg(pPagemaker->appName(), s, arcname)).append("&nbsp;&nbsp;");
        linkslist.append(linktag_dl.arg(pPagemaker->appName(), s, arcname)).append("<br>");
    }

    pPagemaker->addHeader_ContentType("text/html");
    pPagemaker->beginHtmlPage("CGI: page 2");
    pPagemaker->addPageContent(QString("<h2>List of files in archive \"%1\":</h2>").arg(arcname));
    pPagemaker->addPageContent(linkslist);
    pPagemaker->addPageContent(QString("<br><a href=\"%1\"><b>&lt;</b>&nbsp;Back to the list of archives</a>")
                             .arg(pPagemaker->appName()));
    pPagemaker->endHtmlPage();

    return pPagemaker->getResult();
}

