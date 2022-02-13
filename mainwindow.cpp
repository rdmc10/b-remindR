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

#define to_ms(x) x*60000

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(780,600);

    sysTrayIcon=new QSystemTrayIcon();
    //TODO:change icon
    this->sysTrayIcon->setIcon(QIcon("./icon.png"));

    //Generate one timer by default
    plus_clicked();

    QObject::connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::plus_clicked);
    QObject::connect(ui->pushButton_5,&QPushButton::clicked,this,&MainWindow::quit_clicked);
    QObject::connect(ui->pushButton_2,&QPushButton::clicked,this,&MainWindow::start_clicked);
    QObject::connect(ui->pushButton_3,&QPushButton::clicked,this,&MainWindow::stop_clicked);
}

void MainWindow::plus_clicked(){
    QVBoxLayout* layout=ui->verticalLayout;
    QHBoxLayout* new_layout = new QHBoxLayout();
    new_layout->setSpacing(20);

    QLineEdit* line_edit = new QLineEdit();
    line_edit->setText("HEEY");
    new_layout->addWidget(line_edit);

    QSpinBox* spin_box = new QSpinBox();
    spin_box->setRange(1,9999);
    new_layout->addWidget(spin_box);

    QCheckBox* check_box = new QCheckBox();
    check_box->setText(QString(""));
    check_box->setChecked(0);
    new_layout->addWidget(check_box);


    QPushButton* new_close_button = new QPushButton();
    new_close_button->setText(QString("    -    "));
    new_layout->addWidget(new_close_button);

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

void MainWindow::execute_timer(QTimer* timer,QString message,int interval,bool looping){
    connect(timer, &QTimer::timeout, this, [=]() {
        //TODO: change icon
        this->sysTrayIcon->showMessage(QString("Reminder!"), message,
                                        QIcon("./icon.png"),
                                        10000);
        if(looping)
            timer->start(to_ms(interval));
        else{
            timer->stop();
            //TODO: do more memory checking
            delete timer;
        }
    });
    timer->start(to_ms(interval));
}

void MainWindow::start_clicked(){
    int interval;
    QString message;
    bool looping;
    for(auto it:layout_vec){
        QLineEdit* line_edit = qobject_cast<QLineEdit*>(it->itemAt(0)->widget());
        QSpinBox* spin_box = qobject_cast<QSpinBox*>(it->itemAt(1)->widget());
        QCheckBox* check_box = qobject_cast<QCheckBox*>(it->itemAt(2)->widget());
        QTimer* timer = layout_timer_map.value(it);

        looping = check_box->isChecked();
        message = line_edit->text();
        interval = spin_box->value();
        execute_timer(timer,message,interval,looping);
    }
    this->sysTrayIcon->show();
}

void MainWindow::stop_clicked(){
    for(auto it:layout_timer_map)
        it->stop();
}

void MainWindow::quit_clicked(){
    QApplication::quit();
}

MainWindow::~MainWindow(){
    delete ui;
}
