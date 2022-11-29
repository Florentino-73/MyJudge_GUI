#include "login.h"
#include "judge.h"
#include "ui_login.h"
#include <QMessageBox>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_pushButton_clicked()
{
    QString usr_name = ui->lineEdit->text();
    QString usr_passwd = ui->lineEdit_2->text();

    if(usr_name == name && usr_passwd == passwd)
    {
        JudgeWidget * jw = new JudgeWidget();
        delete(this); //关闭登陆窗口
        jw->show();
    }
    else
    {
        QMessageBox::warning(NULL,"Warning","用户名或密码错误！",QMessageBox::Ok);
    }
}
