#include "Shapes.h"
#include "QCoreApplication"
#include "CS123SceneData.h"
//#include "QFileDialog"

// the program's absolute path is prepended
const string Shapes::SPECIAL3_FILE = "../cs123_deploy/cow.obj";

// amount to multiply the .obj model's vertices by
const float Shapes::SPECIAL3_SCALE = .3;

// teddy.obj:   SCALE = .08
// cow.obj:     SCALE = .3
// pumpkin.obj: SCALE = .015;

Shapes::Shapes() {
    m_shape = -1;

    m_points = 0;
    m_normals = 0;
}

Shapes::~Shapes() {
    delete[] m_points;
    delete[] m_normals;

    m_points = 0;
    m_normals = 0;
}

int Shapes::getNumPoints() {
    return m_numPoints;
}

float *Shapes::getNormals() {
    return m_normals;
}

float *Shapes::getVertices() {
    return m_points;
}

void Shapes::drawShape(int shape, int param1, int param2, int param3, Matrix4x4 worldTrans, bool sceneview) {
    if (shape == m_shape && param1 == m_param1 && param2 == m_param2 && param3 == m_param3) {
        // cached object
    }
    else {
        delete[] m_points;
        delete[] m_normals;

        m_points = 0;
        m_normals = 0;

        // recalculate points
        if (sceneview) {
            switch (shape) {
            case PRIMITIVE_CUBE:
                addCubeToScene(param1);
                break;
            case PRIMITIVE_CONE:
                addConeToScene(param1, param2);
                break;
            case PRIMITIVE_SPHERE:
                addSphereToScene(param1, param2);
                break;
            case PRIMITIVE_CYLINDER:
                addCylinderToScene(param1, param2);
                break;
            case PRIMITIVE_TORUS:
                addMobiusToScene(param1, param2);
                break;
            /*case SHAPE_SPECIAL_2:
                addRandomTreeToScene(param1, param2, param3);
                break;*/
            case PRIMITIVE_MESH:
                addFileObjectToScene(param1);
                break;
            }
        }
        else {
            switch (shape) {
            case SHAPE_CUBE:
                addCubeToScene(param1);
                break;
            case SHAPE_CONE:
                addConeToScene(param1, param2);
                break;
            case SHAPE_SPHERE:
                addSphereToScene(param1, param2);
                break;
            case SHAPE_CYLINDER:
                addCylinderToScene(param1, param2);
                break;
            case SHAPE_SPECIAL_1:
                addMobiusToScene(param1, param2);
                break;
            case SHAPE_SPECIAL_2:
                addRandomTreeToScene(param1, param2, param3);
                break;
            case SHAPE_SPECIAL_3:
                addFileObjectToScene(param1);
                break;
            }
        }

        m_shape = shape;
        m_param1 = param1;
        m_param2 = param2;
        m_param3 = param3;
    }

    drawCache();
}

void Shapes::drawCache() {
    for (int i = 0; i < m_numPoints; i++) {
        int index = i * 4;

        glNormal3f(m_normals[index + 0], m_normals[index + 1], m_normals[index + 2]);
        glVertex3f(m_points[index + 0], m_points[index + 1], m_points[index + 2]);
    }
}

