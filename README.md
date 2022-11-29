# **MyJudge GUI**
本实验中为上个实验完成的等价程序性判断程序 `MyJudge` 设计了一个可供用户人工再次判断程序等价性的交互式 `GUI` 界面，基于 `QT5.0` 开发。

以下为本次实验报告内容。

#
## **1. 实验进度**

- 实现了辅助等价性确认 `GUI` 工具；
- 使用该工具对实验四中等价程序对进行进一步人工判断；
- 基于人工判断的结果完善程序等价性判断结果；
- 将项目上传至个人 `GitHub` 公开仓库；

#

## **2. 实验结果**

实现了辅助等价性确认 `GUI` 工具，可以对实验四中机器判定的等价程序对进行人工判断，完善程序等价对判断结果并保存在文件中。

<div align=center><img width = '450' height ='300' src = ./pic/res.png/></div>

#

## **3. 实验过程**

本实验工作环境为 `Ubuntu20.04` + `Windows 11`, 图形化界面通过 `QT Creator` 设计实现，工程项目源码附报告一同上传，这里仅介绍设计思路及核心部分代码。

### **3.0 设计思路**

本实验中我们需要实现一个辅助等价性确认工具，通过 `GUI` 界面实现人工判断的过程，程序可以收集人工判断结果并更新之前的结果。为此我们选择拥有丰富资源工具的 `QT 5.0` 进行设计，分为用户登陆界面和用户判断界面两部分。

### **3.1 设计登陆界面**

首先设计用户登录界面，在 `QT` 中使用工具画出界面图如下：

<div align=center><img width = '300' height ='180' src = ./pic/login.png/></div>

该界面中，用户输入账户名和密码各占一个输入文本框，此外还有一个可选的 `‘Remember me’` `checkbox` ，勾选后程序下一次登陆可以记住用户名，最下面是一个登陆的 `button`。

对应的设计代码如下：
```cpp
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
```
在 `login.cpp` 中，该函数对应登陆界面的 `Login` 按钮按下之后的信号槽，可以对用户输入的账号密码与预先设置好的账号密码比较，若正确则可以进入用户判断界面，通过在栈区新建一个 `JudgeWidget()` 实体实现。

### **3.2 设计判断界面**

接着设计用户判断界面，设计界面如下：

<div align=center><img width = '500' height ='300' src = ./pic/design.png/></div>

该界面从上到下包括：
- 三个 `label` ，用于输出提示语；
- 一个 `Qlabel` ，用于显示推荐程序对；
- 两个 `combobox` 和 `toolbutton` ，用于选择并打开程序对文件；
- 两个 `textbrower` ，用于输出程序对具体内容；
- 三个 `button` ， 用于为用户提供交互选项，包括等价，不等价和存疑；

用户使用该程序时，首先根据推荐判断的程序对打开对应文件，然后根据程序对的具体内容人工判断其等价性，并按下三个之一的按钮，此时我们的工具会输出提示语，将结果保存到对应文件中，并更新下一组推荐程序对给用户判断。

其中，将所选文件内容输出到文本框中对应的 `QT` 代码如下：
```cpp
void JudgeWidget::on_toolButton_clicked()
{
    QString path=
        QDir::toNativeSeparators(QFileDialog::getOpenFileName(this,tr("Save path"),QDir::currentPath()));  //文件路径
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
```

`“等价”` 按钮对应的信号槽代码（即按下该按钮之后触发的函数）如下：
```cpp
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
```

用户判断的部分截图如下：

<div align=center><img width = '400' height ='270' src = ./pic/inequal.png/></div>

<div align=center><img width = '400' height ='270' src = ./pic/doubt.png/></div>

### **3.3 保存人工判断结果**

我们的辅助等价性程序判断工具将结果保存至对应的 `txt` 文件中，结果如下：
<div align=center><img width = '400' height ='220' src = ./pic/txt.png/></div>

#

## **4. 使用 `Git` 操作管理项目**

本项目依托 `git` 实现版本控制，部分 `git` 操作运行截图如下：


使用 `git init` 命令创建并初始化仓库：
<div align=center><img width = '300' height ='100' src = './pic/git init.png'/></div>
 
使用 `git commit -m` 命令提交更新内容：
<div align=center><img width = '300' height ='150' src = './pic/git commit.png'/></div>

使用 `git log` 等命令查看当前版本等：
<div align=center><img width = '300' height ='130' src = './pic/git log.png'/></div>

#

## **5. 在 `Github` 上实现项目开源**

本项目现已在 `Github` 上开源。

公开仓库地址：
https://github.com/Florentino-73/MyJudge_GUI

#

## **6. 实验心得**
本次实验历时两周，实验重点在于学习使用 `QT Creator` 开发程序的 `GUI` 界面。

`QT` 的资源非常丰富，本次实验仅用到了其中一小部分，设计的界面也是最基础的样式，没有经过美化（主要也是因为作者的设计功底不咋滴...)，不过通过这个项目让自己对 `QT` 的使用熟练了很多，之后在做相关软件的界面开发时也可以更加得心应手吧！

最后感谢老师和助教提供的悉心指导的实验手册，希望之后的实验也可以一帆风顺！✌️
