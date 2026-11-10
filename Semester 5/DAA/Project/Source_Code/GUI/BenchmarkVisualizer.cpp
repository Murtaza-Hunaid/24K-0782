#include "BenchmarkVisualizer.h"
#include "DatasetPaths.h"

#include "../Algorithms/ClosestPair.h"
#include "../Algorithms/Karatsuba.h"

#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QPaintEvent>
#include <QMap>
#include <QScrollArea>
#include <QFrame>
#include <QColor>
#include <QFont>
#include <QPen>
#include <QBrush>
#include <QSizePolicy>
#include <QRect>
#include <QVector>

#include <chrono>
#include <cmath>
#include <fstream>
#include <limits>
#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>
#include <set>
#include <tuple>
#include <cstdint>

namespace
{
    struct BenchmarkResult
    {
        QString algorithm;
        QString dataset;
        size_t inputSize = 0;
        double timeMs = 0;
        QString result;
        QString correctness;
    };

    struct ChartEntry
    {
        QString dataset;
        double timeMs = 0;
    };

    // CSV parser: supports quoted fields and escaped quotes
    QStringList parseCsvLine(const QString &line)
    {
        QStringList fields;
        QString field;
        bool insideQuotes = false;

        for (int i = 0; i < line.size(); ++i)
        {
            QChar ch = line[i];

            if (ch == '"')
            {
                if (insideQuotes &&
                    i + 1 < line.size() &&
                    line[i + 1] == '"')
                {
                    field += '"';
                    ++i;
                }
                else
                {
                    insideQuotes = !insideQuotes;
                }
            }
            else if (ch == ',' && !insideQuotes)
            {
                fields.append(field);
                field.clear();
            }
            else
            {
                field += ch;
            }
        }

        fields.append(field);
        return fields;
    }

    // Exact brute-force verification for small Closest Pair sets
    double bruteForceClosestPair(const std::vector<Point> &points)
    {
        double best = std::numeric_limits<double>::infinity();

        for (size_t i = 0; i < points.size(); ++i)
        {
            for (size_t j = i + 1; j < points.size(); ++j)
            {
                double dx = points[i].x - points[j].x;
                double dy = points[i].y - points[j].y;

                best = std::min(best, dx * dx + dy * dy);
            }
        }

        return std::sqrt(best);
    }

    // Independent O(n log n) sweep-line Closest Pair verifier
    double sweepLineClosestPair(const std::vector<Point> &points)
    {
        std::vector<Point> sorted = points;

        std::sort(
            sorted.begin(),
            sorted.end(),
            [](const Point &a, const Point &b)
            {
                if (a.x != b.x)
                    return a.x < b.x;

                return a.y < b.y;
            }
        );

        using ActivePoint = std::tuple<double, double, size_t>;

        std::set<ActivePoint> active;

        double bestSquared =
            std::numeric_limits<double>::infinity();

        size_t left = 0;

        for (size_t i = 0; i < sorted.size(); ++i)
        {
            const Point &current = sorted[i];

            while (left < i)
            {
                double dx = current.x - sorted[left].x;

                if (dx * dx <= bestSquared)
                    break;

                active.erase({
                    sorted[left].y,
                    sorted[left].x,
                    left
                });

                ++left;
            }

            double range = std::sqrt(bestSquared);

            auto it = active.lower_bound({
                current.y - range,
                -std::numeric_limits<double>::infinity(),
                0
            });

            while (it != active.end() &&
                   std::get<0>(*it) <= current.y + range)
            {
                double dx = current.x - std::get<1>(*it);
                double dy = current.y - std::get<0>(*it);

                bestSquared = std::min(
                    bestSquared,
                    dx * dx + dy * dy
                );

                ++it;
            }

            active.insert({
                current.y,
                current.x,
                i
            });
        }

        return std::sqrt(bestSquared);
    }

