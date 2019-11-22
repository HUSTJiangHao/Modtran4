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
	QString aFileName;  // tp5文件的路径
	QString tp7FileName; //tp7w文件路径
	QModtranThread modtranThread;

	

private slots:
	void on_btn_OpenTp5_clicked();  // 点击打开tp5文件
	void on_btn_startMod_clicked();  // 点击开始modtran计算
	void on_btn_OpenTp7_clicked();  // 点击打开tp7
	void on_btn_cRadiance_clicked();  // 点击解析tp7
	void on_btn_clr_clicked();
	void on_btn_cTransmittance_clicked();

	void on_modtranThread_started();  
	void on_modtranThread_finished(); 



};

