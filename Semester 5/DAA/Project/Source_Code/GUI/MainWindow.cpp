#include "MainWindow.h"
#include "ClosestPairVisualizer.h"
#include "KaratsubaVisualizer.h"
#include "BenchmarkVisualizer.h"

#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QWidget>
#include <QStatusBar>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("DAA Algorithm Visualizer");
    resize(1200, 750);
    setMinimumSize(950, 600);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QHBoxLayout *mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Sidebar
    QWidget *sidebar = new QWidget;
    sidebar->setObjectName("sidebar");
    sidebar->setFixedWidth(235);

    QVBoxLayout *sidebarLayout = new QVBoxLayout(sidebar);
    sidebarLayout->setContentsMargins(20, 25, 20, 20);
    sidebarLayout->setSpacing(12);

    QLabel *appTitle = new QLabel("DAA PROJECT");
    appTitle->setObjectName("appTitle");

    QLabel *appSubtitle = new QLabel("Algorithm Visualizer");
    appSubtitle->setObjectName("appSubtitle");

    sidebarLayout->addWidget(appTitle);
    sidebarLayout->addWidget(appSubtitle);
    sidebarLayout->addSpacing(35);

    QLabel *navigationLabel = new QLabel("MAIN MENU");
    navigationLabel->setObjectName("sectionLabel");
    sidebarLayout->addWidget(navigationLabel);

    dashboardButton = new QPushButton("  Dashboard");
    closestPairButton = new QPushButton("  Closest Pair");
    karatsubaButton = new QPushButton("  Karatsuba");

    dashboardButton->setObjectName("navButton");
    closestPairButton->setObjectName("navButton");
    karatsubaButton->setObjectName("navButton");

    dashboardButton->setCheckable(true);
    closestPairButton->setCheckable(true);
    karatsubaButton->setCheckable(true);

    benchmarkButton = new QPushButton("  Benchmark");
    benchmarkButton->setObjectName("navButton");
    benchmarkButton->setCheckable(true);

    sidebarLayout->addWidget(dashboardButton);
    sidebarLayout->addWidget(closestPairButton);
    sidebarLayout->addWidget(karatsubaButton);
    sidebarLayout->addWidget(benchmarkButton);

    sidebarLayout->addStretch();

    QLabel *footer = new QLabel("Design and Analysis\nof Algorithms");
    footer->setObjectName("footer");
    sidebarLayout->addWidget(footer);

    // Main content area
    pages = new QStackedWidget;

    pages->addWidget(createDashboardPage());

    pages->addWidget(new ClosestPairVisualizer);

    pages->addWidget(new KaratsubaVisualizer);

    pages->addWidget(new BenchmarkVisualizer);

    mainLayout->addWidget(sidebar);
    mainLayout->addWidget(pages, 1);

    // Navigation connections
    connect(dashboardButton, &QPushButton::clicked,
            this, [this]() { showPage(0); });

    connect(closestPairButton, &QPushButton::clicked,
            this, [this]() { showPage(1); });

    connect(karatsubaButton, &QPushButton::clicked,
            this, [this]() { showPage(2); });
    
    connect(benchmarkButton, &QPushButton::clicked,
            this, [this]() { showPage(3); });

    showPage(0);

    statusBar()->showMessage("Ready");
    
    // Application styling
    setStyleSheet(R"(
        QMainWindow {
            background-color: #F3F5F9;
        }

        QWidget#sidebar {
            background-color: #172238;
        }

        QLabel#appTitle {
            color: white;
            font-size: 21px;
            font-weight: bold;
        }

        QLabel#appSubtitle {
            color: #AAB6CC;
            font-size: 12px;
        }

        QLabel#sectionLabel {
            color: #8190AA;
            font-size: 10px;
            font-weight: bold;
            padding-bottom: 8px;
        }

        QPushButton#navButton {
            color: #C6D0E0;
            background-color: transparent;
            border: none;
            border-radius: 7px;
            text-align: left;
            padding: 13px;
            font-size: 14px;
        }

        QPushButton#navButton:hover {
            background-color: #263650;
            color: white;
        }

        QPushButton#navButton:checked {
            background-color: #315DAD;
            color: white;
            font-weight: bold;
        }

        QLabel#footer {
            color: #8190AA;
            font-size: 11px;
            padding-top: 15px;
        }

        QLabel#pageTitle {
            color: #172238;
            font-size: 27px;
            font-weight: bold;
        }

        QLabel#pageDescription {
            color: #758198;
            font-size: 13px;
        }

        QFrame#statCard {
            background-color: white;
            border: 1px solid #E3E7EF;
            border-radius: 10px;
        }

        QLabel#cardTitle {
            color: #758198;
            font-size: 12px;
        }

        QLabel#cardValue {
            color: #172238;
            font-size: 25px;
            font-weight: bold;
        }

        QLabel#cardDescription {
            color: #8A95A8;
            font-size: 11px;
        }

        QFrame#infoCard {
            background-color: white;
            border: 1px solid #E3E7EF;
            border-radius: 10px;
        }

        QLabel#infoTitle {
            color: #172238;
            font-size: 16px;
            font-weight: bold;
        }

        QLabel#infoText {
            color: #68758C;
            font-size: 13px;
        }

        QStatusBar {
            background-color: white;
            color: #68758C;
        }
    )");
}

