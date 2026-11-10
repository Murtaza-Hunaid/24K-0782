#include "ClosestPairVisualizer.h"
#include "DatasetPaths.h"

#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QPainter>
#include <QPainterPath>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QElapsedTimer>
#include <QFont>
#include <QPen>
#include <QBrush>
#include <QProgressBar>
#include <QFutureWatcher>
#include <QPlainTextEdit>
#include <QScrollArea>
#include <QScrollBar>
#include <QtConcurrent>

#include <algorithm>
#include <cmath>
#include <chrono>
#include <stdexcept>
#include <QRegularExpression>
#include <QStringList>
#include <utility>
#include <fstream>
#include <limits>

// Custom 2D plotting widget
class ClosestPairPlot : public QWidget
{
public:
    explicit ClosestPairPlot(QWidget *parent = nullptr)
        : QWidget(parent)
    {
        setMinimumHeight(350);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    }

    void setData(
        const std::vector<Point> &newPoints,
        const ClosestPairResult &newResult,
        bool showResult
    )
    {
        points = newPoints;
        result = newResult;
        hasResult = showResult;
        update();
    }

protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing);

        painter.fillRect(rect(), QColor("#FFFFFF"));

        const int margin = 35;

        QRectF area(
            margin,
            margin,
            width() - 2 * margin,
            height() - 2 * margin
        );

        painter.setPen(QPen(QColor("#E9EDF4"), 1));

        for (int i = 0; i <= 10; ++i)
        {
            double x = area.left() + area.width() * i / 10.0;
            double y = area.top() + area.height() * i / 10.0;

            painter.drawLine(
                QPointF(x, area.top()),
                QPointF(x, area.bottom())
            );

            painter.drawLine(
                QPointF(area.left(), y),
                QPointF(area.right(), y)
            );
        }

        if (points.empty())
        {
            painter.setPen(QColor("#8994A8"));

            painter.drawText(
                area,
                Qt::AlignCenter,
                "Load a dataset to visualize its points"
            );

            return;
        }

        double minX = points[0].x;
        double maxX = points[0].x;
        double minY = points[0].y;
        double maxY = points[0].y;

        for (const Point &p : points)
        {
            minX = std::min(minX, p.x);
            maxX = std::max(maxX, p.x);
            minY = std::min(minY, p.y);
            maxY = std::max(maxY, p.y);
        }

        // Avoid division by zero for vertical/horizontal datasets.
        if (maxX == minX)
        {
            minX -= 0.5;
            maxX += 0.5;
        }

        if (maxY == minY)
        {
            minY -= 0.5;
            maxY += 0.5;
        }

        // Add a little space around the plotted points.
        double paddingX = (maxX - minX) * 0.05;
        double paddingY = (maxY - minY) * 0.05;

        minX -= paddingX;
        maxX += paddingX;
        minY -= paddingY;
        maxY += paddingY;

        auto mapPoint = [&](double x, double y)
        {
            double px = area.left()
                + (x - minX) / (maxX - minX) * area.width();

            double py = area.bottom()
                - (y - minY) / (maxY - minY) * area.height();

            return QPointF(px, py);
        };

        // Draw dataset points.
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor("#527FC4"));

        // Draw at most 20,000 points to keep rendering responsive.
        const size_t maxDrawPoints = 20000;

        size_t step = std::max(
            static_cast<size_t>(1),
            (points.size() + maxDrawPoints - 1) / maxDrawPoints
        );

        while (step > 1 && (step % 2 == 0 || step % 5 == 0))
        {
            ++step;
        }

        for (size_t i = 0; i < points.size(); i += step)
        {
            QPointF pos = mapPoint(points[i].x, points[i].y);
            painter.drawEllipse(pos, 2.0, 2.0);
        }

        // Highlight the closest pair.
        if (hasResult)
        {
            QPointF first = mapPoint(result.first.x, result.first.y);
            QPointF second = mapPoint(result.second.x, result.second.y);

            painter.setPen(QPen(QColor("#E34B55"), 2.5));
            painter.drawLine(first, second);

            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor("#E34B55"));

            painter.drawEllipse(first, 6, 6);
            painter.drawEllipse(second, 6, 6);

            painter.setPen(QPen(QColor("#172238"), 1));
            painter.setBrush(Qt::NoBrush);

            painter.drawEllipse(first, 9, 9);
            painter.drawEllipse(second, 9, 9);
        }

        // Axis labels.
        painter.setPen(QColor("#758198"));

        painter.drawText(
            QRectF(area.left(), area.bottom() + 7, area.width(), 20),
            Qt::AlignCenter,
            "X coordinate"
        );

        painter.save();
        painter.translate(12, area.center().y());
        painter.rotate(-90);

        painter.drawText(
            QRectF(-area.height() / 2, -10, area.height(), 20),
            Qt::AlignCenter,
            "Y coordinate"
        );

        painter.restore();
    }

