#include "mtrWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	mtrWidget w;
	w.show();
	return a.exec();
}
