//Constructor

#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>

#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>

static int kRoleBody	= Qt::UserRole + 1;
static int kRoleCreated	= Qt::UserRole + 2;
static int kRoleTitle	= Qt::UserRole + 3;

MainWindow::MainWindow(QWidget *parent)		//Creates main Window
	: QWidget(parent)
{
	setWindowTitle("Notizen");		//Window characteristics
	setMinimumSize(900, 520);

	m_noteslist = new QListWidget(this);	//
	m_noteslist->setMinimumWidth(280);


	auto *titleLable = new QLabel("Titel:", this);		//Titel settings
	m_titleEdit = new QLineEdit(this);
	m_titleEdit->setPlaceholderText("");

	auto *bodyLable = new QLabel("Notiz:", this);		//Notiz settings
        m_bodyEdit = new QTextEdit(this);
        m_bodyEdit->setPlaceholderText("");

	m_addBtn = new QPushButton("Neuer Eintrag", this);		//Button creation
	m_deleteBtn = new QPushButton("Ausgewählte löschen", this);

	auto *viewerLable = new QLabel("Ausgewählter Eintrag", this);	//Viewer for Ausgewählter Eintrag
	m_viewer = new QTextEdit(this);
	m_viewer->setReadOnly(true);
	m_viewer->setPlaceholderText("Wähle Notiz aus");

	m_closeBtn = new QPushButton("Close", this);		//Close Button


	auto *rightTopBox = new QGroupBox("Neue Notiz", this);		//Group Box for Titel & Notiz
	auto *rightTopLayout = new QVBoxLayout(rightTopBox);
	rightTopLayout->addWidget(titleLable);
	rightTopLayout->addWidget(m_titleEdit);
	rightTopLayout->addWidget(bodyLable);
	rightTopLayout->addWidget(m_bodyEdit);

	auto *rightButtons = new QHBoxLayout();		//Button benith Groupbox Titel & Notiz
	rightButtons->addStretch();
	rightButtons->addWidget(m_addBtn);
	rightTopLayout->addLayout(rightButtons);

	auto *rightLayout = new QVBoxLayout();		//Layout of the right side (Groupbox Title & Notiz, viewer Ausgewählter Eintrag
	rightLayout->addWidget(rightTopBox);
	rightLayout->addWidget(viewerLable);
	rightLayout->addWidget(m_viewer);

	auto *contentLayout = new QHBoxLayout();	//Placement ans size left box (Widget) and Right Box (rightLayout)
	contentLayout->addWidget(m_noteslist, 1);
	contentLayout->addLayout(rightLayout, 2);

	auto *footerLayout = new QHBoxLayout();		//Footer (Placement close & delete btn)
	footerLayout->addWidget(m_closeBtn);
	footerLayout->addStretch();
	footerLayout->addWidget(m_deleteBtn);

	auto *mainLayout = new QVBoxLayout(this);	//Sets vertival layout of the Window
	mainLayout->addLayout(contentLayout);
	mainLayout->addLayout(footerLayout);
	setLayout(mainLayout);

	connect(m_addBtn,	&QPushButton::clicked, this, &MainWindow::addNote);				//Connects Buttons with logic
	connect(m_deleteBtn,	&QPushButton::clicked, this, &MainWindow::deleteSelectedNote);
	connect(m_closeBtn, 	&QPushButton::clicked, this, &QWidget::close);
	connect(m_noteslist, &QListWidget::itemSelectionChanged, this, &MainWindow::onSelectionChanged);

}

QString MainWindow::makeDefaultTitle() const	{

	const QString ts = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm");
	return "Notiz " + ts;
}

void MainWindow::addNote()	{		//activated from AddNote

	const QString title = m_titleEdit->text().trimmed();
	const QString body = m_bodyEdit->toPlainText().trimmed();

	if (title.isEmpty() && body.isEmpty())	{

		QMessageBox::information(this, "Kein Eintrag", "Titel und Text leer.");
		return;
	}
	const QDateTime created = QDateTime::currentDateTime();
	const QString finalTitle = title.isEmpty() ? makeDefaultTitle() : title;

	auto *item = new QListWidgetItem(m_noteslist);
	item->setText(created.toString("yyyy-MM-dd HH:mm") + "-" + finalTitle);		//add´s a timestamp
	item->setData(kRoleTitle, finalTitle);
	item->setData(kRoleBody, body);
	item->setData(kRoleCreated, created);

	m_noteslist->setCurrentItem(item);

	m_titleEdit->clear();
	m_bodyEdit->clear();
	m_titleEdit->setFocus();
}

void MainWindow::deleteSelectedNote()	{		//activated from delete Button

	QListWidgetItem *item = m_noteslist->currentItem();
	if (! item)	{
		QMessageBox::information(this, "Keine Auswahl", "Bitte eine Notiz auswählen");
		return;
	}

	delete item;

	if (m_noteslist->currentItem())	{
		showInViewer(m_noteslist->currentItem());
	}
	else	{
		m_viewer->clear();
		m_viewer->setPlaceholderText("Wähle eine Notiz aus");
	}
}

void MainWindow::onSelectionChanged()	{		//Leitet aufgerufenes weiter, wenn ausgewählt

	QListWidgetItem *item = m_noteslist->currentItem();
	showInViewer(item);
}

void MainWindow::showInViewer(QListWidgetItem *item)	{		//called by "onSelectionChanged" 

	if (! item)	{
		m_viewer->clear();
		m_viewer->setPlaceholderText("Wähle eine Notiz aus");
		return;
	}

	const QString title = item->data(kRoleTitle).toString();
	const QDateTime created = item->data(kRoleCreated).toDateTime();
	const QString body = item->data(kRoleBody).toString();

	QString text;
	text += title + "\n";
	text += "Erstellt: " + created.toString("yyyy-MM-dd HH:mm") + "\n";
	text += "---------\n";
	text += body + "\n";

	m_viewer->setPlainText(text);

}
