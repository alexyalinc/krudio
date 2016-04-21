//
//
//
//Krudo Copyright 2016 Ялинчук Александр MIT
//
//
//
//
#ifndef KRUDIO_H
#define KRUDIO_H

#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <QtSql>
#include <QIcon>
#include <QTableWidgetItem>
#include <QMediaPlayer>
#include <QSystemTrayIcon>
#include <QTimer>
#include <QThread>
#include <QMenu>
#include <QEvent>
#include <QCloseEvent>

namespace Ui {
class Krudio;
}

class Krudio : public QMainWindow
{
    Q_OBJECT

public:
    explicit Krudio(QWidget *parent = 0);
    ~Krudio();

private slots:
    void closeEV();

    void closeEvent(QCloseEvent *cb);

    void setsizeIcon(int size,bool save);

    void repeater();

    void setcolorIcon(int colorNumb,bool save);

    void showHide(QSystemTrayIcon::ActivationReason r);

    void currPlayOrNextBack(int check);

    void delRowTable(int id);

    void addRowTable(QString name, QString url);

    void on_pausePlay_clicked();

    void on_prevPlay_clicked();

    void on_nextPlay_clicked();

    void on_pausePause_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_tableWidget_clicked(const QModelIndex &index);

    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_radioButton_released();

    void on_radioButton_2_released();

    void on_volumeChange_valueChanged(int value);

    void on_radioButton_3_released();

    void on_radioButton_4_released();

private:
    QTimer *ceckBUFFtimer;
    void refreshTable();
    Ui::Krudio *ui;
};

#endif // KRUDIO_H
