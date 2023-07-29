# Raycast

This is a project by Yuliya Kunts, who was inspired by the article [SIGHT&LIGHT](https://ncase.me/sight-and-light/) and uses the Qt framework.

This project does not use Qt-based tools for geometry calculations, for example, QLineF. In other words, in Ray, Polygon and Controller, the use of Qt is reduced to the QPoint structure.
In the project, you can switch between three modes of operation of the application: **light**, **polygons** and **static-lights**. 
### light mode:
The point that the user controls is drawn and it serve as a light source.
### polygons mode:
- The first click of the LMB: a new polygon is created.
- The second and subsequent clicks of the LMB: a new vertex is added to the current polygon.
- Pressing the RMB: finish drawing the current polygon (after that, the next pressing of the LMB is treated as the first).
- Polygons will be obstacles to light, creating a shadow.
### static-lighting mode:
In it, when you press the LMB, you can create additional light sources — the user cannot control their movement, but they also create light.
