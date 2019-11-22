#include "mtrWidget.h"
#include<Qstring>
#include<Qdir>
#include<QFileDialog>
#include<QMessageBox>
#include<qtextstream.h>
#include<qdebug.h>
#include<iostream>
#include<fstream>
#include<Windows.h>


/**************************************************************************************************************/

mtrWidget::mtrWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	this->setWindowTitle(u8"Modtran��������");

	connect(ui.btn_openTp5, SIGNAL(clicked()), this, SLOT(on_btn_OpenTp5_clicked()));
	connect(ui.btn_startMod, SIGNAL(clicked()), this, SLOT(on_btn_startMod_clicked()));
	connect(ui.btn_openTp7, SIGNAL(clicked()), this, SLOT(on_btn_OpenTp7_clicked()));
	connect(ui.btn_cRadiance, SIGNAL(clicked()), this, SLOT(on_btn_cRadiance_clicked()));
	connect(ui.btn_clr, SIGNAL(clicked()), this, SLOT(on_btn_clr_clicked()));
	connect(ui.btn_cTransmittance, SIGNAL(clicked()), this, SLOT(on_btn_cTransmittance_clicked()));

	connect(&modtranThread, SIGNAL(started()), this, SLOT(on_modtranThread_started()));
	connect(&modtranThread, SIGNAL(finished()), this, SLOT(on_modtranThread_finished()));

}

/*****************************************************************************************************************/


void mtrWidget::on_btn_OpenTp5_clicked()
{
	QString curPath = QDir::currentPath();  //��ȡϵͳ��ǰĿ¼
	QString dlgTitle = u8"�� .tp5 �ļ� �ļ�����Ҫ������"; //�Ի������
	QString filter = u8"Modtran�����ļ�(*.tp5 )"; //�ļ�������
	aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

	if (aFileName.isEmpty())
		return;
	else
	{
		ui.modtranStateText->clear();
		
		QStringList list = aFileName.split("/");
		QString Qtp5nameFull = list[list.length() - 1];  // exam:  "test.tp5"
		QStringList list2 = Qtp5nameFull.split(".");
		QString Qtp5name = list2[0];  // exam: "test"
		std::string stdtp5name = Qtp5name.toStdString();  // Ҫд��modroot.in �е�ֵ
		std::string stdtp5nameFull = Qtp5nameFull.toStdString();  // exam "test.tp5"

		// дmodroot.in �ļ�
		std::ofstream Modroot;
		Modroot.open("./Modtran4/modroot.in");
		if (!Modroot)
		{
			ui.modtranStateText->appendPlainText(u8"!���� .in �ļ�ʧ�ܣ����Ŀ¼���Ƿ���Modtran4�ļ���");
			QMessageBox Modroot_warn;
			Modroot_warn.setText(u8"!���� .in �ļ�ʧ�ܣ����Ŀ¼���Ƿ���Modtran4�ļ���");
			Modroot_warn.setWindowTitle(u8"����");
			Modroot_warn.exec();
			return;
		}
		else
		{
			Modroot << stdtp5name;
			Modroot.close();
		}

		// Modtran4�ļ���������ѡtp5�ļ�
		QString Qtp5dstPath = "./Modtran4/" + Qtp5nameFull;

		bool isExist = QFile::exists(Qtp5dstPath);
		if (isExist)  // ����ļ����ڣ�ɾ��
		{
			QFile::remove(Qtp5dstPath);
		}


		bool isCopyRight = QFile::copy(aFileName, Qtp5dstPath);
		if (!isCopyRight)
		{
			ui.modtranStateText->appendPlainText(u8"���ƶ��ļ�ʧ�ܣ�����Modtran4�ļ��к�tp5�ļ�·��");
			return;
		}
		
		

		ui.modtranStateText->appendPlainText(QString(u8"��ǰModtran�����ļ�(.tp5)��    "));
		ui.modtranStateText->appendPlainText(aFileName);
		ui.modtranStateText->appendPlainText(QString("==================================================="));
	}
	return;
}

/*****************************************************************************************************************/





void mtrWidget::on_btn_startMod_clicked()
{
	if (aFileName.isEmpty())
	{
		QMessageBox tp5warn;
		tp5warn.setText(u8"������ .tp5 �ļ���");
		tp5warn.setWindowTitle(u8"����");
		tp5warn.exec();
		return;
	}
	else
	{
		modtranThread.start();
	}
}


/*****************************************************************************************************************/

void mtrWidget::on_btn_OpenTp7_clicked()
{
	QString curPath = QDir::currentPath();  //��ȡϵͳ��ǰĿ¼
	QString dlgTitle = u8"�� .tp7 �ļ�"; //�Ի������
	QString filter = u8"Modtran�����ļ�(*.tp7 )"; //�ļ�������
	tp7FileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
	

	if (tp7FileName.isEmpty())
		return;
	else
	{
		ui.modtranStateText->appendPlainText(QString("==================================================="));
		ui.modtranStateText->appendPlainText(QString(u8"��ǰ .tp7 �ļ�·����    "));
		ui.modtranStateText->appendPlainText(tp7FileName);
	}
}


/*****************************************************************************************************************/



