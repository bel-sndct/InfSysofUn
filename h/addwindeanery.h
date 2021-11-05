#ifndef ADDWINDEANERY_H
#define ADDWINDEANERY_H
#include "deanery.h"
#include <QDialog>

namespace Ui {
class AddWindowDeanery;
}

class AddWindowDeanery : public QDialog
{
    Q_OBJECT

public:
    AddWindowDeanery(QWidget *parent, Deanery* deaneryObject);
    ~AddWindowDeanery();

private slots:


private:
    Ui::AddWindowDeanery *ui;
    Deanery* deaneryObject;
};

#endif // ADDWINDEANERY_H
