#include "mainwindow.h"
#include <QApplication>
#include <QtCore>
#include <QtXml>
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include <QGridLayout>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

void ListElements(QDomElement root, QString tagname, QString attribute, QVBoxLayout *vLayout){
    QDomNodeList items = root.elementsByTagName(tagname);

    qDebug() << "Total Items = " << items.count();

    for(int i = 0;i<items.count();i++){
        QDomNode itemNode = items.at(i);
        if(itemNode.isElement()){
            QDomElement itemElem = itemNode.toElement();
            QLabel *nameLabel = new QLabel();
            nameLabel->setText(itemElem.attribute("Name"));
            vLayout->addWidget(nameLabel);
            qDebug()<<itemElem.attribute(attribute);
        }
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);




    MainWindow w;

    w.setWindowTitle("Books");

    // set main Widget
    QWidget widget(&w);
    w.setCentralWidget(&widget);

    // init horizontal layout for main widget
    QHBoxLayout hLayout(&widget);

    //init vertical layout
    QVBoxLayout vLayout1;
    hLayout.addLayout(&vLayout1);

    QVBoxLayout vLayout2;
    hLayout.addLayout(&vLayout2);



    QDomDocument document;

    // Load the file
    QFile file("C:/Users/Garik/My Projects/test/qt/xml-reader/books.xml");

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug()<<"Failed to open file";
        return -1;
    }
    else {
        if(!document.setContent(&file))
        {
            qDebug()<<"Failed to load document";
            return -1;
        }
        file.close();
    }

    // get the root element
    QDomElement root = document.firstChildElement();

    // List the books
    ListElements(root,"Book","Name", &vLayout1);




    QDomNodeList items = root.elementsByTagName("Book");
    qDebug() << "Total Items = " << items.count();
    qDebug()<<"\r\nMore Advanced\r\n";

    // Get the chapters
    QDomNodeList books = root.elementsByTagName("Book");
    for(int i=0;i<books.count();i++){
        QDomNode bookNode = books.at(i);
        if(bookNode.isElement()){
            QDomElement book = bookNode.toElement();
            qDebug() << "\nChapters in " << book.attribute("Name") << "\n";
            QLabel *bookNameLabel = new QLabel();
            bookNameLabel->setText("Chapters in "+book.attribute("Name"));
            vLayout2.addWidget(bookNameLabel);
            ListElements(book, "Chapter", "Name", &vLayout2);
        }
    }

    qDebug()<<"Finished";

    w.show();
    return a.exec();
}
