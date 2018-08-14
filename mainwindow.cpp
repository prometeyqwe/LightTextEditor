#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

#include "dialognewnameoffile.h"

QString MainWindow::fileSaveName = "";
bool MainWindow::fileIsOpen = false;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    ui->statusBar->showMessage("Файл не выбран");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_2_triggered()
{
    if(!fileIsOpen){
        QFileDialog *qfd = new QFileDialog(this);
        QString pathFile = "";
        pathFile = qfd->getOpenFileName(this);
        if(pathFile!=""){
            fileIsOpen = true;
            QFile mFile(pathFile);
        //    emitSendFileName(pathFile);

            fileSaveName = pathFile;

            if(!mFile.open(QFile::ReadOnly | QFile::Text )){
                QMessageBox::warning(this, "Error", "Path not correct");
                return;
            }

            QTextStream stream(&mFile);
            QString buffer = stream.readAll();
            ui->textEdit->setText(buffer);
            ui->statusBar->showMessage("Выбран файл " + pathFile);
            mFile.flush();
            mFile.close();
        }

    }else{
        ui->statusBar->showMessage("Файл уже выбран, закройте его, чтобы продолжить");
    }

}

void MainWindow::on_action_triggered()
{
    DialogNewNameOfFile *wnd = new DialogNewNameOfFile(this);
    wnd->show();
    ui->textEdit->clear();
    connect(wnd, SIGNAL(fileName(QString)), this, SLOT(selectFileName(QString)));
}

void MainWindow::selectFileName(const QString &fName){
    QFileDialog *qdf = new QFileDialog(this);
    QString fileDir = "";
    fileDir = qdf->getExistingDirectory(this);
    if(fileDir!=""){
        QFile mFile(fileDir+"/"+fName+".txt");
        fileIsOpen = true;
        QString qwe = fileDir+"/"+fName+".txt";
    //    emitSendFileName(qwe);
        fileSaveName = qwe;
        ui->statusBar->showMessage("Файл выбран "+qwe);


        if(!mFile.open(QFile::WriteOnly | QFile::Text )){
            QMessageBox::warning(this, "Error", "Path not correct");
            return;
        }

        mFile.close();
    }
}

void MainWindow::on_action_5_triggered()
{
    close();
}

void MainWindow::emitSendFileName(QString &ffName){
    emit sendFilePath(ffName);
}



void MainWindow::getFileName(QString &str){
    QString filePath = ui->statusBar->currentMessage();

    QFile mFile(filePath);
    if(!mFile.open(QFile::WriteOnly | QFile::Text )){
        QMessageBox::warning(this, "Error", "Path not correct");
        return;
    }

    QTextStream stream(&mFile);
    stream << ui->textEdit->toPlainText();
    mFile.close();
    ui->statusBar->showMessage("Файл сохранен");
}

void MainWindow::on_action_3_triggered()
{
//    connect(this, SIGNAL(sendFilePath(QString&)), this, SLOT(getFileName(QString&)));
    QString filePath = fileSaveName;

    QFile mFile(filePath);
    if(!mFile.open(QFile::WriteOnly | QFile::Text )){
        QMessageBox::warning(this, "Error", "Path not correct");
        return;
    }

    QTextStream stream(&mFile);
    stream << ui->textEdit->toPlainText();
    mFile.close();
    ui->statusBar->showMessage("Файл сохранен");

}

void MainWindow::on_action_6_triggered()
{
    ui->textEdit->clear();
    fileIsOpen = false;
    ui->statusBar->showMessage("Файл закрыт");
}

void MainWindow::on_action_4_triggered()
{
    QFileDialog *dfg = new QFileDialog();
    QString fileP = "";
    fileP = dfg->getSaveFileName();
    if(fileP!=""){
        QFile *mFile = new QFile(fileP);
        if(fileP.contains(".txt")){
            mFile = new QFile(fileP);
            fileSaveName = fileP;
        }
        else{
            mFile = new QFile(fileP+".txt");
            fileSaveName = fileP+".txt";
        }

        if(!mFile->open(QFile::ReadWrite | QFile::Text )){
            QMessageBox::warning(this, "Error", "Path not correct");
            return;
        }

        QTextStream stream(mFile);
        stream << ui->textEdit->toPlainText();
        mFile->close();
        ui->statusBar->showMessage("Файл сохранен");
    }
    else{
         ui->statusBar->showMessage("Файл не сохранен. Выберите корректный путь");
    }


}
