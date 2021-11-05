#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "student.h"
#include "undergraduate.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include "QComboBox"
#include "RBTree.h"
#include "Node.h"
#include "RBIterator.h"
#include <QMainWindow>
#include "addingwindow.h"
#include "studentinformation.h"
#include "deanery.h"
#include "addwindeanery.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadTable(QList<Student*> list);
    void addStud(QString l_name, QString f_name, QString m_name, QString email, long long tel_number, int entrance_year, long id_number, QString speciality, long group_number, int course, QString debt, double average_score);
    void addUnd(QString l_name, QString f_name, QString m_name, QString email, long long tel_number, int entrance_year, long id_number, QString speciality, long group_number, QString sc_work, int course, QString debt, double average_score);
    void inputFromFile();
    void saveToFile();
    static bool compareStudentsByName(const Student *s1, const Student *s2);
    static bool compareStudentsByGroupNumber(const Student *s1, const Student *s2);
    static bool compareStudentsById(const Student *s1, const Student *s2);
    void loadTable(QList<Undergraduate*> list);
    static bool compareUndergraduatesByName(const Undergraduate *s1, const Undergraduate *s2);
    static bool compareUndergraduatesByGroupNumber(const Undergraduate *s1, const Undergraduate *s2);
    static bool compareUndergraduatesById(const Undergraduate *s1, const Undergraduate *s2);
    void searchStudent();
    void searchUndergraduate();

private slots:
    void on_courseComboBox_currentTextChanged(const QString &arg1);
    void on_allDebtRadioButton_clicked();
    void on_withDebtRadioButton_clicked();
    void on_noDebtRadioButton_clicked();
    void on_nameSortRadioButton_clicked();
    void on_groupNumberSortRadioButton_clicked();
    void on_idNumberRadioButton_clicked();
    void on_searchPushButton_clicked();
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_studentsRadioButton_clicked(bool checked);
    void on_mastersRadioButton_clicked(bool checked);

    void on_poit1CheckBox_1_stateChanged(int arg1);

    void on_vmsisCheckBox_2_stateChanged(int arg1);

    void on_iitpCheckBox_3_stateChanged(int arg1);

    void on_avsCheckBox_4_stateChanged(int arg1);

    void on_aiuvtisuCheckBox_5_stateChanged(int arg1);

    void on_vmisCheckBox_6_stateChanged(int arg1);

    void on_mmchmikpCheckBox_7_stateChanged(int arg1);

    void on_mipovmkiksCheckBox_8_stateChanged(int arg1);

    void on_iitrpoCheckBox_9_stateChanged(int arg1);

    void on_tviovCheckBox_10_stateChanged(int arg1);

    void on_oboiCheckBox_11_stateChanged(int arg1);

    void on_addPushButton_clicked();

    void on_viewPushButton_clicked();

private:
    QList<Student*> sortStudents();
    QList<Undergraduate*> sortUndergraduates();
    RBTree<Student*, long> *studentsTree;
    RBTree<Undergraduate*, long> *undergraduatesTree;
    Deanery* deanery;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
