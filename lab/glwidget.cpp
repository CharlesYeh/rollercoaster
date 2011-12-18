#include "glwidget.h"

#include <iostream>
#include <QFileDialog>
#include <QGLFramebufferObject>
#include <QGLShaderProgram>
#include <QMouseEvent>
#include <QTime>
#include <QTimer>
#include <QWheelEvent>
#include "glm.h"
#include "game/gameengine.h"
#include <sstream>

using namespace std;

extern "C"
{
    extern void APIENTRY glActiveTexture(GLenum);
}

static const int MAX_FPS = 120;

/**
  Constructor.  Initialize all member variables here.
 **/
GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent),
    m_timer(this), m_prevTime(0), m_prevFps(0.f), m_fps(0.f),
    m_font("Deja Vu Sans Mono", 8, 4)
{
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);

    m_camera = new OrbitCamera();
    m_camera->center = Vector3(0.f, 0.f, 0.f);
    m_camera->up = Vector3(0.f, 1.f, 0.f);
    m_camera->zoom = 3.5f;
    m_camera->theta = M_PI * 1.5f, m_camera->phi = 0.2f;
    m_camera->fovy = 60.f;

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(update()));

    m_showCollisions = false;
}

/**
  Destructor.  Delete any 'new'ed objects here.
 **/
GLWidget::~GLWidget()
{
    //----------------------------CLEAN----------------------------
    m_gameEngine->stop();

    while (m_gameEngine->running()) {
        // wait
    }

    map<string, Model> *models = m_gameEngine->getModels();
    for (map<string, Model>::iterator iter = models->begin(); iter != models->end(); iter++) {
        Model &m = iter->second;
        glmDelete(m.model);
    }

    delete m_gameEngine;
    delete m_camera;

    foreach (QGLShaderProgram *sp, m_shaderPrograms)
        delete sp;
    foreach (QGLFramebufferObject *fbo, m_framebufferObjects)
        delete fbo;
    glDeleteLists(m_skybox, 1);
    const_cast<QGLContext *>(context())->deleteTexture(m_cubeMap);

    glDeleteTextures(1, &m_particleTextureID);
}

/**
  Initialize the OpenGL state and start the drawing loop.
 **/
void GLWidget::initializeGL()
{
    // Set up OpenGL
    glEnable(GL_TEXTURE_2D);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glDisable(GL_DITHER);
    glDisable(GL_LIGHTING);

    //--------------------lighting--------------------
    /*glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float lightpos[] = {1, 1, 1, 1};
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;

    glMaterialf(GL_FRONT, GL_SPECULAR, 1);
    glMaterialf(GL_FRONT, GL_SHININESS, 1);
    glEnable(GL_DEPTH_TEST);*/
    //------------------end lighting------------------

    glShadeModel(GL_FLAT);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Load resources, including creating shader programs and framebuffer objects
    initializeResources();

    // Start the drawing timer
    m_timer.start(1000.0f / MAX_FPS);
}

/**
  Initialize all resources.
  This includes models, textures, call lists, shader programs, and framebuffer objects.
 **/
void GLWidget::initializeResources()
{
    cout << "Using OpenGL Version " << glGetString(GL_VERSION) << endl << endl;
    // Ideally we would now check to make sure all the OGL functions we use are supported
    // by the video card.  But that's a pain to do so we're not going to.
    cout << "--- Loading Resources ---" << endl;

    m_skybox = ResourceLoader::loadSkybox();
    cout << "Loaded skybox..." << endl;

    loadCubeMap();
    cout << "Loaded cube map..." << endl;

    //-----------------------------LOAD OBJECTS-----------------------------

    createShaderPrograms();
    cout << "Loaded shader programs..." << endl;

    createFramebufferObjects(width(), height());
    cout << "Loaded framebuffer objects..." << endl;

    cout << " --- Finish Loading Resources ---" << endl;

    m_particleTextureID = loadTexture("textures/particle1.bmp"); //textureid 1

    m_gameEngine = new GameEngine();
    m_gameEngine->setCamera(this->m_camera);
    m_gameEngine->start();
}

