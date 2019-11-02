#include <QtWidgets>

#include "experiment.h"

Experiment::Experiment()
{
    setAttribute(Qt::WA_DeleteOnClose);
    isUntitled = true;
}

void Experiment::newFile()
{
    static int sequenceNumber = 1;

    isUntitled = true;
    curFile = tr("document%1.txt").arg(sequenceNumber++);
    setWindowTitle(curFile + "[*]");

    connect(document(), &QTextDocument::contentsChanged,
            this, &Experiment::documentWasModified);
}

bool Experiment::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }

    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    setPlainText(in.readAll());
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);

    connect(document(), &QTextDocument::contentsChanged,
            this, &Experiment::documentWasModified);

    return true;
}

bool Experiment::save()
{
    if (isUntitled) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool Experiment::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                                                    curFile);
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool Experiment::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("MDI"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return false;
    }

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << toPlainText();
    QApplication::restoreOverrideCursor();

    setCurrentFile(fileName);
    return true;
}

QString Experiment::userFriendlyCurrentFile()
{
    return strippedName(curFile);
}

void Experiment::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void Experiment::documentWasModified()
{
    setWindowModified(document()->isModified());
}

bool Experiment::maybeSave()
{
    if (!document()->isModified())
        return true;
    const QMessageBox::StandardButton ret
            = QMessageBox::warning(this, tr("MDI"),
                                   tr("'%1' has been modified.\n"
                                      "Do you want to save your changes?")
                                   .arg(userFriendlyCurrentFile()),
                                   QMessageBox::Save | QMessageBox::Discard
                                   | QMessageBox::Cancel);
    switch (ret) {
    case QMessageBox::Save:
        return save();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void Experiment::setCurrentFile(const QString &fileName)
{
    curFile = QFileInfo(fileName).canonicalFilePath();
    isUntitled = false;
    document()->setModified(false);
    setWindowModified(false);
    setWindowTitle(userFriendlyCurrentFile() + "[*]");
}

QString Experiment::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
