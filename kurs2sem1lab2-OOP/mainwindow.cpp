#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QtMultimedia/QSound>
#include<QtMultimedia/QMediaPlayer>
#include <QWidget>
#include<QSound>
#include<QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::tim_end(int i){
    if (!ui->checkBox->isChecked()){
        if (active[i]){
    QMessageBox ent;
    ent.setText("Timer ends");
 //   QMediaPlayer sound(this);
//    sound.setMedia(QUrl::fromLocalFile("/"+ ui->comboBox->currentText() +".mp3"));
//    sound.setVolume(20);
//    sound.play();

    QSound sound(QDir::currentPath() + "/"+ ui->comboBox->currentText() +".mp3");
    sound.play();
    ent.exec();
        }
    }
        active[i]=0;

//    QMediaPlayer player;
//    player.setMedia(QUrl::fromLocalFile("/romulan_alarm.wav"));
 //   player.setVolume(10);
//    player.play();
}
int MainWindow::count_timers(){
    int k=0;
    for (int i=0;i<ui->listWidget_timer->count();i++){
        QTime time;
        QString str;
        str=ui->listWidget_timer->item(i)->text();
        qDebug()<<str;
        time= QTime::fromString(str,"hh:mm:ss");
        if ((time.hour()*3600+time.minute()*60+time.second())==0)
        k++;
    }

    return k;
}
void MainWindow::tim_minimal(){
    QTime minimal_time(23,59,59,0);
    QString str;
        int sec=0;
    QTime time;
    for (int i=0;i<ui->listWidget_timer->count();i++){
       str=ui->listWidget_timer->item(i)->text();
       time= QTime::fromString(str,"hh:mm:ss");
       if (minimal_time.hour()>=time.hour()){
           if (minimal_time.minute()>=time.minute()){
               if (minimal_time.second()>time.second()&& time.second()!=0){
                   sec=0;
           minimal_time=time;
 //          qDebug() <<"AAO "<<minimal_time.second();
           sec+=minimal_time.hour()*3600+minimal_time.minute()*60+minimal_time.second();
           minimal=100/sec;
           minimal_sec=sec;
           minimal_row=i;
           }
       }
       }
       }
}
void MainWindow::tim_update(){
    QTime time;
    QString str;
    int k=0;
    for (int i=0;i<ui->listWidget_timer->count();i++){
       str=ui->listWidget_timer->item(i)->text();
  //     qDebug()<<str;
       time= QTime::fromString(str,"hh:mm:ss");
       if ((time.hour()*3600+time.minute()*60+time.second())!=0 && active[i])
       time = time.addSecs(-1);
       else if ((time.hour()*3600+time.minute()*60+time.second())==0){
           k++;
           tim_end(i);
       }
       if (i==minimal_row){
          ui->progressBar->setValue((minimal_sec-time.hour()*3600-time.minute()*60-time.second())*minimal);
          if (time.second()==0) ui->progressBar->setValue(100);
       }
       ui->listWidget_timer->item(i)->setText(time.toString());
       }
    if (k==ui->listWidget_timer->count()) timer_decrease->stop();
    ui->label->setText("Number of timers: " + QString::number(ui->listWidget_timer->count()-k,10));
    ui->label_2->setText("Fastest timer №" + QString::number(minimal_row+1,10));
}
void MainWindow::starttimer(int ms){
 /*   QTimer *timer=new QTimer(this);
    QTimer *timer_decrease=new QTimer(this);
    ui->listWidget_timer->addItem(ui->time_current->time().toString());
    connect(timer_decrease,SIGNAL(timeout()),this,SLOT(tim_update()));
    connect(timer,SIGNAL(timeout()),this,SLOT(tim_end()));
    timer_decrease->start(1000);
    timer->setSingleShot(1);
    timer->start(ms);*/
//    QTimer *timer=new QTimer(this);
    ms=0;
    if (ui->listWidget_timer->count()==0 || count_timers()==ui->listWidget_timer->count()){
    timer_decrease=new QTimer(this);
    connect(timer_decrease,SIGNAL(timeout()),this,SLOT(tim_update()));
    timer_decrease->start(1000);
    }
    ui->listWidget_timer->addItem(ui->time_current->time().toString());
    tim_minimal();
    active.push_back(0);
//    connect(timer,SIGNAL(timeout()),this,SLOT(tim_end()));
//    timer->setSingleShot(1);
//    timer->start(ms);
}
void MainWindow::clock_ends(){
        int activ=0;
    for (int i=0;i<ui->listWidget_clocks->count();i++){
        QString time_s;
        QTime time;
        time_s=ui->listWidget_clocks->item(i)->text();
        time=QTime::fromString(time_s,"hh:mm:ss");
        if (QTime::currentTime().hour()==time.hour()){
            if (QTime::currentTime().minute()==time.minute()){
                if (QTime::currentTime().second()==time.second()){
                    activ=Cactive[i];
                    Cactive[i]=0;
                    break;
                }
            }
        }
    }
    if (activ==1){
    if (!ui->checkBox->isChecked()){
    QMessageBox ent2;
    QSound sound(QDir::currentPath() + "/"+ ui->comboBox->currentText() +".mp3");
    sound.play();
    ent2.setText("Wake up");
//    QApplication::beep();
    ent2.exec();
    }
    }
}
void MainWindow::startClock(){
    QTime time;
    QTimer *clock=new QTimer(this);
    connect(clock, SIGNAL(timeout()),this,SLOT(clock_ends()));
    ui->listWidget_clocks->addItem(ui->time_current->time().toString());
    clock->setSingleShot(1);
    int cur_time=time.currentTime().hour()*3600 + time.currentTime().minute()*60 + time.currentTime().second();
    clock->start(abs(ui->time_current->time().hour()*3600+ui->time_current->time().minute()*60+ui->time_current->time().second()-cur_time)*1000);
    Cactive.push_back(0);
    Cactive[ui->listWidget_clocks->count()-1]=1;
}