private:
    std::vector<Point> points;
    ClosestPairResult result;
    bool hasResult = false;
};


// Educational Divide and Conquer trace
struct TraceResult
{
    Point first{};
    Point second{};

    double distanceSquared =
        std::numeric_limits<double>::infinity();

    bool valid = false;
};

double traceDistanceSquared(const Point &a, const Point &b)
{
    double dx = a.x - b.x;
    double dy = a.y - b.y;

    return dx * dx + dy * dy;
}

QString pointText(const Point &p)
{
    return QString("(%1, %2)")
        .arg(p.x, 0, 'g', 10)
        .arg(p.y, 0, 'g', 10);
}

TraceResult traceBruteForce(
    const std::vector<Point> &points,
    QString &output,
    int depth
)
{
    QString indent(depth * 4, ' ');

    TraceResult best;

    output += indent + "Base case: " +
              QString::number(points.size()) +
              " point(s). Compare every pair.\n";

    for (size_t i = 0; i < points.size(); ++i)
    {
        for (size_t j = i + 1; j < points.size(); ++j)
        {
            double d2 = traceDistanceSquared(
                points[i],
                points[j]
            );

            double distance = std::sqrt(d2);

            output += indent + "  " +
                      pointText(points[i]) +
                      " and " +
                      pointText(points[j]) +
                      " -> distance = " +
                      QString::number(distance, 'g', 10) +
                      "\n";

            if (!best.valid || d2 < best.distanceSquared)
            {
                best.first = points[i];
                best.second = points[j];
                best.distanceSquared = d2;
                best.valid = true;
            }
        }
    }

    if (best.valid)
    {
        output += indent + "  Minimum in this subset: " +
                  pointText(best.first) +
                  " and " +
                  pointText(best.second) +
                  ", distance = " +
                  QString::number(
                      std::sqrt(best.distanceSquared),
                      'g',
                      10
                  ) +
                  "\n";
    }

    return best;
}