QWidget *MainWindow::createDashboardPage()
{
    QWidget *page = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(40, 35, 40, 30);
    layout->setSpacing(22);

    QLabel *title = new QLabel("Dashboard");
    title->setObjectName("pageTitle");

    QLabel *description = new QLabel(
        "Explore and visualize two fundamental algorithms."
    );
    description->setObjectName("pageDescription");

    layout->addWidget(title);
    layout->addWidget(description);
    layout->addSpacing(10);

    // Statistics cards
    QGridLayout *statsLayout = new QGridLayout;
    statsLayout->setSpacing(18);

    auto createStatCard = [](QString heading,
                             QString value,
                             QString detail) -> QFrame *
    {
        QFrame *card = new QFrame;
        card->setObjectName("statCard");
        card->setMinimumHeight(135);

        QVBoxLayout *cardLayout = new QVBoxLayout(card);
        cardLayout->setContentsMargins(20, 17, 20, 17);
        cardLayout->setSpacing(7);

        QLabel *title = new QLabel(heading);
        title->setObjectName("cardTitle");

        QLabel *number = new QLabel(value);
        number->setObjectName("cardValue");

        QLabel *description = new QLabel(detail);
        description->setObjectName("cardDescription");

        cardLayout->addWidget(title);
        cardLayout->addWidget(number);
        cardLayout->addWidget(description);
        cardLayout->addStretch();

        return card;
    };

    statsLayout->addWidget(
        createStatCard("ALGORITHMS", "02", "Implemented algorithms"),
        0, 0
    );

    statsLayout->addWidget(
        createStatCard("DATASETS", "20", "Generated test datasets"),
        0, 1
    );

    statsLayout->addWidget(
        createStatCard("LANGUAGE", "C++17", "Core implementation"),
        1, 0
    );

    statsLayout->addWidget(
        createStatCard("FRAMEWORK", "Qt 6", "Graphical interface"),
        1, 1
    );

    layout->addLayout(statsLayout);

    // Algorithm information
    QFrame *algorithmsCard = new QFrame;
    algorithmsCard->setObjectName("infoCard");

    QVBoxLayout *infoLayout = new QVBoxLayout(algorithmsCard);
    infoLayout->setContentsMargins(22, 20, 22, 20);
    infoLayout->setSpacing(12);

    QLabel *infoTitle = new QLabel("Implemented Algorithms");
    infoTitle->setObjectName("infoTitle");

    QLabel *closestInfo = new QLabel(
        "<b>01. Closest Pair of Points</b><br>"
        "Finds the two closest points in a 2D plane using "
        "the Divide and Conquer technique.<br>"
        "<span style='color:#315DAD;'>Time Complexity: O(n log n)</span>"
    );
    closestInfo->setObjectName("infoText");
    closestInfo->setWordWrap(true);

    QLabel *karatsubaInfo = new QLabel(
        "<b>02. Karatsuba Integer Multiplication</b><br>"
        "Multiplies large integers using recursive "
        "divide and conquer multiplication.<br>"
        "<span style='color:#315DAD;'>Time Complexity: O(n^1.585)</span>"
    );
    karatsubaInfo->setObjectName("infoText");
    karatsubaInfo->setWordWrap(true);

    infoLayout->addWidget(infoTitle);
    infoLayout->addWidget(closestInfo);
    infoLayout->addWidget(karatsubaInfo);

    layout->addWidget(algorithmsCard);
    layout->addStretch();

    return page;
}

QWidget *MainWindow::createPlaceholderPage(
    const QString &titleText,
    const QString &descriptionText
)
{
    QWidget *page = new QWidget;

    QVBoxLayout *layout = new QVBoxLayout(page);
    layout->setContentsMargins(40, 35, 40, 30);

    QLabel *title = new QLabel(titleText);
    title->setObjectName("pageTitle");

    QLabel *description = new QLabel(descriptionText);
    description->setObjectName("pageDescription");
    description->setWordWrap(true);

    layout->addWidget(title);
    layout->addWidget(description);
    layout->addStretch();

    return page;
}

void MainWindow::showPage(int index)
{
    pages->setCurrentIndex(index);

    dashboardButton->setChecked(index == 0);
    closestPairButton->setChecked(index == 1);
    karatsubaButton->setChecked(index == 2);
    benchmarkButton->setChecked(index == 3);
}