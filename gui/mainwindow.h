#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QString>

#include "timeTracker.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private slots:
        //Button handlers
        void onStartClicked();
        void onStopClicked();
        void onPauseResumeClicked();

        //Called every second by the timer
        void onTimerTick();

        //Navigation
        void showDashboard();
        void showReports();
        void showActivities();
        void showAddPastSession();

    private:
        Ui::MainWindow *ui;
        TimeTracker _tracker;
        QTimer *_timer;

        //helper functions
        void updateTimerDisplay(int totalSeconds);
        void updateButtonStates();
        void updateStatusBar(const QString& message);
};
#endif // MAINWINDOW_H
