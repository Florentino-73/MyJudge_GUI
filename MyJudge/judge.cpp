#include "judge.h"
#include "ui_judge.h"
#include <QMessageBox>
#include <QDebug>
#include <QVector>
#include "QDir"
#include "QFileDialog"
#include "QTextStream"
#include "QFile"

JudgeWidget::JudgeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JudgeWidget)
{
    ui->setupUi(this);

    ojfile.append("./4A/48762087.cpp");
    ojfile.append("./4A/84822638.cpp");
    ojfile.append("./4A/84822639.cpp");
    ojfile.append("./4A/101036360.cpp");
    ojfile.append("./4A/117364748.cpp");
    ojfile.append("./4A/127473352.cpp");
    ojfile.append("./4A/134841308.cpp");
    ojfile.append("./4A/173077807.cpp");

    offer_ojfile = ojfile[0] + ' , ' + ojfile[1];
    ui->OJfile->setText(offer_ojfile);
}

JudgeWidget::~JudgeWidget()
{
    delete ui;
}

void JudgeWidget::on_toolButton_clicked()
{
    QString path=QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,tr("Save path"),QDir::currentPath()));  //文件路径
    path_1 = path;

    if(!path.isEmpty())
    {
        if(ui->comboBox->findText(path)==-1)
            ui->comboBox->addItem(path);    //在comboBox中显示文件路径

        QFile *file=new QFile;   //申请一个文件指针
        file->setFileName(path);   //设置文件路径
        bool ok=file->open(QIODevice::ReadOnly);
        if(ok)
        {
            QTextStream in(file);
            ui->textBrowser->setText(in.readAll());    //在textBrowser中显示文件内容
            file->close();
        }
     }
}

void JudgeWidget::on_toolButton_2_clicked()
{
    QString path=QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,tr("Save path"),QDir::currentPath()));  //文件路径
    path_2 = path;

    if(!path.isEmpty())
    {
        if(ui->comboBox_2->findText(path)==-1)
            ui->comboBox_2->addItem(path);    //在comboBox中显示文件路径

        QFile *file=new QFile;   //申请一个文件指针
        file->setFileName(path);   //设置文件路径
        bool ok=file->open(QIODevice::ReadOnly);
        if(ok)
        {
            QTextStream in(file);
            ui->textBrowser_2->setText(in.readAll());    //在textBrowser中显示文件内容
            file->close();
        }
     }
}

void JudgeWidget::on_yes_clicked()
{
    //创建文件内容
    QString str= path_1 + " , " + path_2;
    QFile file(equal_path);
    qDebug()<<str;

    //打开文件，不存在则创建
    file.open(QIODevice::Append);

    //写入文件需要字符串为QByteArray格式
    QTextStream out(&file);
    out << str << endl;
    file.close();

    //输出提示语
    QMessageBox::information(NULL, "Is_equal","判断程序对等价成功！");

    //推荐下一组人工判断的程序对
    turn = (turn + 1) % ojfile.size();
    offer_ojfile = ojfile[turn] + " , " + ojfile[turn+1];
    ui->OJfile->setText(offer_ojfile);

}

void JudgeWidget::on_no_clicked()
{
    //创建文件内容
    QString str= path_1 + " , " + path_2;
    QFile file(inequal_path);
    qDebug()<<str;

    //打开文件，不存在则创建
    file.open(QIODevice::Append);

    //写入文件需要字符串为QByteArray格式
    QTextStream out(&file);
    out << str << endl;
    file.close();

    //输出提示语
    QMessageBox::information(NULL, "Not_equal","判断程序对不等价成功！");

    //推荐下一组人工判断的程序对
    turn = (turn + 1) % ojfile.size();
    offer_ojfile = ojfile[turn] + " , " + ojfile[turn+1];
    ui->OJfile->setText(offer_ojfile);

}

void JudgeWidget::on_doubt_clicked()
{
    //创建文件内容
    QString str= path_1 + " , " + path_2;
    QFile file(doubt_path);
    qDebug()<<str;

    //打开文件，不存在则创建
    file.open(QIODevice::Append);

    //写入文件需要字符串为QByteArray格式
    QTextStream out(&file);
    out << str << endl;
    file.close();

    //输出提示语
    QMessageBox::information(NULL, "Doubt","程序对存疑！");

    //推荐下一组人工判断的程序对
    turn = (turn + 1) % ojfile.size();
    offer_ojfile = ojfile[turn] + " , " + ojfile[turn+1];
    ui->OJfile->setText(offer_ojfile);

}