/**
  Load a cube map for the skybox
 **/
void GLWidget::loadCubeMap()
{
    QList<QFile *> fileList; 
    fileList.append(new QFile("textures/skybox1/a_right1.png"));
    fileList.append(new QFile("textures/skybox1/a_left2.png"));
    fileList.append(new QFile("textures/skybox1/a_top3.png"));
    fileList.append(new QFile("textures/skybox1/a_bottom4.png"));
    fileList.append(new QFile("textures/skybox1/a_front5.png"));
    fileList.append(new QFile("textures/skybox1/a_back6.png"));
/*
    fileList.append(new QFile("textures/skybox2/b_right1.png"));
    fileList.append(new QFile("textures/skybox2/b_left2.png"));
    fileList.append(new QFile("textures/skybox2/b_top3.png"));
    fileList.append(new QFile("textures/skybox2/b_bottom4.png"));
    fileList.append(new QFile("textures/skybox2/b_front5.png"));
    fileList.append(new QFile("textures/skybox2/b_back6.png"));

    fileList.append(new QFile("textures/astra/posx.jpg"));
    fileList.append(new QFile("textures/astra/negx.jpg"));
    fileList.append(new QFile("textures/astra/posy.jpg"));
    fileList.append(new QFile("textures/astra/negy.jpg"));
    fileList.append(new QFile("textures/astra/posz.jpg"));
    fileList.append(new QFile("textures/astra/negz.jpg"));
*/

    m_cubeMap = ResourceLoader::loadCubeMap(fileList);
}

GLuint GLWidget::loadTexture(const QString &path) {
   QFile file(path);
   QImage image, texture;
   if (!file.exists()) return -1;
   image.load(file.fileName());
   texture = QGLWidget::convertToGLFormat(image);

   GLuint id = 0;
   glGenTextures(1, &id);
   glBindTexture(GL_TEXTURE_2D, id);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.bits());
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

   return id;
}

/**
  Create shader programs.
 **/
void GLWidget::createShaderPrograms()
{
    const QGLContext *ctx = context();
    m_shaderPrograms["reflect"] = ResourceLoader::newShaderProgram(ctx, "shaders/reflect.vert",
                                                                        "shaders/reflect.frag");
    m_shaderPrograms["refract"] = ResourceLoader::newShaderProgram(ctx, "shaders/refract.vert",
                                                                        "shaders/refract.frag");
    m_shaderPrograms["brightpass"] = ResourceLoader::newFragShaderProgram(ctx, "shaders/brightpass.frag");
    m_shaderPrograms["blur"] = ResourceLoader::newFragShaderProgram(ctx, "shaders/blur.frag");
}

/**
  Allocate framebuffer objects.

  @param width: the viewport width
  @param height: the viewport height
 **/
void GLWidget::createFramebufferObjects(int width, int height)
{
    // Allocate the main framebuffer object for rendering the scene to
    // This needs a depth attachment
    m_framebufferObjects["fbo_0"] = new QGLFramebufferObject(width, height, QGLFramebufferObject::Depth,
                                                             GL_TEXTURE_2D, GL_RGB16F_ARB);
    m_framebufferObjects["fbo_0"]->format().setSamples(16);
    // Allocate the secondary framebuffer obejcts for rendering textures to (post process effects)
    // These do not require depth attachments
    m_framebufferObjects["fbo_1"] = new QGLFramebufferObject(width, height, QGLFramebufferObject::NoAttachment,
                                                             GL_TEXTURE_2D, GL_RGB16F_ARB);
    // TODO: Create another framebuffer here.  Look up two lines to see how to do this... =.=
    m_framebufferObjects["fbo_2"] = new QGLFramebufferObject(width, height, QGLFramebufferObject::NoAttachment,
                                                             GL_TEXTURE_2D, GL_RGB16F_ARB);
}