TraceResult generateClosestPairTrace(
    const std::vector<Point> &sortedPoints,
    QString &output,
    int depth = 0
)
{
    QString indent(depth * 4, ' ');

    const size_t count = sortedPoints.size();

    output += indent + "Subproblem with " +
              QString::number(count) +
              " point(s):\n";

    for (const Point &p : sortedPoints)
    {
        output += indent + "  " + pointText(p) + "\n";
    }

    // Base case: directly compare all pairs.
    if (count <= 3)
    {
        return traceBruteForce(
            sortedPoints,
            output,
            depth
        );
    }

    // Divide the points into two halves.
    size_t mid = count / 2;

    std::vector<Point> left(
        sortedPoints.begin(),
        sortedPoints.begin() + mid
    );

    std::vector<Point> right(
        sortedPoints.begin() + mid,
        sortedPoints.end()
    );

    double dividingX = sortedPoints[mid].x;

    output += indent + "\nDivide at x = " +
              QString::number(dividingX, 'g', 10) +
              "\n";

    // Recursively solve the left half.
    output += indent + "Left half:\n";

    TraceResult leftResult =
        generateClosestPairTrace(
            left,
            output,
            depth + 1
        );

    // Recursively solve the right half.
    output += indent + "\nRight half:\n";

    TraceResult rightResult =
        generateClosestPairTrace(
            right,
            output,
            depth + 1
        );

    // Select the better result from the two halves.
    TraceResult best;

    if (leftResult.valid)
    {
        best = leftResult;
    }

    if (rightResult.valid &&
        (!best.valid ||
         rightResult.distanceSquared < best.distanceSquared))
    {
        best = rightResult;
    }

    output += indent + "\nCombine the two halves:\n";

    if (leftResult.valid)
    {
        output += indent + "  Left minimum distance: " +
                  QString::number(
                      std::sqrt(leftResult.distanceSquared),
                      'g',
                      10
                  ) +
                  "\n";
    }

    if (rightResult.valid)
    {
        output += indent + "  Right minimum distance: " +
                  QString::number(
                      std::sqrt(rightResult.distanceSquared),
                      'g',
                      10
                  ) +
                  "\n";
    }

    double currentMinimum = best.distanceSquared;

    output += indent + "  Current minimum distance: " +
              QString::number(
                  std::sqrt(currentMinimum),
                  'g',
                  10
              ) +
              "\n";

    // Build the strip around the dividing line.
    std::vector<Point> strip;

    for (const Point &p : sortedPoints)
    {
        double dx = p.x - dividingX;

        if (dx * dx < currentMinimum)
        {
            strip.push_back(p);
        }
    }

    // Sort the strip by Y coordinate.
    std::sort(
        strip.begin(),
        strip.end(),
        [](const Point &a, const Point &b)
        {
            if (a.y != b.y)
                return a.y < b.y;

            return a.x < b.x;
        }
    );

    output += indent + "  Strip contains " +
              QString::number(strip.size()) +
              " point(s). Check nearby points across the dividing line.\n";

    // Check at most the next seven points for each strip point.
    for (size_t i = 0; i < strip.size(); ++i)
    {
        for (size_t j = i + 1;
             j < strip.size() && j <= i + 7;
             ++j)
        {
            double dy = strip[j].y - strip[i].y;

            if (dy * dy >= best.distanceSquared)
            {
                break;
            }

            double d2 = traceDistanceSquared(
                strip[i],
                strip[j]
            );

            output += indent + "    Strip comparison: " +
                      pointText(strip[i]) +
                      " and " +
                      pointText(strip[j]) +
                      " -> distance = " +
                      QString::number(std::sqrt(d2), 'g', 10) +
                      "\n";

            if (!best.valid || d2 < best.distanceSquared)
            {
                best.first = strip[i];
                best.second = strip[j];
                best.distanceSquared = d2;
                best.valid = true;

                output += indent +
                          "      New minimum found in the strip.\n";
            }
        }
    }

    if (best.valid)
    {
        output += indent + "  Result for this subproblem: " +
                  pointText(best.first) +
                  " and " +
                  pointText(best.second) +
                  ", distance = " +
                  QString::number(
                      std::sqrt(best.distanceSquared),
                      'g',
                      10
                  ) +
                  "\n";
    }

    return best;
}

QString buildClosestPairTrace(
    const std::vector<Point> &points,
    const ClosestPairResult *finalResult
)
{
    QString output;

    output += "CLOSEST PAIR OF POINTS - ALGORITHM TRACE\n";
    output += "========================================\n\n";

    output += "Step 1: Sort all points by their X coordinate.\n";

    std::vector<Point> sortedPoints = points;

    std::sort(
        sortedPoints.begin(),
        sortedPoints.end(),
        [](const Point &a, const Point &b)
        {
            if (a.x != b.x)
                return a.x < b.x;

            return a.y < b.y;
        }
    );

    for (size_t i = 0; i < sortedPoints.size(); ++i)
    {
        output += QString::number(i + 1) +
                  ". " +
                  pointText(sortedPoints[i]) +
                  "\n";
    }

    output += "\nStep 2: Apply Divide and Conquer.\n";

    output +=
        "For subsets of at most 3 points, compare every pair.\n";

    output +=
        "For larger subsets, divide into halves and combine results.\n\n";

    TraceResult traceResult =
        generateClosestPairTrace(
            sortedPoints,
            output
        );

    output += "\nFINAL RESULT\n";
    output += "============\n";

    if (finalResult)
    {
        output += "Closest pair: " +
                  pointText(finalResult->first) +
                  " and " +
                  pointText(finalResult->second) +
                  "\n";

        output += "Minimum distance: " +
                  QString::number(
                      finalResult->distance,
                      'g',
                      12
                  ) +
                  "\n";
    }
    else if (traceResult.valid)
    {
        output += "Closest pair: " +
                  pointText(traceResult.first) +
                  " and " +
                  pointText(traceResult.second) +
                  "\n";

        output += "Minimum distance: " +
                  QString::number(
                      std::sqrt(traceResult.distanceSquared),
                      'g',
                      12
                  ) +
                  "\n";
    }

    return output;
}