    // Schoolbook multiplication for exact small-input checking
    std::string schoolbookMultiply(
        const std::string &a,
        const std::string &b
    )
    {
        std::vector<int> digits(a.size() + b.size(), 0);

        for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
        {
            for (int j = static_cast<int>(b.size()) - 1; j >= 0; --j)
            {
                digits[i + j + 1] +=
                    (a[i] - '0') * (b[j] - '0');
            }
        }

        for (int i = static_cast<int>(digits.size()) - 1; i > 0; --i)
        {
            digits[i - 1] += digits[i] / 10;
            digits[i] %= 10;
        }

        std::string result;

        for (int digit : digits)
            result += char('0' + digit);

        size_t first = result.find_first_not_of('0');

        return first == std::string::npos
            ? "0"
            : result.substr(first);
    }

    // Validate decimal result
    bool validDecimalResult(const std::string &number)
    {
        if (number.empty())
            return false;

        if (number.size() > 1 && number[0] == '0')
            return false;

        for (char digit : number)
        {
            if (digit < '0' || digit > '9')
                return false;
        }

        return true;
    }

    // Calculate a large decimal number modulo a given value
    uint64_t decimalModulo(
        const std::string &number,
        uint64_t mod
    )
    {
        uint64_t result = 0;

        for (char digit : number)
        {
            if (digit < '0' || digit > '9')
            {
                throw std::runtime_error(
                    "Invalid digit in multiplication result."
                );
            }

            result =
                (result * 10 + (digit - '0')) % mod;
        }

        return result;
    }

    // Modular verification for large Karatsuba inputs
    bool verifyKaratsubaModular(
        const std::string &a,
        const std::string &b,
        const std::string &result
    )
    {
        if (!validDecimalResult(result))
            return false;

        const uint64_t mod1 = 1000000007ULL;
        const uint64_t mod2 = 1000000009ULL;

        uint64_t a1 = decimalModulo(a, mod1);
        uint64_t b1 = decimalModulo(b, mod1);
        uint64_t r1 = decimalModulo(result, mod1);

        uint64_t a2 = decimalModulo(a, mod2);
        uint64_t b2 = decimalModulo(b, mod2);
        uint64_t r2 = decimalModulo(result, mod2);

        bool check1 = (a1 * b1) % mod1 == r1;
        bool check2 = (a2 * b2) % mod2 == r2;

        return check1 && check2;
    }

    // Save benchmark result to CSV
    void appendCsv(const BenchmarkResult &result)
    {
        QDir().mkpath("results");

        QFile file("results/benchmark.csv");

        bool needsHeader =
            !file.exists() || file.size() == 0;

        if (!file.open(
                QIODevice::WriteOnly |
                QIODevice::Append |
                QIODevice::Text))
        {
            throw std::runtime_error(
                "Could not open results/benchmark.csv."
            );
        }

        QTextStream out(&file);

        if (needsHeader)
        {
            out << "Algorithm,Dataset,InputSize,TimeMs,Result,Correctness\n";
        }

        out << result.algorithm << ','
            << result.dataset << ','
            << result.inputSize << ','
            << QString::number(result.timeMs, 'f', 3) << ','
            << '"' << result.result << '"' << ','
            << '"' << result.correctness << '"' << '\n';
    }

