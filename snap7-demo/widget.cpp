#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

QTextEdit *g_textedit = nullptr;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    g_textedit = ui->textEdit_output;

    ui->pushButton_connect->setEnabled(true);
    ui->pushButton_disconnect->setEnabled(false);

    m_s7 = new TS7Client();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_connect_clicked()
{
    if (!m_s7->Connected()) {
        int r = m_s7->ConnectTo(ui->lineEdit_ip->text().toStdString().c_str(),
                        ui->spinBox_rack->value(),
                        ui->spinBox_slot->value());
        if (r == 0) {
            qDebug() << "Connected to s7 successfully.";
            ui->pushButton_connect->setEnabled(false);
            ui->pushButton_disconnect->setEnabled(true);
        } else {
            qWarning() << "Failed to connect s7. Error code: " << r;
        }
    } else {
        qDebug() << "It's already connected!";
    }
}

void Widget::on_pushButton_disconnect_clicked()
{
    if (m_s7->Connected()) {
        auto r = m_s7->Disconnect();
        if (r == 0) {
            qDebug() << "Disconnected to s7 successfully.";
            ui->pushButton_connect->setEnabled(true);
            ui->pushButton_disconnect->setEnabled(false);
        } else {
            qWarning() << "Failed to disconnect s7. Error code: " << r;
        }
    } else {
        qDebug() << "Not connected yet.";
    }
}
