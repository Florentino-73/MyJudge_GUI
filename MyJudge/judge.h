#ifndef MYJUDGE_H
#define MYJUDGE_H

#include <QWidget>

namespace Ui {
class JudgeWidget;
}

class JudgeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit JudgeWidget(QWidget *parent = 0);
    ~JudgeWidget();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_yes_clicked();

    void on_no_clicked();

    void on_doubt_clicked();

private:
    Ui::JudgeWidget *ui;
    int turn = 0;
    QVector<QString> ojfile; //保存所有OJ文件名称
    QString offer_ojfile; //推荐的OJ程序对

    QString path_1; //第一个OJ文件路径
    QString path_2; //第二个OJ文件路径

    const QString equal_path = "D:/NJU/【课程】软件工程/实验五/output/equal.txt"; //保存人工判断等价的程序对文件路径
    const QString inequal_path = "D:/NJU/【课程】软件工程/实验五/output/inequal.txt"; //保存人工判断不等价的程序对文件路径
    const QString doubt_path = "D:/NJU/【课程】软件工程/实验五/output/doubt.txt"; //保存人工判断存疑的程序对文件路径

};

#endif // MYJUDGE_H
