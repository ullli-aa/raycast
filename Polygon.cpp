#include "Polygon.h"

Polygon::Polygon(const std::vector<QPointF> &vertices) {
    vertices_ = vertices;
}

std::vector<QPointF> Polygon::getVertices() const {
    return vertices_;
}

void Polygon::AddVertex(const QPointF &vertex) {
    vertices_.push_back(vertex);
}

void Polygon::UpdateLastVertex(const QPointF &new_vertex) {
    vertices_.pop_back();
    this->AddVertex(new_vertex);
}

std::optional<QPointF> Polygon::IntersectRay(const Ray &ray) {
    std::vector<QPointF> points;
    double r_px = ray.getBegin().x();
    double r_py = ray.getBegin().y();
    double r_dx = ray.getEnd().x() - ray.getBegin().x();
    double r_dy = ray.getEnd().y() - ray.getBegin().y();

    for (int i = 0; i < vertices_.size(); ++i) {
        double s_px = vertices_[i].x();
        double s_py = vertices_[i].y();
        double s_dx, s_dy;
        if (i != vertices_.size() - 1) {
            s_dx = vertices_[i + 1].x() - vertices_[i].x();
            s_dy = vertices_[i + 1].y() - vertices_[i].y();
        } else {
            s_dx = vertices_[0].x() - vertices_[i].x();
            s_dy = vertices_[0].y() - vertices_[i].y();
        }

        if (r_dx != 0 && s_dx != 0) {
            if (r_dy / r_dx == s_dy / s_dx) {
                continue;
            }
        }

        if (r_dx == 0) {
            r_dx = 1;
        }

        double T2 = (r_dx * (s_py - r_py) + r_dy * (r_px - s_px)) / (s_dx * r_dy - s_dy * r_dx);
        double T1 = (s_px + s_dx * T2 - r_px) / r_dx;

        if (T1 > 0 && (T2 >= 0 && T2 < 1)) {
            points.emplace_back(r_px + r_dx * T1, r_py + r_dy * T1);
        }
    }

    if (points.empty()) {
        return std::nullopt;
    }

    QPointF result = points[0];
    for (auto point: points) {
        if (distance(ray.getBegin(), point) <= distance(ray.getBegin(), result)) {
            result = point;
        }
    }
    return result;
}

double Polygon::distance(QPointF first, QPointF second) {
    return sqrt(
            (first.x() - second.x()) * (first.x() - second.x()) + (first.y() - second.y()) * (first.y() - second.y()));
}
