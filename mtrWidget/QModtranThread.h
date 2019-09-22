#pragma once
#include <Qthread>
#include <QProcess>

class QModtranThread :public QThread
{
	Q_OBJECT


public:
	QModtranThread();
	//QProcess process;


protected:
	void run() Q_DECL_OVERRIDE;

};