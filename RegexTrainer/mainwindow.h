#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegularExpression>

#include "regexexamples.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onRegexChanged();
    void onTextChanged();
    void onFlagsChanged();
    void onExampleSelected();

private:
    void processRegex();
    void highlightMatches(const QRegularExpression &regex);
    void showHints(const QRegularExpression &regex);

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