// Closest Pair page
ClosestPairVisualizer::ClosestPairVisualizer(QWidget *parent)
    : QWidget(parent)
{
    // Main page scroll area.
    QScrollArea *pageScrollArea = new QScrollArea(this);

    pageScrollArea->setWidgetResizable(true);
    pageScrollArea->setFrameShape(QFrame::NoFrame);

    pageScrollArea->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAsNeeded
    );

    pageScrollArea->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOn
    );

    QWidget *contentWidget = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);

    mainLayout->setContentsMargins(35, 30, 35, 25);
    mainLayout->setSpacing(15);

    QLabel *title = new QLabel("Closest Pair of Points");
    title->setStyleSheet(
        "color: #FFFFFF;"
        "font-size: 28px;"
        "font-weight: 700;"
        "background: transparent;"
        "padding: 4px 0px;"
    );
    title->setObjectName("pageTitle");

    QLabel *description = new QLabel(
        "Visualize the Divide and Conquer algorithm on 2D datasets."
    );

    description->setObjectName("pageDescription");

    mainLayout->addWidget(title);
    mainLayout->addWidget(description);

    // Dataset controls.
    QHBoxLayout *controls = new QHBoxLayout;

    QLabel *datasetLabel = new QLabel("Select Dataset:");

    datasetSelector = new QComboBox;

    for (int i = 1; i <= 10; ++i)
    {
        QString id = QString("cp%1").arg(
            i,
            2,
            10,
            QChar('0')
        );

        datasetSelector->addItem(id);
    }

    browseButton = new QPushButton("Browse...");
    loadButton = new QPushButton("Load Dataset");
    runButton = new QPushButton("Run Algorithm");

    runButton->setEnabled(false);

    controls->addWidget(datasetLabel);
    controls->addWidget(datasetSelector, 1);
    controls->addWidget(browseButton);
    controls->addWidget(loadButton);
    controls->addWidget(runButton);

    mainLayout->addLayout(controls);

    progressBar = new QProgressBar;

    progressBar->setRange(0, 0);
    progressBar->setTextVisible(false);
    progressBar->setFixedHeight(6);
    progressBar->hide();

    mainLayout->addWidget(progressBar);

    // Statistics cards.
    QGridLayout *stats = new QGridLayout;

    stats->setSpacing(12);

    auto createCard = [](
        const QString &heading,
        QLabel *&value
    ) -> QFrame *
    {
        QFrame *card = new QFrame;

        card->setObjectName("statCard");

        QVBoxLayout *layout = new QVBoxLayout(card);

        layout->setContentsMargins(15, 12, 15, 12);
        layout->setSpacing(5);

        QLabel *label = new QLabel(heading);

        label->setObjectName("cardTitle");

        value = new QLabel("--");
        value->setObjectName("cardValue");

        layout->addWidget(label);
        layout->addWidget(value);

        return card;
    };

    stats->addWidget(
        createCard("NUMBER OF POINTS", pointCountLabel),
        0,
        0
    );

    stats->addWidget(
        createCard("MINIMUM DISTANCE", distanceLabel),
        0,
        1
    );

    stats->addWidget(
        createCard("EXECUTION TIME", runtimeLabel),
        0,
        2
    );

    mainLayout->addLayout(stats);

    // Plot.
    QFrame *plotFrame = new QFrame;

    plotFrame->setObjectName("infoCard");

    QVBoxLayout *plotLayout = new QVBoxLayout(plotFrame);

    plotLayout->setContentsMargins(10, 10, 10, 10);

    QLabel *plotTitle = new QLabel("2D Point Visualization");

    plotTitle->setObjectName("infoTitle");

    auto *plot = new ClosestPairPlot;

    plotWidget = plot;

    plotLayout->addWidget(plotTitle);
    plotLayout->addWidget(plot, 1);

    mainLayout->addWidget(plotFrame, 1);

    // Algorithm steps panel
    QFrame *stepsFrame = new QFrame;

    stepsFrame->setObjectName("infoCard");

    QVBoxLayout *stepsLayout = new QVBoxLayout(stepsFrame);

    stepsLayout->setContentsMargins(18, 16, 18, 16);
    stepsLayout->setSpacing(10);

    QLabel *stepsTitle = new QLabel(
        "Divide and Conquer - Step-by-Step Execution"
    );

    stepsTitle->setObjectName("infoTitle");

    QLabel *stepsDescription = new QLabel(
        "Load a dataset to see how the algorithm sorts, divides, "
        "compares, and combines the points."
    );

    stepsDescription->setObjectName("pageDescription");
    stepsDescription->setWordWrap(true);

    stepsDisplay = new QPlainTextEdit;

    stepsDisplay->setReadOnly(true);

    stepsDisplay->setPlaceholderText(
        "Load a dataset to display the algorithm steps."
    );

    stepsDisplay->setMinimumHeight(300);
    stepsDisplay->setMaximumHeight(480);

    stepsDisplay->setLineWrapMode(
        QPlainTextEdit::NoWrap
    );

    stepsDisplay->setVerticalScrollBarPolicy(
        Qt::ScrollBarAlwaysOn
    );

    stepsDisplay->setHorizontalScrollBarPolicy(
        Qt::ScrollBarAsNeeded
    );

    stepsDisplay->setStyleSheet(R"(
        QPlainTextEdit {
            background-color: #F8FAFD;
            color: #263650;
            border: 1px solid #DCE2EC;
            border-radius: 7px;
            padding: 12px;
            font-family: Consolas;
            font-size: 12px;
            selection-background-color: #315DAD;
            selection-color: white;
        }

        QScrollBar:vertical {
            background: #E2E8F0;
            width: 14px;
            margin: 0;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical {
            background: #315DAD;
            min-height: 30px;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical:hover {
            background: #244A91;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0;
        }

        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: transparent;
        }

        QScrollBar:horizontal {
            background: #E2E8F0;
            height: 14px;
            margin: 0;
            border-radius: 6px;
        }

        QScrollBar::handle:horizontal {
            background: #315DAD;
            min-width: 30px;
            border-radius: 6px;
        }

        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 0;
        }
    )");

    stepsLayout->addWidget(stepsTitle);
    stepsLayout->addWidget(stepsDescription);
    stepsLayout->addWidget(stepsDisplay);

    mainLayout->addWidget(stepsFrame);

    // Status label.
    statusLabel = new QLabel(
        "Select a dataset and load it."
    );

    statusLabel->setObjectName("pageDescription");

    mainLayout->addWidget(statusLabel);

    // Connections
    connect(
        loadButton,
        &QPushButton::clicked,
        this,
        &ClosestPairVisualizer::loadDataset
    );

    connect(
        runButton,
        &QPushButton::clicked,
        this,
        &ClosestPairVisualizer::runAlgorithm
    );

    connect(
        datasetSelector,
        &QComboBox::currentTextChanged,
        this,
        [this]()
        {
            runButton->setEnabled(false);

            hasResult = false;

            distanceLabel->setText("--");
            runtimeLabel->setText("--");

            stepsDisplay->clear();

            statusLabel->setText(
                "Dataset selection changed. Load the dataset again."
            );

            updatePlot();
        }
    );

    connect(
        browseButton,
        &QPushButton::clicked,
        this,
        [this]()
        {
            if (!datasetSelector->isEnabled())
                return;

            QString path = QFileDialog::getOpenFileName(
                this,
                "Select Closest Pair Dataset",
                datasetFolder("closest_pair"),
                "Text files (*.txt);;All files (*)"
            );

            if (path.isEmpty())
                return;

            int index = datasetSelector->findData(path);

            if (index < 0)
            {
                datasetSelector->addItem(
                    QFileInfo(path).fileName(),
                    path
                );

                index = datasetSelector->count() - 1;
            }

            datasetSelector->setCurrentIndex(index);

            loadDataset();
        }
    );

    // Page styling.
    setStyleSheet(R"(
        QPushButton {
            background-color: #315DAD;
            color: white;
            border: none;
            border-radius: 6px;
            padding: 9px 15px;
            font-size: 12px;
            font-weight: bold;
        }

        QPushButton:hover {
            background-color: #244A91;
        }

        QPushButton:disabled {
            background-color: #AAB6CC;
        }

        QComboBox {
            background-color: white;
            color: #172238;
            border: 1px solid #DCE2EC;
            border-radius: 6px;
            padding: 8px;
            min-width: 100px;
        }

        QComboBox QAbstractItemView {
            background-color: white;
            color: #172238;
            selection-background-color: #315DAD;
            selection-color: white;
            border: 1px solid #DCE2EC;
            outline: none;
        }

        QLabel#infoTitle {
            color: #172238;
            font-size: 15px;
            font-weight: bold;
        }
    )");

    // Main page scrollbar styling.
    pageScrollArea->verticalScrollBar()->setStyleSheet(R"(
        QScrollBar:vertical {
            background: #E2E8F0;
            width: 14px;
            margin: 0;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical {
            background: #315DAD;
            min-height: 35px;
            border-radius: 6px;
        }

        QScrollBar::handle:vertical:hover {
            background: #244A91;
        }

        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 0;
        }

        QScrollBar::add-page:vertical,
        QScrollBar::sub-page:vertical {
            background: transparent;
        }
    )");

    pageScrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);

    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(pageScrollArea);
}

