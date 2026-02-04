#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])	{

	QApplication app(argc, argv);	//Initializes the GUI

	MainWindow w;			//Creates Main Window
	w.show();			//Shows the Window

	return app.exec();		//Reactions on interaction
}
