#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_addwindeanery.h"
#include <QDebug>
#include "QFile"
#include <QTextStream>
#include <QCloseEvent>

using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    Deanery *object = new Deanery;
    object->setLName("Нупрейчик");
    object->setFName("Антон");
    object->setMName("Батькович");
    object->setEmail("penetrator9k@hub.com");
    object->setTelNumber(375298047042);
    object->setFaculty("ФКСиС");
    object->setOffice("501a");
    object->setBuild(5);

    deanery = object;

    Undergraduate *und1 = new Undergraduate();
    und1->setGroupNumber(510101);
    und1->setSpeciality("ОБОИ");
    und1->setLName("пашуков");
    und1->setFName("дмитрий");
    und1->setMName("батькович");
    und1->setId(21010101);
    und1->setDebt(false);
    und1->setCourse(1);

    Undergraduate *und2 = new Undergraduate();
    und2->setGroupNumber(510101);
    und2->setSpeciality("ОБОИ");
    und2->setLName("пашуков");
    und2->setFName("дмитрий");
    und2->setMName("батькович");
    und2->setId(21010100);
    und2->setDebt(false);
    und2->setCourse(2);

    undergraduatesTree = new RBTree<Undergraduate*, long>();
    undergraduatesTree->insert(und1, und1->getId());
    undergraduatesTree->insert(und2, und2->getId());


    Student *std1 = new Student();
    std1->setGroupNumber(951008);
    std1->setSpeciality("ПОИТ");
    std1->setLName("kostyan");
    std1->setFName("Vladislav");
    std1->setMName("Vyacheslavovich");
    std1->setId(95100128);
    std1->setDebt(false);
    std1->setCourse(3);

    Student *std2 = new Student();
    std2->setGroupNumber(900513);
    std2->setSpeciality("ВМСиС");
    std2->setLName("ok");
    std2->setFName("boomer");
    std2->setMName("watever");
    std2->setId(80400231);
    std2->setDebt(true);
    std2->setCourse(1);

    Student *std3 = new Student();
    std3->setGroupNumber(951048);
    std3->setSpeciality("ИиТП");
    std3->setLName("ui");
    std3->setFName("doesnt");
    std3->setMName("work");
    std3->setId(95100893);
    std3->setDebt(true);
    std3->setCourse(2);

    Student *std4 = new Student();
    std4->setGroupNumber(900900);
    std4->setSpeciality("ИиТП");
    std4->setLName("4");
    std4->setFName("44");
    std4->setMName("444");
    std4->setId(33420000);
    std4->setDebt(true);
    std4->setCourse(2);

    Student *std5 = new Student();
    std5->setGroupNumber(900513);
    std5->setSpeciality("ВМСиС");
    std5->setLName("ui");
    std5->setFName("doesnt");
    std5->setMName("work");
    std5->setId(34208202);
    std5->setDebt(true);
    std5->setCourse(1);

    Student *std6 = new Student();
    std6->setGroupNumber(456320);
    std6->setSpeciality("ЭВС");
    std6->setLName("ui");
    std6->setFName("doesnt");
    std6->setMName("work");
    std6->setId(34209213);
    std6->setDebt(true);
    std6->setCourse(2);

    Student *std7 = new Student();
    std7->setGroupNumber(951008);
    std7->setSpeciality("ПОИТ");
    std7->setLName("ui");
    std7->setFName("doesn't");
    std7->setMName("work");
    std7->setId(56009213);
    std7->setDebt(true);
    std7->setCourse(3);

    studentsTree = new RBTree<Student*, long>();
    studentsTree->insert(std1, std1->getId());
    studentsTree->insert(std2, std2->getId());
    studentsTree->insert(std3, std3->getId());
    studentsTree->insert(std4, std4->getId());
    studentsTree->insert(std5, std5->getId());
    studentsTree->insert(std6, std6->getId());
    studentsTree->insert(std7, std7->getId());

    inputFromFile();

    QStringList courseList = {"Все","1","2","3","4"};
    ui->setupUi(this);
    ui->courseComboBox->addItems(courseList);
}

