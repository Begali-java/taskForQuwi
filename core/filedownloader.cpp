#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl imageUrl, QObject *parent) :
 QObject(parent)
{
 connect(
  &m_managerDownloader, SIGNAL (finished(QNetworkReply*)),
  this, SLOT (fileDownloaded(QNetworkReply*))
  );

 QNetworkRequest request(imageUrl);
 m_managerDownloader.get(request);
}

FileDownloader::~FileDownloader() { }

void FileDownloader::fileDownloaded(QNetworkReply* pReply) {
 m_imageData = pReply->readAll();
 pReply->deleteLater();
 emit downloaded();
}

QByteArray FileDownloader::downloadedData() const {
 return m_imageData;
}
