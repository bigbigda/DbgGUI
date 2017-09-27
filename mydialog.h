#ifndef MYDIALOG_H
#define MYDIALOG_H
#include <QDialog>
#include <QRegExpValidator>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QLabel>


class MyDialog  :   public QDialog
{
    Q_OBJECT

public:
    MyDialog(QWidget *parent);
    ~MyDialog();
    QString getNewValue();
    QLineEdit * le;


};

#endif // MYDIALOG_H
