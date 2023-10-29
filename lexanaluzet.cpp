#include "lexanaluzet.h"

LexAnaluzet::LexAnaluzet(QObject *parent)
    : QObject{parent}
{

}


 QList<LexAnaluzet::LEX> LexAnaluzet::startAnalaze(QString data)
{
    QList<LEX> lexlist;
    QString* cleanStrime = new QString(data);
    cleanStrime->push_back('\n');
    strtoke = 0;
    while (cleanStrime->length() > 0) {
      lexlist.push_back( getLexem(cleanStrime) );
    }
    return lexlist;
}

enum StateMshine {
  Start,
  Identificator,
  Number,
  String,
  RMove,
  LMove,
  AsigmentOper,
};

LexAnaluzet::LEX LexAnaluzet::getLexem(QString* data)
{
  StateMshine state = Start;
  LexAnaluzet::LEX lex;
  QString buf;
  bool off = false;
  int MoveIncriment = 0;

  while ((data->length() > 0) && !off) {
     char c = data->at(0).toLatin1();
     data->remove(0,1);
     switch (state) {
         case Start:
            if ( c == ' ' || c == '\r' ||c == '\t' ){/* Ignore this */}
            if ( c == '\n' ){ strtoke++; }
            else
            if (isalpha(c)) {buf.push_back(c); state = Identificator; }
            else
            if (isdigit(c)) {buf.push_back(c); state = Number; }
            else
            if (c == '>') {buf.push_back(c); state = RMove; }
            else
            if (c == '<') {buf.push_back(c); state = LMove; }
            else
            if (c == ';')
            {
                buf.push_back(c); lex.lexClass = ENDL; lex.name = buf; off = true;
            }
            else
            if (c == '{' || c == '}' ) {buf.push_back(c); lex.lexClass = DefineSumbols; lex.name = buf; off = true;}
            else
            if (c == '+' || c == '-' ) {buf.push_back(c); state = AsigmentOper;}
            else
            if (c == '=') {buf.push_back(c); lex.lexClass = AsigmentOperator; lex.name = buf; off = true;}
            else
            if (c == '!' || c == '~') {buf.push_back(c); lex.lexClass = UnariSumbols; lex.name = buf; off = true;}
            else
            if (c == '"') {buf.push_back(c); state = String;}
         break;
         case Identificator:
          if(delimeters.contains(c))
            { data->push_front(c);
              if ( buf == "delite" || buf == "void" || buf == "typeof" ) {
                  lex.lexClass = DefineSumbols; lex.name = buf; off = true;
              } else {
                  lex.lexClass = ID; lex.name = buf; off = true;
              }
            }
          else
            { buf.push_back(c); }
         break;
         case LMove:
            if( (c == '<' || c == '=' ) && MoveIncriment == 0){ buf.push_back(c);  MoveIncriment++; }
            else
            if(c == '=' && MoveIncriment == 1){MoveIncriment = 0; buf.push_back(c); lex.lexClass = AsigmentOperator; lex.name = buf; off = true;}
            else
            if(MoveIncriment == 1 && buf.endsWith('<')) {data->push_front(c); MoveIncriment = 0; lex.lexClass = Expresion; lex.name = buf; off = true; }
            else
            if(MoveIncriment == 1 && buf.endsWith('=')) {data->push_front(c); MoveIncriment = 0; lex.lexClass = Comparison; lex.name = buf; off = true; }
            else
            { data->push_front(c); MoveIncriment = 0; lex.lexClass = Comparison; lex.name = buf; off = true; }
         break;
         case RMove:
            if( (c == '>' || c == '=' ) && MoveIncriment == 0 ){ buf.push_back(c);  MoveIncriment++; }
            else
            if(c == '=' && MoveIncriment == 1){MoveIncriment = 0; buf.push_back(c); lex.lexClass = AsigmentOperator; lex.name = buf; off = true;}
            else
            if(MoveIncriment == 1 && buf.endsWith('>')) {data->push_front(c); MoveIncriment = 0; lex.lexClass = Expresion; lex.name = buf; off = true; }
            else
            if(MoveIncriment == 1 && buf.endsWith('=')) {data->push_front(c); MoveIncriment = 0; lex.lexClass = Comparison; lex.name = buf; off = true; }
            else
            { data->push_front(c); MoveIncriment = 0; lex.lexClass = Comparison; lex.name = buf; off = true; }
         break;
     }
  }

  lex.striceNum = strtoke;

  return lex;
}

QString LexAnaluzet::getName(LexClass name)
{
    switch (name) {
       case AsigmentOperator: return "AsigmentOperator"; // = *= += -= <<= >>= >>>=
       case MultoplocativeOperator: return "MultoplocativeOperator"; // * / %
       case AdetiveOperator: return "AdetiveOperator";   // + - ++ --
       case DefineSumbols: return "DefineSumbols";    // delite void typeof { }
       case UnariSumbols: return "UnariSumbols";     // ! ~
       case Expresion: return "Expresion";     // >> << >>>
       case Comparison: return "Comparison";     // >> << >>>
       case ID: return "ID";       // Indetificator
       case INT: return "INT";     // 12
       case FLOAT: return "FLOAT";  // 12.23 12.1E-3
       case STRING: return "STRING"; // " ... "
       case ENDL: return "ENDL"; // ;
       case Error: return "Error"; // erroro status
    }
    return "No name";
}

