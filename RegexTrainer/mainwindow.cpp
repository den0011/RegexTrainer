#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "regexhelper.h"

#include <QTextCursor>
#include <QTextCharFormat>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->lineEditRegex, &QLineEdit::textChanged,
            this, &MainWindow::onRegexChanged);
    connect(ui->textEditInput, &QTextEdit::textChanged,
            this, &MainWindow::onTextChanged);
    connect(ui->checkBoxCaseInsensitive, &QCheckBox::stateChanged,
            this, &MainWindow::onFlagsChanged);
    connect(ui->checkBoxMultiline, &QCheckBox::stateChanged,
            this, &MainWindow::onFlagsChanged);

    auto examples = RegexExamples::examples();

    for (const auto &ex : examples) {
        ui->comboBoxExamples->addItem(ex.title);
    }

    connect(ui->comboBoxExamples,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            this,
            &MainWindow::onExampleSelected);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onExampleSelected()
{
    auto examples = RegexExamples::examples();
    int index = ui->comboBoxExamples->currentIndex();

    if (index < 0 || index >= examples.size())
        return;

    const auto &ex = examples[index];

    ui->textEditInput->blockSignals(true);   // <-- блокируем сигналы
    ui->lineEditRegex->setText(ex.pattern);
    ui->textEditInput->setPlainText(ex.testText);
    ui->textEditHints->setPlainText(ex.description);
    ui->textEditInput->blockSignals(false);  // <-- разблокируем сигналы

    processRegex();
}



void MainWindow::onRegexChanged()
{
    processRegex();
}

void MainWindow::onTextChanged()
{
    processRegex();
}

void MainWindow::onFlagsChanged()
{
    processRegex();
}

void MainWindow::processRegex()
{
    QRegularExpression::PatternOptions options;

    if (ui->checkBoxCaseInsensitive->isChecked())
        options |= QRegularExpression::CaseInsensitiveOption;

    if (ui->checkBoxMultiline->isChecked())
        options |= QRegularExpression::MultilineOption;

    QRegularExpression regex(ui->lineEditRegex->text(), options);

    ui->listWidgetMatches->clear();

    if (!regex.isValid()) {
        ui->labelStatus->setText("Ошибка: " + regex.errorString());
        ui->textEditInput->selectAll();
        return;
    }

    ui->labelStatus->setText("Регулярное выражение корректно");

    highlightMatches(regex);
    showHints(regex);

    QRegularExpressionMatchIterator it =
        regex.globalMatch(ui->textEditInput->toPlainText());

    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        ui->listWidgetMatches->addItem(match.captured(0));
    }
}

void MainWindow::highlightMatches(const QRegularExpression &regex)
{
    ui->textEditInput->blockSignals(true);

    QTextDocument *doc = ui->textEditInput->document();
    if (!doc || doc->isEmpty()) {
        ui->textEditInput->blockSignals(false);
        return;
    }

    QTextCursor cursor(doc);
    QTextCharFormat normalFormat;
    QTextCharFormat highlightFormat;

    normalFormat.setBackground(Qt::white);
    highlightFormat.setBackground(QColor(255, 255, 0));

    cursor.select(QTextCursor::Document);
    cursor.setCharFormat(normalFormat);

    QRegularExpressionMatchIterator it = regex.globalMatch(doc->toPlainText());
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        cursor.setPosition(match.capturedStart());
        cursor.setPosition(match.capturedEnd(), QTextCursor::KeepAnchor);
        cursor.setCharFormat(highlightFormat);
    }

    ui->textEditInput->blockSignals(false);
}


void MainWindow::showHints(const QRegularExpression &regex)
{
    ui->textEditHints->clear();
    QStringList hints = RegexHelper::generateHints(regex.pattern());
    ui->textEditHints->setPlainText(hints.join("\n"));
}
