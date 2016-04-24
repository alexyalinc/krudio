//
//
//
//Krudo Copyright 2016 Ялинчук Александр MIT
//
//
//
//
#include "krudio.h"
#include "ui_krudio.h"
#include "time.h"

QString baseName = "krudio.sqlite";//Имя базы
QString tableStationsName = "stations";//Имя таблицы со станциями
QString tableSettingName = "settings";//Имя таблицы с настройками
QString metaDataTitle="Название трека";
int curretPlay = 0;//Номер строки, котороя сейчас воспроизводится
QMediaPlayer*player;//Плеер
QTableWidgetItem *itemRow;//Headers
QSystemTrayIcon *trIcon;//Иконка в трее
QString fullPath;//Полный путь до приложения

bool firstPlay=true;//Первое воспроизведение или нет
bool playPause=false;//Воспроизводится или нет
bool iconTrayEv=false;//Иконка в трее не активная
bool closeEv=false;
int  countRow;//Количество строк в таблице
int  currentColorNumb;//Текущий цвет иконок
int  currentsizeIcon;//Текущий размер значков
int  blockNumb=0;
int  slidersize=0;

void Krudio::closeEvent( QCloseEvent *cb)
{
    if(!closeEv){
        cb->ignore();
        if (!this->isVisible()) {  //если окно было не видимо - отображаем его
            this->show();
        } else {
            this->hide();  //иначе скрываем
        }
    }else{
        cb->accept();
    }
    return;
}
void Krudio::closeEV(){
    closeEv=true;
    close();
}

/*////////////////////////////////////////////Start program//////////////////////////////////////////////*/
/*////////////////////////////////////////////Start program//////////////////////////////////////////////*/
/*////////////////////////////////////////////Start program//////////////////////////////////////////////*/
Krudio::Krudio(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Krudio)
{
    ui->setupUi(this);
    ui->pausePause->hide();//скрываем кнопку паузы
    ui->waitMinute->hide();//Скрываем label загрузки буфера
    ceckBUFFtimer = new QTimer();//таймер для буферинга
    QDir(QDir::homePath()).mkdir(".krudio");
    //Иконка в трее
    trIcon = new QSystemTrayIcon();  //инициализируем объект
    trIcon->setIcon(QIcon::fromTheme("krudio",QIcon(":/src/icons/48x48/apps/krudio.svg")));  //устанавливаем иконку
    trIcon->show();  //отображаем объект
    //При клике сворачивать или разворачивать окно
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));
    //Создаем контекстное меню для иконки в трее, чтобы закрывать программу
    QMenu*   pmnu   = new QMenu("&Menu");
    pmnu->addAction("&Exit", this, SLOT(closeEV()));
    trIcon->setContextMenu(pmnu);
    //Иконка в трее

    //Подключение к базе
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    fullPath=QDir::homePath()+"/.krudio/"+baseName;
    dbase.setDatabaseName(fullPath);
    if (!dbase.open()) {
        qDebug() << "Что-то пошло не так!";
        return;
    }
    //Подключение к базе

    QSqlQuery a_query;

    //Создаем таблицу со станциями
    QString str =
            "CREATE TABLE "+tableStationsName+" (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, name TEXT, url TEXT);";
    bool b = a_query.exec(str);
    if (!b) {qDebug() << "Таблица со станциями уже существует.";}
    //Создаем таблицу со станциями

    //Создаем таблицу с настройками
    str = "CREATE TABLE "+tableSettingName+" (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, setting TEXT, value INTEGER);";
    b = a_query.exec(str);
    if (!b) {qDebug() << "Таблица с настройками уже существует.";}
    //Создаем таблицу с настройками

    //Проверяем какие настройки включены
    if (!a_query.exec("SELECT * FROM "+tableSettingName)) {qDebug() << "Не получается прочитать информацию с таблицы.";return;}
    QSqlRecord rec = a_query.record();//Записываем результ с выборки
    //Создаем переменные к которым будем присваивать значения из таблицы
    QString setting="",
            id="";
    int     value,
            colorIcons=-1,// -1 Настроек нет
            sizeIcon=-1;// -1 Настроек нет
    while (a_query.next()) {
        id = a_query.value(rec.indexOf("id")).toString();
        setting = a_query.value(rec.indexOf("setting")).toString();
        value = a_query.value(rec.indexOf("value")).toInt();
        //Если есть настройки цвета иконок, то добавляем в переменную значение
        if(setting=="color"){
            colorIcons=value;
        }
        //Если есть настройки размера иконок, то добавляем в переменную значение
        if(setting=="iconsize"){
            sizeIcon=value;
        }
    }
    //Сохраняем настройки если их нет
    QString str_insert;
    if(sizeIcon==-1){
        str_insert = "INSERT INTO "+tableSettingName+" (id, setting, value) VALUES (NULL, '%1', %2);";
        str = str_insert.arg("iconsize").arg(0);//32
        b = a_query.exec(str);
        if (!b) {qDebug() << "Данные не вставляются";}
        currentsizeIcon=0;
    }
    else{
        setsizeIcon(sizeIcon,false);
        currentsizeIcon=sizeIcon;
    }
    if(colorIcons==-1){
        //Добавляем настройку цвета по умолчанию
        str_insert = "INSERT INTO "+tableSettingName+" (id, setting, value) VALUES (NULL, '%1', %2);";
        str = str_insert.arg("color").arg(0);
        b = a_query.exec(str);
        if (!b) {qDebug() << "Данные не вставляются";}
        setcolorIcon(0,false);
        currentColorNumb=0;
    }else{
        setcolorIcon(colorIcons,false);
        currentColorNumb=colorIcons;
    }

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//Включаем запрет на редактирование таблицы
    refreshTable();//Обновляем содержимое таблицы
}

