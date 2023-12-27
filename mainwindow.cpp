#include "mainwindow.h"
#include "ui_microalage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //    connect(ui->importButton, SIGNAL(clicked()), this, SLOT(on_importButton_clicked()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxIndexChanged(int)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_importButton_clicked() {
    qDebug() << "Import button clicked";

    // Disconnect the signal and slot to avoid multiple connections
    disconnect(ui->importButton, SIGNAL(clicked()), this, SLOT(on_importButton_clicked()));

    // Open a file dialog to select an image
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open Image"), "", tr("Image Files (*.png *.jpg *.bmp *.tif)"));

    // Check if a file was selected
    if (!filePath.isEmpty()) {
        // Load the image and display it in leftLabel
        QPixmap pixmap(filePath);
        ui->leftLabel->setPixmap(pixmap);
        ui->leftLabel->setScaledContents(true);
    }

    // Reconnect the signal and slot
    connect(ui->importButton, SIGNAL(clicked()), this, SLOT(on_importButton_clicked()));
}


void MainWindow::on_analysisButton_clicked() {
    // Generate random data
    data = DetectionResult::generateRandomData(20);

    // Count occurrences of each label
    QHash<QString, int> labelCount;
    for (const DetectionResult &result : data) {
        labelCount[result.label]++;
    }

    // Filter out labels with count 0
    QHash<QString, int>::iterator it = labelCount.begin();
    while (it != labelCount.end()) {
        if (it.value() == 0) {
            it = labelCount.erase(it);
        } else {
            ++it;
        }
    }

    // Populate the QTableWidget
    ui->tableWidget->setRowCount(labelCount.size());
    ui->tableWidget->setColumnCount(2);

    int row = 0;
    for (auto it = labelCount.begin(); it != labelCount.end(); ++it) {
        QTableWidgetItem *labelItem = new QTableWidgetItem(it.key());
        QTableWidgetItem *countItem = new QTableWidgetItem(QString::number(it.value()));

        ui->tableWidget->setItem(row, 0, labelItem);
        ui->tableWidget->setItem(row, 1, countItem);

        ++row;
    }
    ui->comboBox->clear();

    // Add labels to the comboBox
    QStringList labels = labelCount.keys();
    ui->comboBox->addItems(labels);


    QString selectedLabel = ui->comboBox->currentText();

    QVector<DetectionResult> filteredResults;
       for (const DetectionResult &result : data) {
           if (result.label == selectedLabel) {
               filteredResults.append(result);
           }
       }
    displayMarkedImage(filteredResults);
    populateOtherTableWidget(selectedLabel, filteredResults);
}

void MainWindow::MainWindow::onComboBoxIndexChanged(int index) {
    Q_UNUSED(index);  // 防止未使用的警告

    // 获取当前选择的标签
    QString selectedLabel = ui->comboBox->currentText();


    // 过滤检测结果，仅保留与选择标签匹配的结果
    QVector<DetectionResult> filteredResults;
    for (const DetectionResult &result : data) {
        if (result.label == selectedLabel) {
            filteredResults.append(result);
        }
    }

    // 调用displayMarkedImage显示绘制的检测框
    displayMarkedImage(filteredResults);
    populateOtherTableWidget(selectedLabel, filteredResults);
}


void MainWindow::displayMarkedImage(const QVector<DetectionResult> &detectionResults) {
    // Get the image from ui->leftLabel
    QPixmap originalPixmap = *ui->leftLabel->pixmap();

    // Create a copy of the original image
    QPixmap markedPixmap = originalPixmap;

    // Draw detection boxes on the markedPixmap
    QPainter painter(&markedPixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::HighQualityAntialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    for (const DetectionResult &result : detectionResults) {
        // Calculate the QRectF in the image coordinates
        QRectF rectInImage(
                    result.location.left(),
            result.location.top(),
            result.location.width(),
            result.location.height()
        );

        // Draw the rectangle
        painter.setPen(QPen(QColor(0, 0, 255), 2));  // Red pen color
        painter.drawRect(rectInImage);

        // Add label and score as text
        QString text = QString("%1\nScore: %2").arg(result.label).arg(result.score);
        painter.setPen(Qt::green);  // Green text color
        painter.drawText(rectInImage.topLeft() + QPointF(5, -15), text);
    }

    // Display the marked image in markedimageLabel
    ui->markedimageLabel->setPixmap(markedPixmap);
    ui->markedimageLabel->setScaledContents(true);
}

void MainWindow::MainWindow::populateOtherTableWidget(const QString &selectedLabel, const QVector<DetectionResult> &filteredResults) {
    // 设置othertableWidget的行数和列数
    ui->othertableWidget->setRowCount(filteredResults.size());
    ui->othertableWidget->setColumnCount(2);

    // 将选择的标签和分数填充到othertableWidget中
    for (int row = 0; row < filteredResults.size(); ++row) {
        QTableWidgetItem *labelItem = new QTableWidgetItem(selectedLabel);
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(filteredResults[row].score));

        ui->othertableWidget->setItem(row, 0, labelItem);
        ui->othertableWidget->setItem(row, 1, scoreItem);
    }
}


