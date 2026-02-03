#pragma once

#include <QWidget>
#include <QDateTime>

class QLineEdit;
class QTextEdit;
class QListWidget;
class QListWidgetItem;
class QPushButton;

class MainWindow : public QWidget	{
	public:
		explicit MainWindow(QWidget *parent = nullptr);

	private:
		void addNote();
		void deleteSelectedNote();
		void onSelectionChanged();

	QString makeDefaultTitle() const;
	void showInViewer(QListWidgetItem *Item);

	QLineEdit	*m_titleEdit	= nullptr;
	QTextEdit       *m_bodyEdit	= nullptr;
	QListWidget	*m_noteslist    = nullptr;
	QTextEdit       *m_viewer	= nullptr;

	QPushButton	*m_addBtn	= nullptr;
	QPushButton	*m_deleteBtn	= nullptr;
	QPushButton	*m_closeBtn	= nullptr;
};
