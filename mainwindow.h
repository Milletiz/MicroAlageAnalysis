#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QVector>
#include <QPainter>
#include "detectionresult.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void displayMarkedImage(const QVector<DetectionResult> &detectionResults);
    void populateOtherTableWidget(const QString &selectedLabel, const QVector<DetectionResult> &filteredResults);

private:
    Ui::MainWindow *ui;
    QVector<DetectionResult> data;

public slots:
    void on_importButton_clicked();
    void on_analysisButton_clicked();
    void onComboBoxIndexChanged(int index);
};
#endif // MAINWINDOW_H
