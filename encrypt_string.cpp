#include "encrypt_string.hpp"

QString encrypt_string(QString str) {

	// create qt hashing object
	QCryptographicHash * qhash = new QCryptographicHash(QCryptographicHash::Sha512);

	// create qt byte array object of string
	QByteArray qarray; qarray+=str;
	qhash->addData(qarray);

	QString res = qhash->result();

	delete qhash;
	return res;
}