    // Execute selected benchmark
    BenchmarkResult executeBenchmark(
        const QString &algorithm,
        const QString &dataset,
        const QString &closestFolder,
        const QString &integerFolder
    )
    {
        BenchmarkResult output;

        output.algorithm = algorithm;
        output.dataset = dataset;

        using Clock = std::chrono::steady_clock;

        if (algorithm == "Closest Pair")
        {
            std::string path =
                (closestFolder + "/" + dataset + ".txt")
                    .toLocal8Bit().toStdString();

            std::ifstream file(path);

            if (!file)
                throw std::runtime_error(
                    "Could not open dataset file."
                );

            size_t n;

            if (!(file >> n) || n < 2)
                throw std::runtime_error(
                    "Invalid closest-pair dataset."
                );

            std::vector<Point> points;
            points.reserve(n);

            for (size_t i = 0; i < n; ++i)
            {
                Point p;

                if (!(file >> p.x >> p.y) ||
                    !std::isfinite(p.x) ||
                    !std::isfinite(p.y))
                {
                    throw std::runtime_error(
                        "Invalid point data."
                    );
                }

                points.push_back(p);
            }

            auto start = Clock::now();

            ClosestPairResult answer = closestPair(points);

            auto end = Clock::now();

            output.inputSize = n;

            output.timeMs =
                std::chrono::duration<double, std::milli>(
                    end - start
                ).count();

            output.result =
                "Distance: " +
                QString::number(answer.distance, 'g', 12);

            double expected = sweepLineClosestPair(points);

            double tolerance =
                1e-9 * std::max(1.0, std::abs(expected));

            output.correctness =
                std::abs(expected - answer.distance) <= tolerance
                ? "PASS"
                : "FAIL";
        }
        else
        {
            std::string path =
                (integerFolder + "/" + dataset + ".txt")
                    .toLocal8Bit().toStdString();

            std::ifstream file(path);

            if (!file)
                throw std::runtime_error(
                    "Could not open dataset file."
                );

            std::string first, second;

            if (!(file >> first >> second))
                throw std::runtime_error(
                    "Invalid multiplication dataset."
                );

            auto start = Clock::now();

            std::string answer =
                multiplyKaratsuba(first, second);

            auto end = Clock::now();

            output.inputSize =
                std::max(first.size(), second.size());

            output.timeMs =
                std::chrono::duration<double, std::milli>(
                    end - start
                ).count();

            output.result =
                "Result has " +
                QString::number(answer.size()) +
                " digits";

            if (first.size() <= 100 && second.size() <= 100)
            {
                output.correctness =
                    schoolbookMultiply(first, second) == answer
                    ? "PASS"
                    : "FAIL";
            }
            else
            {
                output.correctness =
                    verifyKaratsubaModular(first, second, answer)
                    ? "PASS"
                    : "FAIL";
            }
        }

        if (output.correctness == "FAIL")
        {
            throw std::runtime_error(
                "Benchmark correctness check failed."
            );
        }

        appendCsv(output);

        return output;
    }
}

// Custom benchmark chart widget
class BenchmarkChart : public QWidget
{
public:
    explicit BenchmarkChart(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setMinimumHeight(210);
        setSizePolicy(
            QSizePolicy::Expanding,
            QSizePolicy::Expanding
        );
        setMinimumSize(680, 340);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    }

    void setEntries(const QVector<ChartEntry> &newEntries)
    {
        entries = newEntries;
        update();
    }

    QSize sizeHint() const override
    {
        return QSize(900, 380);
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.fillRect(rect(), QColor("#1f2937"));

        if (entries.isEmpty())
        {
            painter.setPen(QColor("#9ca3af"));
            painter.drawText(
                rect(),
                Qt::AlignCenter,
                "No benchmark results available for this algorithm yet."
            );
            return;
        }

        const int leftMargin = 90;
        const int rightMargin = 30;
        const int topMargin = 25;
        const int bottomMargin = 65;

        QRect plotRect(
            leftMargin,
            topMargin,
            width() - leftMargin - rightMargin,
            height() - topMargin - bottomMargin
        );

        if (plotRect.width() <= 0 || plotRect.height() <= 0)
            return;

        double maxTime = 0;

        for (const ChartEntry &entry : entries)
            maxTime = std::max(maxTime, entry.timeMs);

        if (maxTime <= 0)
            maxTime = 1.0;

        // Add some space above the tallest bar.
        maxTime *= 1.15;

        painter.setFont(QFont("Segoe UI", 9));

        // Horizontal grid lines and Y-axis labels.
        const int gridLines = 4;

        for (int i = 0; i <= gridLines; ++i)
        {
            double fraction =
                static_cast<double>(i) / gridLines;

            double y =
                plotRect.bottom() -
                fraction * plotRect.height();

            painter.setPen(QPen(QColor("#374151"), 1));
            painter.drawLine(
                QPointF(plotRect.left(), y),
                QPointF(plotRect.right(), y)
            );

            double value = fraction * maxTime;

            painter.setPen(QColor("#9ca3af"));

            painter.drawText(
                QRect(5, y - 12, leftMargin - 15, 24),
                Qt::AlignRight | Qt::AlignVCenter,
                QString::number(value, 'g', 3)
            );
        }

        // Axis titles.
        painter.save();
        painter.setPen(QColor("#9ca3af"));
        painter.translate(17, plotRect.center().y());
        painter.rotate(-90);
        painter.drawText(
            QRectF(-plotRect.height() / 2, -10,
                   plotRect.height(), 20),
            Qt::AlignCenter,
            "Execution Time (ms)"
        );
        painter.restore();

        painter.setPen(QColor("#9ca3af"));
        painter.drawText(
            QRectF(
                plotRect.left(),
                plotRect.bottom() + 27,
                plotRect.width(),
                18
            ),
            Qt::AlignCenter,
            "Dataset"
        );

        // Bars.
        const int count = entries.size();
        const double slotWidth = plotRect.width() / count;
        const double barWidth = std::min(
            42.0,
            slotWidth * 0.58
        );

        for (int i = 0; i < count; ++i)
        {
            const ChartEntry &entry = entries[i];

            double barHeight =
                (entry.timeMs / maxTime) * plotRect.height();

            double x =
                plotRect.left() +
                i * slotWidth +
                (slotWidth - barWidth) / 2.0;

            double y = plotRect.bottom() - barHeight;

            QRectF bar(
                x,
                y,
                barWidth,
                std::max(1.0, barHeight)
            );

            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor("#3b82f6"));
            painter.drawRoundedRect(bar, 4, 4);

            // Value above each bar.
            painter.setPen(QColor("#e5e7eb"));

            painter.drawText(
                QRectF(
                    x - 12,
                    y - 21,
                    barWidth + 24,
                    18
                ),
                Qt::AlignCenter,
                QString::number(entry.timeMs, 'g', 3)
            );

            // Dataset label below each bar.
            painter.setPen(QColor("#d1d5db"));

            painter.drawText(
                QRectF(
                    plotRect.left() + i * slotWidth,
                    plotRect.bottom() + 5,
                    slotWidth,
                    19
                ),
                Qt::AlignCenter,
                entry.dataset
            );
        }
    }

