#include "KaratsubaVisualizer.h"

#include "../Algorithms/Karatsuba.h"
#include "DatasetPaths.h"

#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QMessageBox>
#include <QFileDialog>
#include <QFileInfo>
#include <QScrollArea>
#include <QProgressBar>
#include <QFutureWatcher>
#include <QtConcurrent>
#include <QSizePolicy>
#include <QScrollBar>

#include <fstream>
#include <chrono>
#include <algorithm>
#include <utility>
#include <vector>
#include <string>

// Karatsuba page
static QString previewNumber(const std::string &number)
{
    constexpr size_t LIMIT = 120;

    if (number.size() <= LIMIT * 2)
        return QString::fromStdString(number);

    return QString::fromStdString(
        number.substr(0, LIMIT) +
        "\n\n... " + std::to_string(number.size() - LIMIT * 2) +
        " digits omitted ...\n\n" +
        number.substr(number.size() - LIMIT)
    );
}

KaratsubaVisualizer::KaratsubaVisualizer(QWidget *parent)
    : QWidget(parent)
{
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    scrollArea->verticalScrollBar()->setStyleSheet(R"(
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
    )");

    QWidget *contentWidget = new QWidget;

    QVBoxLayout *mainLayout = new QVBoxLayout(contentWidget);
    mainLayout->setContentsMargins(35, 30, 35, 25);
    mainLayout->setSpacing(18);

    QLabel *title = new QLabel("Karatsuba Multiplication");
    title->setObjectName("pageTitle");

    title->setStyleSheet(
        "color: #ffffff;"
        "background-color: #2563eb;"
        "font-size: 27px;"
        "font-weight: bold;"
        "padding: 7px 11px;"
        "border-radius: 5px;"
    );

    QLabel *description = new QLabel(
        "Multiply large integers using recursive Divide and Conquer."
    );
    description->setObjectName("pageDescription");

    mainLayout->addWidget(title);
    mainLayout->addWidget(description);

    // Dataset controls
    QHBoxLayout *controls = new QHBoxLayout;

    QLabel *datasetLabel = new QLabel("Select Dataset:");

    datasetSelector = new QComboBox;

    for (int i = 1; i <= 10; ++i)
    {
        QString id = QString("im%1").arg(i, 2, 10, QChar('0'));
        datasetSelector->addItem(id);
    }

    browseButton = new QPushButton("Browse...");
    loadButton = new QPushButton("Load Dataset");
    runButton = new QPushButton("Multiply");

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

    // Statistics
    QGridLayout *stats = new QGridLayout;
    stats->setSpacing(12);

    auto createCard = [](const QString &heading,
                         QLabel *&value) -> QFrame *
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
        createCard("TOTAL INPUT DIGITS", operandDigitsLabel), 0, 0
    );

    stats->addWidget(
        createCard("RESULT DIGITS", resultDigitsLabel), 0, 1
    );

    stats->addWidget(
        createCard("EXECUTION TIME", runtimeLabel), 0, 2
    );

    mainLayout->addLayout(stats);

    // Operand display
    QFrame *operandFrame = new QFrame;
    operandFrame->setObjectName("infoCard");

    QVBoxLayout *operandLayout = new QVBoxLayout(operandFrame);
    operandLayout->setContentsMargins(15, 12, 15, 12);

    QLabel *operandTitle = new QLabel("Input Operands");
    operandTitle->setObjectName("infoTitle");

    operandDisplay = new QPlainTextEdit;
    operandDisplay->setReadOnly(true);
    operandDisplay->setMinimumHeight(210);
    operandDisplay->setMaximumHeight(230);
    operandDisplay->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Preferred
    );
    operandDisplay->setPlaceholderText(
        "Load a dataset to display the two integers."
    );

    operandLayout->addWidget(operandTitle);
    operandLayout->addWidget(operandDisplay);

    mainLayout->addWidget(operandFrame);

    // Result display
    QFrame *resultFrame = new QFrame;
    resultFrame->setObjectName("infoCard");

    QVBoxLayout *resultLayout = new QVBoxLayout(resultFrame);
    resultLayout->setContentsMargins(15, 12, 15, 12);

    QLabel *resultTitle = new QLabel("Multiplication Result");
    resultTitle->setObjectName("infoTitle");

    resultDisplay = new QPlainTextEdit;
    resultDisplay->setReadOnly(true);
    resultDisplay->setMinimumHeight(100);
    resultDisplay->setMaximumHeight(100);
    resultDisplay->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Preferred
    );
    resultDisplay->setPlaceholderText(
        "The multiplication result will appear here."
    );

    resultLayout->addWidget(resultTitle);
    resultLayout->addWidget(resultDisplay);

    mainLayout->addWidget(resultFrame);

    // Recursion explanation
    QFrame *stepsFrame = new QFrame;
    stepsFrame->setObjectName("infoCard");

    QVBoxLayout *stepsLayout = new QVBoxLayout(stepsFrame);
    stepsLayout->setContentsMargins(15, 12, 15, 12);

    QLabel *stepsTitle = new QLabel(
        "Karatsuba Decomposition"
    );
    stepsTitle->setObjectName("infoTitle");

    stepsDisplay = new QPlainTextEdit;
    stepsDisplay->setReadOnly(true);
    stepsDisplay->setMinimumHeight(360);
    stepsDisplay->setMaximumHeight(520);

    stepsDisplay->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    stepsDisplay->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    stepsDisplay->verticalScrollBar()->setVisible(true);
    stepsDisplay->verticalScrollBar()->setStyleSheet(R"(
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
    )");

    stepsDisplay->setSizePolicy(
        QSizePolicy::Expanding,
        QSizePolicy::Preferred
    );
    stepsDisplay->setPlaceholderText(
        "The decomposition will appear here after loading."
    );

    stepsLayout->addWidget(stepsTitle);
    stepsLayout->addWidget(stepsDisplay);

    mainLayout->addWidget(stepsFrame);

    statusLabel = new QLabel("Select a dataset and load it.");
    statusLabel->setObjectName("pageDescription");

    mainLayout->addWidget(statusLabel);

    // Connections
    connect(loadButton, &QPushButton::clicked,
            this, &KaratsubaVisualizer::loadDataset);

    connect(runButton, &QPushButton::clicked,
            this, &KaratsubaVisualizer::runAlgorithm);

    connect(datasetSelector,
            &QComboBox::currentTextChanged,
            this,
            [this]()
            {
                datasetLoaded = false;
                runButton->setEnabled(false);

                operandDigitsLabel->setText("--");
                resultDigitsLabel->setText("--");
                runtimeLabel->setText("--");

                operandDisplay->clear();
                resultDisplay->clear();
                stepsDisplay->clear();

                statusLabel->setText(
                    "Dataset selection changed. Load it again."
                );
            });

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
                "Select Integer Multiplication Dataset",
                datasetFolder("integer_multiplication"),
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
        }

        QPlainTextEdit {
            background-color: #F8FAFD;
            color: #172238;
            border: 1px solid #E3E7EF;
            border-radius: 5px;
            padding: 8px;
            font-family: Consolas;
            font-size: 12px;
        }

        QLabel#infoTitle {
            color: #172238;
            font-size: 15px;
            font-weight: bold;
        }
    )");

    scrollArea->setWidget(contentWidget);

    QVBoxLayout *outerLayout = new QVBoxLayout(this);
    outerLayout->setContentsMargins(0, 0, 0, 0);
    outerLayout->addWidget(scrollArea);
}

