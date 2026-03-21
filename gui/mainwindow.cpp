#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up the QTimer - it will fire every 1000ms (1 second)
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

    // Connect navigation buttons to page switching
    connect(ui->navDashboard, &QPushButton::clicked, this, &MainWindow::showDashboard);
    connect(ui->navReports,   &QPushButton::clicked, this, &MainWindow::showReports);
    connect(ui->navActivities,&QPushButton::clicked, this, &MainWindow::showActivities);
    connect(ui->navAddPast,   &QPushButton::clicked, this, &MainWindow::showAddPastSession);

    // Connect action buttons
    connect(ui->startButton,       &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->stopButton,        &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(ui->pauseResumeButton, &QPushButton::clicked, this, &MainWindow::onPauseResumeClicked);

    // Connect report buttons
    connect(ui->dailyReportButton,   &QPushButton::clicked, this, [this](){
        ui->reportOutput->setText(QString::fromStdString(_tracker.getDailyReport()));
    });
    connect(ui->weeklyReportButton,  &QPushButton::clicked, this, [this](){
        ui->reportOutput->setText(QString::fromStdString(_tracker.getWeeklyReport()));
    });
    connect(ui->monthlyReportButton, &QPushButton::clicked, this, [this](){
        ui->reportOutput->setText(QString::fromStdString(_tracker.getMonthlyReport()));
    });

    // Connect add past session button
    connect(ui->addPastButton, &QPushButton::clicked, this, [this](){
        QString activity = ui->pastActivitySelector->currentText();
        QString date     = ui->pastDateInput->text();
        QString start    = ui->pastStartInput->text();
        QString end      = ui->pastEndInput->text();

        if (date.isEmpty() || start.isEmpty() || end.isEmpty()) {
            QMessageBox::warning(this, "Missing Fields", "Please fill in all fields.");
            return;
        }

        _tracker.addPastSession(
            activity.toStdString(),
            date.toStdString(),
            start.toStdString(),
            end.toStdString()
            );

        QMessageBox::information(this, "Success", "Past session added successfully!");

        // Clear the inputs
        ui->pastDateInput->clear();
        ui->pastStartInput->clear();
        ui->pastEndInput->clear();
    });

    // Show/hide custom activity input when "Custom..." is selected
    connect(ui->activitySelector, &QComboBox::currentTextChanged, this, [this](const QString& text){
        ui->customActivityInput->setVisible(text == "Custom...");
    });

    // Start on dashboard
    showDashboard();
    updateButtonStates();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// ─── Navigation ────────────────────────────────────────────

void MainWindow::showDashboard()
{
    ui->stackedPages->setCurrentIndex(0);

    // Highlight active nav button
    ui->navDashboard->setStyleSheet(
        "QPushButton { background-color: #3b3b52; color: #ffffff; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #4b4b6a; }"
        );
    ui->navReports->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navActivities->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navAddPast->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
}

void MainWindow::showReports()
{
    ui->stackedPages->setCurrentIndex(1);

    ui->navDashboard->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navReports->setStyleSheet(
        "QPushButton { background-color: #3b3b52; color: #ffffff; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #4b4b6a; }"
        );
    ui->navActivities->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navAddPast->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
}

void MainWindow::showActivities()
{
    ui->stackedPages->setCurrentIndex(2);

    ui->navDashboard->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navReports->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navActivities->setStyleSheet(
        "QPushButton { background-color: #3b3b52; color: #ffffff; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #4b4b6a; }"
        );
    ui->navAddPast->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );

    // Populate activities list
    ui->activitiesList->clear();
    for (Activity* activity : _tracker.getAllActivities())
    {
        QString entry = QString("%1  —  %2")
                            .arg(QString::fromStdString(activity->getName()), 20)
                            .arg(QString::fromStdString(activity->getFormattedTime()));
        ui->activitiesList->addItem(entry);
    }
}

void MainWindow::showAddPastSession()
{
    ui->stackedPages->setCurrentIndex(3);

    ui->navDashboard->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navReports->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navActivities->setStyleSheet(
        "QPushButton { background-color: transparent; color: #aaaacc; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #2e2e42; color: #ffffff; }"
        );
    ui->navAddPast->setStyleSheet(
        "QPushButton { background-color: #3b3b52; color: #ffffff; border: none; border-radius: 8px; padding: 10px; text-align: left; font-size: 13px; }"
        "QPushButton:hover { background-color: #4b4b6a; }"
        );
}

// ─── Timer ─────────────────────────────────────────────────

void MainWindow::onTimerTick()
{
    // Called every second while a session is active
    int elapsed = _tracker.getCurrentSessionElapsed();
    updateTimerDisplay(elapsed);
}

void MainWindow::updateTimerDisplay(int totalSeconds)
{
    int hours = totalSeconds / 3600;
    int mins  = (totalSeconds % 3600) / 60;
    int secs  = totalSeconds % 60;

    QString timeStr = QString("%1 : %2 : %3")
                          .arg(hours, 2, 10, QChar('0'))
                          .arg(mins,  2, 10, QChar('0'))
                          .arg(secs,  2, 10, QChar('0'));

    ui->timerDisplay->setText(timeStr);
}

// ─── Button handlers ───────────────────────────────────────

void MainWindow::onStartClicked()
{
    // Get the selected activity name
    QString activity = ui->activitySelector->currentText();
    if (activity == "Custom...")
    {
        activity = ui->customActivityInput->text().trimmed();
        if (activity.isEmpty())
        {
            QMessageBox::warning(this, "No Activity", "Please enter a custom activity name.");
            return;
        }
    }

    _tracker.startSession(activity.toStdString());
    _timer->start(1000); // fire every 1 second

    ui->currentActivityLabel->setText(activity);
    updateButtonStates();
    updateStatusBar("Tracking: " + activity);
}

void MainWindow::onStopClicked()
{
    _tracker.stopSession();
    _timer->stop();

    ui->currentActivityLabel->setText("—");
    updateTimerDisplay(0);
    updateButtonStates();
    updateStatusBar("Session stopped and saved.");
}

void MainWindow::onPauseResumeClicked()
{
    _tracker.pauseOrResume();

    if (_tracker.isSessionPaused())
    {
        _timer->stop();
        ui->pauseResumeButton->setText("Resume");
        updateStatusBar("Session paused.");
    }
    else
    {
        _timer->start(1000);
        ui->pauseResumeButton->setText("Pause");
        updateStatusBar("Session resumed.");
    }
}

// ─── Helpers ───────────────────────────────────────────────

void MainWindow::updateButtonStates()
{
    bool active = _tracker.hasActiveSession();

    ui->startButton->setEnabled(!active);
    ui->stopButton->setEnabled(active);
    ui->pauseResumeButton->setEnabled(active);
    ui->activitySelector->setEnabled(!active);

    if (!active)
    {
        ui->statusLabel->setText("No active session");
        ui->pauseResumeButton->setText("Pause");
    }
    else
    {
        ui->statusLabel->setText("Session in progress");
    }
}

void MainWindow::updateStatusBar(const QString& message)
{
    ui->statusLabel->setText(message);
}
