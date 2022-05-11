#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include "s7.h"

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

void Widget::on_pushButton_read_bool_clicked()
{
    read(S7_TYPE_BOOL);
}

void Widget::on_pushButton_read_ushort_clicked()
{
    read(S7_TYPE_UINT);
}

void Widget::on_pushButton_read_int_clicked()
{
    read(S7_TYPE_DINT);
}

void Widget::on_pushButton_read_uint_clicked()
{
    read(S7_TYPE_UDINT);
}

void Widget::on_pushButton_read_real_clicked()
{
    read(S7_TYPE_REAL);
}

void Widget::read(int type)
{
    if (!m_s7->Connected()) {
        qWarning() << "Not connected yet. Plz connect first!";
        return;
    }
    auto addr = ui->lineEdit_read_addr->text();
    auto tmp = addr.split('.', Qt::SkipEmptyParts);
    int db_num = tmp.first().replace("DB", "").toInt();
    int offset = 0;
    int bit = 0;
    if (tmp.size() >= 2) {
        offset = tmp.at(1).toInt();
    }
    if (tmp.size() >= 3) {
        bit = tmp.at(2).toInt();
    }
    byte buffer[64];
    m_s7->DBRead(db_num, offset, S7_GetDataTypeSize(type), buffer);
    if (type == S7_TYPE_BOOL) {
        qDebug() << "Read bool : " << S7_GetBitAt(buffer, 0, bit);
    } else if (type == S7_TYPE_UINT) {
        qDebug() << "Read uint16 : " << S7_GetUIntAt(buffer, 0);
    } else if (type == S7_TYPE_DINT) {
        qDebug() << "Read int32 : " << S7_GetDIntAt(buffer, 0);
    } else if (type == S7_TYPE_UDINT) {
        qDebug() << "Read uint32 : " << S7_GetUDIntAt(buffer, 0);
    } else if (type == S7_TYPE_REAL) {
        qDebug() << "Read real : " << S7_GetRealAt(buffer, 0);
    }
}
