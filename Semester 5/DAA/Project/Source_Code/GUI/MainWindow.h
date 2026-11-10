
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QStackedWidget;
class QPushButton;
class BenchmarkVisualizer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QStackedWidget *pages;

    QPushButton *dashboardButton;
    QPushButton *closestPairButton;
    QPushButton *karatsubaButton;
    QPushButton *benchmarkButton;

    QWidget *createDashboardPage();
    QWidget *createPlaceholderPage(
        const QString &title,
        const QString &description
    );

    void setupNavigation();
    void showPage(int index);
};

#endif
