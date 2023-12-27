// detectionresult.h

#ifndef DETECTIONRESULT_H
#define DETECTIONRESULT_H

#include <QString>
#include <QRectF>
#include <QVector>

class DetectionResult {
public:
    QString label;
    qreal score;
    QRectF location;

    static QVector<DetectionResult> generateRandomData(int count);
};

#endif // DETECTIONRESULT_H
