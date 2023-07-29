#pragma once

#include <QPoint>
#include "cmath"

class Ray {
public:
    Ray(const QPointF &begin, const QPointF &end);

    Ray(const QPointF &begin, double angle);

    QPointF getBegin() const;

    QPointF getEnd() const;

    double getAngle() const;

    void setBegin(QPointF begin);

    void setEnd(QPointF end);

    void setAngle(double angle);

    Ray Rotate(double angle) const;

private:
    QPointF begin_;
    QPointF end_;
    double angle_;
};
