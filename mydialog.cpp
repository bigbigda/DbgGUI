#include "mydialog.h"
#include <QDialogButtonBox>
#include <QDebug>

MyDialog::MyDialog(QWidget *parent)
    : QDialog(parent)
{
    le = 0;
    this->setAttribute(Qt::WA_QuitOnClose, false);

    QVBoxLayout * vbox = new QVBoxLayout;

    vbox->addWidget(new QLabel(tr("Type in the address:")));

    le = new QLineEdit();

    // le->setText(tr("Profile"));
    // le->selectAll();
    le->setPlaceholderText(tr("Profile"));

    vbox->addWidget(le);

    QRegExpValidator * v = new QRegExpValidator(QRegExp("^[0-9A-Fa-f]*$"));
    le->setValidator(v);


    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
        | QDialogButtonBox::Cancel);
    vbox->addWidget(buttonBox);
    this->setLayout(vbox);

      connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
      connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

MyDialog::~MyDialog()
{

}

QString MyDialog::getNewValue()
{
        return le->text();
}