Krudio::~Krudio()
{
    delete ui;
}

/*/////////////////////////////////ЦВЕТ ИКОНОК///////////////////////////////////////*/
void Krudio::setcolorIcon(int colorNumb,bool save){
    currentColorNumb=colorNumb;
    QString path;
    QString namesvg;
    switch ( currentsizeIcon )
          {
             case 0:
                path="16x16";
                namesvg="16";
                break;
             case 1:
                path="22x22";
                namesvg="22";
                break;
             case 2:
                path="24x24";
                namesvg="24";
                break;
             default:
                path="16x16";
                namesvg="16";
          }
    path=":/src/icons/"+path+"/status/";

    switch ( colorNumb )
          {
            case 0://темная тема
                {
                    ui->radioButton_2->setChecked(true);
                    if(iconTrayEv){
                        trIcon->setIcon(QIcon::fromTheme("krudio-dark-on-tray"+namesvg,QIcon(path+"krudio-dark-on-tray"+namesvg+".svg")));  //устанавливаем иконкудля трея
                    }else{trIcon->setIcon(QIcon::fromTheme("krudio-dark-off-tray"+namesvg,QIcon(path+"krudio-dark-off-tray"+namesvg+".svg")));} //плеер не играет
                    break;
                }
            case 1://светлая тема
                {
                    ui->radioButton->setChecked(true);
                    if(iconTrayEv){
                        trIcon->setIcon(QIcon::fromTheme("krudio-light-on-tray"+namesvg,QIcon(path+"krudio-light-on-tray"+namesvg+".svg")));  //устанавливаем иконкудля трея
                    }else{trIcon->setIcon(QIcon::fromTheme("krudio-light-off-tray"+namesvg,QIcon(path+"krudio-light-off-tray"+namesvg+".svg")));} //плеер не играет
                    break;
                }
          }

    setWindowIcon(QIcon::fromTheme("krudio",QIcon(":/src/icons/48x48/apps/krudio.svg")));//иконка окна
    if(save){//сохраняем изменения в базу
        QString str;
        QSqlQuery a_query;
        bool b;
        //Вставить значения
        QString str_insert = "UPDATE "+tableSettingName+" SET value = %1 WHERE setting ='%2';";
        str = str_insert.arg(colorNumb).arg("color");
        b = a_query.exec(str);
        if (!b) {qDebug() << "Данные не сохнаняются";}
    }
}
/*/////////////////////////////////РАЗМЕР ИКОНОК В ТРЕЕ///////////////////////////////////////*/
void Krudio::setsizeIcon(int size,bool save){
    currentsizeIcon=size;
    switch (size)
          {
             case 0:
                ui->horizontalSlider->setValue(0);
                break;
             case 1:
                ui->horizontalSlider->setValue(50);
                break;
             case 2:
                ui->horizontalSlider->setValue(99);
                break;
             default:
                ui->horizontalSlider->setValue(0);
          }

    if(save){
        QString str;
        QSqlQuery a_query;
        bool b;
        //Вставить значения
        QString str_insert = "UPDATE "+tableSettingName+" SET value = %1 WHERE setting ='%2';";
        str = str_insert.arg(size).arg("iconsize");
        b = a_query.exec(str);
        if (!b) {qDebug() << "Данные не сохнаняются";}
    }
}