MainWindow::~MainWindow()
{
    saveToFile();
    delete ui;
}


/////////////////////////////////////////////////////////////////// FILE READ-WRITE ////////////////////////////////////////////////////////////////////


void MainWindow::addStud(QString l_name, QString f_name, QString m_name, QString email, long long tel_number, int entrance_year, long id_number, QString speciality, long group_number, int course, QString debt, double average_score)
{
    Student* tmp = new Student;

    tmp->setLName(l_name);
    tmp->setFName(f_name);
    tmp->setMName(m_name);
    tmp->setEmail(email);
    tmp->setTelNumber(tel_number);
    tmp->setId(id_number);
    if (debt == 't')
        tmp->setDebt(true);
    else
        tmp->setDebt(false);
    tmp->setGroupNumber(group_number);
    tmp->setCourse(course);
    tmp->setSpeciality(speciality);
    tmp->setEntranceYear(entrance_year);
    tmp->setAverageScore(average_score);

    studentsTree->insert(tmp, tmp->getId());
}

void MainWindow::addUnd(QString l_name, QString f_name, QString m_name, QString email, long long tel_number, int entrance_year, long id_number, QString speciality, long group_number, QString sc_work, int course, QString debt, double average_score)
{
    Undergraduate* tmp = new Undergraduate;

    tmp->setLName(l_name);
    tmp->setFName(f_name);
    tmp->setMName(m_name);
    tmp->setEmail(email);
    tmp->setTelNumber(tel_number);
    tmp->setId(id_number);
    if (debt == 't')
        tmp->setDebt(true);
    else
        tmp->setDebt(false);
    tmp->setGroupNumber(group_number);
    tmp->setCourse(course);
    tmp->setSpeciality(speciality);
    tmp->setResWork(sc_work);
    tmp->setEntranceYear(entrance_year);
    tmp->setAverageScore(average_score);

    undergraduatesTree->insert(tmp, tmp->getId());
}

void MainWindow::inputFromFile()
{
    QFile file_stud("D:\\MyCourseProject\\Students.txt");
    if (file_stud.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream out(&file_stud);
        while (!out.atEnd())
        {
            QString str = out.readLine();
            QStringList list = str.split("#");
            addStud(list[0], list[1], list[2], list[3], list[4].toLong(), list[5].toInt(), list[6].toLong(),
                  list[7], list[8].toLong(), list[9].toInt(), list[10], list[11].toDouble());
        }
    }
    file_stud.close();

    QFile file_und("D:\\MyCourseProject\\Undergraduates.txt");
    if (file_und.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream out(&file_und);
        while (!out.atEnd())
        {
            QString str = out.readLine();
            QStringList list = str.split("#");
            addUnd(list[0], list[1], list[2], list[3], list[4].toLong(), list[5].toInt(), list[6].toLong(),
                  list[7], list[8].toLong(), list[9], list[10].toInt(), list[11], list[12].toDouble());
        }
    }
    file_und.close();

    /*QFile file_dean("D:\\MyCourseProject\\Deanery.txt");
    if (file_dean.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream out(&file_dean);
        while (!out.atEnd())
        {
            QString str = out.readLine();
            QStringList list = str.split("#");
            addUnd(list[0], list[1], list[2], list[3], list[4].toLong(), list[5].toInt(), list[6].toLong(),
                  list[7], list[8].toLong(), list[9], list[10].toInt(), list[11], list[12].toDouble());
        }
    }
    file_dean.close();*/
}

