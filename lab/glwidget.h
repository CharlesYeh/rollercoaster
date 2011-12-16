#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QHash>
#include <QString>
#include <QTimer>
#include <QTime>

#include "camera.h"
#include "vector.h"
#include "resourceloader.h"

class QGLShaderProgram;
class QGLFramebufferObject;

class GameEngine;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

protected:
    // Overridden QGLWidget methods
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void wheelEvent(QWheelEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);

    Vector3 getMouseRay(const Vector2 &mouse, const OrbitCamera *camera);

    // Initialization code
    void initializeResources();
    void loadCubeMap();
    void createShaderPrograms();
    void createFramebufferObjects(int width, int height);
    void createBlurKernel(int radius, int width, int height, GLfloat* kernel, GLfloat* offsets);

    GLuint loadTexture(const QString &path);

    // Drawing code
    void applyOrthogonalCamera(float width, float height);
    void applyPerspectiveCamera(float width, float height);
    void renderTexturedQuad(int width, int height, bool flip);
    void renderBlur(int width, int height);
    void renderScene();
    void paintText();


private:
    GLuint m_particleTextureID;

    bool m_mouseDown;
    bool m_showBoxes, m_showCollisions;

    QTimer m_timer;
    QTime m_clock;
    int m_prevTime;
    float m_prevFps, m_fps;
    Vector2 m_currMousePos, m_prevMousePos;
    OrbitCamera *m_camera;

    // Resources
    QHash<QString, QGLShaderProgram *> m_shaderPrograms; // hash map of all shader programs
    QHash<QString, QGLFramebufferObject *> m_framebufferObjects; // hash map of all framebuffer objects

    GLuint m_skybox; // skybox call list ID
    GLuint m_cubeMap; // cubeMap texture ID
    QFont m_font; // font for rendering text

    GameEngine *m_gameEngine;
};

#endif // GLWIDGET_H
