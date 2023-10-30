#ifndef LEXANALUZET_H
#define LEXANALUZET_H

#include <QObject>
#include <QSet>
class LexAnaluzet : public QObject
{
    Q_OBJECT
public:
    enum LexClass {
        NUUL, // System lexem
        AsigmentOperator, // = *= += -= <<= >>= >>=
        MultoplocativeOperator, // * / %
        AdetiveOperator,   // + - ++ --
        DefineSumbols,    // delite void typeof { }
        UnariSumbols,     // ! ~
        Expresion,     // >> <<
        Comparison,     // <= >= < >
        ID,        // Indetificator
        INT,     // 12
        FLOAT,   // 12.23 12.1E-3
        STRING, // " ... "
        ENDL, // ;
        Error // erroro status
    };

    struct LEX {
        int striceNum = 0;
        QString name;
        LexClass lexClass = NUUL;
        QString value;
    };

    explicit LexAnaluzet(QObject *parent = nullptr);
    QList<LEX> startAnalaze(QString data);
    LEX getLexem(QString* data);
    QString getName(LexClass name);
private:
   int strtoke = 0;
   QSet<char> delimeters = {'=','+','-','!','>','<',';','*','/','%',' ','"','\n'};
};

#endif // LEXANALUZET_H
