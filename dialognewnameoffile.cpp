#include "dialognewnameoffile.h"
#include "ui_dialognewnameoffile.h"
#include <QPushButton>
DialogNewNameOfFile::DialogNewNameOfFile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogNewNameOfFile)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked(bool)), SLOT(close()));
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked(bool)), SLOT(okClickedFileName()));
}

DialogNewNameOfFile::~DialogNewNameOfFile()
{
    delete ui;
}

void DialogNewNameOfFile::okClickedFileName(){
    emit fileName(ui->lineEdit->text());
    close();
}
