#ifndef CLOSESTPAIRVISUALIZER_H
#define CLOSESTPAIRVISUALIZER_H

#include <QWidget>
#include <vector>
#include <QString>

#include "../Algorithms/ClosestPair.h"

class QComboBox;
class QLabel;
class QPushButton;
class QProgressBar;
class QPlainTextEdit;

class ClosestPairVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit ClosestPairVisualizer(QWidget *parent = nullptr);

private:
    QComboBox *datasetSelector;
    QPushButton *browseButton;
    QPushButton *loadButton;
    QPushButton *runButton;
    QProgressBar *progressBar;

    QLabel *pointCountLabel;
    QLabel *distanceLabel;
    QLabel *runtimeLabel;
    QLabel *statusLabel;

    QPlainTextEdit *stepsDisplay;

    std::vector<Point> points;
    ClosestPairResult result;
    bool hasResult = false;

    QWidget *plotWidget;

    void loadDataset();
    void runAlgorithm();
    void updatePlot();
    void updateSteps();
};

#endif