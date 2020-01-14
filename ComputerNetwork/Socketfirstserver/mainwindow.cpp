#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QtNetwork/QNetworkInterface.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&server,&webserver::valueChanged,this,&MainWindow::output_message);
    ui->setupUi(this);
    ui->listenport->setPlainText("80");
    ui->virtualaddress->setPlainText("D:/ComputerNetwork/html");
    ui->end->setEnabled(false);

    //获得本机所有IP地址
    QString ipAddr;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    foreach (QHostAddress address,ipAddressesList) {
        if (address.toIPv4Address()) {
            ipAddr = address.toString();
            ui -> listenaddress->addItem(ipAddr);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    ui->start->setEnabled(false);
    ui->pushButton->setEnabled(false);
    ui->exit->setEnabled(false);
    QString port = ui->listenport->toPlainText();
    QString virtualaddress = ui->virtualaddress->toPlainText();
    QString listenaddress = ui -> listenaddress->currentText();
    server.set_port(port.toInt());
    server.set_filename(virtualaddress.toStdString());
    server.set_ip(listenaddress.toStdString());
    server.set_isnend(true);
    ui->end->setEnabled(true);
    server.start();

}

void MainWindow::on_end_clicked()
{
    ui->end->setEnabled(false);
    ui->start->setEnabled(true);
    ui->pushButton->setEnabled(true);
    ui->exit->setEnabled(true);
    server.end();
    WSACleanup();
}

void MainWindow::on_pushButton_clicked()
{
    QString file = QFileDialog::getExistingDirectory(this);
    ui->virtualaddress->setPlainText(file);
}

void MainWindow::output_message(QString s)
{
    ui->output->appendPlainText(s);
    ui->output->moveCursor(QTextCursor::End,QTextCursor::MoveAnchor);
}


void MainWindow::on_pushButton_2_clicked()
{
    ui->output->clear();
}

