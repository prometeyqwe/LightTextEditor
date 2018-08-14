#ifndef DIALOGNEWNAMEOFFILE_H
#define DIALOGNEWNAMEOFFILE_H

#include <QDialog>

namespace Ui {
class DialogNewNameOfFile;
}

class DialogNewNameOfFile : public QDialog
{
    Q_OBJECT

public:
    explicit DialogNewNameOfFile(QWidget *parent = 0);
    ~DialogNewNameOfFile();

private:
    Ui::DialogNewNameOfFile *ui;
signals:
    void fileName(const QString &str);
private slots:
    void okClickedFileName();
};



#endif // DIALOGNEWNAMEOFFILE_H
