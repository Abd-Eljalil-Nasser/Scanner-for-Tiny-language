#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTextEdit>
#include<QLabel>
#include<QPushButton>
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void setputUi();
  private slots:
    void button_clicked();
    void clear();
     private:
     QTextEdit * inputbox;
     QTextEdit *output;
     QLabel * label;
     QLabel  *inputlabel;
     QLabel  *outputlabel;
     QPushButton * submit;


};

#endif // WIDGET_H
