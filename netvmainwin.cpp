#include <QtWidgets>

#include "netvmainwin.h"
#include "ui_netvmainwin.h"

NetVMainWin::NetVMainWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NetVMainWin)
{
    ui->setupUi(this);
    ui->menuExperiment->menuAction()->setVisible(false);
    // setupUi

    for (int i = 0; i < MaxRecentFiles; ++i){
        recentFileActs[i] = ui->menuRecent->addAction(QString(), this, &NetVMainWin::openRecentFile);
        recentFileActs[i]->setVisible(false);
    }
    ui->menuRecent->menuAction()->setVisible(NetVMainWin::existRecentFile());
    emit ui->mdiArea->subWindowActivated(0);
    // updateMenus(); 子窗口存在于是更新控件
    // 让mdiArea发一个信号不就得了？有必要再定义一个updateMenus函数吗？真是糟糕的官方例子

    readAppSets();
    setUnifiedTitleAndToolBarOnMac(true);

    ui->statusBar->showMessage(tr("Ready"));
    // ui intalization finished

    // Q: how to do ablov in the ui file?
}

NetVMainWin::~NetVMainWin()
{
    delete eng;
    delete ui;
}

bool NetVMainWin::openFile(const QString &fileName)
{
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        if (qobject_cast<Experiment *>(window->widget())->currentFile() == QFileInfo(fileName).canonicalFilePath())
        {
            ui->mdiArea->setActiveSubWindow(window);
            return true;
        }
    }
    // 1.given file was already loaded

    const bool succeeded = loadFile(fileName);
    if (succeeded)
        ui->statusBar->showMessage(tr("File loaded"), 2000);
    return succeeded;
    // 2.given file was not loaded yet
}

void NetVMainWin::closeEvent(QCloseEvent *event)
{
    ui->mdiArea->closeAllSubWindows();
    if (ui->mdiArea->currentSubWindow()) {
        event->ignore();
    } else {
        saveAppSets();
        event->accept();
    }
}

void NetVMainWin::updateActionsInMenuRecent()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for ( ; i < count; ++i) {
        const QString fileName = QFileInfo(recentFiles.at(i)).fileName();
        recentFileActs[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        recentFileActs[i]->setData(recentFiles.at(i));
        recentFileActs[i]->setVisible(true);
    }
    for ( ; i < MaxRecentFiles; ++i)
        recentFileActs[i]->setVisible(false);
}

void NetVMainWin::updateMenuWindow()
{
    ui->menuExperiment->clear();

    QList<QMdiSubWindow *> sub_win_list = ui->mdiArea->subWindowList();
    ui->menuExperiment->menuAction()->setVisible(!sub_win_list.isEmpty());

    for (int i = 0; i < sub_win_list.size(); ++i) {
        QMdiSubWindow *mdiSubWindow = sub_win_list.at(i);
        Experiment *child = qobject_cast<Experiment *>(mdiSubWindow->widget());
        QString text;
        if (i < 9) {
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action = ui->menuExperiment->addAction(text, mdiSubWindow, [this, mdiSubWindow]() {
            ui->mdiArea->setActiveSubWindow(mdiSubWindow);
        });
        action->setCheckable(true);
        action ->setChecked(child == activeExp());
    }
}

void NetVMainWin::on_actionNeuronViewer_triggered()
{
    eng->Exe("neuronviewer");
}

void NetVMainWin::on_actionOption_triggered()
{
    OptionWin opt(this);
    opt.exec();
}

void NetVMainWin::on_actionCut_triggered()
{
    if (activeExp())
        activeExp()->cut();
}

void NetVMainWin::on_actionCopy_triggered()
{
    if (activeExp())
        activeExp()->copy();
}

void NetVMainWin::on_actionPaste_triggered()
{
    if (activeExp())
        activeExp()->paste();
}

void NetVMainWin::on_actionOpen_triggered()
{
    const QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        openFile(fileName);
}

void NetVMainWin::on_actionSave_triggered()
{
    if (activeExp() && activeExp()->save())
        ui->statusBar->showMessage(tr("File saved"), 2000);
}

void NetVMainWin::on_actionSave_as_triggered()
{
    Experiment *exp = activeExp();
    if (exp && exp->saveAs()) {
        ui->statusBar->showMessage(tr("File saved"), 2000);
        NetVMainWin::prependToRecentFiles(exp->currentFile());
    }
}

void NetVMainWin::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About MDI"),
             tr("The <b>MDI</b> example demonstrates how to write multiple "
                "document interface applications using Qt."));
}

