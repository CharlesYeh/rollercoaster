
#ifndef __SHAPES_H__
#define __SHAPES_H__

#include "CS123Common.h"
#include <qgl.h>
#include "Settings.h"
#include "pointslist.h"

#include <iostream>
#include <fstream>
#include <string>

class Scene;

class Shapes {
public:
    Shapes();
    virtual ~Shapes();
    void drawShape(int shape, int param1, int param2, int param3, Matrix4x4 worldTrans, bool sceneview);

    int getNumPoints();
    float *getNormals();
    float *getVertices();

    static const string SPECIAL3_FILE;
    static const float  SPECIAL3_SCALE;

    void drawCache();

private:

    void addCubeToScene(int tessellations);
    void addConeToScene(int tessellations, int radiiSegments);
    void addSphereToScene(int latSegments, int longSegments);
    void addCylinderToScene(int tessellations, int radiiSegments);

    // special shapes
    void addMobiusToScene(int tessellations, int radiiSegments);
    void addRandomTreeToScene(int tessellations, int branches, int seed);
    void addBranch(int iter, int tessellations, int branches, float x, float y, float z, float rad, float phi, PointsList &vList, PointsList &nList);

    void addFileObjectToScene(int tessellations);

    // Returns the normal vector given a vertex list, and three vertex indices
    void calculateNormal(float &x, float &y, float &z, PointsList &pList, int v1, int v2, int v3);

    // Returns the normal vector given two triangle vectors
    void calculateNormal(float &nx, float &ny, float &nz, float ux, float uy, float uz, float vx, float vy, float vz);

    // {x, y, z, 1, x, y, z, 1...}
    float *m_points;
    float *m_normals;
    int m_numPoints;

    // if these don't match current params, recalculate shape
    int m_shape;
    int m_param1;
    int m_param2;
    int m_param3;

};


#endif
