#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mtrWidget.h"
#include<Qstring>
#include"QModtranThread.h"

class mtrWidget : public QMainWindow
{
	Q_OBJECT

public:
	mtrWidget(QWidget *parent = Q_NULLPTR);


private:
	Ui::mtrWidgetClass ui;
	QString aFileName;  // tp5�ļ���·��
	QString tp7FileName; //tp7w�ļ�·��
	QModtranThread modtranThread;

	

private slots:
	void on_btn_OpenTp5_clicked();  // �����tp5�ļ�
	void on_btn_startMod_clicked();  // �����ʼmodtran����
	void on_btn_OpenTp7_clicked();  // �����tp7
	void on_btn_cRadiance_clicked();  // �������tp7
	void on_btn_clr_clicked();
	void on_btn_cTransmittance_clicked();

	void on_modtranThread_started();  
	void on_modtranThread_finished(); 



};

