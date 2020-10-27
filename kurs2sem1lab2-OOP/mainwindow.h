#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include<QListWidget>
#include<QListWidgetItem>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
 //   QTimer *timer;
    int minimal=0;
    int minimal_sec=0;
    int minimal_row=0;
    QVector<int> active;
    QVector<int> Cactive;
    QTimer *timer_decrease;
private slots:
    void clock_ends();
    void starttimer(int ms);
    int count_timers();
    void startClock();
    void tim_minimal();
    void tim_update();
    void tim_end(int i);
    void on_pushButton_clicked();

    void on_listWidget_timer_itemDoubleClicked(QListWidgetItem *item);
    void on_pushButton_2_clicked();

    void on_listWidget_timer_itemChanged(QListWidgetItem *item);

    void on_pushButton_3_clicked();

    void on_listWidget_clocks_itemDoubleClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
