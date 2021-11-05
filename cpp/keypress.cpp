#include <QApplication>
#include <QKeyEvent>
#include "keypress.h"

KeyPress::KeyPress(QWidget *parent)
    : QWidget(parent)
{ }

void KeyPress::keyPressEvent(QKeyEvent *event) {
   if (event->key() == Qt::Key_Q && event->key() == Qt::Key_Control) {
       qApp->quit();
   }
}