/**
  Called to switch to an orthogonal OpenGL camera.
  Useful for rending a textured quad across the whole screen.

  @param width: the viewport width
  @param height: the viewport height
**/
void GLWidget::applyOrthogonalCamera(float width, float height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0.f, -1.f, 1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
  Called to switch to a perspective OpenGL camera.

  @param width: the viewport width
  @param height: the viewport height
**/
void GLWidget::applyPerspectiveCamera(float width, float height)
{
    float ratio = ((float) width) / height;
    Vector3 dir(-Vector3::fromAngles(m_camera->theta, m_camera->phi));
    Vector3 eye(m_camera->center - dir * m_camera->zoom);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(m_camera->fovy, ratio, 0.1f, 1000.f);
    gluLookAt(eye.x, eye.y, eye.z, eye.x + dir.x, eye.y + dir.y, eye.z + dir.z,
              m_camera->up.x, m_camera->up.y, m_camera->up.z);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/**
  Draws the scene to a buffer which is rendered to the screen when this function exits.
 **/
void GLWidget::paintGL()
{
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Update the fps
    int time = m_clock.elapsed();
    m_fps = 1000.f / (time - m_prevTime);
    m_prevTime = time;
    int width = this->width();
    int height = this->height();

    // Render the scene to a framebuffer
    //m_framebufferObjects["fbo_0"]->bind();
    applyPerspectiveCamera(width, height);
    renderScene();

    //-----------------------------RENDER-----------------------------

    //m_framebufferObjects["fbo_0"]->release();

    // Copy the rendered scene into framebuffer 1
    /*m_framebufferObjects["fbo_0"]->blitFramebuffer(m_framebufferObjects["fbo_1"],
                                                   QRect(0, 0, width, height), m_framebufferObjects["fbo_0"],
                                                   QRect(0, 0, width, height), GL_COLOR_BUFFER_BIT, GL_NEAREST);

    applyOrthogonalCamera(width, height);
    glBindTexture(GL_TEXTURE_2D, m_framebufferObjects["fbo_0"]->texture());
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // Enable alpha blending and render the texture to the screen
    renderTexturedQuad(width, height, false);

    // TODO: Add drawing code here
    applyOrthogonalCamera(width, height);
    glBindTexture(GL_TEXTURE_2D, m_framebufferObjects["fbo_1"]->texture());
    renderTexturedQuad(width, height, true);
    glBindTexture(GL_TEXTURE_2D, 0);

    m_framebufferObjects["fbo_2"]->bind();
    m_shaderPrograms["brightpass"]->bind();
    glBindTexture(GL_TEXTURE_2D, m_framebufferObjects["fbo_1"]->texture());
    renderTexturedQuad(width, height, true);
    glBindTexture(GL_TEXTURE_2D, 0);
    m_shaderPrograms["brightpass"]->release();
    m_framebufferObjects["fbo_2"]->release();

    // TODO: Uncomment this section in step 2 of the lab

    float scales[] = {4.f,8.f,16.f,32.f};
    for (int i = 0; i < 4; ++i)
    {
        // Render the blurred brightpass filter result to fbo 1
        renderBlur(width / scales[i], height / scales[i]);

        // Bind the image from fbo to a texture
        glBindTexture(GL_TEXTURE_2D, m_framebufferObjects["fbo_1"]->texture());
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        // Enable alpha blending and render the texture to the screen
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_ONE);
        glTranslatef(0.f, (scales[i] - 1) * -height, 0.f);
        renderTexturedQuad(width * scales[i], height * scales[i], false);
        glDisable(GL_BLEND);
        glBindTexture(GL_TEXTURE_2D, 0);
    }*/

    paintText();
}

/**
  Renders the scene.  May be called multiple times by paintGL() if necessary.
**/
void GLWidget::renderScene() {
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    glClear(GL_DEPTH_BUFFER_BIT);

    // Enable cube maps and draw the skybox
    glEnable(GL_TEXTURE_CUBE_MAP);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);
    glCallList(m_skybox);

    // Enable culling (back) faces for rendering the dragon
    glEnable(GL_CULL_FACE);
    /*
    // Render the dragon with the refraction shader bound
    glActiveTexture(GL_TEXTURE0);
    m_shaderPrograms["refract"]->bind();
    m_shaderPrograms["refract"]->setUniformValue("CubeMap", GL_TEXTURE0);
    glPushMatrix();
    glTranslatef(-1.25f, 0.f, 0.f);
    glCallList(m_dragon.idx);
    glPopMatrix();
    m_shaderPrograms["refract"]->release();

    // Render the dragon with the reflection shader bound
    m_shaderPrograms["reflect"]->bind();
    m_shaderPrograms["reflect"]->setUniformValue("CubeMap", GL_TEXTURE0);
    glPushMatrix();
    glTranslatef(1.25f,0.f,0.f);
    glCallList(m_dragon.idx);

    glPopMatrix();
    m_shaderPrograms["reflect"]->release();
    */
    //-----------------------------RENDER-----------------------------

    glShadeModel(GL_SMOOTH);
    glActiveTexture(GL_TEXTURE0);
    m_shaderPrograms["reflect"]->bind();
    m_shaderPrograms["reflect"]->setUniformValue("CubeMap", GL_TEXTURE0);

    vector<GameObject*> *objs = m_gameEngine->getGameObjects();
    vector<GameObject*>::iterator iter;
    //m_gameEngine->mutex.lock();
    for (iter = objs->begin(); iter != objs->end(); iter++)
    {
        GameObject *gobj = (*iter);
        if (gobj->getIsAlive())
        {
            Model model = gobj->getModel();
            Vector3 pos = gobj->getPosition();
            Vector3 rot = gobj->getRotation();

            glPushMatrix();
            glColor3f(1, 0, 0);
            glTranslatef(pos.x, pos.y, pos.z);
            glRotatef(gobj->getAngleRotation(), rot.x, rot.y, rot.z);
            glCallList(model.idx);

            glPopMatrix();
        }
    }

    m_shaderPrograms["reflect"]->release();

    // Disable culling, depth testing and cube maps
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_CUBE_MAP,0);
    glDisable(GL_TEXTURE_CUBE_MAP);

    //-----------------particles-----------------
    std::vector<ParticleEmitter*> *emitters = m_gameEngine->getEmitters();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, m_particleTextureID);

    for (unsigned int i = 0; i < emitters->size(); i++) {
        ParticleEmitter* em = emitters->at(i);
        if (em->getIsAlive()) {
            em->updateParticles();
            em->drawParticles();
        }
    }
    glDisable(GL_TEXTURE_2D);

    if (m_showCollisions) {
        m_gameEngine->mutex.lock();
        glColor3f(1, 0, 0);
        for (iter = objs->begin(); iter != objs->end(); iter++) {
            GameObject *gobj = (*iter);
            if (!gobj->getIsAlive())
                continue;
            gobj->drawBoundingBox();
        }

        glColor3f(1, 1, 0);
        set<CollisionPair> *cp = m_gameEngine->getCollisions();
        for (set<CollisionPair>::iterator iter = cp->begin(); iter != cp->end(); iter++) {
            CollisionPair p = *iter;
            if (!p.m_obj1->getIsAlive() || !p.m_obj2->getIsAlive())
                continue;

            p.m_obj1->drawBoundingBox();
            p.m_obj2->drawBoundingBox();
        }
        m_gameEngine->mutex.unlock();
    }

}

