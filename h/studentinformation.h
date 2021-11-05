#ifndef STUDENTINFORMATION_H
#define STUDENTINFORMATION_H

#include <QDialog>
#include "student.h"
#include "undergraduate.h"
#include "RBTree.h"
#include "RBIterator.h"
#include "Node.h"
#include <QMessageBox>


namespace Ui {
class StudentInformation;
}

class StudentInformation : public QDialog
{
    Q_OBJECT

public:
    explicit StudentInformation(QWidget *parent, long id, bool isStudent, RBTree<Student*, long>* studentsTree, RBTree<Undergraduate*, long>* undergraduatesTree);
    ~StudentInformation();

private slots:
    void on_deletePushButton_clicked();

    void on_backPushButton_clicked();

    void on_acceptPushButton_clicked();

private:
    long currentId;
    bool isStudent;
    QString currentSpeciality;
    RBTree<Student*, long> *studentsTree;
    RBTree<Undergraduate*, long> *undergraduatesTree;
    Ui::StudentInformation *ui;
};

#endif // STUDENTINFORMATION_H