void Shapes::addCubeToScene(int tessellations) {
    tessellations = std::max(tessellations, 1);

    PointsList nList;
    PointsList vList;

    // draw a square
    for (int a = 0; a < tessellations; a++) {
        for (int b = 0; b < tessellations; b++) {
            float a1 = ((float) a) / tessellations - .5;
            float b1 = ((float) b) / tessellations - .5;

            float a2 = (a + 1.f) / tessellations - .5;
            float b2 = (b + 1.f) / tessellations - .5;

            // front
            nList.addPoint(0, 0, 1);
            nList.addPoint(0, 0, 1);
            nList.addPoint(0, 0, 1);
            vList.addPoint(a1, b1, .5);
            vList.addPoint(a2, b1, .5);
            vList.addPoint(a1, b2, .5);

            nList.addPoint(0, 0, 1);
            nList.addPoint(0, 0, 1);
            nList.addPoint(0, 0, 1);
            vList.addPoint(a1, b2, .5);
            vList.addPoint(a2, b1, .5);
            vList.addPoint(a2, b2, .5);

            // back
            nList.addPoint(0, 0, -1);
            nList.addPoint(0, 0, -1);
            nList.addPoint(0, 0, -1);
            vList.addPoint(a1, b1, -.5);
            vList.addPoint(a1, b2, -.5);
            vList.addPoint(a2, b1, -.5);

            nList.addPoint(0, 0, -1);
            nList.addPoint(0, 0, -1);
            nList.addPoint(0, 0, -1);
            vList.addPoint(a1, b2, -.5);
            vList.addPoint(a2, b2, -.5);
            vList.addPoint(a2, b1, -.5);

            // left
            nList.addPoint(-1, 0, 0);
            nList.addPoint(-1, 0, 0);
            nList.addPoint(-1, 0, 0);
            vList.addPoint(-.5, a1, b1);
            vList.addPoint(-.5, a1, b2);
            vList.addPoint(-.5, a2, b1);

            nList.addPoint(-1, 0, 0);
            nList.addPoint(-1, 0, 0);
            nList.addPoint(-1, 0, 0);
            vList.addPoint(-.5, a1, b2);
            vList.addPoint(-.5, a2, b2);
            vList.addPoint(-.5, a2, b1);

            // right
            nList.addPoint(1, 0, 0);
            nList.addPoint(1, 0, 0);
            nList.addPoint(1, 0, 0);
            vList.addPoint(.5, a1, b1);
            vList.addPoint(.5, a2, b1);
            vList.addPoint(.5, a1, b2);

            nList.addPoint(1, 0, 0);
            nList.addPoint(1, 0, 0);
            nList.addPoint(1, 0, 0);
            vList.addPoint(.5, a1, b2);
            vList.addPoint(.5, a2, b1);
            vList.addPoint(.5, a2, b2);

            // top
            nList.addPoint(0, 1, 0);
            nList.addPoint(0, 1, 0);
            nList.addPoint(0, 1, 0);
            vList.addPoint(a1, .5, b1);
            vList.addPoint(a1, .5, b2);
            vList.addPoint(a2, .5, b1);

            nList.addPoint(0, 1, 0);
            nList.addPoint(0, 1, 0);
            nList.addPoint(0, 1, 0);
            vList.addPoint(a1, .5, b2);
            vList.addPoint(a2, .5, b2);
            vList.addPoint(a2, .5, b1);

            // bottom
            nList.addPoint(0, -1, 0);
            nList.addPoint(0, -1, 0);
            nList.addPoint(0, -1, 0);
            vList.addPoint(a1, -.5, b1);
            vList.addPoint(a2, -.5, b1);
            vList.addPoint(a1, -.5, b2);

            nList.addPoint(0, -1, 0);
            nList.addPoint(0, -1, 0);
            nList.addPoint(0, -1, 0);
            vList.addPoint(a1, -.5, b2);
            vList.addPoint(a2, -.5, b1);
            vList.addPoint(a2, -.5, b2);
        }
    }

    m_numPoints = vList.getSize();
    m_points = vList.getPoints();
    m_normals = nList.getPoints();
}

