#include "refresh_thread.hpp"

refresh_thread::refresh_thread(QObject * _p_parent) {}
refresh_thread::~refresh_thread() {}

QString * refresh_thread::setup_connection(QString * content)
{
  /* this needs to be in a register... for... reasons */
  register QTcpSocket * pSocket = NULL;
  QString * read, tcp_server, port_string;
  read = new QString();

  bool contin = true;

  for (; contin; ) {
    if (pSocket != NULL) {delete pSocket;}
    pSocket = new QTcpSocket();

    QString host = "allen-software.com";
    // QString host = "localhost";

    /* connect to master */
    pSocket->connectToHost(host, (quint16) 3224, QIODevice::ReadWrite);
    pSocket->waitForConnected(500);

    std::cerr << "setup_connection: " << host.toStdString() << std::endl;
    // if socket did not connect start over
    if (pSocket->state() == QAbstractSocket::UnconnectedState) {
      pSocket->disconnectFromHost();
      pSocket->abort();
      delete pSocket;
      pSocket = NULL;
      continue;
    }

    // write to master to request a worker
    pSocket->write("REQUEST_WORKER\r\n");

    // not sure if i need to do this part...
    tcp_server = QString("localhost") + ':';
    port_string.setNum(3224);
    tcp_server += port_string + "\r\n" + '\0';

    std::cerr << "setup_connection: " << tcp_server.toStdString() << std::endl;
    pSocket->write(tcp_server.toStdString().c_str());

    // for for the stuff to be written
    pSocket->waitForBytesWritten(-1);

wait_on_master:
    pSocket->waitForReadyRead();

    // read from master to get worker
    for (; pSocket->canReadLine(); (*read) += pSocket->readLine()) {
    }

    // if nothing read, then start over
    if (read->size() == 0) {goto wait_on_master;}

    // get host and port
    read->replace("\r\n", "");
    QStringList l = read->split(':');

    pSocket->disconnectFromHost();
    delete pSocket; pSocket = new QTcpSocket();

    /* connect to worker */
    pSocket->connectToHost(l.at(0), (quint16)l.at(1).toInt(), QIODevice::ReadWrite);
    pSocket->waitForConnected(500);

    // if never connects to worker then start over
    if (pSocket->state() == QAbstractSocket::UnconnectedState) {
      pSocket->disconnectFromHost();
      pSocket->abort();
      delete pSocket;
      pSocket = NULL;
      read->clear();
      continue;
    }

    // write content to worker
    pSocket->write(content->toStdString().c_str());
    pSocket->waitForBytesWritten(-1);

    pSocket->waitForReadyRead();
    read->clear();
    for (; pSocket->canReadLine(); (*read) += pSocket->readLine()) {
    }

    //clean up stuff
    pSocket->disconnectFromHost();
    pSocket->abort();
    delete pSocket;
    pSocket = NULL;
    contin = false;
  }

  return read;
}
