#ifndef NETVMAINWIN_H
#define NETVMAINWIN_H

#include <QMainWindow>
#include "./engine/vengine.h"
#include "ioprocess.h"
#include "optionwin.h"
#include "experiment.h"

extern VEngine* eng;

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QMdiArea;
class QMdiSubWindow;
QT_END_NAMESPACE

namespace Ui {
class NetVMainWin;
}

class NetVMainWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit NetVMainWin(QWidget *parent = 0);
    ~NetVMainWin();

    bool openFile(const QString &fileName);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void updateActionsInMenuRecent();
    void updateMenuWindow();
    // self-definetion slots

    void on_actionNeuronViewer_triggered();

    void on_actionOption_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSave_as_triggered();

    void on_actionAbout_triggered();

    void on_mdiArea_subWindowActivated(QMdiSubWindow *arg1);

    void on_actionNew_triggered();

    void on_actionSwitch_Layout_triggered();

private:

    enum { MaxRecentFiles = 6 };

    void readAppSets();
    void saveAppSets();
    //

    bool loadFile(const QString &fileName);
    // for commandline

    static bool existRecentFile();
    void openRecentFile();
    void prependToRecentFiles(const QString &fileName);
    // too complicated

    Experiment *createExp();
    Experiment *activeExp() const;
    //

    Ui::NetVMainWin *ui;

    QAction* recentFileActs[MaxRecentFiles];
    // Can not be created in Qt Creator
};

#endif // NETVMAINWIN_H