/*/////////////////////////////////////BUFFERING///////////////////////////////*/
bool chekBUFF=true;
bool blockPlay=false;
bool blockPause=false;
void Krudio::repeater(){

    if(player->mediaStatus()==QMediaPlayer::BufferedMedia || player->mediaStatus()==QMediaPlayer::LoadedMedia){
        if(chekBUFF){
            if(playPause){
                player->play();
            }
            itemRow = new QTableWidgetItem(">");
            ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
            ui->waitMinute->hide();
            ui->volumeChange->show();
            chekBUFF=false;
            if(blockNumb==2){blockNumb=0;}else{blockNumb++;}
        }
    }else{
        chekBUFF=true;
        ui->waitMinute->show();
        ui->volumeChange->hide();
        player->pause();
        itemRow = new QTableWidgetItem("~");
        ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
        if(blockNumb==1){ceckBUFFtimer->setInterval(5000);}
        else if(blockNumb==2){ceckBUFFtimer->setInterval(10000);}
        else if(blockNumb==0){ceckBUFFtimer->setInterval(50);}
    }
    //Показываем название трека
    if (player->isMetaDataAvailable())
    {
        if(metaDataTitle != player->metaData(QMediaMetaData::Title).toString()){
                      ui->label_5->setText(player->metaData(QMediaMetaData::Title).toString());
                      if(player->metaData(QMediaMetaData::Title).toString()!=""){
                          QString str1 =player->metaData(QMediaMetaData::Title).toString();
                          QString str = "notify-send 'Сейчас играет' '"+str1+"'  -t 5000";
                          QByteArray byteArray = str.toUtf8();
                          char* data = byteArray.data();
                          system(data);
                      }else {
                          ui->label_5->setText("Название трека");
                      }
                      metaDataTitle=player->metaData(QMediaMetaData::Title).toString();
          }
    }


}

