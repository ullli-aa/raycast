#include "Controller.h"

const std::vector<Polygon> &Controller::GetPolygons() {
    return polygons_;
}

void Controller::AddPolygon(const Polygon &polygon) {
    polygons_.push_back(polygon);
}

void Controller::AddVertexToLastPolygon(const QPointF &new_vertex) {
    polygons_.back().AddVertex(new_vertex);
}

void Controller::UpdateLastPolygon(const QPointF &new_vertex) {
    polygons_.back().UpdateLastVertex(new_vertex);
}

QPointF Controller::GetLightSource() {
    return light_source;
}

void Controller::SetLightSource(QPointF newLightSource) {
    light_source = newLightSource;
}

std::vector<Ray> Controller::CastRays() {
    rays_.clear();
    for (auto &polygon: polygons_) {
        for (int i = 0; i < polygon.getVertices().size(); ++i) {
            Ray newRay(light_source, polygon.getVertices()[i]);
            rays_.push_back(newRay);
            rays_.push_back(newRay.Rotate(0.0001));
            rays_.push_back(newRay.Rotate(-0.0001));
        }
    }

    for (const auto &ray: rays_) {
        for (int j = 0; j < rays_.size() - 1; j++) {
            if (rays_[j].getAngle() >= rays_[j + 1].getAngle()) {
                std::swap(rays_[j], rays_[j + 1]);
            }
        }
    }

    return rays_;
}

void Controller::IntersectRays(std::vector<Ray> &rays) {
    for (auto &ray: rays) {
        std::vector<QPointF> inters;
        for (auto &polygon: polygons_) {
            std::optional<QPointF> newPoint = polygon.IntersectRay(ray);
            if (newPoint.has_value()) {
                inters.emplace_back(newPoint.value());
            }
        }
        double firstDistance = 0;
        if (!inters.empty()) {
            firstDistance = distance(ray.getBegin(), inters[0]);
            ray.setEnd(inters[0]);
        }

        if (inters.size() > 1) {
            for (int i = 1; i < inters.size(); ++i) {
                double secondDistance = distance(ray.getBegin(), inters[i]);
                if (secondDistance < firstDistance) {
                    ray.setEnd(inters[i]);
                    firstDistance = secondDistance;
                }
            }
        }
    }
}

double Controller::sqr(double x) {
    return x * x;
}

double Controller::distance(QPointF first, QPointF second) {
    return sqrt(sqr(first.x() - second.x()) + sqr(first.y() - second.y()));
}

void Controller::RemoveAdjacentRays(std::vector<Ray> &rays) {
    std::vector<Ray> newRays;
    for (int i = 0; i < rays.size(); ++i) {
        for (int j = i + 1; j < rays.size(); ++j) {
            if (distance(rays[i].getEnd(), rays[j].getEnd()) < 0.00001) {
                rays[j].setEnd(rays[i].getEnd());
            }
        }
    }

    for (int i = 0; i < rays.size(); ++i) {
        int count = 0;
        for (int j = i + 1; j < rays.size(); ++j) {
            if (rays[i].getEnd() == rays[j].getEnd()) {
                ++count;
            }
        }
        if (count == 0) {
            newRays.push_back(rays[i]);
        }
    }

    rays.clear();
    rays = newRays;
}

Polygon Controller::CreateLightArea() {
    IntersectRays(rays_);
    RemoveAdjacentRays(rays_);

    std::vector<QPointF> vertices;

    for (const auto &ray: rays_) {
        vertices.push_back(ray.getEnd());
    }

    Polygon polygon = Polygon(vertices);
    return polygon;
}

std::vector<Ray> Controller::GetRays() {
    return rays_;
}

void Controller::setLightArea(Polygon polygon) {
    light_area_.getVertices().clear();
    light_area_ = std::move(polygon);
}

Polygon Controller::getLightArea() {
    return light_area_;
}

void Controller::setLightSources(QPointF lightSource) {
    light_sources_.clear();
    double count = 0;
    light_sources_.push_back(lightSource);
    while (light_sources_.size() != 9) {
        light_sources_.emplace_back(lightSource.x() + 15 * cos(count), lightSource.y() + 15 * sin(count));
        count += M_PI / 4;
    }
}

std::vector<QPointF> Controller::getLightSources() {
    return light_sources_;
}

void Controller::setStaticLights(QPointF static_light) {
    static_lights_.emplace_back(static_light);
}

std::vector<QPointF> Controller::getStaticLights() {
    return static_lights_;
}

void Controller::UpdatePolygon(QPointF new_vertex, int i, int j) {
    polygons_[i].getVertices()[j] = new_vertex;
}

void Controller::deleteLastPolygon() {
    polygons_.pop_back();
}

void Controller::deleteLastStaticLight() {
    static_lights_.pop_back();
}