void MainWindow::on_pushButton_clicked()
{

  //  QTime time(ui->time_current->time());

//    if (time.hour()!=0 && time.minute()!=0){
    if(ui->time_current->time().toString()!="00:00:00" ) {
  //  QTime tim = ui->timeEdit->time();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                 "Choose action",
                                 "Press Yes to add timer, No to add clock",
                                 QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);
   if (reply == QMessageBox::Yes) {
                starttimer((ui->time_current->time().hour()*3600+ui->time_current->time().minute()*60+ui->time_current->time().second())*1000);
               } else if (reply == QMessageBox::No) {
                    startClock();
               }
   else {
       // do nothing
    }
    }
    else {
        QMessageBox ent;
        ent.setText("You can't interract with 0:00 time");
        ent.exec();
    }


}

void MainWindow::on_listWidget_timer_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                 "Choose action",
                                 "Press Yes delete timer, No to return",
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes) {
               if (active[ui->listWidget_timer->currentRow()]){
                   active[ui->listWidget_timer->currentRow()]=0;
                   for (int i=item->listWidget()->currentRow();i<ui->listWidget_timer->count()-1;i++){
                       active[i]=active[i+1];
                   }
                    ui->listWidget_timer->takeItem(item->listWidget()->currentRow());
               }
               else{
                for (int i=item->listWidget()->currentRow();i<ui->listWidget_timer->count()-1;i++){
                    active[i]=active[i+1];
                }
                active[ui->listWidget_timer->count()-1]=0;
                ui->listWidget_timer->takeItem(item->listWidget()->currentRow());
               }
               } else if (reply == QMessageBox::No) {
                    // if no then do nothing, don't write anything here
               }
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->listWidget_timer->item(ui->listWidget_timer->currentRow())->text()!="00:00:00")
    active[ui->listWidget_timer->currentRow()]=1;
}

void MainWindow::on_listWidget_timer_itemChanged(QListWidgetItem *item)
{
    if (ui->listWidget_timer->count()==0) timer_decrease->stop();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (ui->listWidget_timer->item(ui->listWidget_timer->currentRow())->text()!="00:00:00")
    active[ui->listWidget_timer->currentRow()]=0;
}

void MainWindow::on_listWidget_clocks_itemDoubleClicked(QListWidgetItem *item)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                                 "Choose action",
                                 "Press Yes delete Clock, No to return",
                                 QMessageBox::Yes|QMessageBox::No);
   if (reply == QMessageBox::Yes) {
               if (Cactive[ui->listWidget_clocks->currentRow()]){
                   Cactive[ui->listWidget_clocks->currentRow()]=0;
                   for (int i=item->listWidget()->currentRow();i<ui->listWidget_clocks->count()-1;i++){
                       Cactive[i]=Cactive[i+1];
                   }
                   ui->listWidget_clocks->takeItem(item->listWidget()->currentRow());
               }
               } else if (reply == QMessageBox::No) {
                    // if no then do nothing, don't write anything here
               }
}
