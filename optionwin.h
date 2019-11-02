#ifndef OPTIONWIN_H
#define OPTIONWIN_H

#include <QDialog>

namespace Ui {
class OptionWin;
}

class OptionWin : public QDialog
{
    Q_OBJECT

public:
    explicit OptionWin(QWidget *parent = 0);
    ~OptionWin();

private:
    Ui::OptionWin *ui;
};

#endif // OPTIONWIN_H