// Load Dataset
void ClosestPairVisualizer::loadDataset()
{
    QString path = datasetSelector->currentData().toString();

    if (path.isEmpty())
    {
        path = datasetFolder("closest_pair") + "/" +
               datasetSelector->currentText() + ".txt";
    }

    std::string filePath = path.toLocal8Bit().toStdString();

    loadButton->setEnabled(false);
    runButton->setEnabled(false);
    datasetSelector->setEnabled(false);

    progressBar->show();

    statusLabel->setText(
        "Loading dataset in background..."
    );

    auto *watcher =
        new QFutureWatcher<std::vector<Point>>(this);

    connect(
        watcher,
        &QFutureWatcher<std::vector<Point>>::finished,
        this,
        [this, watcher]()
        {
            try
            {
                points = watcher->result();

                hasResult = false;

                pointCountLabel->setText(
                    QString::number(points.size())
                );

                distanceLabel->setText("Not calculated");
                runtimeLabel->setText("Not calculated");

                updatePlot();
                updateSteps();

                statusLabel->setText(
                    "Dataset loaded successfully."
                );

                runButton->setEnabled(points.size() >= 2);
            }
            catch (const std::exception &e)
            {
                points.clear();
                hasResult = false;

                stepsDisplay->clear();

                QMessageBox::critical(
                    this,
                    "Dataset Error",
                    QString::fromUtf8(e.what())
                );

                statusLabel->setText(
                    "Dataset loading failed."
                );

                pointCountLabel->setText("0");
                distanceLabel->setText("--");
                runtimeLabel->setText("--");

                updatePlot();

                runButton->setEnabled(false);
            }

            progressBar->hide();

            loadButton->setEnabled(true);
            datasetSelector->setEnabled(true);

            watcher->deleteLater();
        }
    );

    watcher->setFuture(
        QtConcurrent::run(
            [filePath]() -> std::vector<Point>
            {
                std::ifstream file(filePath);

                if (!file.is_open())
                {
                    throw std::runtime_error(
                        "Could not open dataset file:\n" + filePath
                    );
                }

                size_t count;

                if (!(file >> count))
                {
                    throw std::runtime_error(
                        "Invalid dataset format."
                    );
                }

                std::vector<Point> loadedPoints;

                loadedPoints.reserve(count);

                for (size_t i = 0; i < count; i++)
                {
                    Point p;

                    if (!(file >> p.x >> p.y))
                    {
                        throw std::runtime_error(
                            "Dataset contains invalid or incomplete points."
                        );
                    }

                    if (!std::isfinite(p.x) ||
                        !std::isfinite(p.y))
                    {
                        throw std::runtime_error(
                            "Dataset contains non-finite coordinates."
                        );
                    }

                    loadedPoints.push_back(p);
                }

                return loadedPoints;
            }
        )
    );
}


