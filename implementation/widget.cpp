#include "widget.h"
#include<QLayout>
#include<string>
#include<QString>
#include<iostream>
#include <QStack>
using std::string;
using std::cout;
using std::endl;
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setputUi();
}

Widget::~Widget()
{
    delete label;
    delete inputbox;
}
void Widget::setputUi()
{
       this->resize(800,800);
       //this->move(300,300);
       this->setWindowTitle("scanner");
       inputbox = new QTextEdit;
       output = new QTextEdit;
       inputbox->setMinimumSize(400,400);
       output->setMinimumSize(400,400);
       QHBoxLayout  *horizontal= new QHBoxLayout;
       QVBoxLayout  *vertical= new QVBoxLayout;
       QHBoxLayout * horizontalforbutton = new QHBoxLayout;
       QHBoxLayout * horizontalforlabels = new QHBoxLayout;
       label= new QLabel;
       //label->setText("scanner");
       label->setAlignment(Qt::AlignCenter);
       inputlabel  = new QLabel;
       outputlabel = new QLabel;
       inputlabel->setText("Input");
       outputlabel->setText("Output");
       submit = new QPushButton;
       submit->setText("submit");
       submit->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
       horizontalforlabels->addWidget(inputlabel);
       horizontalforlabels->addWidget(outputlabel);
       horizontal->addWidget(inputbox);
       horizontal->addWidget(output);
       //horizontal->addWidget(submit);
       horizontal->addStretch();
       horizontal->setStretchFactor(output,1);
       horizontal->setStretchFactor(inputbox,1);
       horizontalforbutton->addWidget(submit);
       horizontalforbutton->setAlignment(Qt::AlignCenter);
       //vertical->addWidget(label);
       vertical->addLayout(horizontalforlabels);
       vertical->addLayout(horizontal);
       vertical->addLayout(horizontalforbutton);
       vertical->addLayout(horizontalforlabels);
       vertical->addStretch();
      // vertical->setStretchFactor(label,1);
       vertical->setStretchFactor(horizontal,1);
       vertical->setStretchFactor(submit,1);
       vertical->setAlignment(Qt::AlignRight);
       this->setLayout(vertical);
       connect(submit,SIGNAL(clicked()),this,SLOT(button_clicked()));
       connect(inputbox,SIGNAL(textChanged()),this,SLOT(clear()));

}
void Widget::button_clicked()
{
    QStack<int> x;
    output->clear();
    QString reservedWords[8] = {"if","then","else","end","repeat","until","read","write"};
    QString specialSymbols[10] = {"+","-","*","/","=","<","(",")",";",":="};
    QString symbolName[10] = {"Plus","Minus","Multiply","Division","Equal","Smaller than","Open Bracket","Close Bracket","Semicolon","Assign"};
    QString id = "";
    QString num = "";
    int lineCount = 1;
  QString input = inputbox->toPlainText();
  QString outputtext ="";
  for(int i =0 ; i < input.length() ; i++)
  {
      if (input[i]=="{")
      {
          int f=0;
          i++;
          x.push(i);
          while (i <input.length())
          {
              if (input[i] !='}' && input[i] !='{')
              {
                  if (input[i] == '\n')
                  {
                      lineCount++;
                  }
                  i++;
              }
              else if (input[i] =='{')
              {
                  x.push(i);
                  i++;
              }
              else
              {
                  x.pop();
                  i++;
                  if (x.empty()==true)
                  {
                      i--;
                      f=1;
                      break;
                  }
              }
          }
          if (i==input.length() && x.empty()==false)
          {
              outputtext = outputtext+"Error on line "+QString::number(lineCount)+ "comment isn't closed";
              output->setText(outputtext);
              return;
          }
          if (f==1)
              continue;
      }
      if (i ==input.length())
      {
          break;
      }
      if(i < input.length()&& input[i] == '\n')
                    {
                      lineCount++;
                      continue;
                    }

      int flag=0;
          if ( (input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))
          {
          id = "";
          while (i < input.length())
          {
              if (( input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))
              {
              id = id+input[i];
              i++;
              }
              else
              {
              if (input[i].isDigit())
              {
                  outputtext = outputtext+"Error on line "+QString::number(lineCount);
                  output->setText(outputtext);
                  return;
              }
              break;
              }
          }
          for (int r = 0; r < 8 ; r++)
          {
              if (id == reservedWords[r])
              {
              QString tempid = id;
              for(int d = 0 ; d < tempid.length() ; d++)
                    {
               tempid[d]=static_cast<QChar>(tempid.at(d).unicode()-32);
                    }
              //cout << id << " , " << tempid << endl;
               outputtext = outputtext+ id+" , " +tempid+" "+"\n";
              id = "";
              flag=1;
              break;
              }
           }

          if (id != "")
              {
            // cout << id <<" , " << "Identifier" << endl;
              outputtext = outputtext+id+" , " + "Identifier"+" "+"\n";
              id = "";
              i--;
              continue;
              }
          else if(flag==1)
          {
              i--;
              continue;
          }
          }

              while (i < input.length())
              {
              if(input[i].isDigit())
                 {
              num += input[i];
              i++;
              flag=1;
                 }
              else
                 {
                   if ((input[i] > 64 && input[i] < 91) || (input[i] > 96 && input[i] < 123))
                   {
                       outputtext = outputtext+"Error on line "+QString::number(lineCount);
                       output->setText(outputtext);
                       return;
                   }
                    break;
                 }
              }
              if (flag==1)
              {
                  //cout << num <<" , " << "Number" << endl;
                  outputtext = outputtext+num+" , " + "Number"+" "+"\n";
                  num = "";
                  i--;
                  continue;
              }
              if (input[i]==":" && i<input.length()-1)
              {
                  if (input[i+1]=="=")
                  {
                    outputtext = outputtext+":=" +" , " + "Assign"+" "+"\n";
                    i++;
                    continue;
                  }
                  else
                  {
                      outputtext = outputtext+"Error on line "+QString::number(lineCount);
                      output->setText(outputtext);
                      return;
                  }
              }
              else
              {
               for (int r = 0; r < 9 ; r++)
               {
                   if (input[i]==specialSymbols[r])
                   {
                    outputtext = outputtext+specialSymbols[r]+" , " +symbolName[r]+" "+"\n";
                    flag=1;
                    break;
                   }
               }
               if (flag==1)
               {
                   continue;
               }
               else
               {
                   if (input[i]==" ")
                   {
                       continue;
                   }
                   outputtext = outputtext+"Error on line "+QString::number(lineCount);
                   output->setText(outputtext);
                   return;
               }
              }
  }
  output->setText(outputtext);
}
void Widget::clear()
{
    output->clear();
}