void Shapes::addConeToScene(int tessellations, int radiiSegments) {
    tessellations = std::max(tessellations, 1);
    radiiSegments = std::max(radiiSegments, 3);

    PointsList nList;
    PointsList vList;

    float rad = 2 * M_PI / radiiSegments;
    // draw circular
    for (int a = 0; a < radiiSegments; a++) {
        int a1 = a;
        int a2 = a + 1;

        bool first = true;

        // draw flat side
        for (int b = 0; b < tessellations; b++) {
            int b1 = b;
            int b2 = b + 1;

            // norm radius
            float normMag = 2 / sqrt(5);
            float norm1X = normMag * cos(rad * (a));
            float norm1Y = normMag * sin(rad * (a));
            float normZ = 1 / sqrt(5);

            float norm2X = normMag * cos(rad * (a + 1));
            float norm2Y = normMag * sin(rad * (a + 1));

            // first radius
            float refX1 = cos(rad * a1) / 2;
            float innerX1 = refX1 * b1 / tessellations;
            float outerX1 = refX1 * b2 / tessellations;

            float refY1 = sin(rad * a1) / 2;
            float innerY1 = refY1 * b1 / tessellations;
            float outerY1 = refY1 * b2 / tessellations;

            // second radius
            float refX2 = cos(rad * a2) / 2;
            float innerX2 = refX2 * b1 / tessellations;
            float outerX2 = refX2 * b2 / tessellations;

            float refY2 = sin(rad * a2) / 2;
            float innerY2 = refY2 * b1 / tessellations;
            float outerY2 = refY2 * b2 / tessellations;

            float innerZ = .5 - ((float) b1) / tessellations;
            float outerZ = .5 - ((float) b2) / tessellations;

            if (first) {
                // draw first triangle
                first = false;

                nList.addPoint(norm1X, normZ, norm1Y);
                nList.addPoint(norm2X, normZ, norm2Y);
                nList.addPoint(norm1X, normZ, norm1Y);
                vList.addPoint(innerX1, innerZ, innerY1);
                vList.addPoint(outerX2, outerZ, outerY2);
                vList.addPoint(outerX1, outerZ, outerY1);

                // part of base
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                vList.addPoint(innerX1, -.5, innerY1);
                vList.addPoint(outerX1, -.5, outerY1);
                vList.addPoint(outerX2, -.5, outerY2);
            }
            else {
                nList.addPoint(norm1X, normZ, norm1Y);
                nList.addPoint(norm2X, normZ, norm2Y);
                nList.addPoint(norm1X, normZ, norm1Y);
                vList.addPoint(innerX1, innerZ, innerY1);
                vList.addPoint(outerX2, outerZ, outerY2);
                vList.addPoint(outerX1, outerZ, outerY1);

                nList.addPoint(norm1X, normZ, norm1Y);
                nList.addPoint(norm2X, normZ, norm2Y);
                nList.addPoint(norm2X, normZ, norm2Y);
                vList.addPoint(innerX1, innerZ, innerY1);
                vList.addPoint(innerX2, innerZ, innerY2);
                vList.addPoint(outerX2, outerZ, outerY2);

                // part of base
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                vList.addPoint(innerX1, -.5, innerY1);
                vList.addPoint(outerX1, -.5, outerY1);
                vList.addPoint(outerX2, -.5, outerY2);

                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                vList.addPoint(innerX1, -.5, innerY1);
                vList.addPoint(outerX2, -.5, outerY2);
                vList.addPoint(innerX2, -.5, innerY2);
            }
        }
    }

    m_numPoints = vList.getSize();
    m_points = vList.getPoints();
    m_normals = nList.getPoints();
}

void Shapes::addSphereToScene(int latSegments, int longSegments) {
    latSegments = std::max(latSegments, 2);
    longSegments = std::max(longSegments, 3);

    PointsList nList;
    PointsList vList;

    float phiPart  = M_PI / latSegments;
    float thetaPart= 2 * M_PI / longSegments;

    const float RADIUS = .5;

    // vertical angles
    for (int a = 0; a < latSegments; a++) {
        float phi = phiPart * a - M_PI_2;

        float r1 = RADIUS * cos(phi);
        float r2 = RADIUS * cos(phi + phiPart);
        
        float y1 = RADIUS * sin(phi);
        float y2 = RADIUS * sin(phi + phiPart);

        // rotate around current position, r is radius, y stays constant
        for (int b = 0; b < longSegments; b++) {
            float theta = thetaPart * b;
            
            // not rotated point
            float x11 = r1 * cos(theta);
            float z11 = r1 * sin(theta);
            
            // rotated horiz point
            float x12 = r1 * cos(theta + thetaPart);
            float z12 = r1 * sin(theta + thetaPart);
            
            // rotated vert point
            float x21 = r2 * cos(theta);
            float z21 = r2 * sin(theta);
            
            // rotated vert and horiz point
            float x22 = r2 * cos(theta + thetaPart);
            float z22 = r2 * sin(theta + thetaPart);
            
            // bottom triangle
            if (a > 0) {
                float mag = sqrt(x11 * x11 + y1 * y1 + z11 * z11);
                nList.addPoint(x11 / mag, y1 / mag, z11 / mag);
                vList.addPoint(x11, y1, z11);

                mag = sqrt(x21 * x21 + y2 * y2 + z21 * z21);
                nList.addPoint(x21 / mag, y2 / mag, z21 / mag);
                vList.addPoint(x21, y2, z21);

                mag = sqrt(x12 * x12 + y1 * y1 + z12 * z12);
                nList.addPoint(x12 / mag, y1 / mag, z12 / mag);
                vList.addPoint(x12, y1, z12);
            }

            // top triangle
            if (a < latSegments - 1) {
                float mag = sqrt(x12 * x12 + y1 * y1 + z12 * z12);
                nList.addPoint(x12 / mag, y1 / mag, z12 / mag);
                vList.addPoint(x12, y1, z12);

                mag = sqrt(x21 * x21 + y2 * y2 + z21 * z21);
                nList.addPoint(x21 / mag, y2 / mag, z21 / mag);
                vList.addPoint(x21, y2, z21);

                mag = sqrt(x22 * x22 + y2 * y2 + z22 * z22);
                nList.addPoint(x22 / mag, y2 / mag, z22 / mag);
                vList.addPoint(x22, y2, z22);
            }
        }
    }

    m_numPoints = vList.getSize();
    m_points = vList.getPoints();
    m_normals = nList.getPoints();
}