void MainWindow::saveToFile()
{
    QFile file_stud("D:\\MyCourseProject\\Students.txt");
    if (file_stud.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream outstream_stud(&file_stud);
        RBIterator<Student*, long> it;
        it = it.begin(studentsTree, studentsTree->getRoot());
        for (; it != it.end(studentsTree, studentsTree->getRoot()); it++)
        {
            QString debt_str = "";
            if ((*it)->getDebt() == true) debt_str = 't';
            else debt_str = 'f';
            outstream_stud << (*it)->getLName() << "#" << (*it)->getFName() << "#" << (*it)->getMName() << "#" << (*it)->getEmail() << "#" <<
            (*it)->getTelNumber() << "#" << (*it)->getEntranceYear() << "#" << (*it)->getId() << "#" << (*it)->getSpeciality() << "#" <<
                  (*it)->getGroupNumber() << "#" << (*it)->getCourse() << "#" << debt_str << "#" << (*it)->getAverageScore() << "\n";
        }
    }
    file_stud.close();

    QFile file_und("D:\\MyCourseProject\\Undergraduates.txt");
    if (file_und.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream outstream_und(&file_und);
        RBIterator<Undergraduate*, long> it;
        it = it.begin(undergraduatesTree, undergraduatesTree->getRoot());
        for (; it != it.end(undergraduatesTree, undergraduatesTree->getRoot()); it++)
        {
            QString debt_str = "";
            if ((*it)->getDebt() == true) debt_str = 't';
            else debt_str = 'f';
            outstream_und << (*it)->getLName() << "#" << (*it)->getFName() << "#" << (*it)->getMName() << "#" << (*it)->getEmail() << "#" <<
            (*it)->getTelNumber() << "#" << (*it)->getEntranceYear() << "#" << (*it)->getId() << "#" << (*it)->getSpeciality() << "#" <<
                  (*it)->getGroupNumber() << "#" << (*it)->getResWork() << "#" << (*it)->getCourse() << "#" << debt_str << "#" <<
                  (*it)->getAverageScore() << "\n";
        }
    }
    file_und.close();

    /*QFile file_dean("D:\\MyCourseProject\\Undergraduates.txt");
    if (file_dean.open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream outstream_und(&file_dean);
        RBIterator<Undergraduate*, long> it;
        it = it.begin(undergraduatesTree, undergraduatesTree->getRoot());
        for (; it != it.end(undergraduatesTree, undergraduatesTree->getRoot()); it++)
        {
            QString debt_str = "";
            if ((*it)->getDebt() == true) debt_str = 't';
            else debt_str = 'f';
            outstream_und << (*it)->getLName() << "#" << (*it)->getFName() << "#" << (*it)->getMName() << "#" << (*it)->getEmail() << "#" <<
            (*it)->getTelNumber() << "#" << (*it)->getEntranceYear() << "#" << (*it)->getId() << "#" << (*it)->getSpeciality() << "#" <<
                  (*it)->getGroupNumber() << "#" << (*it)->getResWork() << "#" << (*it)->getCourse() << "#" << debt_str << "#" <<
                  (*it)->getAverageScore() << "\n";
        }
    }
    file_dean.close();*/
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//сортировка таблицы
QList<Student*> MainWindow::sortStudents(){
    RBIterator<Student*, long> iterator;
    QList<Student*> sortedList;
    iterator = iterator.begin(studentsTree, studentsTree->getRoot());
    if (iterator.getNode() != nullptr) {
        while (iterator != iterator.end(studentsTree, studentsTree->getRoot())) {
            if (iterator.getNode() != nullptr) sortedList.append(*iterator);
            iterator++;
        }
    }
    //сортировка по наличию долга
    if(ui->noDebtRadioButton->isChecked()) {
       for(int i = 0; i < sortedList.length(); i++){
           if(sortedList.at(i)->getDebt()) {
               sortedList.removeAt(i);
               i--;
           }
       }
    } else if(ui->withDebtRadioButton->isChecked()) {
        for(int i = 0; i < sortedList.length(); i++) {
            if(!sortedList.at(i)->getDebt()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    //сортировка по ФИО, номеру группы, номеру студ. билета
    if(ui->nameSortRadioButton->isChecked()) {
        std::sort(sortedList.begin(),sortedList.end(), compareStudentsByName);
    } else if (ui->groupNumberSortRadioButton->isChecked()) {
        std::sort(sortedList.begin(),sortedList.end(), compareStudentsByGroupNumber);
    } else std::sort(sortedList.begin(),sortedList.end(), compareStudentsById);
    //сортровка комбо-бокса курса
    if(ui->courseComboBox->currentText() != "Все") {
        int neededCourse = ui->courseComboBox->currentText().toInt();
        for(int i = 0; i < sortedList.length(); i++){
            if(sortedList.at(i)->getCourse() != neededCourse ) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    //сортировка по чек-боксам специальностей
    if(!ui->poit1CheckBox_1->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->poit1CheckBox_1->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->vmsisCheckBox_2->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->vmsisCheckBox_2->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->iitpCheckBox_3->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->iitpCheckBox_3->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->avsCheckBox_4->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->avsCheckBox_4->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    iterator.~RBIterator();
    loadTable(sortedList);
    return sortedList;
}
QList<Undergraduate*> MainWindow::sortUndergraduates(){
    RBIterator<Undergraduate*, long> iterator;
    QList<Undergraduate*> sortedList;
    iterator = iterator.begin(undergraduatesTree, undergraduatesTree->getRoot());
    if (iterator.getNode() != nullptr) {
        while (iterator != iterator.end(undergraduatesTree, undergraduatesTree->getRoot())) {
            if (iterator.getNode() != nullptr) sortedList.append(*iterator);
            iterator++;
        }
    }
    //сортировка по наличию долга
    if(ui->noDebtRadioButton->isChecked()) {
       for(int i = 0; i < sortedList.length(); i++){
           if(sortedList.at(i)->getDebt()) {
               sortedList.removeAt(i);
               i--;
           }
       }
    } else if(ui->withDebtRadioButton->isChecked()) {
        for(int i = 0; i < sortedList.length(); i++) {
            if(!sortedList.at(i)->getDebt()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    //сортировка по ФИО, номеру группы, номеру студ. билета
    if(ui->nameSortRadioButton->isChecked()) {
        std::sort(sortedList.begin(),sortedList.end(), compareUndergraduatesByName);
    } else if (ui->groupNumberSortRadioButton->isChecked()) {
        std::sort(sortedList.begin(),sortedList.end(), compareUndergraduatesByGroupNumber);
    } else std::sort(sortedList.begin(),sortedList.end(), compareUndergraduatesById);
    //сортровка комбо-бокса курса
    if(ui->courseComboBox->currentText() != "Все") {
        int neededCourse = ui->courseComboBox->currentText().toInt();
        for(int i = 0; i < sortedList.length(); i++){
            if(sortedList.at(i)->getCourse() != neededCourse ) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    //сортировка по чек-боксам специальностей
    if(!ui->aiuvtisuCheckBox_5->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->aiuvtisuCheckBox_5->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->vmisCheckBox_6->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->vmisCheckBox_6->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->mmchmikpCheckBox_7->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->mmchmikpCheckBox_7->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->mipovmkiksCheckBox_8->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->mipovmkiksCheckBox_8->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->iitrpoCheckBox_9->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->iitrpoCheckBox_9->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->tviovCheckBox_10->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->tviovCheckBox_10->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    if(!ui->oboiCheckBox_11->isChecked()){
        for (int i = 0; i < sortedList.size(); i++) {
            if(sortedList.at(i)->getSpeciality() == ui->oboiCheckBox_11->text()) {
                sortedList.removeAt(i);
                i--;
            }
        }
    }
    iterator.~RBIterator();
    loadTable(sortedList);
    return sortedList;
}

void MainWindow::searchStudent(){
    QList<Student*> list = sortStudents();
    QString searchQuery = ui->searchLineEdit->text();
    if(searchQuery.isEmpty()) loadTable(list);
    else {
        QRegExp searchQueryReg("(.+\\s)?" + searchQuery.toLower() + "(.+)?");
        QRegExp groupNumberReg("^\\d{6}$");
        QRegExp idNumberReg("^\\d{8}$");
        QRegExp nameReg("([a-zA-Zа-яА-Я]([\\s\\-])?)+");
        if (groupNumberReg.exactMatch(searchQuery)){
            printf("group number\n");
                for(int i = 0; i< list.size(); i++){
            if (list.at(i)->getGroupNumber() != searchQuery.toLong()){
                    list.removeAt(i);
                    i--;
                }
            }
        }
        else if (idNumberReg.exactMatch(searchQuery)){
            printf("id number\n");
            list.clear();
            Node<Student*, long> *foundNode = studentsTree->find(searchQuery.toLong());
            if(foundNode != nullptr) list.append(foundNode->getData());
        }
        else if(nameReg.exactMatch(searchQuery)){
            printf("name\n");
            for(int i = 0; i< list.size(); i++){
                if (!searchQueryReg.exactMatch(list.at(i)->getLName().toLower() + " " + list.at(i)->getFName().toLower() + " " +list.at(i)->getMName().toLower())){
                    list.removeAt(i);
                    i--;
                }
            }
        }
        else printf("some shit");
        loadTable(list);
    }
    list.clear();
    list.~QList();
}

void MainWindow::searchUndergraduate(){
    QList<Undergraduate*> list = sortUndergraduates();
    QString searchQuery = ui->searchLineEdit->text();
    if(searchQuery.isEmpty()) loadTable(list);
    else {
        QRegExp searchQueryReg("(.+\\s)?" + searchQuery.toLower() + "(.+)?");
        QRegExp groupNumberReg("\\d{6}$");
        QRegExp idNumberReg("\\d{8}$");
        QRegExp nameReg("([a-zA-Zа-яА-Я]([\\s\\-])?)+");
        if (groupNumberReg.exactMatch(searchQuery)){
            printf("group number\n");
                for(int i = 0; i< list.size(); i++){
            if (list.at(i)->getGroupNumber() != searchQuery.toLong()){
                    list.removeAt(i);
                    i--;
                }
            }
        }
        else if (idNumberReg.exactMatch(searchQuery)){
            printf("id number\n");
            list.clear();
            Node<Undergraduate*, long> *foundNode = undergraduatesTree->find(searchQuery.toLong());
            if(foundNode != nullptr) list.append(foundNode->getData());
        }
        else if(nameReg.exactMatch(searchQuery)){
            printf("name\n");
            for(int i = 0; i< list.size(); i++){
                if (!searchQueryReg.exactMatch(list.at(i)->getLName().toLower() + " " + list.at(i)->getFName().toLower() + " " +list.at(i)->getMName().toLower())){
                    list.removeAt(i);
                    i--;
                }
            }
        }
        else printf("some shit");
        loadTable(list);
    }
    list.clear();
    list.~QList();
}

bool MainWindow::compareStudentsByName(const Student *s1, const Student *s2){
    return s1->getLName() + s1->getFName() + s1->getMName() < s2->getLName() + s2->getFName() + s2->getMName();
}

bool MainWindow::compareStudentsByGroupNumber(const Student *s1, const Student *s2){
    return s1->getGroupNumber() < s2->getGroupNumber();
}

bool MainWindow::compareStudentsById(const Student *s1, const Student *s2){
    return s1->getId() < s2->getId();
}
bool MainWindow::compareUndergraduatesByName(const Undergraduate *s1, const Undergraduate *s2) {
    return s1->getLName() + s1->getFName() + s1->getMName() < s2->getLName() + s2->getFName() + s2->getMName();
}

bool MainWindow::compareUndergraduatesByGroupNumber(const Undergraduate *s1, const Undergraduate *s2) {
    return s1->getGroupNumber() < s2->getGroupNumber();
}

bool MainWindow::compareUndergraduatesById(const Undergraduate *s1, const Undergraduate *s2) {
    return s1->getId() < s2->getId();
}

void MainWindow::loadTable(QList<Student*> list) {
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    QFont *font = new QFont("Times New Roman", 10, 1);
    horizontalHeader.append("Номер группы");
    horizontalHeader.append("                          ФИО студента                          ");
    horizontalHeader.append("Номер студ. билета    ");
    QString str;
    model->setHorizontalHeaderLabels(horizontalHeader);
    QStringList verticalHeader;
    if(!list.isEmpty()) {
        for (int i = 0; i < list.length(); i++) {
            item = new QStandardItem(str.setNum(list.at(i)->getGroupNumber()));
            model->setItem(i,0,item);
            item = new QStandardItem(list.at(i)->getLName()+" "+list.at(i)->getFName()+" "+list.at(i)->getMName());
            model->setItem(i,1,item);
            item = new QStandardItem(str.setNum(list.at(i)->getId(),10));
            model->setItem(i,2,item);
        }
    }
    model->setVerticalHeaderLabels(verticalHeader);
    ui->tableView->setFont(*font);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::loadTable(QList<Undergraduate*> list) {
    QStandardItemModel *model = new QStandardItemModel;
    QStandardItem *item;
    QStringList horizontalHeader;
    QFont *font = new QFont("Times New Roman", 10, 1);
    horizontalHeader.append("   Номер группы   ");
    horizontalHeader.append("                       ФИО студента                        ");
    horizontalHeader.append("   Номер студ. билета    ");
    QString str;
    model->setHorizontalHeaderLabels(horizontalHeader);
    QStringList verticalHeader;
    if(!list.isEmpty()) {
        for (int i = 0; i < list.length(); i++) {
            item = new QStandardItem(str.setNum(list.at(i)->getGroupNumber()));
            model->setItem(i,0,item);
            item = new QStandardItem(list.at(i)->getLName()+" "+list.at(i)->getFName()+" "+list.at(i)->getMName());
            model->setItem(i,1,item);
            item = new QStandardItem(str.setNum(list.at(i)->getId(),10));
            model->setItem(i,2,item);
        }
    }
    model->setVerticalHeaderLabels(verticalHeader);
    ui->tableView->setFont(*font);
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->resizeColumnsToContents();
}

void MainWindow::on_courseComboBox_currentTextChanged(const QString &arg1)
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_allDebtRadioButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_withDebtRadioButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_noDebtRadioButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_nameSortRadioButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_groupNumberSortRadioButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_idNumberRadioButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) sortStudents();
    else sortUndergraduates();
}

void MainWindow::on_searchPushButton_clicked()
{
    if(ui->studentsRadioButton->isChecked()) searchStudent();
    else searchUndergraduate();
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QModelIndex neededIndex = ui->tableView->model()->index(index.row(), 2);
    long id = ui->tableView->model()->data(neededIndex).toLongLong();
    StudentInformation *w = new StudentInformation(nullptr, id, ui->studentsRadioButton->isChecked(), studentsTree, undergraduatesTree);
    w->setFixedSize(800, 535);
    w->setModal(true);
    if(ui->studentsRadioButton->isChecked()) w->setWindowTitle("Окно студента");
    else w->setWindowTitle("Окно магистранта");
    w->exec();
    if(ui->studentsRadioButton->isChecked()) searchStudent();
    else searchUndergraduate();
}


void MainWindow::on_studentsRadioButton_clicked(bool checked)
{
    if (checked){
        ui->aiuvtisuCheckBox_5->setChecked(false);
        ui->aiuvtisuCheckBox_5->setCheckable(false);
        ui->vmisCheckBox_6->setChecked(false);
        ui->vmisCheckBox_6->setCheckable(false);
        ui->mmchmikpCheckBox_7->setChecked(false);
        ui->mmchmikpCheckBox_7->setCheckable(false);
        ui->mipovmkiksCheckBox_8->setChecked(false);
        ui->mipovmkiksCheckBox_8->setCheckable(false);
        ui->iitrpoCheckBox_9->setChecked(false);
        ui->iitrpoCheckBox_9->setCheckable(false);
        ui->tviovCheckBox_10->setChecked(false);
        ui->tviovCheckBox_10->setCheckable(false);
        ui->oboiCheckBox_11->setChecked(false);
        ui->oboiCheckBox_11->setCheckable(false);

        ui->poit1CheckBox_1->setCheckable(true);
        ui->poit1CheckBox_1->setChecked(true);
        ui->vmsisCheckBox_2->setCheckable(true);
        ui->vmsisCheckBox_2->setChecked(true);
        ui->iitpCheckBox_3->setCheckable(true);
        ui->iitpCheckBox_3->setChecked(true);
        ui->avsCheckBox_4->setCheckable(true);
        ui->avsCheckBox_4->setChecked(true);
    }
    ui->courseComboBox->insertItem(3, "3");
    ui->courseComboBox->insertItem(4, "4");
    sortStudents();
}

void MainWindow::on_mastersRadioButton_clicked(bool checked)
{
    if (checked){
        ui->poit1CheckBox_1->setChecked(false);
        ui->poit1CheckBox_1->setCheckable(false);
        ui->vmsisCheckBox_2->setChecked(false);
        ui->vmsisCheckBox_2->setCheckable(false);
        ui->iitpCheckBox_3->setChecked(false);
        ui->iitpCheckBox_3->setCheckable(false);
        ui->avsCheckBox_4->setChecked(false);
        ui->avsCheckBox_4->setCheckable(false);

        ui->aiuvtisuCheckBox_5->setCheckable(true);
        ui->aiuvtisuCheckBox_5->setChecked(true);
        ui->vmisCheckBox_6->setCheckable(true);
        ui->vmisCheckBox_6->setChecked(true);
        ui->mmchmikpCheckBox_7->setCheckable(true);
        ui->mmchmikpCheckBox_7->setChecked(true);
        ui->mipovmkiksCheckBox_8->setCheckable(true);
        ui->mipovmkiksCheckBox_8->setChecked(true);
        ui->iitrpoCheckBox_9->setCheckable(true);
        ui->iitrpoCheckBox_9->setChecked(true);
        ui->tviovCheckBox_10->setCheckable(true);
        ui->tviovCheckBox_10->setChecked(true);
        ui->oboiCheckBox_11->setCheckable(true);
        ui->oboiCheckBox_11->setChecked(true);
    }
    ui->courseComboBox->removeItem(3);
    ui->courseComboBox->removeItem(3);
    sortUndergraduates();
}


void MainWindow::on_poit1CheckBox_1_stateChanged(int arg1)
{
    sortStudents();
}

void MainWindow::on_vmsisCheckBox_2_stateChanged(int arg1)
{
    sortStudents();
}


void MainWindow::on_iitpCheckBox_3_stateChanged(int arg1)
{
    sortStudents();
}

void MainWindow::on_avsCheckBox_4_stateChanged(int arg1)
{
    sortStudents();
}


void MainWindow::on_aiuvtisuCheckBox_5_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_vmisCheckBox_6_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_mmchmikpCheckBox_7_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_mipovmkiksCheckBox_8_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_iitrpoCheckBox_9_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_tviovCheckBox_10_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_oboiCheckBox_11_stateChanged(int arg1)
{
    sortUndergraduates();
}

void MainWindow::on_addPushButton_clicked()
{
    AddingWindow *w = new AddingWindow(nullptr, ui->studentsRadioButton->isChecked(), studentsTree, undergraduatesTree);
    w->setFixedSize(800, 535);
    w->setModal(true);
    if(ui->studentsRadioButton->isChecked()) w->setWindowTitle("Добавление студента");
    else w->setWindowTitle("Добавление магистранта");
    w->exec();
    if(ui->studentsRadioButton->isChecked()) searchStudent();
    else searchUndergraduate();
}

void MainWindow::on_viewPushButton_clicked()
{
    AddWindowDeanery *w = new AddWindowDeanery(nullptr, deanery);
    w->setFixedSize(400, 300);
    w->setModal(true);
    w->setWindowTitle("Деканат");
    w->exec();
}
