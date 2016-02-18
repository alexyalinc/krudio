/********************************************************************************
** Form generated from reading UI file 'krudio.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KRUDIO_H
#define UI_KRUDIO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Krudio
{
public:
    QAction *action;
    QWidget *centralWidget;
    QTableWidget *tableWidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *prevPlay;
    QPushButton *pausePlay;
    QPushButton *nextPlay;
    QPushButton *pausePause;
    QLabel *waitMinute;
    QSlider *volumeChange;
    QWidget *tab_2;
    QLineEdit *nameStations;
    QLabel *label;
    QLineEdit *urlStations;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *tab_4;
    QLabel *label_3;
    QLabel *label_4;
    QGroupBox *groupBox;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_3;
    QGroupBox *groupBox_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;

    void setupUi(QMainWindow *Krudio)
    {
        if (Krudio->objectName().isEmpty())
            Krudio->setObjectName(QStringLiteral("Krudio"));
        Krudio->resize(250, 342);
        Krudio->setMinimumSize(QSize(250, 342));
        Krudio->setMaximumSize(QSize(250, 342));
        QIcon icon(QIcon::fromTheme(QStringLiteral("radio")));
        Krudio->setWindowIcon(icon);
        Krudio->setTabShape(QTabWidget::Rounded);
        action = new QAction(Krudio);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(Krudio);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 250, 192));
        tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setEnabled(true);
        tabWidget->setGeometry(QRect(0, 192, 250, 150));
        tabWidget->setMouseTracking(false);
        tabWidget->setAcceptDrops(false);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 16));
        tabWidget->setElideMode(Qt::ElideNone);
        tabWidget->setUsesScrollButtons(false);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        tabWidget->setTabBarAutoHide(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        prevPlay = new QPushButton(tab);
        prevPlay->setObjectName(QStringLiteral("prevPlay"));
        prevPlay->setGeometry(QRect(2, 60, 41, 29));
        QIcon icon1;
        QString iconThemeName = QStringLiteral("media-skip-backward");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        prevPlay->setIcon(icon1);
        pausePlay = new QPushButton(tab);
        pausePlay->setObjectName(QStringLiteral("pausePlay"));
        pausePlay->setGeometry(QRect(65, 43, 80, 60));
        QIcon icon2;
        iconThemeName = QStringLiteral("media-playback-start");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        pausePlay->setIcon(icon2);
        pausePlay->setIconSize(QSize(36, 36));
        nextPlay = new QPushButton(tab);
        nextPlay->setObjectName(QStringLiteral("nextPlay"));
        nextPlay->setGeometry(QRect(170, 60, 40, 29));
        QIcon icon3;
        iconThemeName = QStringLiteral("media-skip-forward");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        nextPlay->setIcon(icon3);
        pausePause = new QPushButton(tab);
        pausePause->setObjectName(QStringLiteral("pausePause"));
        pausePause->setGeometry(QRect(65, 43, 80, 60));
        QIcon icon4;
        iconThemeName = QStringLiteral("media-playback-pause");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        pausePause->setIcon(icon4);
        pausePause->setIconSize(QSize(36, 36));
        waitMinute = new QLabel(tab);
        waitMinute->setObjectName(QStringLiteral("waitMinute"));
        waitMinute->setGeometry(QRect(40, 10, 131, 20));
        volumeChange = new QSlider(tab);
        volumeChange->setObjectName(QStringLiteral("volumeChange"));
        volumeChange->setGeometry(QRect(19, 120, 181, 20));
        volumeChange->setValue(50);
        volumeChange->setOrientation(Qt::Horizontal);
        QIcon icon5;
        iconThemeName = QStringLiteral("go-next");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon5 = QIcon::fromTheme(iconThemeName);
        } else {
            icon5.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        tabWidget->addTab(tab, icon5, QString());
        pausePause->raise();
        prevPlay->raise();
        pausePlay->raise();
        nextPlay->raise();
        waitMinute->raise();
        volumeChange->raise();
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        nameStations = new QLineEdit(tab_2);
        nameStations->setObjectName(QStringLiteral("nameStations"));
        nameStations->setGeometry(QRect(10, 30, 191, 29));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 101, 17));
        urlStations = new QLineEdit(tab_2);
        urlStations->setObjectName(QStringLiteral("urlStations"));
        urlStations->setGeometry(QRect(10, 80, 191, 29));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 61, 55, 17));
        pushButton_2 = new QPushButton(tab_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 115, 85, 29));
        QIcon icon6;
        iconThemeName = QStringLiteral("dialog-ok-apply");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon6 = QIcon::fromTheme(iconThemeName);
        } else {
            icon6.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_2->setIcon(icon6);
        pushButton_2->setIconSize(QSize(24, 24));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(117, 115, 85, 29));
        QIcon icon7;
        iconThemeName = QStringLiteral("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon7 = QIcon::fromTheme(iconThemeName);
        } else {
            icon7.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_3->setIcon(icon7);
        QIcon icon8;
        iconThemeName = QStringLiteral("document-edit");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon8 = QIcon::fromTheme(iconThemeName);
        } else {
            icon8.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        tabWidget->addTab(tab_2, icon8, QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QStringLiteral(""));
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        label_3 = new QLabel(tab_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 30, 81, 17));
        label_4 = new QLabel(tab_4);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(110, 30, 91, 17));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(110, 50, 71, 61));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(0, 30, 71, 22));
        radioButton_4->setChecked(false);
        radioButton_4->setAutoExclusive(true);
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(0, 0, 71, 22));
        groupBox_2 = new QGroupBox(tab_4);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 50, 81, 61));
        radioButton = new QRadioButton(groupBox_2);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(0, 0, 81, 22));
        radioButton_2 = new QRadioButton(groupBox_2);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(0, 30, 81, 22));
        radioButton_2->setChecked(false);
        radioButton_2->setAutoExclusive(true);
        QIcon icon9;
        iconThemeName = QStringLiteral("view-preview");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon9 = QIcon::fromTheme(iconThemeName);
        } else {
            icon9.addFile(QStringLiteral("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        tabWidget->addTab(tab_4, icon9, QString());
        Krudio->setCentralWidget(centralWidget);

        retranslateUi(Krudio);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Krudio);
    } // setupUi

    void retranslateUi(QMainWindow *Krudio)
    {
        Krudio->setWindowTitle(QApplication::translate("Krudio", "Krudio", 0));
        action->setText(QApplication::translate("Krudio", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", 0));
        prevPlay->setText(QString());
        pausePlay->setText(QString());
        nextPlay->setText(QString());
        pausePause->setText(QString());
        waitMinute->setText(QApplication::translate("Krudio", "\320\237\320\276\320\264\320\276\320\266\320\264\320\270\321\202\320\265 \320\274\320\270\320\275\321\203\321\202\320\272\321\203...", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QString());
        label->setText(QApplication::translate("Krudio", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265", "Name"));
        label_2->setText(QApplication::translate("Krudio", "URL", 0));
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
        label_3->setText(QApplication::translate("Krudio", "\320\242\320\265\320\274\320\260 \320\270\320\272\320\276\320\275\320\276\320\272", 0));
        label_4->setText(QApplication::translate("Krudio", "\320\240\320\260\320\267\320\274\320\265\321\200 \320\270\320\272\320\276\320\275\320\276\320\272", 0));
        groupBox->setTitle(QString());
        radioButton_4->setText(QApplication::translate("Krudio", "&32x32", 0));
        radioButton_3->setText(QApplication::translate("Krudio", "&16x16", 0));
        groupBox_2->setTitle(QString());
        radioButton->setText(QApplication::translate("Krudio", "\320\241\320\262\320\265\321\202\320\273\320\260\321\217", 0));
        radioButton_2->setText(QApplication::translate("Krudio", "\320\242\320\265\320\274\320\275\320\260\321\217", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QString());
    } // retranslateUi

};

namespace Ui {
    class Krudio: public Ui_Krudio {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KRUDIO_H