void NetVMainWin::on_mdiArea_subWindowActivated(QMdiSubWindow *arg1)
{
    bool is_exp_exist = (arg1 != 0);
    ui->actionSave->setEnabled(is_exp_exist);
    ui->actionSave_as->setEnabled(is_exp_exist);
#ifndef QT_NO_CLIPBOARD
    ui->actionPaste->setEnabled(is_exp_exist);
#endif
    ui->actionClose->setEnabled(is_exp_exist);
    ui->actionClose_All->setEnabled(is_exp_exist);
    ui->actionTile->setEnabled(is_exp_exist);
    ui->actionCascade->setEnabled(is_exp_exist);
    ui->actionNext->setEnabled(is_exp_exist);
    ui->actionPrevious->setEnabled(is_exp_exist);
    ui->menuExperiment->menuAction()->setVisible(is_exp_exist);
#ifndef QT_NO_CLIPBOARD
    bool hasSelection = (arg1 &&
                         qobject_cast<Experiment *>(arg1->widget())->textCursor().hasSelection());
    ui->actionCut->setEnabled(hasSelection);
    ui->actionCopy->setEnabled(hasSelection);
#endif
}

void NetVMainWin::readAppSets()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void NetVMainWin::saveAppSets()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

bool NetVMainWin::loadFile(const QString &fileName)
{
    Experiment *exp = createExp();
    const bool succeeded = exp->loadFile(fileName);
    if (succeeded)
        exp->show();
    else
        exp->close();
    NetVMainWin::prependToRecentFiles(fileName);
    return succeeded;
}

bool NetVMainWin::existRecentFile()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const int count = settings.beginReadArray(recentFilesKey());
    settings.endArray();
    return count > 0;
}

void NetVMainWin::openRecentFile()
{
    if (const QAction *action = qobject_cast<const QAction *>(sender()))
        openFile(action->data().toString());
}

void NetVMainWin::prependToRecentFiles(const QString &fileName)
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList oldRecentFiles = readRecentFiles(settings);
    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
    if (oldRecentFiles != recentFiles)
        writeRecentFiles(recentFiles, settings);

    ui->menuRecent->menuAction()->setVisible(!recentFiles.isEmpty());
}// 相当于更新recent列表

Experiment* NetVMainWin::createExp()
{
    Experiment *child = new Experiment;
    ui->mdiArea->addSubWindow(child);

#ifndef QT_NO_CLIPBOARD
    connect(child, &QTextEdit::copyAvailable, ui->actionCut, &QAction::setEnabled);
    connect(child, &QTextEdit::copyAvailable, ui->actionCopy, &QAction::setEnabled);
#endif

    return child;
}

Experiment* NetVMainWin::activeExp() const
{
    if (QMdiSubWindow *act_sub_win = ui->mdiArea->activeSubWindow())
        return qobject_cast<Experiment *>(act_sub_win->widget());
    return 0;
}

void NetVMainWin::on_actionNew_triggered()
{
    Experiment *child = createExp();
    child->newFile();
    child->show();
}

void NetVMainWin::on_actionSwitch_Layout_triggered()
{
    if (layoutDirection() == Qt::LeftToRight)
        QGuiApplication::setLayoutDirection(Qt::RightToLeft);
    else
        QGuiApplication::setLayoutDirection(Qt::LeftToRight);
}
