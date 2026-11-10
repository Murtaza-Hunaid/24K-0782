
#ifndef BENCHMARKVISUALIZER_H
#define BENCHMARKVISUALIZER_H

#include <QWidget>
#include <QString>

#include <cstddef>

class QComboBox;
class QPushButton;
class QLabel;
class QProgressBar;
class QTableWidget;
class BenchmarkChart;

class BenchmarkVisualizer : public QWidget
{
    Q_OBJECT

public:
    explicit BenchmarkVisualizer(QWidget *parent = nullptr);

private:
    QComboBox *algorithmSelector;
    QComboBox *datasetSelector;
    QComboBox *chartAlgorithmSelector;

    QPushButton *runButton;

    QLabel *statusLabel;
    QLabel *runtimeLabel;
    QLabel *inputSizeLabel;
    QLabel *correctnessLabel;

    QProgressBar *progressBar;
    QTableWidget *historyTable;

    BenchmarkChart *chartWidget;

    void runBenchmark();
    void refreshChart();

    void saveResult(
        const QString &algorithm,
        const QString &dataset,
        size_t inputSize,
        double timeMs,
        const QString &result
    );
};

#endif
