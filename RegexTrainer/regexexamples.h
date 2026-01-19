#ifndef REGEXEXAMPLES_H
#define REGEXEXAMPLES_H

#include <QString>
#include <QVector>

struct RegexExample
{
    QString title;
    QString description;
    QString pattern;
    QString testText;
};

class RegexExamples
{
public:
    static QVector<RegexExample> examples();
};

#endif // REGEXEXAMPLES_H