void Shapes::addCylinderToScene(int tessellations, int radiiSegments) {
    tessellations = std::max(tessellations, 1);
    radiiSegments = std::max(radiiSegments, 3);

    PointsList nList;
    PointsList vList;

    float rad = 2 * M_PI / radiiSegments;

    // draw circular
    for (int a = 0; a < radiiSegments; a++) {
        int a1 = a;
        int a2 = a + 1;

        bool first = true;

        // draw flat side
        for (int b = 0; b < tessellations; b++) {
            int b1 = b;
            int b2 = b + 1;

            // norm radius
            float norm1X = cos(rad * a);
            float norm1Y = sin(rad * a);
            float norm2X = cos(rad * (a + 1));
            float norm2Y = sin(rad * (a + 1));


            // first radius
            float refX1 = cos(rad * a1) / 2;
            float innerX1 = refX1 * b1 / tessellations;
            float outerX1 = refX1 * b2 / tessellations;

            float refY1 = sin(rad * a1) / 2;
            float innerY1 = refY1 * b1 / tessellations;
            float outerY1 = refY1 * b2 / tessellations;

            // second radius
            float refX2 = cos(rad * a2) / 2;
            float innerX2 = refX2 * b1 / tessellations;
            float outerX2 = refX2 * b2 / tessellations;

            float refY2 = sin(rad * a2) / 2;
            float innerY2 = refY2 * b1 / tessellations;
            float outerY2 = refY2 * b2 / tessellations;

            float innerZ = ((float) b) / tessellations - .5;
            float outerZ = ((float) b + 1) / tessellations - .5;

            // draw bases
            if (first) {
                first = false;

                // top
                nList.addPoint(0, 1, 0);
                nList.addPoint(0, 1, 0);
                nList.addPoint(0, 1, 0);
                vList.addPoint(innerX1, .5, innerY1);
                vList.addPoint(outerX2, .5, outerY2);
                vList.addPoint(outerX1, .5, outerY1);

                // bottom
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                vList.addPoint(innerX1, -.5, innerY1);
                vList.addPoint(outerX1, -.5, outerY1);
                vList.addPoint(outerX2, -.5, outerY2);
            }
            else {
                // top
                nList.addPoint(0, 1, 0);
                nList.addPoint(0, 1, 0);
                nList.addPoint(0, 1, 0);
                vList.addPoint(innerX1, .5, innerY1);
                vList.addPoint(outerX2, .5, outerY2);
                vList.addPoint(outerX1, .5, outerY1);

                nList.addPoint(0, 1, 0);
                nList.addPoint(0, 1, 0);
                nList.addPoint(0, 1, 0);
                vList.addPoint(innerX1, .5, innerY1);
                vList.addPoint(innerX2, .5, innerY2);
                vList.addPoint(outerX2, .5, outerY2);

                // bottom
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                vList.addPoint(innerX1, -.5, innerY1);
                vList.addPoint(outerX1, -.5, outerY1);
                vList.addPoint(outerX2, -.5, outerY2);

                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                nList.addPoint(0, -1, 0);
                vList.addPoint(innerX1, -.5, innerY1);
                vList.addPoint(outerX2, -.5, outerY2);
                vList.addPoint(innerX2, -.5, innerY2);
            }

            // draw side
            nList.addPoint(norm1X, 0, norm1Y);
            nList.addPoint(norm2X, 0, norm2Y);
            nList.addPoint(norm2X, 0, norm2Y);
            vList.addPoint(refX1, innerZ, refY1);
            vList.addPoint(refX2, outerZ, refY2);
            vList.addPoint(refX2, innerZ, refY2);

            nList.addPoint(norm1X, 0, norm1Y);
            nList.addPoint(norm1X, 0, norm1Y);
            nList.addPoint(norm2X, 0, norm2Y);
            vList.addPoint(refX1, innerZ, refY1);
            vList.addPoint(refX1, outerZ, refY1);
            vList.addPoint(refX2, outerZ, refY2);
        }
    }

    m_numPoints = vList.getSize();
    m_points = vList.getPoints();
    m_normals = nList.getPoints();
}

