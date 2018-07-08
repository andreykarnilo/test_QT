#include "win_second.h"
#include "ui_win_second.h"
#include <QProcess>

#include <QApplication>
#include <QTimer>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

#ifdef Q_OS_WIN
   QFont font_tabl("Courier", 9);
   QFont font_text_label("Monospace", 10);
   QFont font_button_add("Monospace", 8);
   QFont font_button_logout("Monospace", 8);

   const int pos_size = 61; //позиция size
   const int pos_done = 74; //позиция done
#else
    #ifdef Q_OS_MACOS
        QFont font_tabl("Monaco", 13);
        QFont font_text_label("Monospace", 13);
        QFont font_button_add("Monospace", 8);
        QFont font_button_logout("Monospace", 8);

        const int pos_size = 54; //позиция size
        const int pos_done = 64; //позиция done
    #else
        QFont font_tabl("Courier", 9);
        QFont font_text_label("Monospace", 10);
        QFont font_button_add("Monospace", 8);
        QFont font_button_logout("Monospace", 8);

        const int pos_size = 54; //позиция size
        const int pos_done = 64; //позиция done
    #endif
#endif
QString _size[5] = { "B", "Kb", "Mb", "Gb", "Tb" };
win_second::win_second(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::win_second)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::Window |Qt::WindowTitleHint | Qt::CustomizeWindowHint| Qt::WindowCloseButtonHint); //оставить только кнопку закрытия
    //------------------------  listWidget  ---------------------------
    ui->label_name_tab->setFont (font_tabl);
    ui->label->setFont (font_text_label);
    ui->button_logout->setFont (font_button_logout);
    ui->button_add->setFont (font_button_add);
    ui->table->setAttribute(Qt::WA_MacShowFocusRect, false);  //убрать голубую подсветку в mac os

    //--------------     заголовок таблицы      ----------------------------------
    QString str_name(" ");
    // Name
    str_name.push_back("Name");
    // size
    str_name += QString(pos_size-str_name.length(), ' ');
    str_name.push_back("Size");
    // Done
    str_name += QString(pos_done-str_name.length(), ' ');
    str_name.push_back("Status");
    ui->label_name_tab->setText(str_name);

    //-------------------   таблица  ---------------------------------
    ui->table->setRowCount(13);//количество строк
    ui->table->setColumnCount(4); //количество столбцов
    ui->table->verticalHeader()->hide();
    ui->table->horizontalHeader()->hide();
    ui->table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->table->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->table->setSelectionMode(QAbstractItemView::SingleSelection);//выделение строки
    ui->table->setSelectionMode(QAbstractItemView::NoSelection);//отменить выделение
    ui->table->setFocusPolicy(Qt::NoFocus); //убрать фокус ячейки
    ui->table->setShowGrid(false);//убрать сетку
    ui->table->verticalHeader()->setDefaultSectionSize(40); //высота строки
    ui->table->setColumnWidth(0,430);
    ui->table->setColumnWidth(1,80);
    ui->table->setColumnWidth(2,100);
    ui->table->setColumnWidth(3,40);
    ui->table->setIconSize(QSize(40, 40)); //размер иконок

    for(int i=0;i< ui->table->rowCount();i++)
        for(int j=0;j<ui->table->columnCount();j++)
        {
            QString str= "name_"+QString::number(i);
            QTableWidgetItem *itm= new QTableWidgetItem(str);
            ui->table->setItem(i,0,itm);
            //--------------------------------------------------
            QTableWidgetItem *itm1= new QTableWidgetItem("320mb");
            ui->table->setItem(i,1,itm1);
            //--------------------------------------------------
            QTableWidgetItem *itm2= new QTableWidgetItem("Encoding 98%");
            ui->table->setItem(i,2,itm2);
            //--------------------------------------------------
            QTableWidgetItem * cubesHeaderItem = new QTableWidgetItem ;
            cubesHeaderItem->setSizeHint(QSize(100, 100));

            cubesHeaderItem-> setIcon (QIcon (QPixmap (":/button/button_delete.png")));

            cubesHeaderItem-> setTextAlignment (Qt::AlignCenter );
            ui->table-> setItem (i,3, cubesHeaderItem);
           }
}

win_second::~win_second()
{
    delete ui;
}

void win_second::on_table_clicked(const QModelIndex &index)
{
    if((index.column()==3))
        ui->table->removeRow(index.row());
}

void win_second::on_button_logout_clicked()
{
    QProcess::startDetached(QApplication::applicationFilePath());
    exit(12);
}

void win_second::on_button_add_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this, QString::fromUtf8("Open a file"), QDir::rootPath(), "All files (*.*)");
    if (filenames.isEmpty())
        return;
    foreach(QString filename, filenames)
    {
        int i = ui->table->rowCount();
        ui->table->setRowCount(i + 1);

        qint64 size = 0;
        QFile myFile(filename);

        //---------------------  get size  ----------------------------
        if(myFile.open(QIODevice::ReadOnly)){
            size = myFile.size();
            myFile.close();
        }
        int pol = 0;
        int size_last = 0;
        while (size > 1024)
        {
            pol++;
            size_last = size % 1024;
            size = size / 1024;
        }
        size_last = (size_last * 10) / 1024;

        //---------------------  write file name  ----------------------------
        QString str = filename.toUtf8();
        QTableWidgetItem *itm = new QTableWidgetItem(str);
        ui->table->setItem(i, 0, itm);

        //---------------------  write size  ----------------------------
        str = QString::number(size) + "." + QString::number(size_last) + " " + _size[pol];
         QTableWidgetItem *itm1 = new QTableWidgetItem(str);
        ui->table->setItem(i, 1, itm1);

        //---------------------  write status  ----------------------------
        QString str_status("");
        str_status = "Waiting";
        QTableWidgetItem *itm2 = new QTableWidgetItem(str_status);
        ui->table->setItem(i, 2, itm2);

        //---------------------  write button  ----------------------------
        QTableWidgetItem * cubesHeaderItem = new QTableWidgetItem;
        cubesHeaderItem->setSizeHint(QSize(100, 100));
        cubesHeaderItem->setIcon(QIcon(QPixmap(":/button/button_delete.png")));
        cubesHeaderItem->setTextAlignment(Qt::AlignCenter);
        ui->table->setItem(i, 3, cubesHeaderItem);
    }
}