/**
  Run a gaussian blur on the texture stored in fbo 2 and
  put the result in fbo 1.  The blur should have a radius of 2.

  @param width: the viewport width
  @param height: the viewport height
**/
void GLWidget::renderBlur(int width, int height)
{
    int radius = 4;
    int dim = radius * 2 + 1;
    GLfloat kernel[dim * dim];
    GLfloat offsets[dim * dim * 2];
    createBlurKernel(radius, width, height, &kernel[0], &offsets[0]);
    // TODO: Finish filling this in

    m_framebufferObjects["fbo_1"]->bind();
    m_shaderPrograms["blur"]->bind();
    m_shaderPrograms["blur"]->setUniformValueArray("offsets", offsets, dim * dim, 2);
    m_shaderPrograms["blur"]->setUniformValueArray("kernel", kernel, dim * dim, 1);
    m_shaderPrograms["blur"]->setUniformValue("arraySize", dim*dim);

    glBindTexture(GL_TEXTURE_2D, m_framebufferObjects["fbo_2"]->texture());

    // draw rect
    renderTexturedQuad(width, height, false);

    m_shaderPrograms["blur"]->release();
    m_framebufferObjects["fbo_1"]->release();
    glBindTexture(GL_TEXTURE_2D, 0);

}

/**
  Called when the mouse is dragged.  Rotates the camera based on mouse movement.
**/
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_currMousePos.x = event->x();
    m_currMousePos.y = event->y();

    if (event->buttons() & Qt::RightButton)
    {
        m_camera->mouseMove(m_currMousePos - m_prevMousePos);
        m_prevMousePos = m_currMousePos;
    }

    //on left click, fire
    if (event->buttons() & Qt::LeftButton) {
        Vector3 dir(getMouseRay(m_currMousePos, m_camera));
        m_gameEngine->fireProjectile(dir);
    }
}

