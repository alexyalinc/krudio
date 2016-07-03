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
int  countRow=0;//Количество строк в таблице
int  currentRow=0;//Активная строка
int  currentColorNumb;//Текущий цвет иконок
int  currentsizeIcon;//Текущий размер значков
int  currentEditRow=-1;//Редактируемая строчка
int  currentEditId=-1;//id станции которая редактируется
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
    //поворачиваем иконки табов
    QIcon icon = QIcon::fromTheme("media-playback-start",QIcon("/usr/share/krudio/icons/media-playback-start.svg")); // use your method to retrieve the QIcon object
    QImage srcImg(icon.pixmap(22,22).toImage());
    QPoint center = srcImg.rect().center();
    QMatrix matrix;
    matrix.translate(center.x(), center.y());
    matrix.rotate(90);
    QImage dstImg = srcImg.transformed(matrix);
    QPixmap dstPix = QPixmap::fromImage(dstImg);
    ui->tabWidget->setTabIcon(0,QIcon(dstPix));

    icon = QIcon::fromTheme("document-edit",QIcon("/usr/share/krudio/icons/document-edit.svg")); // use your method to retrieve the QIcon object
    QImage srcImg2(icon.pixmap(22,22).toImage());
    center = srcImg2.rect().center();
    dstImg = srcImg2.transformed(matrix);
    dstPix = QPixmap::fromImage(dstImg);
    ui->tabWidget->setTabIcon(1,QIcon(dstPix));

    icon = QIcon::fromTheme("configure",QIcon("/usr/share/krudio/icons/configure.svg")); // use your method to retrieve the QIcon object
    QImage srcImg3(icon.pixmap(22,22).toImage());
    center = srcImg3.rect().center();
    dstImg = srcImg3.transformed(matrix);
    dstPix = QPixmap::fromImage(dstImg);
    ui->tabWidget->setTabIcon(2,QIcon(dstPix));

    //Меняем иконки
    ui->pausePlay->setIcon(QIcon::fromTheme("media-playback-start",QIcon("/usr/share/krudio/icons/media-playback-start.svg")));
    ui->pausePause->setIcon(QIcon::fromTheme("media-playback-pause",QIcon("/usr/share/krudio/icons/media-playback-pause.svg")));
    ui->prevPlay->setIcon(QIcon::fromTheme("media-skip-backward",QIcon("/usr/share/krudio/icons/media-skip-backward.svg")));
    ui->nextPlay->setIcon(QIcon::fromTheme("media-skip-forward",QIcon("/usr/share/krudio/icons/media-skip-forward.svg")));
    ui->nextPlay_2->setIcon(QIcon::fromTheme("search",QIcon("/usr/share/krudio/icons/search.svg")));
    ui->pushButton_2->setIcon(QIcon::fromTheme("list-add",QIcon("/usr/share/krudio/icons/list-add.svg")));
    ui->pushButton_3->setIcon(QIcon::fromTheme("edit-delete",QIcon("/usr/share/krudio/icons/edit-delete.svg")));
    ui->editStation->setIcon(QIcon::fromTheme("document-edit",QIcon("/usr/share/krudio/icons/document-edit.svg")));
    ui->saveStation->setIcon(QIcon::fromTheme("document-save",QIcon("/usr/share/krudio/icons/document-save.svg")));

    ui->pausePause->hide();//скрываем кнопку паузы
    ui->waitMinute->hide();//Скрываем label загрузки буфера
    ceckBUFFtimer = new QTimer();//таймер для буферинга
    QDir(QDir::homePath()).mkdir(".krudio");//Создаем папку в домашнем каталоге
    //Иконка в трее
    trIcon = new QSystemTrayIcon();  //инициализируем объект
    //При клике сворачивать или разворачивать окно
    //connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showHide(QSystemTrayIcon::ActivationReason)));
    connect(trIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(playorpause(QSystemTrayIcon::ActivationReason)));
    //Создаем контекстное меню для иконки в трее, чтобы закрывать программу
    QMenu*   pmnu   = new QMenu("&Menu");
    pmnu->addAction("&Show/Hide", this, SLOT(showHide()));
    pmnu->addAction("&Exit", this, SLOT(closeEV()));
    trIcon->setContextMenu(pmnu);
    //Иконка в трее

    //Подключение к базе
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    fullPath=QDir::homePath()+"/.krudio/krudio.sqlite";
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

