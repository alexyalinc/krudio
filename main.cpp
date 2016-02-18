//
//
//
//Krudo Copyright 2016 Ялинчук Александр MIT
//
//
//
//
#include "krudio.h"
#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QTextCodec* codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QApplication a(argc, argv);
    Krudio w;
    w.setAttribute(Qt::WA_DeleteOnClose);
    w.show();

    return a.exec();
}
