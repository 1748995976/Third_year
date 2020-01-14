#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <server.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_clicked();

    void on_end_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public slots:
    void output_message(QString s);

private:
    Ui::MainWindow *ui;
    webserver server;
};

#endif // MAINWINDOW_H