private:
    QVector<ChartEntry> entries;
};

// Benchmark Visualizer GUI
BenchmarkVisualizer::BenchmarkVisualizer(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet(R"(
        QWidget {
            color: #e5e7eb;
            background-color: #111827;
            font-family: "Segoe UI";
            font-size: 13px;
        }

        QLabel {
            color: #e5e7eb;
            background-color: transparent;
        }

        QLabel#pageTitle {
            color: #111827;
            background-color: #f3f4f6;
            font-size: 27px;
            font-weight: bold;
            padding: 7px 11px;
            border-radius: 5px;
        }

        QLabel#pageDescription {
            color: #374151;
            background-color: #f3f4f6;
            font-size: 13px;
            padding: 7px 11px;
            border-radius: 5px;
        }

        QLabel#infoTitle {
            color: #ffffff;
            font-size: 16px;
            font-weight: bold;
        }

        QLabel#summaryValue {
            color: #e5e7eb;
            font-size: 13px;
            padding: 2px;
        }

        QLabel#statusLabel {
            color: #93c5fd;
            font-weight: bold;
            padding-top: 3px;
        }

        QGroupBox {
            color: #60a5fa;
            background-color: #1f2937;
            border: 1px solid #4b5563;
            border-radius: 9px;
            margin-top: 13px;
            padding: 14px;
            font-size: 14px;
            font-weight: bold;
        }

        QGroupBox::title {
            color: #60a5fa;
            subcontrol-origin: margin;
            subcontrol-position: top left;
            left: 12px;
            padding: 0 6px;
            background-color: #1f2937;
        }

        QComboBox {
            color: #ffffff;
            background-color: #374151;
            border: 1px solid #6b7280;
            border-radius: 6px;
            padding: 8px;
            min-width: 105px;
        }

        QComboBox:hover {
            border: 1px solid #60a5fa;
        }

        QComboBox QAbstractItemView {
            color: #ffffff;
            background-color: #374151;
            selection-background-color: #2563eb;
            selection-color: #ffffff;
            border: 1px solid #6b7280;
        }

        QPushButton {
            color: #ffffff;
            background-color: #2563eb;
            border: none;
            border-radius: 6px;
            padding: 9px 17px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #1d4ed8;
        }

        QPushButton:pressed {
            background-color: #1e40af;
        }

        QPushButton:disabled {
            color: #9ca3af;
            background-color: #374151;
        }

        QProgressBar {
            background-color: #374151;
            border: none;
            border-radius: 3px;
        }

        QProgressBar::chunk {
            background-color: #3b82f6;
            border-radius: 3px;
        }

        QTableWidget {
            color: #e5e7eb;
            background-color: #1f2937;
            alternate-background-color: #273449;
            gridline-color: #374151;
            border: 1px solid #4b5563;
            border-radius: 6px;
        }

        QHeaderView::section {
            color: #ffffff;
            background-color: #374151;
            border: none;
            border-bottom: 1px solid #4b5563;
            padding: 8px;
            font-weight: bold;
        }

        QTableWidget::item {
            padding: 5px;
        }

        QTableWidget::item:selected {
            background-color: #1d4ed8;
            color: #ffffff;
        }
    )");

    // Main layout
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    QWidget *contentWidget = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout(contentWidget);
    layout->setContentsMargins(30, 25, 30, 30);
    layout->setSpacing(22);

    QLabel *title = new QLabel("Benchmarking");
    title->setObjectName("pageTitle");

    QLabel *description = new QLabel(
        "Measure and compare algorithm performance across generated datasets."
    );
    description->setObjectName("pageDescription");

    layout->addWidget(title);
    layout->addWidget(description);

    // Benchmark controls
    QGroupBox *controls = new QGroupBox("Run Benchmark");
    QHBoxLayout *controlsLayout = new QHBoxLayout(controls);
    controlsLayout->setSpacing(12);

    algorithmSelector = new QComboBox;
    algorithmSelector->addItems({
        "Closest Pair",
        "Karatsuba"
    });

    datasetSelector = new QComboBox;

    runButton = new QPushButton("Run Benchmark");

    controlsLayout->addWidget(new QLabel("Algorithm:"));
    controlsLayout->addWidget(algorithmSelector);
    controlsLayout->addWidget(new QLabel("Dataset:"));
    controlsLayout->addWidget(datasetSelector);
    controlsLayout->addStretch();
    controlsLayout->addWidget(runButton);

    layout->addWidget(controls);

    // Progress bar
    progressBar = new QProgressBar;
    progressBar->setRange(0, 0);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(6);
    progressBar->hide();

    layout->addWidget(progressBar);

    // Latest benchmark summary
    QGroupBox *summary = new QGroupBox("Latest Benchmark");
    QHBoxLayout *summaryLayout = new QHBoxLayout(summary);
    summaryLayout->setSpacing(20);

    runtimeLabel = new QLabel("Execution time: —");
    inputSizeLabel = new QLabel("Input size: —");
    correctnessLabel = new QLabel("Correctness: —");
    statusLabel = new QLabel("Ready to run a benchmark.");

    runtimeLabel->setObjectName("summaryValue");
    inputSizeLabel->setObjectName("summaryValue");
    correctnessLabel->setObjectName("summaryValue");
    statusLabel->setObjectName("statusLabel");

    summaryLayout->addWidget(runtimeLabel);
    summaryLayout->addWidget(inputSizeLabel);
    summaryLayout->addWidget(correctnessLabel);
    summaryLayout->addStretch();

    layout->addWidget(summary);
    layout->addWidget(statusLabel);

    // Performance chart
    QGroupBox *chartGroup = new QGroupBox("Performance Comparison");
    QVBoxLayout *chartLayout = new QVBoxLayout(chartGroup);
    chartLayout->setContentsMargins(18, 18, 18, 18);
    chartLayout->setSpacing(14);

    QHBoxLayout *chartControls = new QHBoxLayout;

    chartControls->addWidget(
        new QLabel("View results for:")
    );

    chartAlgorithmSelector = new QComboBox;
    chartAlgorithmSelector->addItems({
        "Closest Pair",
        "Karatsuba"
    });

    chartControls->addWidget(chartAlgorithmSelector);
    chartControls->addStretch();

    chartLayout->addLayout(chartControls);

    chartWidget = new BenchmarkChart;
    chartWidget->setMinimumSize(680, 340);
    chartWidget->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Preferred
    );
    chartLayout->addWidget(chartWidget, 1);

    chartGroup->setMinimumHeight(500);

    layout->addWidget(chartGroup, 2);

    // Benchmark history
    QLabel *historyTitle = new QLabel("Benchmark History");
    historyTitle->setObjectName("infoTitle");

    historyTable = new QTableWidget(0, 5);

    historyTable->setHorizontalHeaderLabels({
        "Algorithm",
        "Dataset",
        "Input Size",
        "Time (ms)",
        "Correctness"
    });

    historyTable->horizontalHeader()->setSectionResizeMode(
        QHeaderView::Stretch
    );

    historyTable->setEditTriggers(
        QAbstractItemView::NoEditTriggers
    );

    historyTable->setSelectionBehavior(
        QAbstractItemView::SelectRows
    );

    historyTable->setSelectionMode(
        QAbstractItemView::SingleSelection
    );

    historyTable->setAlternatingRowColors(true);
    historyTable->verticalHeader()->setVisible(false);
    historyTable->setMinimumHeight(170);
    historyTable->setMinimumHeight(220);
    historyTable->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Preferred
    );

    layout->addWidget(historyTitle);
    layout->addWidget(historyTable, 2);

    scrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scrollArea);

    // Load previous benchmark history from CSV
    QFile historyFile("results/benchmark.csv");

    if (historyFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&historyFile);

        if (!in.atEnd())
            in.readLine();

        QString lastAlgorithm;
        QString lastDataset;
        QString lastInputSize;
        QString lastTime;
        QString lastCorrectness;

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (line.trimmed().isEmpty())
                continue;

            QStringList fields = parseCsvLine(line);

            if (fields.size() < 5)
                continue;

            QString algorithm = fields[0].trimmed();
            QString dataset = fields[1].trimmed();
            QString inputSize = fields[2].trimmed();
            QString time = fields[3].trimmed();

            QString correctness =
                fields.size() >= 6
                ? fields[5].trimmed()
                : "Not recorded";

            int row = historyTable->rowCount();
            historyTable->insertRow(row);

            historyTable->setItem(
                row, 0, new QTableWidgetItem(algorithm)
            );

            historyTable->setItem(
                row, 1, new QTableWidgetItem(dataset)
            );

            historyTable->setItem(
                row, 2, new QTableWidgetItem(inputSize)
            );

            historyTable->setItem(
                row, 3, new QTableWidgetItem(time)
            );

            historyTable->setItem(
                row, 4, new QTableWidgetItem(correctness)
            );

            lastAlgorithm = algorithm;
            lastDataset = dataset;
            lastInputSize = inputSize;
            lastTime = time;
            lastCorrectness = correctness;
        }

        if (historyTable->rowCount() > 0)
        {
            runtimeLabel->setText(
                "Execution time: " + lastTime + " ms"
            );

            inputSizeLabel->setText(
                "Input size: " + lastInputSize
            );

            correctnessLabel->setText(
                "Correctness: " + lastCorrectness
            );

            statusLabel->setText(
                "Previous benchmark loaded: " +
                lastAlgorithm + " - " + lastDataset
            );
        }

        historyFile.close();
    }

    // Dataset selection
    auto updateDatasets = [this]()
    {
        datasetSelector->clear();

        if (algorithmSelector->currentText() == "Closest Pair")
        {
            for (int i = 1; i <= 10; ++i)
            {
                datasetSelector->addItem(
                    QString("cp%1").arg(i, 2, 10, QChar('0'))
                );
            }
        }
        else
        {
            for (int i = 1; i <= 10; ++i)
            {
                datasetSelector->addItem(
                    QString("im%1").arg(i, 2, 10, QChar('0'))
                );
            }
        }
    };

    connect(
        algorithmSelector,
        &QComboBox::currentTextChanged,
        this,
        updateDatasets
    );

    connect(
        runButton,
        &QPushButton::clicked,
        this,
        &BenchmarkVisualizer::runBenchmark
    );

    connect(
        chartAlgorithmSelector,
        &QComboBox::currentTextChanged,
        this,
        [this]()
        {
            refreshChart();
        }
    );

    updateDatasets();
    refreshChart();
}