// Load multiplication dataset
void KaratsubaVisualizer::loadDataset()
{
    QString path = datasetSelector->currentData().toString();

    if (path.isEmpty())
    {
        path = datasetFolder("integer_multiplication") + "/" +
               datasetSelector->currentText() + ".txt";
    }

    std::string filePath = path.toLocal8Bit().toStdString();

    loadButton->setEnabled(false);
    runButton->setEnabled(false);
    datasetSelector->setEnabled(false);

    progressBar->show();
    statusLabel->setText("Loading operands in background...");

    using LoadedData = std::pair<std::string, std::string>;

    auto *watcher = new QFutureWatcher<LoadedData>(this);

    connect(watcher, &QFutureWatcher<LoadedData>::finished,
            this, [this, watcher]()
    {
        try
        {
            LoadedData data = watcher->result();

            firstNumber = std::move(data.first);
            secondNumber = std::move(data.second);

            datasetLoaded = true;

            operandDigitsLabel->setText(
                QString::number(firstNumber.size()) + " × " +
                QString::number(secondNumber.size()) + " digits"
            );

            resultDigitsLabel->setText("Not calculated");
            runtimeLabel->setText("Not calculated");

            operandDisplay->setPlainText(
                "First operand:\n" + previewNumber(firstNumber) +
                "\n\nSecond operand:\n" + previewNumber(secondNumber)
            );

            resultDisplay->clear();
            updateSteps();

            statusLabel->setText("Dataset loaded successfully.");
            runButton->setEnabled(true);
        }
        catch (const std::exception &e)
        {
            firstNumber.clear();
            secondNumber.clear();
            datasetLoaded = false;

            QMessageBox::critical(
                this,
                "Dataset Error",
                QString::fromUtf8(e.what())
            );

            statusLabel->setText("Dataset loading failed.");
            operandDigitsLabel->setText("Not loaded");
            runButton->setEnabled(false);
        }

        progressBar->hide();
        loadButton->setEnabled(true);
        datasetSelector->setEnabled(true);

        watcher->deleteLater();
    });

    watcher->setFuture(QtConcurrent::run(
        [filePath]() -> LoadedData
        {
            std::ifstream file(filePath);

            if (!file.is_open())
                throw std::runtime_error(
                    "Could not open dataset file:\n" + filePath
                );

            std::string a, b;

            if (!(file >> a >> b))
                throw std::runtime_error("Invalid dataset format.");

            auto isValidNumber = [](const std::string &number)
            {
                if (number.empty())
                    return false;

                for (char c : number)
                {
                    if (c < '0' || c > '9')
                        return false;
                }

                return true;
            };

            if (!isValidNumber(a) || !isValidNumber(b))
                throw std::runtime_error(
                    "Dataset contains invalid integer operands."
                );

            return {std::move(a), std::move(b)};
        }
    ));
}


