#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <storage.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Storage * _storage;
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
