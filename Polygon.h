#pragma once

#include <vector>
#include <QPoint>
#include "Ray.h"
#include "optional"


class Polygon {
public:
    Polygon(const std::vector<QPointF> &vertices);

    std::vector<QPointF> getVertices() const;

    void AddVertex(const QPointF &vertex);

    void UpdateLastVertex(const QPointF &new_vertex);

    std::optional<QPointF> IntersectRay(const Ray &ray);

    double distance(QPointF, QPointF);

private:
    std::vector<QPointF> vertices_;
};