// Run Algorithm
void ClosestPairVisualizer::runAlgorithm()
{
    if (points.size() < 2)
        return;

    runButton->setEnabled(false);
    loadButton->setEnabled(false);
    datasetSelector->setEnabled(false);

    progressBar->show();

    statusLabel->setText(
        "Running Divide and Conquer in background..."
    );

    // Copy the dataset so the background task has independent data.
    std::vector<Point> pointsCopy = points;

    using TaskResult = std::pair<ClosestPairResult, double>;

    auto *watcher = new QFutureWatcher<TaskResult>(this);

    connect(
        watcher,
        &QFutureWatcher<TaskResult>::finished,
        this,
        [this, watcher]()
        {
            try
            {
                TaskResult taskResult = watcher->result();

                result = taskResult.first;

                double elapsed = taskResult.second;

                hasResult = true;

                distanceLabel->setText(
                    QString::number(
                        result.distance,
                        'g',
                        12
                    )
                );

                runtimeLabel->setText(
                    QString::number(elapsed, 'f', 3) +
                    " ms"
                );

                statusLabel->setText(
                    "Algorithm completed successfully. "
                    "The closest pair is highlighted in red."
                );

                updatePlot();
                updateSteps();
            }
            catch (const std::exception &e)
            {
                QMessageBox::critical(
                    this,
                    "Algorithm Error",
                    QString::fromUtf8(e.what())
                );

                statusLabel->setText(
                    "Algorithm execution failed."
                );
            }

            progressBar->hide();

            runButton->setEnabled(true);
            loadButton->setEnabled(true);
            datasetSelector->setEnabled(true);

            watcher->deleteLater();
        }
    );

    watcher->setFuture(
        QtConcurrent::run(
            [pointsCopy = std::move(pointsCopy)]() -> TaskResult
            {
                auto start = std::chrono::steady_clock::now();

                ClosestPairResult answer =
                    closestPair(pointsCopy);

                auto end = std::chrono::steady_clock::now();

                double elapsed =
                    std::chrono::duration<double, std::milli>(
                        end - start
                    ).count();

                return {answer, elapsed};
            }
        )
    );
}