/*////////////////////////////////////////////Показать/Скрыть в трее//////////////////////////////////////////////*/
void Krudio::showHide(QSystemTrayIcon::ActivationReason r) {
    if (r==QSystemTrayIcon::Trigger){  //если нажато левой кнопкой продолжаем
        if (!this->isVisible()) {  //если окно было не видимо - отображаем его
            this->show();
        } else {
            this->hide();  //иначе скрываем
        }
    }
}
/*////////////////////////////////////////////Refresh Table//////////////////////////////////////////////*/
void Krudio::refreshTable(){

    do{
        ui->tableWidget->removeRow(0);
        ui->tableWidget->removeColumn(0);
    }while (ui->tableWidget->rowCount() > 0);

    QSqlQuery a_query;
    if (!a_query.exec("SELECT * FROM "+tableStationsName)) {
        qDebug() << "Не получается прочитать информацию с таблицы.";
        return;
    }
    QSqlRecord rec = a_query.record();//Записываем результ с выборки
    //Создаем переменные к которым будем присваивать значения из таблицы
    QString name = "",
            url = "",
            id = "";
    //Создаем столбецы в представлении
    ui->tableWidget->insertColumn(0);
    itemRow = new QTableWidgetItem("");
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setHorizontalHeaderItem(0,itemRow);
    ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
    ui->tableWidget->insertColumn(1);
    ui->tableWidget->insertColumn(2);
    ui->tableWidget->hideColumn(1);
    ui->tableWidget->hideColumn(2);
    int indexStr=0;
    while (a_query.next()) {
        id = a_query.value(rec.indexOf("id")).toString();
        name = a_query.value(rec.indexOf("name")).toString();
        url = a_query.value(rec.indexOf("url")).toString();
        ui->tableWidget->insertRow(indexStr);
        itemRow = new QTableWidgetItem("-");
        ui->tableWidget->setVerticalHeaderItem(indexStr,itemRow);
        itemRow = new QTableWidgetItem(name);
        ui->tableWidget->setItem(indexStr,0,itemRow);
        itemRow = new QTableWidgetItem(url);
        ui->tableWidget->setItem(indexStr,1,itemRow);
        itemRow = new QTableWidgetItem(id);
        ui->tableWidget->setItem(indexStr,2,itemRow);
        indexStr++;
    }

    countRow=ui->tableWidget->rowCount()-1;
    //Визуальная часть текущего трека)
    for(int i=0;i<=countRow;i++){
        itemRow = new QTableWidgetItem("-");
        ui->tableWidget->setVerticalHeaderItem(i,itemRow);
    }
    curretPlay=0;
    if(playPause){
        itemRow = new QTableWidgetItem(">");
        ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
    }
    ui->tableWidget->selectRow(curretPlay);
    if(playPause){
        currPlayOrNextBack(0);
    }

    //Стобец на всю ширину таблицы
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

}
/*////////////////////////////////////////////DelRow//////////////////////////////////////////////*/
void Krudio::delRowTable(int id){
    QString str;
    QSqlQuery a_query;
    bool b;
    //Удалить строку
    QString str_insert = "DELETE FROM "+tableStationsName+" WHERE id='%1';";
    str = str_insert.arg(id);
    b = a_query.exec(str);
    if (!b) {qDebug() << "Данные не удаляются.";}
}

/*////////////////////////////////////////////AddRow//////////////////////////////////////////////*/
void Krudio::addRowTable(QString name, QString url){
    QString str;
    QSqlQuery a_query;
    bool b;
    //Вставить значения
    QString str_insert = "INSERT INTO "+tableStationsName+" (id, name, url) VALUES (NULL, '%1', '%2');";
    str = str_insert.arg(name).arg(url);
    b = a_query.exec(str);
    if (!b) {qDebug() << "Данные не вставляются";}
}
/*////////////////////////////////////////////Play//////////////////////////////////////////////*/
void Krudio::currPlayOrNextBack(int check){
    if(countRow!=-1){
    bool newCurret=false;
    if(curretPlay!=ui->tableWidget->currentRow()){newCurret=true;}
    curretPlay=ui->tableWidget->currentRow();
    bool PP=false;
    QUrl urlcurr;
    if(firstPlay){
        player=new QMediaPlayer(this, QMediaPlayer::StreamPlayback);
        player->setVolume(50);
        urlcurr=ui->tableWidget->item(curretPlay,1)->text();
        player->setMedia(QUrl(urlcurr));
        firstPlay=false;
        ceckBUFFtimer->setInterval( 50 );
        ceckBUFFtimer->start();
        connect(ceckBUFFtimer,SIGNAL(timeout()),SLOT(repeater())) ;
    }
    if(check==0){//Play/Pause
        blockNumb=0;
        PP=true;
    }
    if(check==1){//Next
        curretPlay++;
        if(curretPlay>countRow){curretPlay=0;}
        blockNumb=0;
        ceckBUFFtimer->setInterval(50);
    }
    if(check==2){//Back
        curretPlay--;
        if(curretPlay<0){curretPlay=countRow;}
        blockNumb=0;
        ceckBUFFtimer->setInterval(50);
    }
    if(PP){
        if(newCurret){
            urlcurr=ui->tableWidget->item(curretPlay,1)->text();
            player->setMedia(urlcurr);
            playPause=false;
        }
        //Плей или пауза
        if(!playPause){
            player->play();
            playPause=true;
            ui->pausePlay->hide();
            ui->pausePause->show();
            ui->pausePause->setFocus();
        }
        else{
            player->pause();
            playPause=false;
            ui->pausePlay->show();
            ui->pausePlay->setFocus();
            ui->pausePause->hide();

        }
    }
    else{
        urlcurr=ui->tableWidget->item(curretPlay,1)->text();
        player->setMedia(urlcurr);
        player->play();
        playPause=true;
        ui->pausePlay->hide();
        ui->pausePause->show();
        ui->pausePause->setFocus();
    }
    //Визуальная часть текущего трека)
    for(int i=0;i<=countRow;i++){
        itemRow = new QTableWidgetItem("-");
        ui->tableWidget->setVerticalHeaderItem(i,itemRow);
    }
    if(playPause){
        iconTrayEv=true;
    }else{iconTrayEv=false;}
    setcolorIcon(currentColorNumb,false);
    itemRow = new QTableWidgetItem(">");
    ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
    ui->tableWidget->selectRow(curretPlay);
    }
}

