#include "Ray.h"

Ray::Ray(const QPointF &begin, const QPointF &end) {
    begin_ = begin;
    end_ = end;

    double sideX;
    double sideY;
    if (begin.x() < end.x()) {
        sideX = end.x() - begin.x();
        if (begin.y() < end.y()) {
            sideY = end.y() - begin.y();
            angle_ = atan(sideY / sideX);
        } else if (begin.y() > end.y()) {
            sideY = begin.y() - end.y();
            angle_ = 2 * M_PI - atan(sideY / sideX);
        } else {
            angle_ = 0;
        }
    } else if (begin.x() > end.x()) {
        sideX = begin.x() - end.x();
        if (begin.y() < end.y()) {
            sideY = end.y() - begin.y();
            angle_ = M_PI - atan(sideY / sideX);
        } else if (begin.y() > end.y()) {
            sideY = begin.y() - end.y();
            angle_ = M_PI + atan(sideY / sideX);
        } else {
            angle_ = M_PI;
        }
    } else {
        if (begin.y() < end.y()) {
            angle_ = M_PI / 2;
        }
        if (begin.y() > end.y()) {
            angle_ = 3 * M_PI / 2;
        }
    }
}

Ray::Ray(const QPointF &begin, double angle) {
    begin_ = begin;
    angle_ = angle;

    double coordX;
    double coordY;
    if (angle == 0 || angle == M_PI) {
        QPointF newEnd(begin.x() + 1, begin.y());
        end_ = newEnd;
    } else if (angle == M_PI / 2 || angle == 3 * M_PI / 2) {
        QPointF newEnd(begin.x(), begin.y() + 1);
        end_ = newEnd;
    } else {
        if (angle > 0 && angle < M_PI / 2) {
            coordX = begin.x() + cos(angle);
            coordY = begin.y() + sin(angle);
            QPointF newEnd(coordX, coordY);
            end_ = newEnd;
        } else if (angle > M_PI / 2 && angle < M_PI) {
            coordX = begin.x() - sin(angle - M_PI / 2);
            coordY = begin.y() + cos(angle - M_PI / 2);
            QPointF newEnd(coordX, coordY);
            end_ = newEnd;
        } else if (angle > M_PI && angle < 3 * M_PI / 2) {
            coordX = begin.x() - cos(angle - M_PI);
            coordY = begin.y() - sin(angle - M_PI);
            QPointF newEnd(coordX, coordY);
            end_ = newEnd;
        } else {
            coordX = begin.x() + sin(angle - 3 * M_PI / 2);
            coordY = begin.y() - cos(angle - 3 * M_PI / 2);
            QPointF newEnd(coordX, coordY);
            end_ = newEnd;
        }
    }
}

QPointF Ray::getBegin() const {
    return begin_;
}

QPointF Ray::getEnd() const {
    return end_;
}

double Ray::getAngle() const {
    return angle_;
}

void Ray::setBegin(QPointF begin) {
    *this = Ray(begin, end_);
}

void Ray::setEnd(QPointF end) {
    *this = Ray(begin_, end);
}

void Ray::setAngle(double angle) {
    *this = Ray(begin_, angle);
}

Ray Ray::Rotate(double angle) const {
    Ray newRay = *this;
    newRay.setAngle(angle + angle_);
    return newRay;
}