void Shapes::addMobiusToScene(int tessellations, int radiiSegments) {
    tessellations = std::max(tessellations, 1);
    radiiSegments = std::max(radiiSegments, 3);

    PointsList nList;
    PointsList vList;

    float rad = 2 * M_PI / radiiSegments;

    for(int a = 0; a < radiiSegments; a++) {
        float currRad = rad * a;
        float nextRad = rad * (a + 1);

        for (int b = 0; b < tessellations; b++) {
            float w1 = ((float) b) / tessellations - .5;
            float w2 = ((float) b + 1) / tessellations - .5;

            float genX11 = (1 + w1 * cos(currRad / 2)) * cos(currRad);
            float genY11 = (1 + w1 * cos(currRad / 2)) * sin(currRad);
            float genZ11 = .5 * w1 * sin(currRad / 2);

            float genX12 = (1 + w2 * cos(currRad / 2)) * cos(currRad);
            float genY12 = (1 + w2 * cos(currRad / 2)) * sin(currRad);
            float genZ12 = .5 * w2 * sin(currRad / 2);

            float genX21 = (1 + w1 * cos(nextRad / 2)) * cos(nextRad);
            float genY21 = (1 + w1 * cos(nextRad / 2)) * sin(nextRad);
            float genZ21 = .5 * w1 * sin(nextRad / 2);

            float genX22 = (1 + w2 * cos(nextRad / 2)) * cos(nextRad);
            float genY22 = (1 + w2 * cos(nextRad / 2)) * sin(nextRad);
            float genZ22 = .5 * w2 * sin(nextRad / 2);

            float nx, ny, nz;

            // inner
            calculateNormal(nx, ny, nz, genX12 - genX11, genY12 - genY11, genZ12 - genZ11,
                                        genX21 - genX11, genY21 - genY11, genZ21 - genZ11);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            vList.addPoint(genX11, genY11, genZ11);
            vList.addPoint(genX12, genY12, genZ12);
            vList.addPoint(genX21, genY21, genZ21);

            calculateNormal(nx, ny, nz, genX22 - genX12, genY22 - genY12, genZ22 - genZ12,
                                        genX21 - genX12, genY21 - genY12, genZ21 - genZ12);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            vList.addPoint(genX12, genY12, genZ12);
            vList.addPoint(genX22, genY22, genZ22);
            vList.addPoint(genX21, genY21, genZ21);

            // outer
            calculateNormal(nx, ny, nz, genX21 - genX11, genY21 - genY11, genZ21 - genZ11,
                                        genX12 - genX11, genY12 - genY11, genZ12 - genZ11);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            vList.addPoint(genX11, genY11, genZ11);
            vList.addPoint(genX21, genY21, genZ21);
            vList.addPoint(genX12, genY12, genZ12);

            calculateNormal(nx, ny, nz, genX21 - genX12, genY21 - genY12, genZ21 - genZ12,
                                        genX22 - genX12, genY22 - genY12, genZ22 - genZ12);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            nList.addPoint(nx, ny, nz);
            vList.addPoint(genX12, genY12, genZ12);
            vList.addPoint(genX21, genY21, genZ21);
            vList.addPoint(genX22, genY22, genZ22);
        }
    }

    m_numPoints = vList.getSize();
    m_points = vList.getPoints();
    m_normals = nList.getPoints();
}