// Run Karatsuba multiplication

void KaratsubaVisualizer::runAlgorithm()
{
    if (!datasetLoaded)
        return;

    runButton->setEnabled(false);
    loadButton->setEnabled(false);
    datasetSelector->setEnabled(false);

    progressBar->show();
    statusLabel->setText(
        "Running Karatsuba multiplication in background..."
    );

    std::string a = firstNumber;
    std::string b = secondNumber;

    using TaskResult = std::pair<std::string, double>;

    auto *watcher = new QFutureWatcher<TaskResult>(this);

    connect(watcher, &QFutureWatcher<TaskResult>::finished,
            this, [this, watcher]()
    {
        try
        {
            TaskResult taskResult = watcher->result();

            multiplicationResult = std::move(taskResult.first);

            resultDigitsLabel->setText(
                QString::number(multiplicationResult.size())
            );

            runtimeLabel->setText(
                QString::number(taskResult.second, 'f', 3) + " ms"
            );

            resultDisplay->setPlainText(
                previewNumber(multiplicationResult)
            );

            statusLabel->setText(
                "Multiplication completed successfully."
            );
        }
        catch (const std::exception &e)
        {
            QMessageBox::critical(
                this,
                "Algorithm Error",
                QString::fromUtf8(e.what())
            );

            statusLabel->setText("Multiplication failed.");
        }

        progressBar->hide();
        runButton->setEnabled(true);
        loadButton->setEnabled(true);
        datasetSelector->setEnabled(true);

        watcher->deleteLater();
    });

    watcher->setFuture(QtConcurrent::run(
        [a = std::move(a), b = std::move(b)]() -> TaskResult
        {
            auto start = std::chrono::steady_clock::now();

            std::string answer = multiplyKaratsuba(a, b);

            auto end = std::chrono::steady_clock::now();

            double elapsed =
                std::chrono::duration<double, std::milli>(
                    end - start
                ).count();

            return {std::move(answer), elapsed};
        }
    ));
}


// Helpers for displaying recursive Karatsuba working

static constexpr size_t TRACE_CUTOFF = 18;
static constexpr size_t TRACE_MAX_DIGITS = 200;

static std::string cleanDecimal(const std::string &number)
{
    size_t first = number.find_first_not_of('0');

    if (first == std::string::npos)
        return "0";

    return number.substr(first);
}

static std::string addDecimal(
    const std::string &a,
    const std::string &b
)
{
    std::string result;

    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;

        if (i >= 0)
            sum += a[i--] - '0';

        if (j >= 0)
            sum += b[j--] - '0';

        result.push_back(char('0' + sum % 10));
        carry = sum / 10;
    }

    std::reverse(result.begin(), result.end());

    return cleanDecimal(result);
}

