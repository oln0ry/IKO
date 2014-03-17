#ifndef COMMONVIEW_H
#define COMMONVIEW_H

#include <QWidget>

namespace Ui {
class commonview;
}

class commonview : public QWidget
{
    Q_OBJECT

public:
    explicit commonview(QWidget *parent = 0);
    ~commonview();

private:
    Ui::commonview *ui;
};

#endif // COMMONVIEW_H
