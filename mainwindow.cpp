#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef Q_OS_WIN
    QFont font_remember ("Monospace", 8);
    QFont font_email("Monospace", 10);
    QFont font_pass("Monospace", 10);
    QFont font_button_login("Monospace", 11);
#else
    #ifdef Q_OS_MACOS
        QFont font_remember("Monospace", 11);
        QFont font_email("Monospace", 13);
        QFont font_pass("Monospace", 13);
        QFont font_button_login("Monospace", 14);
    #else
        QFont font_remember("Monospace", 8);
        QFont font_email("Monospace", 10);
        QFont font_pass("Monospace", 10);
        QFont font_button_login("Monospace", 11);
    #endif
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //background
    QPixmap bkgnd(":/backgrounds/login.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    this->setWindowFlags(Qt::Window |Qt::WindowTitleHint | Qt::CustomizeWindowHint| Qt::WindowCloseButtonHint); //оставить только кнопку закрытия
    this->statusBar()->setSizeGripEnabled(false); //убрать значек растяжения

    ui->edit_email->setFrame(0); //убрать рамку в поле Email
    ui->edit_pass->setFrame(0); //убрать рамку в поле Pass
    ui->edit_email->setAttribute(Qt::WA_MacShowFocusRect, false); //убрать голубую подсветку в mac os
    ui->edit_pass->setAttribute(Qt::WA_MacShowFocusRect, false);  //убрать голубую подсветку в mac os

    ui->edit_email->setFont(font_email);
    ui->edit_pass->setFont(font_pass);
    ui->checkBox->setFont(font_remember);
    ui->button_login->setFont(font_button_login);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_button_login_clicked()
{
    close();
    win_second w_second;
    w_second.exec();
}