/**
  Record a mouse press position.
 **/
void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_currMousePos.x = event->x();
    m_currMousePos.y = event->y();

    //on left click, fire
    if (event->buttons() & Qt::LeftButton) {
        Vector3 dir(getMouseRay(m_currMousePos, m_camera));
        m_gameEngine->fireProjectile(dir);
    }

    m_mouseDown = true;
    m_prevMousePos = m_currMousePos;
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    m_mouseDown = false;
}

Vector3 GLWidget::getMouseRay(const Vector2 &mouse, const OrbitCamera *camera)
{
    int viewport[4];
    double worldX, worldY, worldZ, modelviewMatrix[16], projectionMatrix[16];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelviewMatrix);
    glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix);
    gluUnProject(mouse.x, viewport[3] - mouse.y - 1, 1,
                 modelviewMatrix, projectionMatrix, viewport,
                 &worldX, &worldY, &worldZ);

    Vector3 wpt(worldX, worldY, worldZ);
    Vector3 peye = camera->center;
    peye.normalize();

    Vector3 dir(wpt - peye);
    return dir;
}

/**
  Called when the mouse wheel is turned.  Zooms the camera in and out.
**/
void GLWidget::wheelEvent(QWheelEvent *event)
{
    if (event->orientation() == Qt::Vertical)
    {
        m_camera->mouseWheel(event->delta());
    }
}

/**
  Called when the GLWidget is resized.
 **/
void GLWidget::resizeGL(int width, int height)
{
    // Resize the viewport
    glViewport(0, 0, width, height);

    // Reallocate the framebuffers with the new window dimensions
    foreach (QGLFramebufferObject *fbo, m_framebufferObjects)
    {
        const QString &key = m_framebufferObjects.key(fbo);
        QGLFramebufferObjectFormat format = fbo->format();
        delete fbo;
        m_framebufferObjects[key] = new QGLFramebufferObject(width, height, format);
    }
}

/**
  Draws a textured quad. The texture most be bound and unbound
  before and after calling this method - this method assumes that the texture
  has been bound before hand.

  @param w: the width of the quad to draw
  @param h: the height of the quad to draw
  @param flip: flip the texture vertically
**/
void GLWidget::renderTexturedQuad(int width, int height, bool flip) {
    // Clamp value to edge of texture when texture index is out of bounds
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // Draw the  quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, flip ? 1.0f : 0.0f);
    glVertex2f(0.0f, 0.0f);
    glTexCoord2f(1.0f, flip ? 1.0f : 0.0f);
    glVertex2f(width, 0.0f);
    glTexCoord2f(1.0f, flip ? 0.0f : 1.0f);
    glVertex2f(width, height);
    glTexCoord2f(0.0f, flip ? 0.0f : 1.0f);
    glVertex2f(0.0f, height);
    glEnd();
}

