#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialognewnameoffile.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    static QString fileSaveName;
    void emitSendFileName(QString & ffName);
    ~MainWindow();

private slots:
    void on_action_2_triggered();
    void selectFileName(const QString &fName);
    void on_action_triggered();
    void getFileName(QString & str);
    void on_action_5_triggered();

    void on_action_3_triggered();

    void on_action_6_triggered();

    void on_action_4_triggered();

private:
    Ui::MainWindow *ui;
    static QString dirFile;
    static bool fileIsOpen;


signals:
    void sendFilePath(QString & fName);
};



#endif // MAINWINDOW_H