/*////////////////////////////////////////////Button Play//////////////////////////////////////////////*/
void Krudio::on_pausePlay_clicked()
{
    currPlayOrNextBack(0);
}

void Krudio::on_prevPlay_clicked()
{
    currPlayOrNextBack(2);
}

void Krudio::on_nextPlay_clicked()
{
    currPlayOrNextBack(1);
}

void Krudio::on_pausePause_clicked()
{
    currPlayOrNextBack(0);
}
//Добавить станцию
void Krudio::on_pushButton_2_clicked()
{
    addRowTable(ui->nameStations->text(),ui->urlStations->text());
    refreshTable();
}
//Удалить станцию
void Krudio::on_pushButton_3_clicked()
{
    if(countRow!=-1){
        delRowTable(ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text().toInt());
        refreshTable();
    }
}

void Krudio::on_tableWidget_clicked(const QModelIndex &index)
{
    if(curretPlay==index.row()){
        if(playPause){
            ui->pausePause->show();
            ui->pausePause->setFocus();
            ui->pausePlay->hide();
        }else{
            ui->pausePlay->show();
            ui->pausePlay->setFocus();
            ui->pausePause->hide();
        }
    }else{
        ui->pausePlay->show();
        ui->pausePlay->setFocus();
        ui->pausePause->hide();
    }
}

void Krudio::on_tableWidget_doubleClicked(const QModelIndex &index)
{

    blockNumb=0;
    if(blockNumb!=0){qDebug () << index;}
    ceckBUFFtimer->setInterval(50);
    currPlayOrNextBack(0);
}

void Krudio::on_radioButton_released()
{
    setcolorIcon(1,true);
}

void Krudio::on_radioButton_2_released()
{
    setcolorIcon(0,true);
}

void Krudio::on_volumeChange_valueChanged(int value)
{
    if(!firstPlay){
        player->setVolume(value);
    }
}

void Krudio::on_horizontalSlider_valueChanged(int value)
{
    if(value <= 25) {slidersize=0;}
    if(value <= 75 && value >= 25) {slidersize=1;}
    if(value <= 99 && value >= 75) {slidersize=2;}
    switch (slidersize)
          {
             case 0:
                ui->horizontalSlider->setValue(0);
                break;
             case 1:
                ui->horizontalSlider->setValue(50);
                break;
             case 2:
                ui->horizontalSlider->setValue(99);
                break;
             default:
                ui->horizontalSlider->setValue(0);
          }
    if(slidersize != currentsizeIcon) {
        setsizeIcon(slidersize,true);
        setcolorIcon(currentColorNumb,true);
    }
}


void Krudio::on_nextPlay_2_clicked()
{
    if(metaDataTitle != "Название трека"){
        QString link = "https://www.google.ru/search?q="+metaDataTitle;
        QDesktopServices::openUrl(QUrl(link));
    }
}
