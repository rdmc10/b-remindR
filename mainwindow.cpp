#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "timercpp.h"
#include <QAction>
#include <QMessageBox>
#include <QCloseEvent>
#include <QDebug>
#include <QLayout>
#include <QVBoxLayout>
#include <QCheckBox>

#define to_ms(x) (int)(x*60000)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(780,600);

    sysTrayIcon=new QSystemTrayIcon();

    QAction* exit_action = new QAction(tr("&Exit"),this);
    connect(exit_action,&QAction::triggered,[=](){
        QApplication::quit();
    });

    QAction* hide_action = new QAction(tr("&Hide"),this);
    connect(hide_action,&QAction::triggered,[=](){
        this->hide();
    });

    QAction* show_action = new QAction(tr("&Show"),this);
    connect(show_action,&QAction::triggered,[=](){
        this->show();
        resize(780,600);
    });

    //TODO:change icon
    this->sysTrayIcon->setIcon(QIcon("./reminder.png"));
    QMenu* tray_menu = new QMenu();
    tray_menu->addAction(exit_action);
    tray_menu->addAction(hide_action);
    tray_menu->addAction(show_action);
    this->sysTrayIcon->setContextMenu(tray_menu);

    this->sysTrayIcon->show();

    //Generate one timer by default
    plus_clicked();

    QObject::connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::plus_clicked);
    QObject::connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::start_clicked);
    QObject::connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::stop_clicked);
    QObject::connect(ui->pushButton_4,&QPushButton::clicked,this,&MainWindow::update_clicked);
    QObject::connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWindow::quit_clicked);
    QObject::connect(ui->pushButton_6,&QPushButton::clicked,this,[=](){
            this->hide();
        });
}

void MainWindow::plus_clicked(){
    QVBoxLayout* layout=ui->verticalLayout;
    QHBoxLayout* new_layout = new QHBoxLayout();
    new_layout->setSpacing(15);

    QLineEdit* line_edit = new QLineEdit();
    line_edit->setText("HEEY");
    new_layout->addWidget(line_edit);

    QDoubleSpinBox* spin_box = new QDoubleSpinBox();
    spin_box->setRange(0,9999);
    new_layout->addWidget(spin_box);
    spin_box->setSingleStep(1.0);

    QCheckBox* check_box = new QCheckBox();
    check_box->setText(QString("Loop"));
    check_box->setChecked(0);
    new_layout->addWidget(check_box);

    QPushButton* new_close_button = new QPushButton();
    new_close_button->setText(QString("-"));
    new_layout->addWidget(new_close_button);

    QLabel* label = new QLabel();
    label->setText(QString("Stopped"));
    new_layout->addWidget(label);

    button_to_layout_map.insert(new_close_button,new_layout);

    layout_vec.push_back(new_layout);
    connect(new_close_button,&QPushButton::clicked,this,&MainWindow::minus_clicked);
    layout->insertLayout(0,new_layout);

    QTimer* timer = new QTimer();
    layout_timer_map.insert(new_layout,timer);
}

void MainWindow::minus_clicked(){
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    QHBoxLayout* layout = button_to_layout_map.value(button);
    QTimer* timer = layout_timer_map.value(layout);
    layout_timer_map.remove(layout);
    if(timer->isActive())
        timer->stop();
    delete timer;

    layout_vec.removeOne(layout);
    while(layout->count()){
        QLayoutItem* item = layout->takeAt(0);
        delete item->widget();
        delete item;
    }
    delete layout;
}

void MainWindow::execute_timer(QTimer* timer,QLayout* layout){
    QLineEdit* line_edit = qobject_cast<QLineEdit*>(layout->itemAt(0)->widget());
    QDoubleSpinBox* spin_box = qobject_cast<QDoubleSpinBox*>(layout->itemAt(1)->widget());
    QCheckBox* check_box = qobject_cast<QCheckBox*>(layout->itemAt(2)->widget());
    QLabel* label = qobject_cast<QLabel*>(layout->itemAt(4)->widget());

    bool looping = check_box->isChecked();
    QString message = line_edit->text();
    double interval = spin_box->value();
    if(interval>0)
        label->setText(QString("Running"));
    else
        label->setText(QString("Stopped"));

    connect(timer, &QTimer::timeout, this, [=]() {
        //TODO: change icon
        this->sysTrayIcon->showMessage(QString("Reminder!"), message,
                                        QIcon("./warning.png"),
                                        15000);
        label->setText("Stopped");
        if(looping && interval)
            timer->start(to_ms(interval));
        else{
            timer->stop();
        }
    });

    if(interval>0)
        timer->start(to_ms(interval));
}

void MainWindow::start_clicked(){
    QTimer* timer;
    for(auto it:layout_vec){
        timer = layout_timer_map.value(it);
        execute_timer(timer,it);
    }
    this->hide();
}

void MainWindow::update_clicked(){
    QMapIterator<QLayout*,QTimer*> it(layout_timer_map);
    QLabel* label;
    double interval;
    while(it.hasNext()){
        it.next();
        interval = qobject_cast<QDoubleSpinBox*>(it.key()->itemAt(1)->widget())->value();
        if(!(it.value()->isActive()))
            if(interval > 0)
                execute_timer(it.value(),it.key());
        if(!interval)
            qobject_cast<QLabel*>(it.key()->itemAt(4)->widget())->setText(QString("Stopped"));
    }
}

void MainWindow::stop_clicked(){
    QMapIterator<QLayout*,QTimer*> it(layout_timer_map);
    while(it.hasNext()){
        it.next();
        it.value()->stop();
    }
}

void MainWindow::quit_clicked(){
    QApplication::quit();
}

MainWindow::~MainWindow(){
    delete ui;
}
