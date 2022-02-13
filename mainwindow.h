#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
} // namespace Ui

class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent=nullptr);
    QMap<QPushButton*,QHBoxLayout*> button_to_layout_map;
    QMap<QLayout*,QTimer*> layout_timer_map;
    QVector<QHBoxLayout*> layout_vec;
    QSystemTrayIcon* sysTrayIcon;

    void plus_clicked();
    void minus_clicked();
    void quit_clicked();
    void start_clicked();
    void stop_clicked();
    void execute_timer(QTimer*,QString,int,bool);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

};


QT_END_NAMESPACE

#endif // MAINWINDOW_H
