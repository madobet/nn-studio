#include "netvmainwin.h"
#include "./engine/vengine.h"
#include "./engine/mateng.h"
#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSplashScreen>
#include <QPixmap>
#include <QWidget>
#include <QString>
#include <iostream>

VEngine* eng;    // 不能建在栈上，有些不够大的导致崩溃…因此不能直接用VEngine eng对象要用指针

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resource);

    QApplication app(argc, argv);
    //

    QCommandLineParser parser;
    parser.setApplicationDescription("Qt MDI Example");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(app);
    // process command line

    QPixmap pix(":/logo/loading");
    QSplashScreen splash(pix,Qt::WindowStaysOnTopHint);
    splash.showMessage("<font size=\"6\" face=\"verdana\" color=\"red\">starting MATLAB engine...</font>"); // use setStyleSheet to replace font label?
    splash.show();
    app.processEvents();    // keep responsing to mouse and key board event
    // "loading" interface

    std::string dir = app.applicationDirPath().toStdString() + "/m";
    eng = new MatEng(dir);

    splash.showMessage("<font size=\"6\" face=\"verdana\" color=\"red\">loading NetworkV...</font>");
    NetVMainWin w;
    splash.finish(&w);//启动画面在最后一个窗口创建完成以后结束
    w.show();
    // intalization finished

    return app.exec();
}
