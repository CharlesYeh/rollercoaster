#include <qgl.h>

#include "GameScene.h"
#include "CS123SceneData.h"
#include "Camera.h"
#include "math/CS123Matrix.h"


GameScene::GameScene()
{
    // TODO: [SCENEVIEW] Set up anything you need for your Sceneview scene here...
    glEnable(GL_NORMALIZE);

    m_light.type = LIGHT_DIRECTIONAL;
    m_light.dir = Vector4(1, -1, 0, 1);
    m_light.color.r = m_light.color.g = m_light.color.b = 1;
    m_light.id = 0;
}

GameScene::~GameScene()
{
    // TODO: [SCENEVIEW] Don't leak memory!

}

void GameScene::setLights(const Camera *follow)
{

    for (int id = 0; id < NUM_OPENGL_LIGHTS; ++id)
        glDisable(GL_LIGHT0 + id);

    vector<CS123SceneLightData>::iterator iterLight;
    for(iterLight = m_lights->begin(); iterLight != m_lights->end(); iterLight++) {
        setLight(*iterLight);
    }

}

void GameScene::renderGeometry(bool useMaterials)
{
    // TODO: [SCENEVIEW] Fill this in...
    //
    // This is where you should render the geometry of the scene. Use what you
    // know about OpenGL and leverage your Shapes classes to get the job done.
    //

    glDisable(GL_LIGHTING);
    cout << "render " << endl;
    //setLight(m_light);

    glMatrixMode(GL_MODELVIEW);

    /*for (unsigned int i = 0; i < m_shapes->size(); i++) {
        Shapes *s             = (*m_shapes)[i];
        CS123SceneMaterial m  = (*m_materials)[i];
        Matrix4x4 &t          = (*m_matrices)[i];

        glPushMatrix();
        glMultMatrixd(t.getTranspose().data);
        glBegin(GL_TRIANGLES);

        if (useMaterials) {
            applyMaterial(m);
        }

        s->drawCache();

        glEnd();
        glPopMatrix();

    }*/

    glColor3f(1, 1, 1);

    GLUquadric *m_quadric = gluNewQuadric();
    gluSphere(m_quadric, 1, 10, 10);

    glBegin(GL_TRIANGLES);

    glNormal3f(0, 1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f( 1, 1, 0);

    glEnd();
}

void GameScene::renderNormals()
{
    // TODO: [SCENEVIEW] Fill this in...
    //
    // Rendering normals is an **optional** part of Sceneview (sorry, not extra credit)
    // You can put all of your renderNormal() calls here if you want to render normals.
    //
    // HINT: Rendering normals can be a helpful debugging tool if things don't look
    // quite right. Your Shapes might be incorrect, and if that's the case, you'll
    // need to go back and fix your buggy shapes code before turning in Sceneview.
    //

}