// Load chart data from CSV
void BenchmarkVisualizer::refreshChart()
{
    QVector<ChartEntry> entries;

    QFile file("results/benchmark.csv");

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);

        if (!in.atEnd())
            in.readLine();

        // Keep the latest recorded time for each dataset.
        QMap<QString, double> latestTimes;

        const QString selectedAlgorithm =
            chartAlgorithmSelector->currentText();

        while (!in.atEnd())
        {
            QString line = in.readLine();

            if (line.trimmed().isEmpty())
                continue;

            QStringList fields = parseCsvLine(line);

            if (fields.size() < 5)
                continue;

            QString algorithm = fields[0].trimmed();
            QString dataset = fields[1].trimmed();

            if (algorithm != selectedAlgorithm)
                continue;

            bool validTime = false;
            double time = fields[3].trimmed().toDouble(&validTime);

            if (!validTime || time < 0)
                continue;

            latestTimes[dataset] = time;
        }

        file.close();

        for (auto it = latestTimes.cbegin();
             it != latestTimes.cend();
             ++it)
        {
            entries.append({
                it.key(),
                it.value()
            });
        }
    }

    chartWidget->setEntries(entries);
}


// Run benchmark asynchronously
void BenchmarkVisualizer::runBenchmark()
{
    QString algorithm = algorithmSelector->currentText();
    QString dataset = datasetSelector->currentText();

    if (dataset.isEmpty())
        return;

    runButton->setEnabled(false);
    algorithmSelector->setEnabled(false);
    datasetSelector->setEnabled(false);

    progressBar->show();

    statusLabel->setText(
        "Benchmark running in the background..."
    );

    statusLabel->setStyleSheet(
        "color: #93c5fd; font-weight: bold;"
    );

    auto *watcher =
        new QFutureWatcher<BenchmarkResult>(this);

    connect(
        watcher,
        &QFutureWatcher<BenchmarkResult>::finished,
        this,
        [this, watcher]()
        {
            try
            {
                BenchmarkResult result = watcher->result();

                runtimeLabel->setText(
                    "Execution time: " +
                    QString::number(result.timeMs, 'f', 3) +
                    " ms"
                );

                inputSizeLabel->setText(
                    "Input size: " +
                    QString::number(result.inputSize)
                );

                correctnessLabel->setText(
                    "Correctness: " + result.correctness
                );

                correctnessLabel->setStyleSheet(
                    "color: #86efac; font-weight: bold;"
                );

                statusLabel->setText(
                    "Benchmark completed. Result saved to results/benchmark.csv."
                );

                statusLabel->setStyleSheet(
                    "color: #86efac; font-weight: bold;"
                );

                int row = historyTable->rowCount();
                historyTable->insertRow(row);

                historyTable->setItem(
                    row, 0,
                    new QTableWidgetItem(result.algorithm)
                );

                historyTable->setItem(
                    row, 1,
                    new QTableWidgetItem(result.dataset)
                );

                historyTable->setItem(
                    row, 2,
                    new QTableWidgetItem(
                        QString::number(result.inputSize)
                    )
                );

                historyTable->setItem(
                    row, 3,
                    new QTableWidgetItem(
                        QString::number(result.timeMs, 'f', 3)
                    )
                );

                historyTable->setItem(
                    row, 4,
                    new QTableWidgetItem(result.correctness)
                );

                historyTable->scrollToBottom();

                // Refresh chart if this algorithm is currently selected.
                refreshChart();
            }
            catch (const std::exception &e)
            {
                QMessageBox::critical(
                    this,
                    "Benchmark Error",
                    QString::fromUtf8(e.what())
                );

                statusLabel->setText("Benchmark failed.");

                statusLabel->setStyleSheet(
                    "color: #fca5a5; font-weight: bold;"
                );
            }

            progressBar->hide();

            runButton->setEnabled(true);
            algorithmSelector->setEnabled(true);
            datasetSelector->setEnabled(true);

            watcher->deleteLater();
        }
    );

    const QString closestFolder = datasetFolder("closest_pair");
    const QString integerFolder = datasetFolder("integer_multiplication");

    watcher->setFuture(
        QtConcurrent::run(
            [algorithm, dataset, closestFolder, integerFolder]()
            {
                return executeBenchmark(
                    algorithm,
                    dataset,
                    closestFolder,
                    integerFolder
                );
            }
        )
    );
}