void mtrWidget::on_btn_cRadiance_clicked()
{
	QFile Tp7File(tp7FileName);
	QString str;
	QString strSim;
	QString strGet;

	double RadTotal = 0.0;  // ������ͳ��
	double Rad = 0.0;

	int Tp7case;  // =0 :ɢ�������  =1��ֱ�������

	
	if (!Tp7File.exists())
	{
		QMessageBox tp7warn;
		tp7warn.setText(u8"������ .tp7 �ļ���");
		tp7warn.setWindowTitle(u8"����");
		tp7warn.exec();
		return;
	}
	else if (!Tp7File.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return ;
	}

	
	QTextStream Tp7Stream(&Tp7File);
	str = Tp7Stream.readLine();

	strSim = str.simplified();
	strGet = strSim.section(" ", 3, 3);  // ��ȡmodtran����ģʽ

	//ui.modtranStateText->appendPlainText(strGet);

	if (strGet == QString("2"))  // ɢ��
	{

		for (int i = 0; i < 10; i++)
		{
			str = Tp7Stream.readLine();
			//ui.modtranStateText->appendPlainText(str);
		}


		while (true)
		{
			str = Tp7Stream.readLine();

			if (Tp7Stream.atEnd())
			{
				//ui.modtranStateText->appendPlainText(str);
				break;
			}
			else
			{
				strSim = str.simplified();
				strGet = strSim.section(" ", 9, 9);  // ��Ҫȡ�ĵڼ���

				Rad = strGet.toDouble();

				RadTotal += Rad;

			}
		}

		RadTotal = RadTotal * 10000 * 3.14159;

		QString displayRadNum = QString::number(RadTotal, 'f', 2);

		ui.modtranStateText->appendPlainText(u8"����ɢ����ն���ֵ��  ");
		ui.modtranStateText->appendPlainText(displayRadNum);
		ui.modtranStateText->appendPlainText("===================================================");


	}// ɢ��



	else if (strGet == QString("3"))  //ֱ��
	{
		for (int i = 0; i < 10; i++)
		{
			str = Tp7Stream.readLine();
			//ui.modtranStateText->appendPlainText(str);
		}


		while (true)
		{
			str = Tp7Stream.readLine();

			if (Tp7Stream.atEnd())
			{
				//ui.modtranStateText->appendPlainText(str);
				break;
			}
			else
			{
				strSim = str.simplified();
				strGet = strSim.section(" ", 2, 2);  // ��Ҫȡ�ĵڼ���

				Rad = strGet.toDouble();

				RadTotal += Rad;

			}
		}

		RadTotal = RadTotal * 10000 * 3.14159;

		QString displayRadNum = QString::number(RadTotal, 'f', 2);

		ui.modtranStateText->appendPlainText(u8"����ֱ����ն���ֵ��  ");
		ui.modtranStateText->appendPlainText(displayRadNum);
		ui.modtranStateText->appendPlainText("===================================================");
	}//ֱ��

	else
	{
		ui.modtranStateText->appendPlainText(u8"����ʧ��");
		ui.modtranStateText->appendPlainText("===================================================");
		return;
	}





	Tp7File.close();

	return;
}





/*****************************************************************************************************************/



void mtrWidget::on_modtranThread_started()
{
	ui.modtranStateText->appendPlainText(u8"��ʼModtran��������");
	ui.modtranStateText->appendPlainText(u8"���ڽ���Modtran��������");
}


/*****************************************************************************************************************/

void mtrWidget::on_modtranThread_finished()
{
	ui.modtranStateText->appendPlainText(u8"���Modtran��������,������tp7�ļ�");
	ui.modtranStateText->appendPlainText(QString("==================================================="));

	QString curPath = QDir::currentPath();
	QFileInfo fileInfo(aFileName);
	tp7FileName = curPath + "/Modtran4/" + fileInfo.baseName() +".tp7";
	ui.modtranStateText->appendPlainText(QString(u8"��ǰ .tp7 �ļ�·����    "));

	ui.modtranStateText->appendPlainText(tp7FileName);

}


/*****************************************************************************************************************/

void mtrWidget::on_btn_clr_clicked()
{
	ui.modtranStateText->clear();
}

void mtrWidget::on_btn_cTransmittance_clicked()
{
	QFile Tp7File(tp7FileName);
	QString str;
	QString strSim;
	QString strGet;

	double TransTotal = 0.0;  // ͸��ͳ��
	double Trans = 0.0;


	if (!Tp7File.exists())
	{
		QMessageBox tp7warn;
		tp7warn.setText(u8"������ .tp7 �ļ���");
		tp7warn.setWindowTitle(u8"����");
		tp7warn.exec();
		return;
	}
	else if (!Tp7File.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		return;
	}


	QTextStream Tp7Stream(&Tp7File);
	str = Tp7Stream.readLine();

	strSim = str.simplified();



	for (int i = 0; i < 10; i++)
	{
		str = Tp7Stream.readLine();
	}


	while (true)
	{
		str = Tp7Stream.readLine();

		if (Tp7Stream.atEnd())
		{

			break;
		}
		else
		{
			strSim = str.simplified();
			strGet = strSim.section(" ", 1, 1);  // ��Ҫȡ�ĵڼ��� ��һ�б�ʾ͸����

			Trans = strGet.toDouble();

			TransTotal += Trans;
			//qDebug() << TransTotal << endl;
		}
	}

		

		QString displayRadNum = QString::number(TransTotal, 'f', 2);

		ui.modtranStateText->appendPlainText(u8"����͸������ֵ��  ");
		ui.modtranStateText->appendPlainText(displayRadNum);
		ui.modtranStateText->appendPlainText("===================================================");
}

/*****************************************************************************************************************/