// Update Plot
void ClosestPairVisualizer::updatePlot()
{
    auto *plot =
        static_cast<ClosestPairPlot *>(plotWidget);

    plot->setData(
        points,
        result,
        hasResult
    );
}


// Update Algorithm Steps
void ClosestPairVisualizer::updateSteps()
{
    if (points.size() < 2)
    {
        stepsDisplay->setPlainText(
            "At least two points are required to find the closest pair."
        );

        return;
    }

    // Keep detailed traces manageable for large datasets.
    if (points.size() > 500)
    {
        QString message;

        message += "DETAILED TRACE NOT DISPLAYED\n";
        message += "============================\n\n";

        message += "This dataset contains " +
                   QString::number(points.size()) +
                   " points.\n\n";

        message +=
            "The Divide and Conquer algorithm performs these stages:\n";

        message += "1. Sort the points by their X coordinates.\n";
        message += "2. Divide the points into two halves.\n";
        message += "3. Recursively find the closest pair in each half.\n";
        message += "4. Select the smaller of the two distances.\n";
        message += "5. Build a strip around the dividing line.\n";
        message += "6. Compare nearby points in the strip.\n";
        message += "7. Return the closest pair found.\n\n";

        message +=
            "Detailed pair comparisons are displayed for datasets "
            "containing up to 500 points.";

        if (hasResult)
        {
            message += "\n\nFINAL RESULT\n";
            message += "============\n";

            message += "Closest pair: " +
                       pointText(result.first) +
                       " and " +
                       pointText(result.second) +
                       "\n";

            message += "Minimum distance: " +
                       QString::number(
                           result.distance,
                           'g',
                           12
                       ) +
                       "\n";
        }

        stepsDisplay->setPlainText(message);

        return;
    }

    stepsDisplay->setPlainText(
        buildClosestPairTrace(
            points,
            hasResult ? &result : nullptr
        )
    );
}