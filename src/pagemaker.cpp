#include "pagemaker.h"
#include "constants.h"

PageMaker::PageMaker(const QString &appname)
    : m_appName(appname + APP_EXT)
{}

QString PageMaker::appName() const
{ return m_appName; }

void PageMaker::addHeader_ContentType(const QString &mime)
{ m_page.append(QString("Content-Type: %1\r\n").arg(mime)); }

void PageMaker::addHeader_ContentDisposition(const QString &filename)
{ m_page.append(QString("Content-Disposition: attachment; filename=\"%1\"\r\n").arg(filename)); }

void PageMaker::addHeader_ContentDescription(const QString &description)
{ m_page.append(QString("Content-Description: %1\r\n").arg(description)); }

void PageMaker::addHeader_ContentLength(int len)
{ m_page.append(QString("Content-Length: %1\r\n").arg(len)); }

void PageMaker::addEmptyString()
{ m_page.append("\r\n"); }

void PageMaker::beginHtmlPage(const QString &title)
{ m_page.append(QString("\r\n<html><head><title>%1</title></head><body>").arg(title)); }

void PageMaker::endHtmlPage()
{ m_page.append("</body></html>"); }

void PageMaker::addPageContent(const QString &content)
{ m_page.append(content); }

QString PageMaker::getResult() const
{ return m_page; }
