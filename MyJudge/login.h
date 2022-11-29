#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWidget *ui;
    QString name = "swb";
    QString passwd = "8888";

};

#endif // WIDGET_H