// Assumes a >= b.
static std::string subtractDecimal(
    const std::string &a,
    const std::string &b
)
{
    std::string result;

    int i = static_cast<int>(a.size()) - 1;
    int j = static_cast<int>(b.size()) - 1;
    int borrow = 0;

    while (i >= 0)
    {
        int current = (a[i--] - '0') - borrow;

        if (j >= 0)
            current -= b[j--] - '0';

        if (current < 0)
        {
            current += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        result.push_back(char('0' + current));
    }

    std::reverse(result.begin(), result.end());

    return cleanDecimal(result);
}

static std::string shiftDecimal(
    const std::string &number,
    size_t positions
)
{
    if (number == "0")
        return "0";

    return number + std::string(positions, '0');
}

static std::string multiplyDecimal(
    const std::string &a,
    const std::string &b
)
{
    std::vector<int> digits(a.size() + b.size(), 0);

    for (int i = static_cast<int>(a.size()) - 1; i >= 0; --i)
    {
        for (int j = static_cast<int>(b.size()) - 1; j >= 0; --j)
        {
            digits[i + j + 1] += (a[i] - '0') * (b[j] - '0');
        }
    }

    for (int i = static_cast<int>(digits.size()) - 1; i > 0; --i)
    {
        digits[i - 1] += digits[i] / 10;
        digits[i] %= 10;
    }

    std::string result;

    for (int digit : digits)
    {
        result.push_back(char('0' + digit));
    }

    return cleanDecimal(result);
}

static QString tracePreview(const std::string &number)
{
    constexpr size_t LIMIT = 36;

    if (number.size() <= LIMIT * 2)
        return QString::fromStdString(number);

    return QString::fromStdString(
        number.substr(0, LIMIT) +
        "... (" +
        std::to_string(number.size() - LIMIT * 2) +
        " digits omitted) ..." +
        number.substr(number.size() - LIMIT)
    );
}

static std::pair<std::string, std::string> traceSplit(
    const std::string &number,
    size_t split
)
{
    std::string value = cleanDecimal(number);

    if (value.size() <= split)
        return { "0", value };

    size_t position = value.size() - split;

    return {
        cleanDecimal(value.substr(0, position)),
        cleanDecimal(value.substr(position))
    };
}

static std::string generateKaratsubaTrace(
    const std::string &x,
    const std::string &y,
    QString &output,
    int depth,
    int &callCounter
)
{
    ++callCounter;

    const std::string aNumber = cleanDecimal(x);
    const std::string bNumber = cleanDecimal(y);

    QString indent(depth * 3, ' ');

    output += indent + "----------------------------------------\n";
    output += indent + "Karatsuba call: " +
              QString::number(callCounter) + "\n";

    output += indent + "x = " +
              tracePreview(aNumber) + "\n";

    output += indent + "y = " +
              tracePreview(bNumber) + "\n";

    // Base case: small operands are multiplied directly.
    if (aNumber.size() <= TRACE_CUTOFF ||
        bNumber.size() <= TRACE_CUTOFF)
    {
        std::string product = multiplyDecimal(aNumber, bNumber);

        output += indent + "\n";
        output += indent + "BASE CASE\n";

        output += indent + "One number has at most " +
                  QString::number(TRACE_CUTOFF) +
                  " digits, so ordinary multiplication is used.\n";

        output += indent + "x * y = " +
                  tracePreview(product) + "\n\n";

        return product;
    }

    size_t n = std::max(aNumber.size(), bNumber.size());
    size_t m = n / 2;

    auto first = traceSplit(aNumber, m);
    auto second = traceSplit(bNumber, m);

    std::string a = first.first;
    std::string b = first.second;

    std::string c = second.first;
    std::string d = second.second;

    output += indent + "\n";
    output += indent + "STEP 1: SPLIT THE OPERANDS\n";
    output += indent + "m = " + QString::number(m) + "\n\n";

    output += indent + "x = a * 10^m + b\n";
    output += indent + "a = " + tracePreview(a) + "\n";
    output += indent + "b = " + tracePreview(b) + "\n\n";

    output += indent + "y = c * 10^m + d\n";
    output += indent + "c = " + tracePreview(c) + "\n";
    output += indent + "d = " + tracePreview(d) + "\n\n";

    output += indent + "STEP 2: CALCULATE z0 = b * d\n";

    std::string z0 = generateKaratsubaTrace(
        b, d, output, depth + 1, callCounter
    );

    output += indent + "z0 = " + tracePreview(z0) + "\n\n";

    output += indent + "STEP 3: CALCULATE z2 = a * c\n";

    std::string z2 = generateKaratsubaTrace(
        a, c, output, depth + 1, callCounter
    );

    output += indent + "z2 = " + tracePreview(z2) + "\n\n";

    std::string sumA = addDecimal(a, b);
    std::string sumB = addDecimal(c, d);

    output += indent + "STEP 4: CALCULATE z1\n";
    output += indent + "z1 = (a + b) * (c + d) - z2 - z0\n\n";

    output += indent + "a + b = " +
              tracePreview(sumA) + "\n";

    output += indent + "c + d = " +
              tracePreview(sumB) + "\n\n";

    std::string sumProduct = generateKaratsubaTrace(
        sumA, sumB, output, depth + 1, callCounter
    );

    output += indent + "(a + b) * (c + d) = " +
              tracePreview(sumProduct) + "\n";

    std::string z1 = subtractDecimal(
        subtractDecimal(sumProduct, z0),
        z2
    );

    output += indent + "z1 = " + tracePreview(z1) + "\n\n";

    output += indent + "STEP 5: COMBINE THE RESULTS\n";
    output += indent +
              "x * y = z2 * 10^(2m) + z1 * 10^m + z0\n";

    std::string result = addDecimal(
        addDecimal(
            shiftDecimal(z2, m * 2),
            shiftDecimal(z1, m)
        ),
        z0
    );

    output += indent + "x * y = " +
              tracePreview(result) + "\n\n";

    return result;
}

// Show the recursive Karatsuba decomposition
void KaratsubaVisualizer::updateSteps()
{
    if (!datasetLoaded)
        return;

    QString steps;

    steps += "KARATSUBA MULTIPLICATION - RECURSIVE WORKING\n";
    steps += "============================================\n\n";

    steps += "Karatsuba uses the identity:\n\n";

    steps += "x = a * 10^m + b\n";
    steps += "y = c * 10^m + d\n\n";

    steps += "It calculates three products:\n\n";

    steps += "z0 = b * d\n";
    steps += "z2 = a * c\n";
    steps += "z1 = (a + b) * (c + d) - z2 - z0\n\n";

    steps += "The final result is:\n\n";

    steps += "x * y = z2 * 10^(2m) + z1 * 10^m + z0\n\n";

    const size_t digits =
        std::max(firstNumber.size(), secondNumber.size());

    if (digits > TRACE_MAX_DIGITS)
    {
        steps += "============================================\n";
        steps += "DETAILED TRACE NOT DISPLAYED\n";
        steps += "============================================\n\n";

        steps += "The larger operand has " +
                 QString::number(digits) +
                 " digits.\n\n";

        steps += "The recursive working is displayed for operands of up to " +
                 QString::number(TRACE_MAX_DIGITS) +
                 " digits.\n\n";

        steps += "Each call splits both numbers in half, makes three\n";
        steps += "recursive multiplications, and combines the results.\n";
        steps += "Ordinary multiplication is used once the numbers are small.\n\n";

        steps += "Click Run Algorithm to see the product and running time.\n";

        stepsDisplay->setPlainText(steps);

        return;
    }

    steps += "============================================\n";
    steps += "RECURSIVE DECOMPOSITION\n";
    steps += "============================================\n\n";

    steps += "To keep the recursion visible, this working switches to\n";
    steps += "ordinary multiplication when a number has at most " +
             QString::number(TRACE_CUTOFF) +
             " digits.\n";

    steps += "Run Algorithm uses the same method, but works in blocks\n";
    steps += "of 9 digits and switches below 32 blocks (288 digits).\n\n";

    int callCounter = 0;

    std::string product = generateKaratsubaTrace(
        firstNumber,
        secondNumber,
        steps,
        0,
        callCounter
    );

    steps += "\n============================================\n";
    steps += "FINAL RESULT\n";
    steps += "============================================\n\n";

    steps += "x * y = " + tracePreview(product) + "\n\n";

    steps += "Total Karatsuba calls: " +
             QString::number(callCounter) + "\n";

    std::string expected =
        multiplyKaratsuba(firstNumber, secondNumber);

    steps += "Check against the Karatsuba implementation: ";
    steps += (product == expected) ? "MATCH\n" : "MISMATCH\n";

    stepsDisplay->setPlainText(steps);
}