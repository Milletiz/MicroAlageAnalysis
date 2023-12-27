// detectionresult.cpp

#include "detectionresult.h"
#include <QRandomGenerator>
#include <QStringList>

QVector<DetectionResult> DetectionResult::generateRandomData(int count) {
    QVector<DetectionResult> data;
    QStringList labels = {"Spirulina", "Limnothrix", "Chlorella"};

    for (int i = 0; i < count; ++i) {
        DetectionResult result;
        result.label = labels[QRandomGenerator::global()->bounded(labels.size())];
        result.score = QRandomGenerator::global()->generateDouble();
        result.location = QRectF(
            QRandomGenerator::global()->generateDouble() * 500, // left
            QRandomGenerator::global()->generateDouble() * 500, // top
            QRandomGenerator::global()->generateDouble() * 500, // width
            QRandomGenerator::global()->generateDouble() * 500  // height
        );
        data.append(result);
    }

    return data;
}