void Krudio::playorpause(QSystemTrayIcon::ActivationReason r){
    if (r==QSystemTrayIcon::Trigger){  //если нажато левой кнопкой продолжаем
        currPlayOrNextBack(0);
    }
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
                namesvg="16";
                break;
             case 1:
                namesvg="22";
                break;
             case 2:
                namesvg="24";
                break;
             default:
                namesvg="16";
          }
    path="/usr/share/krudio/icons/";
    switch ( colorNumb )
          {
            case 0://темная тема
                {
                    ui->radioButton_2->setChecked(true);
                    if(iconTrayEv){
                        trIcon->setIcon(QIcon::fromTheme("krudiotray-dark-on"+namesvg,QIcon(path+"krudiotray-dark-on"+namesvg+".svg"))); //устанавливаем иконкудля трея
                    }else{trIcon->setIcon(QIcon::fromTheme("krudiotray-dark-off"+namesvg,QIcon(path+"krudiotray-dark-off"+namesvg+".svg")));} //плеер не играет
                    break;
                }
            case 1://светлая тема
                {
                    ui->radioButton->setChecked(true);
                    if(iconTrayEv){
                        trIcon->setIcon(QIcon::fromTheme("krudiotray-light-on"+namesvg,QIcon(path+"krudiotray-light-on"+namesvg+".svg")));  //устанавливаем иконкудля трея
                    }else{trIcon->setIcon(QIcon::fromTheme("krudiotray-light-off"+namesvg,QIcon(path+"krudiotray-light-off"+namesvg+".svg")));} //плеер не играет
                    break;
                }
          }

    trIcon->show();  //отображаем объект
    setWindowIcon(QIcon::fromTheme("krudio",QIcon(path+"krudio.svg")));//иконка окна
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
            itemRow = new QTableWidgetItem();
            itemRow->setIcon(QIcon::fromTheme("media-playback-start",QIcon("/usr/share/krudio/icons/media-playback-start.svg")));
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
        itemRow = new QTableWidgetItem();
        itemRow->setIcon(QIcon::fromTheme("media-playback-pause",QIcon("/usr/share/krudio/icons/media-playback-pause.svg")));
        ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
        if(blockNumb==1){ceckBUFFtimer->setInterval(5000);}
        else if(blockNumb==2){ceckBUFFtimer->setInterval(10000);}
        else if(blockNumb==0){ceckBUFFtimer->setInterval(50);}
    }
    //Показываем название трека
    if (player->isMetaDataAvailable())
    {
        if(metaDataTitle != player->metaData(QMediaMetaData::Title).toString()){
                      if(player->metaData(QMediaMetaData::Title).toString()!=""){
                          QString str1 =player->metaData(QMediaMetaData::Title).toString();
                          QString str = "notify-send 'Krudio' '"+str1+"'  -t 5000";
                          QByteArray byteArray = str.toUtf8();
                          char* data = byteArray.data();                          
                          ui->label_5->setText(player->metaData(QMediaMetaData::Title).toString().toUtf8());
                          system(data);
                      }else {
                          ui->label_5->setText("Название трека");
                      }
                      metaDataTitle=player->metaData(QMediaMetaData::Title).toString();
          }
    }


}

/*////////////////////////////////////////////Показать/Скрыть в трее//////////////////////////////////////////////*/
void Krudio::showHide() {
        if (!this->isVisible()) {  //если окно было не видимо - отображаем его
            this->show();
        } else {
            this->hide();  //иначе скрываем
        }
}
/*////////////////////////////////////////////Refresh Table//////////////////////////////////////////////*/
void Krudio::refreshTable(){
    currentRow=ui->tableWidget->currentRow();
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
        itemRow = new QTableWidgetItem();
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
        itemRow = new QTableWidgetItem();
        ui->tableWidget->setVerticalHeaderItem(i,itemRow);
    }
    //Стобец на всю ширину таблицы
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    if(curretPlay<=countRow){
        if(playPause){
            itemRow = new QTableWidgetItem();
            itemRow->setIcon(QIcon::fromTheme("media-playback-start",QIcon("/usr/share/krudio/icons/media-playback-start.svg")));
            ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
        }else{
            itemRow = new QTableWidgetItem();
            itemRow->setSizeHint(QSize(24,24));
            ui->tableWidget->setVerticalHeaderItem(curretPlay,itemRow);
        }
        ui->tableWidget->selectRow(curretPlay);
    }

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
    bool newCurret;
    if(countRow!=-1){
    newCurret=false;
    if(curretPlay!=ui->tableWidget->currentRow()){newCurret=true;}
    if(check==3){newCurret=true;check=0;}//Релоад плэй
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
        itemRow = new QTableWidgetItem();
        ui->tableWidget->setVerticalHeaderItem(i,itemRow);
    }
    if(playPause){
        iconTrayEv=true;
    }else{iconTrayEv=false;}
    setcolorIcon(currentColorNumb,false);
    itemRow = new QTableWidgetItem();
    itemRow->setIcon(QIcon::fromTheme("media-playback-start",QIcon("/usr/share/krudio/icons/media-playback-start.svg")));
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
    if(ui->nameStations->text()!="" && ui->urlStations->text()!="") {
        addRowTable(ui->nameStations->text(),ui->urlStations->text());
        ui->nameStations->setText("");
        ui->urlStations->setText("");
        countRow=countRow+1;
        refreshTable();
    }
}
//Удалить станцию
void Krudio::on_pushButton_3_clicked()
{
    if(countRow!=-1){
        delRowTable(ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text().toInt());
        ui->nameStations->setText("");
        ui->urlStations->setText("");
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

void Krudio::on_editStation_released()
{
    currentEditRow=ui->tableWidget->currentRow();
    currentEditId=ui->tableWidget->item(ui->tableWidget->currentRow(),2)->text().toInt();
    ui->nameStations->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),0)->text());
    ui->urlStations->setText(ui->tableWidget->item(ui->tableWidget->currentRow(),1)->text());
    //блокируем кнопки
    ui->editStation->setDisabled(true);
    ui->pushButton_2->setDisabled(true);
    ui->pushButton_3->setDisabled(true);
    ui->saveStation->setDisabled(false);
}

void Krudio::on_saveStation_released()
{
    QString str;
    QSqlQuery a_query;
    bool b;
    //Вставить значения
    QString str_insert = "UPDATE "+tableStationsName+" SET name = '%1', url = '%2' WHERE id = %3;";
    str = str_insert.arg(ui->nameStations->text()).arg(ui->urlStations->text()).arg(currentEditId);
    b = a_query.exec(str);
    if (!b) {qDebug() << "Данные не вставляются";}
    else{
    ui->nameStations->setText("");
    ui->urlStations->setText("");
    currentEditId=-1;
    currentEditRow=-1;
    //разблокируем кнопки
    ui->editStation->setDisabled(false);
    ui->pushButton_2->setDisabled(false);
    ui->pushButton_3->setDisabled(false);
    ui->saveStation->setDisabled(true);
    refreshTable();//Обновляем содержимое таблицы


        if(playPause){
            currPlayOrNextBack(3);
        }
    }
}
