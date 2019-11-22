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

	this->setWindowTitle(u8"Modtran大气计算");

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
	QString curPath = QDir::currentPath();  //获取系统当前目录
	QString dlgTitle = u8"打开 .tp5 文件 文件名不要有中文"; //对话框标题
	QString filter = u8"Modtran输入文件(*.tp5 )"; //文件过滤器
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
		std::string stdtp5name = Qtp5name.toStdString();  // 要写入modroot.in 中的值
		std::string stdtp5nameFull = Qtp5nameFull.toStdString();  // exam "test.tp5"

		// 写modroot.in 文件
		std::ofstream Modroot;
		Modroot.open("./Modtran4/modroot.in");
		if (!Modroot)
		{
			ui.modtranStateText->appendPlainText(u8"!生成 .in 文件失败，检查目录下是否有Modtran4文件夹");
			QMessageBox Modroot_warn;
			Modroot_warn.setText(u8"!生成 .in 文件失败，检查目录下是否有Modtran4文件夹");
			Modroot_warn.setWindowTitle(u8"提醒");
			Modroot_warn.exec();
			return;
		}
		else
		{
			Modroot << stdtp5name;
			Modroot.close();
		}

		// Modtran4文件夹移入所选tp5文件
		QString Qtp5dstPath = "./Modtran4/" + Qtp5nameFull;

		bool isExist = QFile::exists(Qtp5dstPath);
		if (isExist)  // 如果文件存在，删除
		{
			QFile::remove(Qtp5dstPath);
		}


		bool isCopyRight = QFile::copy(aFileName, Qtp5dstPath);
		if (!isCopyRight)
		{
			ui.modtranStateText->appendPlainText(u8"！移动文件失败，请检查Modtran4文件夹和tp5文件路径");
			return;
		}
		
		

		ui.modtranStateText->appendPlainText(QString(u8"当前Modtran输入文件(.tp5)：    "));
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
		tp5warn.setText(u8"请输入 .tp5 文件！");
		tp5warn.setWindowTitle(u8"提醒");
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
	QString curPath = QDir::currentPath();  //获取系统当前目录
	QString dlgTitle = u8"打开 .tp7 文件"; //对话框标题
	QString filter = u8"Modtran输入文件(*.tp7 )"; //文件过滤器
	tp7FileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);
	

	if (tp7FileName.isEmpty())
		return;
	else
	{
		ui.modtranStateText->appendPlainText(QString("==================================================="));
		ui.modtranStateText->appendPlainText(QString(u8"当前 .tp7 文件路径：    "));
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

	double RadTotal = 0.0;  // 辐亮度统计
	double Rad = 0.0;

	int Tp7case;  // =0 :散射辐亮度  =1：直射辐亮度

	
	if (!Tp7File.exists())
	{
		QMessageBox tp7warn;
		tp7warn.setText(u8"请输入 .tp7 文件！");
		tp7warn.setWindowTitle(u8"提醒");
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
	strGet = strSim.section(" ", 3, 3);  // 获取modtran运行模式

	//ui.modtranStateText->appendPlainText(strGet);

	if (strGet == QString("2"))  // 散射
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
				strGet = strSim.section(" ", 9, 9);  // 需要取的第几列

				Rad = strGet.toDouble();

				RadTotal += Rad;

			}
		}

		RadTotal = RadTotal * 10000 * 3.14159;

		QString displayRadNum = QString::number(RadTotal, 'f', 2);

		ui.modtranStateText->appendPlainText(u8"计算散射辐照度数值：  ");
		ui.modtranStateText->appendPlainText(displayRadNum);
		ui.modtranStateText->appendPlainText("===================================================");


	}// 散射



	else if (strGet == QString("3"))  //直射
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
				strGet = strSim.section(" ", 2, 2);  // 需要取的第几列

				Rad = strGet.toDouble();

				RadTotal += Rad;

			}
		}

		RadTotal = RadTotal * 10000 * 3.14159;

		QString displayRadNum = QString::number(RadTotal, 'f', 2);

		ui.modtranStateText->appendPlainText(u8"计算直射辐照度数值：  ");
		ui.modtranStateText->appendPlainText(displayRadNum);
		ui.modtranStateText->appendPlainText("===================================================");
	}//直射

	else
	{
		ui.modtranStateText->appendPlainText(u8"解析失败");
		ui.modtranStateText->appendPlainText("===================================================");
		return;
	}





	Tp7File.close();

	return;
}





/*****************************************************************************************************************/



void mtrWidget::on_modtranThread_started()
{
	ui.modtranStateText->appendPlainText(u8"开始Modtran大气计算");
	ui.modtranStateText->appendPlainText(u8"正在进行Modtran大气计算");
}


/*****************************************************************************************************************/

void mtrWidget::on_modtranThread_finished()
{
	ui.modtranStateText->appendPlainText(u8"完成Modtran大气计算,已生成tp7文件");
	ui.modtranStateText->appendPlainText(QString("==================================================="));

	QString curPath = QDir::currentPath();
	QFileInfo fileInfo(aFileName);
	tp7FileName = curPath + "/Modtran4/" + fileInfo.baseName() +".tp7";
	ui.modtranStateText->appendPlainText(QString(u8"当前 .tp7 文件路径：    "));

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

	double TransTotal = 0.0;  // 透过统计
	double Trans = 0.0;


	if (!Tp7File.exists())
	{
		QMessageBox tp7warn;
		tp7warn.setText(u8"请输入 .tp7 文件！");
		tp7warn.setWindowTitle(u8"提醒");
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
			strGet = strSim.section(" ", 1, 1);  // 需要取的第几列 第一列表示透过率

			Trans = strGet.toDouble();

			TransTotal += Trans;
			//qDebug() << TransTotal << endl;
		}
	}

		

		QString displayRadNum = QString::number(TransTotal, 'f', 2);

		ui.modtranStateText->appendPlainText(u8"计算透过率数值：  ");
		ui.modtranStateText->appendPlainText(displayRadNum);
		ui.modtranStateText->appendPlainText("===================================================");
}

/*****************************************************************************************************************/
