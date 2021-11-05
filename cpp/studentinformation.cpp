#include "studentinformation.h"
#include "ui_studentinformation.h"

StudentInformation::StudentInformation(QWidget *parent, long id, bool isStudent, RBTree<Student*, long> *studentsTree, RBTree<Undergraduate*, long> *undergraduatesTree) :
    QDialog(parent),
    ui(new Ui::StudentInformation)
{
    this->studentsTree = studentsTree;
    this->undergraduatesTree = undergraduatesTree;
    currentId = id;
    this->isStudent = isStudent;
    ui->setupUi(this);
    QString str;
    if(isStudent) {
        Student *current = studentsTree->find(currentId)->getData();
        currentSpeciality = current->getSpeciality();
        ui->lNameLineEdit->setText(current->getLName());
        ui->fNameLineEdit->setText(current->getFName());
        ui->mNameLineEdit->setText(current->getMName());
        ui->telNumberLineEdit->setText(str.setNum(current->getTelNumber()));
        ui->emailLineEdit->setText(current->getEmail());
        ui->courseComboBox->addItem("1");
        ui->courseComboBox->addItem("2");
        ui->courseComboBox->addItem("3");
        ui->courseComboBox->addItem("4");
        ui->courseComboBox->setCurrentText(str.setNum(current->getCourse()));
        ui->specialityComboBox->addItem("ПОИТ");
        ui->specialityComboBox->addItem("ВМСиС");
        ui->specialityComboBox->addItem("ИиТП");
        ui->specialityComboBox->addItem("ЭВС");
        ui->specialityComboBox->setCurrentText(currentSpeciality);
        ui->groupNumberLineEdit->setText(str.setNum(current->getGroupNumber()));
        ui->idLineEdit->setText(str.setNum(current->getId()));
        ui->averageScoreLineEdit->setText(str.setNum(current->getAverageScore()));
        ui->entranceLineEdit->setText(str.setNum(current->getEntranceYear()));
        ui->debtRadioButton->setChecked(current->getDebt());
        ui->sctWorkLabel->hide();
        ui->sctWorkLineEdit->hide();
    } else {
        Undergraduate *current = undergraduatesTree->find(currentId)->getData();
        currentSpeciality = current->getSpeciality();
        ui->lNameLineEdit->setText(current->getLName());
        ui->fNameLineEdit->setText(current->getFName());
        ui->mNameLineEdit->setText(current->getMName());
        ui->telNumberLineEdit->setText(str.setNum(current->getTelNumber()));
        ui->emailLineEdit->setText(current->getEmail());
        ui->courseComboBox->addItem("1");
        ui->courseComboBox->addItem("2");
        ui->courseComboBox->setCurrentText(str.setNum(current->getCourse()));
        ui->specialityComboBox->addItem("ЭиУВТиСУ");
        ui->specialityComboBox->addItem("ВМиС");
        ui->specialityComboBox->addItem("ММЧМиКП");
        ui->specialityComboBox->addItem("МиПОВМКиКС");
        ui->specialityComboBox->addItem("ИиТРПО");
        ui->specialityComboBox->addItem("ТВиОВ");
        ui->specialityComboBox->addItem("ОБОИ");
        ui->specialityComboBox->setCurrentText(currentSpeciality);
        ui->groupNumberLineEdit->setText(str.setNum(current->getGroupNumber()));
        ui->idLineEdit->setText(str.setNum(current->getId()));
        ui->averageScoreLineEdit->setText(str.setNum(current->getAverageScore()));
        ui->entranceLineEdit->setText(str.setNum(current->getEntranceYear()));
        ui->debtRadioButton->setChecked(current->getDebt());
        ui->sctWorkLineEdit->setText(current->getResWork());
    }
}

StudentInformation::~StudentInformation()
{
    delete ui;
}

void StudentInformation::on_deletePushButton_clicked()
{
    if(isStudent) {
        if (studentsTree->find(currentId) != studentsTree->getRoot()) {
            studentsTree->deleteNode(currentId);
        } else {
            studentsTree->root = studentsTree->createNewTree(studentsTree);
        }
    }
    else {
        if (undergraduatesTree->find(currentId) != undergraduatesTree->getRoot()) {
            undergraduatesTree->deleteNode(currentId);
        } else {
            undergraduatesTree->root = undergraduatesTree->createNewTree(undergraduatesTree);
        }
    }
    close();
}

void StudentInformation::on_backPushButton_clicked()
{
    close();
}