void Shapes::addRandomTreeToScene(int tessellations, int branches, int seed) {
    tessellations = std::min(std::max(tessellations / 10, 1), 5);
    branches      = std::min(std::max(branches / 10, 1), 30);
    seed          = std::max(seed, 1);

    PointsList nList;
    PointsList vList;

    srand(seed);

    float botY = -1;
    float topY = 0;

    for (int b = 0; b < branches; b++) {

        float phi = (rand() % 90) * M_PI / 180;
        float rad = (rand() % 360) * M_PI / 180;

        float innerX = 0;
        float innerY = 0;
        float innerZ = topY;

        // add trunk
        for (int i = 0; i < 5; i++) {
            float rad1 = i * 2 * M_PI / 5;
            float rad2 = (i + 1) * 2 * M_PI / 5;

            float outerX1 = cos(rad1);
            float outerX2 = cos(rad2);
            float outerY1 = sin(rad1);
            float outerY2 = sin(rad2);
            float outerZ = botY;

            nList.addPoint(0, 1, 0);
            nList.addPoint(outerX2, 0, outerY2);
            nList.addPoint(outerX1, 0, outerY1);
            vList.addPoint(innerX, innerZ, innerY);
            vList.addPoint(outerX2 / 5, outerZ, outerY2 / 5);
            vList.addPoint(outerX1 / 5, outerZ, outerY1 / 5);

            nList.addPoint(0, -1, 0);
            nList.addPoint(0, -1, 0);
            nList.addPoint(0, -1, 0);
            vList.addPoint(innerX, botY, innerY);
            vList.addPoint(outerX1 / 5, botY, outerY1 / 5);
            vList.addPoint(outerX2 / 5, botY, outerY2 / 5);
        }

        addBranch(1, tessellations, branches, 0, topY, 0, rad, phi, vList, nList);
    }

    m_numPoints = vList.getSize();
    m_points = vList.getPoints();
    m_normals = nList.getPoints();
}

/*
 * Creates a branch at x, y, z with rotations rad, phi
 */
void Shapes::addBranch(int iter, int tessellations, int branches, float x, float y, float z, float rad, float phi, PointsList &vList, PointsList &nList) {
    // draw main branch
    if (iter >= tessellations)
        return;

    float len = ((float) tessellations - iter) / tessellations;

    float r = len * cos(phi);
    float ey = y + len * sin(phi);

    // rotate around current position, r is radius, y stays constant
    float ex = x + r * cos(rad);
    float ez = z + r * sin(rad);

    //for
    float mag = sqrt(ex * ex + ey * ey + ez * ez);
    float nx = ex / mag;
    float ny = ey / mag;
    float nz = ez / mag;

    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);
    nList.addPoint(nx, ny, nz);

    if (phi < 0) {

        // pointing downwards
        vList.addPoint(x, y, z);
        vList.addPoint(x + len / 10, y, z);
        vList.addPoint(ex, ey, ez);

        vList.addPoint(x, y, z + len / 10);
        vList.addPoint(ex, ey, ez);
        vList.addPoint(x + len / 10, y, z);

        vList.addPoint(x, y, z);
        vList.addPoint(ex, ey, ez);
        vList.addPoint(x, y, z + len / 10);
    }
    else {
        // pointing upwards
        vList.addPoint(x, y, z);
        vList.addPoint(ex, ey, ez);
        vList.addPoint(x + len / 10, y, z);

        vList.addPoint(x, y, z + len / 10);
        vList.addPoint(x + len / 10, y, z);
        vList.addPoint(ex, ey, ez);

        vList.addPoint(x, y, z);
        vList.addPoint(x, y, z + len / 10);
        vList.addPoint(ex, ey, ez);
    }

    for (int i = 0; i < branches; i++) {
        float dphi = (rand() % 180 - 90) * M_PI / 180;
        float drad = (rand() % 360) * M_PI / 180;

        addBranch(iter + 1, tessellations, branches, ex, ey, ez, drad, dphi, vList, nList);
    }

}

