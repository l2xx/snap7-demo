#include "widget.h"
#include <QApplication>

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    if (g_textedit != nullptr) {
        switch (type) {
        case QtDebugMsg:
            g_textedit->append("<font color='gray'>" +msg+"</font>");
            break;
        case QtWarningMsg:
            g_textedit->append("<font color='red'>" +msg+"</font>");
            break;
        case QtCriticalMsg:
            g_textedit->append("<font color='red'>" +msg+"</font>");
            break;
        case QtFatalMsg:
            abort();
        }
    } else {
        QByteArray localMsg = msg.toLocal8Bit();
        switch (type) {
        case QtDebugMsg:
            fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtInfoMsg:
            fprintf(stderr, "Info: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtWarningMsg:
            fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtCriticalMsg:
            fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            break;
        case QtFatalMsg:
            fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
            abort();
        }
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QApplication a(argc, argv);
    a.setApplicationDisplayName("snap7 demo");
    Widget w;
    w.show();
    return a.exec();
}
