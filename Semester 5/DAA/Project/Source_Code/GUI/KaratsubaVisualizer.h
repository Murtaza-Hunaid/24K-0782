#ifndef KARATSUBAVISUALIZER_H
#define KARATSUBAVISUALIZER_H

#include <QWidget>
#include <QString>

#include <string>

class QComboBox;
class QPushButton;
class QLabel;
class QPlainTextEdit;
class QProgressBar;

class KaratsubaVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit KaratsubaVisualizer(QWidget *parent = nullptr);

private:
    QComboBox *datasetSelector;
    QPushButton *browseButton;
    QPushButton *loadButton;
    QPushButton *runButton;
    QProgressBar *progressBar;

    QLabel *operandDigitsLabel;
    QLabel *resultDigitsLabel;
    QLabel *runtimeLabel;
    QLabel *statusLabel;

    QPlainTextEdit *operandDisplay;
    QPlainTextEdit *resultDisplay;
    QPlainTextEdit *stepsDisplay;

    std::string firstNumber;
    std::string secondNumber;
    std::string multiplicationResult;

    bool datasetLoaded = false;

    void loadDataset();
    void runAlgorithm();
    void updateSteps();
};

#endif