void Shapes::addFileObjectToScene(int tessellations) {
    // appends the program's absolute path
    string path = QCoreApplication::applicationDirPath().toStdString() + "/" + SPECIAL3_FILE;
    fprintf(stderr, ("Opening file: " + path + "\n").c_str());
    ifstream myfile (path.c_str());

    PointsList vertices;
    PointsList normals;

    PointsList faceVertices;
    PointsList faceNormals;

    if (myfile.is_open()) {
        string line;

        while (myfile.good()) {
            getline(myfile, line);

            // parse line
            if (line.empty())
                continue;

            int space1 = line.find(" ");
            int space2 = line.find(" ", space1 + 1);
            int space3 = line.find(" ", space2 + 1);

            switch (line[0]) {
            case 'v':
                {
                    float p1 = atof(line.substr(space1 + 1, space2 - space1).c_str()) * SPECIAL3_SCALE;
                    float p2 = atof(line.substr(space2 + 1, space3 - space2).c_str()) * SPECIAL3_SCALE;
                    float p3 = atof(line.substr(space3 + 1).c_str()) * SPECIAL3_SCALE;

                    if (line[1] == 'n') {
                        // normal
                        normals.addPoint(p1, p2, p3);
                    }
                    else {
                        // vertex
                        vertices.addPoint(p1, p2, p3);
                    }
                }
                break;
            case 'f':
                {
                    // face, points
                    int v[3];
                    v[0] = atoi(line.substr(space1 + 1, space2 - space1).c_str());
                    v[1] = atoi(line.substr(space2 + 1, space3 - space2).c_str());
                    v[2] = atoi(line.substr(space3 + 1).c_str());

                    // calculate normal?
                    float nx, ny, nz;
                    calculateNormal(nx, ny, nz, vertices, v[0] - 1, v[1] - 1, v[2] - 1);

                    for (int i = 0; i < 3; i++) {
                        int vi = v[i] - 1;

                        faceVertices.addPoint(vertices.getPointX(vi), vertices.getPointY(vi), vertices.getPointZ(vi));
                        if (normals.getSize() <= vi) {
                            faceNormals.addPoint(nx, ny, nz);
                        }
                        else {
                            faceNormals.addPoint(normals.getPointX(vi), normals.getPointY(vi), normals.getPointZ(vi));
                        }
                    }
                }
                break;
            }
        }

        myfile.close();

        m_numPoints = faceVertices.getSize();
        m_points    = faceVertices.getPoints();
        m_normals   = faceNormals.getPoints();
    }
    else {
        myfile.close();
        fprintf(stderr, "File not found for special 3.\n");
        m_numPoints = 0;
    }
}

/*
 * Input: the vertex list and the triangle's three vertex indices
 * Modifies the first three parameters to be the x, y, z coordinates of the normal.
 */
void Shapes::calculateNormal(float &nx, float &ny, float &nz, PointsList &pList, int v1, int v2, int v3) {
    float v1x = pList.getPointX(v1);
    float v1y = pList.getPointY(v1);
    float v1z = pList.getPointZ(v1);

    float v2x = pList.getPointX(v2);
    float v2y = pList.getPointY(v2);
    float v2z = pList.getPointZ(v2);

    float v3x = pList.getPointX(v3);
    float v3y = pList.getPointY(v3);
    float v3z = pList.getPointZ(v3);

    float ux = v2x - v1x;
    float uy = v2y - v1y;
    float uz = v2z - v1z;

    float vx = v3x - v1x;
    float vy = v3y - v1y;
    float vz = v3z - v1z;

    calculateNormal(nx, ny, nz, ux, uy, uz, vx, vy, vz);
}

/*
 * Input: the x, y, z values of the two difference vectors which constitute the triangle.
 * Modifies the first three parameters to be the x, y, z coordinates of the normal.
 */
void Shapes::calculateNormal(float &nx, float &ny, float &nz, float ux, float uy, float uz, float vx, float vy, float vz) {
    nx = uy * vz - uz * vy;
    ny = uz * vx - ux * vz;
    nz = ux * vy - uy * vx;

    float mag = sqrt(nx * nx + ny * ny + nz * nz);

    nx /= mag;
    ny /= mag;
    nz /= mag;
}
