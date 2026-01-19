#ifndef REGEXHELPER_H
#define REGEXHELPER_H

#include <QStringList>

class RegexHelper
{
public:
    static QStringList generateHints(const QString &pattern);
};

#endif // REGEXHELPER_H
