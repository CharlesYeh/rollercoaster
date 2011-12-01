#include "SupportCanvas3D.h"
#include "GameScene.h"
#include "camera/CamtransCamera.h"
#include <Settings.h>
#include <QFileDialog>
#include <QMouseEvent>
#include <QMessageBox>
#include <qgl.h>
#ifdef __WIN32
#include <gl/glext.h>
#endif

SupportCanvas3D::SupportCanvas3D(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    m_isDragging = false;
    m_scene = new GameScene();

    m_camera = new CamtransCamera();

    settingsChanged();
}

SupportCanvas3D::~SupportCanvas3D()
{
    delete m_camera;
    delete m_scene;
}

CamtransCamera *SupportCanvas3D::getCamera()
{
    return m_camera;
}

void SupportCanvas3D::settingsChanged()
{

}

void SupportCanvas3D::setScene(OpenGLScene *scene)
{
    delete m_scene;
    m_scene = scene;
}

void SupportCanvas3D::copyPixels(int width, int height, BGRA *data)
{
    glReadPixels(0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, data);
    cout << "copied " << width << "x" << height << endl;

    // Flip the image and since OpenGL uses an origin in the lower left and we an origin in the upper left
    for (int y = 0; y < (height + 1) / 2; y++)
        for (int x = 0; x < width; x++)
            swap(data[x + y * width], data[x + (height - y - 1) * width]);
}

void SupportCanvas3D::updateCameraHeightAngle()
{
    // The height angle is half the overall field of view of the camera
    m_camera->setHeightAngle(settings.cameraFov / 2);
}

void SupportCanvas3D::updateCameraTranslation()
{
    m_camera->translate(Vector4(settings.cameraPosX - m_oldPosX, settings.cameraPosY - m_oldPosY, settings.cameraPosZ - m_oldPosZ, 0));
    m_oldPosX = settings.cameraPosX;
    m_oldPosY = settings.cameraPosY;
    m_oldPosZ = settings.cameraPosZ;
}

void SupportCanvas3D::updateCameraRotationU()
{
    m_camera->rotateU(settings.cameraRotU - m_oldRotU);
    m_oldRotU = settings.cameraRotU;
}

void SupportCanvas3D::updateCameraRotationV()
{
    m_camera->rotateV(settings.cameraRotV - m_oldRotV);
    m_oldRotV = settings.cameraRotV;
}

void SupportCanvas3D::updateCameraRotationN()
{
    m_camera->rotateN(settings.cameraRotN - m_oldRotN);
    m_oldRotN = settings.cameraRotN;
}

void SupportCanvas3D::updateCameraClip()
{
    m_camera->setClip(settings.cameraNear, settings.cameraFar);
}


void SupportCanvas3D::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        getCamera()->mouseDown(event->x(), event->y());
        m_isDragging = true;
        update();
    }
}

void SupportCanvas3D::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging)
    {
        getCamera()->mouseDragged(event->x(), event->y());
        update();
    }
}

void SupportCanvas3D::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_isDragging && event->button() == Qt::RightButton)
    {
        getCamera()->mouseUp(event->x(), event->y());
        m_isDragging = false;
        update();
    }
}

void SupportCanvas3D::wheelEvent(QWheelEvent *event)
{
    getCamera()->mouseScrolled(event->delta());
    update();
}

void SupportCanvas3D::resizeEvent(QResizeEvent *event)
{
    emit aspectRatioChanged();
}
