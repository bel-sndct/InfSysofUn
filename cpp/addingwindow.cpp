#include "addingwindow.h"
#include "ui_addingwindow.h"

AddingWindow::AddingWindow(QWidget *parent, bool isStudent, RBTree<Student*, long> *studentsTree, RBTree<Undergraduate*, long> *undergraduatesTree) :
    QDialog(parent),
    ui(new Ui::AddingWindow)
{
    this->isStudent = isStudent;
    this->studentsTree = studentsTree;
    this->undergraduatesTree = undergraduatesTree;
    ui->setupUi(this);
    if(isStudent) {
        ui->sctWorkLabel->hide();
        ui->sctWorkLineEdit->hide();
        QStringList list = {"1", "2", "3", "4"};
        ui->courseComboBox->addItems(list);
        ui->specialityComboBox->addItem("ПОИТ");
        ui->specialityComboBox->addItem("ВМСиС");
        ui->specialityComboBox->addItem("ИиТП");
        ui->specialityComboBox->addItem("ЭВС");
    } else {
        ui->courseComboBox->addItem("1");
        ui->courseComboBox->addItem("2");
        ui->specialityComboBox->addItem("ЭиУВТиСУ");
        ui->specialityComboBox->addItem("ВМиС");
        ui->specialityComboBox->addItem("ММЧМиКП");
        ui->specialityComboBox->addItem("МиПОВМКиКС");
        ui->specialityComboBox->addItem("ИиТРПО");
        ui->specialityComboBox->addItem("ТВиОВ");
        ui->specialityComboBox->addItem("ОБОИ");
    }

}

AddingWindow::~AddingWindow()
{
    delete ui;
}

void AddingWindow::on_addPushButton_clicked()
{
    QRegExp nameReg("^([a-zA-Zа-яА-Я])+(\\-)?([a-zA-Zа-яА-Я])+(\\s)?$");
    QRegExp telNumberReg("^(\\+)?\\d{3}(\\()?\\d{2}(\\))?\\d{7}$");
    QRegExp emailReg("^([a-zA-Z\\.\\-\\_\\d])+@([a-zA-Z\\.\\-\\_\\d])+$");
    QRegExp idNumberReg("^\\d{8}$");
    QRegExp groupNumberReg("^\\d{6}$");
    QRegExp averageScoreReg("^\\d{1}\\.(\\d)+$");
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
        QString currentCourse = ui->courseComboBox->currentText();
        QString currentSpeciality = ui->specialityComboBox->currentText();
        while (iterator != iterator.end(studentsTree, studentsTree->getRoot())) {
            if(iterator.getNode()->getData()->getCourse() != currentCourse || iterator.getNode()->getData()->getSpeciality() != currentSpeciality) list.append(iterator.getNode()->getData()->getGroupNumber());
            iterator++;
        }
        long input = ui->groupNumberLineEdit->text().toLong();
        for (int i = 0; i < list.size(); i++) {
            if (list.at(i) == input){
                QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера группы");
                return;
            }
        }
        Node<Student*, long> *foundNode = studentsTree->find(ui->idLineEdit->text().toLong());
        if(foundNode != nullptr) {
            QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nВведён уже существующий номер студ. билета");
            return;
        }
        Student* newStudent = new Student();
        newStudent->setLName(ui->lNameLineEdit->text());
        newStudent->setFName(ui->fNameLineEdit->text());
        newStudent->setMName(ui->mNameLineEdit->text());
        newStudent->setTelNumber(ui->telNumberLineEdit->text().toLongLong());
        newStudent->setEmail(ui->emailLineEdit->text());

        newStudent->setEntranceYear(ui->entranceLineEdit->text().toInt());
        newStudent->setCourse(ui->courseComboBox->currentText().toInt());
        newStudent->setSpeciality(ui->specialityComboBox->currentText());
        newStudent->setGroupNumber(ui->groupNumberLineEdit->text().toLong());
        newStudent->setAverageScore(ui->averageScoreLineEdit->text().toDouble());
        newStudent->setDebt(ui->debtRadioButton->isChecked());
        newStudent->setId(ui->idLineEdit->text().toLong());

        studentsTree->insert(newStudent, newStudent->getId());
    } else {
        RBIterator<Undergraduate*, long> iterator;
        QList<long> list;
        iterator = iterator.begin(undergraduatesTree, undergraduatesTree->getRoot());
        QString currentCourse = ui->courseComboBox->currentText();
        QString currentSpeciality = ui->specialityComboBox->currentText();
        while (iterator != iterator.end(undergraduatesTree, undergraduatesTree->getRoot())) {
            if(iterator.getNode()->getData()->getCourse() != currentCourse || iterator.getNode()->getData()->getSpeciality() != currentSpeciality) list.append(iterator.getNode()->getData()->getGroupNumber());
            iterator++;
        }
        long input = ui->groupNumberLineEdit->text().toLong();
        for (int i = 0; i < list.size(); i++) {
            if (list.at(i) == input){
                QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nПроверьте ввод номера группы");
                return;
            }
        }
        Node<Student*, long> *foundNode = studentsTree->find(ui->idLineEdit->text().toLong());
        if(foundNode != nullptr) {
            QMessageBox::warning(this, "Некорректный ввод","Введённые вами данные не являются корректными\nВведён уже существующий номер студ. билета");
            return;
        }
        Undergraduate* newUndergraduate = new Undergraduate();
        newUndergraduate->setLName(ui->lNameLineEdit->text());
        newUndergraduate->setFName(ui->fNameLineEdit->text());
        newUndergraduate->setMName(ui->mNameLineEdit->text());
        newUndergraduate->setTelNumber(ui->telNumberLineEdit->text().toLongLong());
        newUndergraduate->setEmail(ui->emailLineEdit->text());

        newUndergraduate->setEntranceYear(ui->entranceLineEdit->text().toInt());
        newUndergraduate->setCourse(ui->courseComboBox->currentText().toInt());
        newUndergraduate->setSpeciality(ui->specialityComboBox->currentText());
        newUndergraduate->setGroupNumber(ui->groupNumberLineEdit->text().toLong());
        newUndergraduate->setAverageScore(ui->averageScoreLineEdit->text().toDouble());
        newUndergraduate->setDebt(ui->debtRadioButton->isChecked());
        newUndergraduate->setId(ui->idLineEdit->text().toLong());
        newUndergraduate->setResWork(ui->sctWorkLineEdit->text());

        undergraduatesTree->insert(newUndergraduate, newUndergraduate->getId());
    }
    close();
}

void AddingWindow::on_backPushButton_clicked()
{
    close();
}
