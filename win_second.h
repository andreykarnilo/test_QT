#ifndef WIN_SECOND_H
#define WIN_SECOND_H

#include <QDialog>

namespace Ui {
class win_second;
}

class win_second : public QDialog
{
    Q_OBJECT

public:
    explicit win_second(QWidget *parent = 0);
    ~win_second();

private slots:
    void on_table_clicked(const QModelIndex &index);

    void on_button_logout_clicked();

    void on_button_add_clicked();

private:
    Ui::win_second *ui;
};

#endif // WIN_SECOND_H
