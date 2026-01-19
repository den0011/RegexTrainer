#include "regexhelper.h"

QStringList RegexHelper::generateHints(const QString &pattern)
{
    QStringList hints;

    if (pattern.contains(".*"))
        hints << "Подсказка: .* — квантификатор, может захватывать слишком много.";

    if (pattern.contains(".+"))
        hints << "Подсказка: .+ требует хотя бы один символ.";

    if (pattern.contains("^"))
        hints << "Подсказка: ^ — начало строки.";

    if (pattern.contains("$"))
        hints << "Подсказка: $ — конец строки.";

    if (pattern.contains("(") && !pattern.contains("?:"))
        hints << "Подсказка: () создаёт захватывающую группу.";

    if (pattern.contains("[") && !pattern.contains("]"))
        hints << "Ошибка: открытая символьная группа [ без ].";

    if (hints.isEmpty())
        hints << "Подсказок нет. Регулярное выражение выглядит нормально.";

    return hints;
}
