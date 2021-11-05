#ifndef ADDINGWINDOW_H
#define ADDINGWINDOW_H

#include <QDialog>
#include "RBTree.h"
#include "RBIterator.h"
#include "student.h"
#include "undergraduate.h"
#include <QMessageBox>
#include "Node.h"

namespace Ui {
class AddingWindow;
}

class AddingWindow : public QDialog
{
    Q_OBJECT

public:
    AddingWindow(QWidget *parent, bool isStudent, RBTree<Student*, long> *studentsTree, RBTree<Undergraduate*, long> *undergraduatesTree);
    ~AddingWindow();

private slots:
    void on_addPushButton_clicked();

    void on_backPushButton_clicked();

private:
    Ui::AddingWindow *ui;
    bool isStudent;
    RBTree<Student*, long> *studentsTree;
    RBTree<Undergraduate*, long> *undergraduatesTree;
};

#endif // ADDINGWINDOW_H
