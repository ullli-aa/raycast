#pragma once

#include <vector>
#include "Polygon.h"
#include "Ray.h"

class Controller {
public:
    const std::vector<Polygon> &GetPolygons();

    void AddPolygon(const Polygon &);

    void AddVertexToLastPolygon(const QPointF &new_vertex);

    void UpdateLastPolygon(const QPointF &new_vertex);

    QPointF GetLightSource();

    void SetLightSource(QPointF);

    std::vector<Ray> CastRays();

    void IntersectRays(std::vector<Ray> &rays);

    static double sqr(double x);

    double distance(QPointF, QPointF);

    void RemoveAdjacentRays(std::vector<Ray> &rays);

    Polygon CreateLightArea();

    std::vector<Ray> GetRays();

    void setLightArea(Polygon);

    Polygon getLightArea();

    void setLightSources(QPointF);

    std::vector<QPointF> getLightSources();

    void setStaticLights(QPointF);

    std::vector<QPointF> getStaticLights();

    void UpdatePolygon(QPointF new_vertex, int, int);

    void deleteLastPolygon();

    void deleteLastStaticLight();


private:
    std::vector<Polygon> polygons_;
    QPointF light_source;
    std::vector<QPointF> light_sources_;
    std::vector<Ray> rays_;
    Polygon light_area_ = Polygon({{0, 0}});
    std::vector<QPointF> static_lights_;
};
