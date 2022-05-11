#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTextEdit>
#include "snap7.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_pushButton_read_bool_clicked();
    void on_pushButton_read_ushort_clicked();
    void on_pushButton_read_int_clicked();
    void on_pushButton_read_uint_clicked();
    void on_pushButton_read_real_clicked();
    void on_pushButton_write_bool_clicked();
    void on_pushButton_write_uint16_clicked();
    void on_pushButton_write_int32_clicked();
    void on_pushButton_write_uint32_clicked();
    void on_pushButton_write_real_clicked();

private:
    void read(int type);
    void write(int type);
private:
    Ui::Widget *ui;
    TS7Client *m_s7 = nullptr;
};

extern QTextEdit *g_textedit;
#endif // WIDGET_H