/**
  Creates a gaussian blur kernel with the specified radius.  The kernel values
  and offsets are stored.

  @param radius: The radius of the kernel to create.
  @param width: The width of the image.
  @param height: The height of the image.
  @param kernel: The array to write the kernel values to.
  @param offsets: The array to write the offset values to.
**/
void GLWidget::createBlurKernel(int radius, int width, int height,
                                                    GLfloat* kernel, GLfloat* offsets)
{
    int size = radius * 2 + 1;
    float sigma = radius / 3.0f;
    float twoSigmaSigma = 2.0f * sigma * sigma;
    float rootSigma = sqrt(twoSigmaSigma * M_PI);
    float total = 0.0f;
    float xOff = 1.0f / width, yOff = 1.0f / height;
    int offsetIndex = 0;
    for (int y = -radius, idx = 0; y <= radius; ++y)
    {
        for (int x = -radius; x <= radius; ++x,++idx)
        {
            float d = x * x + y * y;
            kernel[idx] = exp(-d / twoSigmaSigma) / rootSigma;
            total += kernel[idx];
            offsets[offsetIndex++] = x * xOff;
            offsets[offsetIndex++] = y * yOff;
        }
    }
    for (int i = 0; i < size * size; ++i)
    {
        kernel[i] /= total;
    }
}

/**
  Handles any key press from the keyboard
 **/
void GLWidget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_S:
        {
        QImage qi = grabFrameBuffer(false);
        QString filter;
        QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG Image (*.png)"), &filter);
        qi.save(QFileInfo(fileName).absoluteDir().absolutePath() + "/" + QFileInfo(fileName).baseName() + ".png", "PNG", 100);
        }
        break;
    case Qt::Key_C:
        m_showCollisions = !m_showCollisions;
        break;
    }
}

/**
  Draws text for the FPS and screenshot prompt
 **/
void GLWidget::paintText()
{
    glColor3f(1.f, 1.f, 1.f);

    // Combine the previous and current framerate
    if (m_fps >= 0 && m_fps < 1000)
    {
       m_prevFps *= 0.95f;
       m_prevFps += m_fps * 0.05f;
    }

    // QGLWidget's renderText takes xy coordinates, a string, and a font
    renderText(10, 20, "FPS: " + QString::number((int) (m_prevFps)), m_font);
    renderText(10, 35, "S: Save screenshot", m_font);
    renderText(10, 50, "C: Highlight collided bounding boxes", m_font);

    glColor3f(1, .8, 0);

    // show score board
    QFont scoreFont = QFont("Courier New", 24, 2);
    QFontMetrics fm(scoreFont);

    ostringstream oss;
    oss << "HITS: " << m_gameEngine->getHits();
    QString qs = QString(oss.str().c_str());

    int x = (width() - fm.width(qs)) / 2 + 10;
    renderText(x, 75, qs, scoreFont);

    // show accuracy
    float acc = 10000 * m_gameEngine->getHits() / max(1, m_gameEngine->getFired()) / 100.f;

    oss.str("");
    oss << "Accuracy: " << acc << " %";
    qs = QString(oss.str().c_str());

    x = (width() - QFontMetrics(m_font).width(qs)) / 2;
    renderText(x, 100, qs);

    /*QString str = m_gameEngine->getStory();
    QFontMetrics fm(m_font);
    int x = (this->width() - m_gameEngine->getFullStoryWidth(fm)) / 2;

    renderText(x, 65, str);*/

    glColor3f(1, 1, 1);
}