void StudentInformation::on_acceptPushButton_clicked()
{
    QRegExp nameReg("^([a-zA-Zа-яА-Я])+(\\-)?([a-zA-Zа-яА-Я])+(\\s)?$");
    QRegExp telNumberReg("^\\d{12}$");
    QRegExp emailReg("^([a-zA-Z\\.\\-\\_\\d])+@([a-zA-Z\\.\\-\\_\\d])+$");
    QRegExp idNumberReg("^\\d{8}$");
    QRegExp groupNumberReg("^\\d{6}$");
    QRegExp averageScoreReg("^\\d{1}\\.((\\d)+)?$");
    QRegExp yearReg("^\\d{4}$");
    if(!nameReg.exactMatch(ui->lNameLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод фамилии");
        return;
    }
    if(!nameReg.exactMatch(ui->fNameLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод имени");
        return;
    }
    if(!nameReg.exactMatch(ui->mNameLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод отчества");
        return;
    }
    if(!telNumberReg.exactMatch(ui->telNumberLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера телефона");
        return;
    }
    if(!emailReg.exactMatch(ui->emailLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод эл. почты");
        return;
    }
    if(!yearReg.exactMatch(ui->entranceLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод года поступления");
        return;
    } else {
        int year = ui->entranceLineEdit->text().toInt();
        if(year < 2016 || year > 2020) {
            QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод года поступления");
            return;
        }
    }
    if(!idNumberReg.exactMatch(ui->idLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера студ. билета");
        return;
    }
    if(!groupNumberReg.exactMatch(ui->groupNumberLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера группы");
        return;
    }
    if(!averageScoreReg.exactMatch(ui->averageScoreLineEdit->text())){
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод среднего балла");
        return;
    }
    if(isStudent){
        RBIterator<Student*, long> iterator;
        QList<long> list;
        iterator = iterator.begin(studentsTree, studentsTree->getRoot());
        QString newCourse = ui->courseComboBox->currentText();
        QString newSpeciality = ui->specialityComboBox->currentText();
        while (iterator != iterator.end(studentsTree, studentsTree->getRoot())) {
            if(iterator.getNode()->getData()->getCourse() != newCourse && iterator.getNode()->getData()->getSpeciality() != newSpeciality) list.append(iterator.getNode()->getData()->getGroupNumber());
            iterator++;
        }
        long input = ui->groupNumberLineEdit->text().toLong();
        for (int i = 0; i < list.size(); i++) {
            if (list.at(i) == input){
                QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера группы");
                return;
            }
        }
        if (currentId != ui->idLineEdit->text().toLong()){
            Node<Student*, long> *foundNode = studentsTree->find(ui->idLineEdit->text().toLong());
            if(foundNode != nullptr) {
                QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nВведён уже существующий номер студ. билета");
                return;
            }
        }
    } else {
        RBIterator<Undergraduate*, long> iterator;
        QList<long> list;
        iterator = iterator.begin(undergraduatesTree, undergraduatesTree->getRoot());
        QString newCourse = ui->courseComboBox->currentText();
        QString newSpeciality = ui->specialityComboBox->currentText();
        while (iterator != iterator.end(undergraduatesTree, undergraduatesTree->getRoot())) {
            if(iterator.getNode()->getData()->getCourse() != newCourse || iterator.getNode()->getData()->getSpeciality() != newSpeciality) list.append(iterator.getNode()->getData()->getGroupNumber());
            iterator++;
        }
        long input = ui->groupNumberLineEdit->text().toLong();
        for (int i = 0; i < list.size(); i++) {
            if (list.at(i) == input){
                QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера группы");
                return;
            }
        }
        if(currentId != ui->idLineEdit->text().toLong()) {
            Node<Student*, long> *foundNode = studentsTree->find(ui->idLineEdit->text().toLong());
            if(foundNode != nullptr) {
                QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nВведён уже существующий номер студ. билета");
                return;
            }
        }
    }
    if(currentSpeciality != ui->specialityComboBox->currentText() && ui->debtRadioButton->isChecked()) {
        QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nУчащегося с задолженностями нельзя перевести на другую специальность");
        return;
    }
    if(isStudent) {
        if (studentsTree->find(currentId) == studentsTree->getRoot()) {
            studentsTree->root = studentsTree->createNewTree(studentsTree);
        } else {
            studentsTree->deleteNode(currentId);
        }
        Student *newStudent = new Student();
        newStudent->setLName(ui->lNameLineEdit->text());
        newStudent->setFName(ui->fNameLineEdit->text());
        newStudent->setMName(ui->mNameLineEdit->text());
        newStudent->setTelNumber(ui->telNumberLineEdit->text().toLongLong());
        newStudent->setEmail(ui->emailLineEdit->text());

        newStudent->setId(ui->idLineEdit->text().toLong());
        newStudent->setAverageScore(ui->averageScoreLineEdit->text().toDouble());
        newStudent->setEntranceYear(ui->entranceLineEdit->text().toInt());
        newStudent->setCourse(ui->courseComboBox->currentText().toInt());
        newStudent->setSpeciality(ui->specialityComboBox->currentText());
        newStudent->setGroupNumber(ui->groupNumberLineEdit->text().toLong());
        newStudent->setDebt(ui->debtRadioButton->isChecked());
        studentsTree->insert(newStudent, newStudent->getId());
    } else {
        if (undergraduatesTree->find(currentId) != undergraduatesTree->getRoot()) {
            undergraduatesTree->deleteNode(currentId);
        } else {
            undergraduatesTree->root = undergraduatesTree->createNewTree(undergraduatesTree);
        }
        Undergraduate *newUndergraduate = new Undergraduate();
        newUndergraduate->setLName(ui->lNameLineEdit->text());
        newUndergraduate->setFName(ui->fNameLineEdit->text());
        newUndergraduate->setMName(ui->mNameLineEdit->text());
        newUndergraduate->setTelNumber(ui->telNumberLineEdit->text().toLongLong());
        newUndergraduate->setEmail(ui->emailLineEdit->text());

        newUndergraduate->setId(ui->idLineEdit->text().toLong());
        newUndergraduate->setAverageScore(ui->averageScoreLineEdit->text().toDouble());
        newUndergraduate->setEntranceYear(ui->entranceLineEdit->text().toInt());
        newUndergraduate->setCourse(ui->courseComboBox->currentText().toInt());
        newUndergraduate->setSpeciality(ui->specialityComboBox->currentText());
        newUndergraduate->setGroupNumber(ui->groupNumberLineEdit->text().toLong());
        newUndergraduate->setDebt(ui->debtRadioButton->isChecked());
        newUndergraduate->setResWork(ui->sctWorkLineEdit->text());
        undergraduatesTree->insert(newUndergraduate, newUndergraduate->getId());
    }
    close();
}
