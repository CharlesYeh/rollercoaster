#include "Scene.h"
#include "Camera.h"
#include "CS123SceneData.h"
#include "CS123ISceneParser.h"
#include <QtGlobal>
#include <queue>

#include "math/CS123Matrix.h"

using namespace std;

Scene::Scene() //: m_camera(NULL)
{
    m_textMaps  = new map<string, QImage>();
    m_types     = new vector<int>();
    m_shapes    = new vector<Shapes *>();
    m_materials = new vector<CS123SceneMaterial>();
    m_fileMaps  = new vector<CS123SceneFileMap>();
    m_matrices  = new vector<Matrix4x4>();

    m_lights = new vector<CS123SceneLightData>();
}

Scene::~Scene()
{
    // Do not delete m_camera, it is owned by SupportCanvas3D
    /*for (unsigned int i = 0; i < m_shapes->size(); i++) {
        Shapes *shape = m_shapes->at(i);
        delete shape;
    }*/

    delete m_textMaps;
    delete m_types;
    delete m_shapes;
    delete m_materials;
    delete m_fileMaps;
    delete m_matrices;

    delete m_lights;
}

void Scene::parse(Scene *sceneToFill, CS123ISceneParser *parser)
{
    // TODO: load scene into sceneToFill using setGlobal(), addLight(), addPrimitive(), and finishParsing()
    CS123SceneGlobalData gData;
    if (parser->getGlobalData(gData)) {
        sceneToFill->setGlobal(gData);
    }

    // lights
    int l = parser->getNumLights();
    CS123SceneLightData lightData;

    for (int i = 0; i < l; i++) {
        if (parser->getLightData(i, lightData)) {
            sceneToFill->addLight(lightData);
        }
    }

    Matrix4x4 iMat = Matrix4x4::identity();
    Scene::parseNode(sceneToFill, parser->getRootNode(), iMat);
}

//void Scene::setCamera(Camera *newCamera)
//{
//    // Do not delete the old m_camera, it is owned by SupportCanvas3D
//    m_camera = newCamera;
//}

void Scene::parseNode(Scene *sceneToFill, CS123SceneNode *curr, Matrix4x4 transf) {
/*
    vector<CS123SceneNode*>::iterator itTrans;
    for (unsigned int i = 0; i < curr->transformations.size(); i++) {
        CS123SceneTransformation *sceneTrans = curr->transformations[i];

        // determine type
        switch(sceneTrans->type) {
        case TRANSFORMATION_TRANSLATE:
            transf = transf * getTransMat(sceneTrans->translate);
            break;
        case TRANSFORMATION_SCALE:
            transf = transf * getScaleMat(sceneTrans->scale);
            break;
        case TRANSFORMATION_ROTATE:
            transf = transf * getRotMat(Vector4::zero(), sceneTrans->rotate, sceneTrans->angle);
            break;
        case TRANSFORMATION_MATRIX:
            transf = transf * sceneTrans->matrix;
            break;
        }
    }

    // add primitives
    vector<CS123ScenePrimitive*>::iterator itPrim;
    for (itPrim = curr->primitives.begin(); itPrim < curr->primitives.end(); itPrim++) {
        CS123ScenePrimitive &prim = **itPrim;
        // pass in transformation

        // multiply by global vars
        for(int c = 0; c < 4; c++) {
            prim.material.cAmbient.channels[c]    *= sceneToFill->m_global.ka;
            prim.material.cDiffuse.channels[c]    *= sceneToFill->m_global.kd;
            prim.material.cSpecular.channels[c]   *= sceneToFill->m_global.ks;
            prim.material.cTransparent.channels[c]*= sceneToFill->m_global.kt;
        }

        sceneToFill->addPrimitive(prim, transf);
    }

    // add children
    vector<CS123SceneNode*>::iterator itChild;
    for (itChild = curr->children.begin(); itChild < curr->children.end(); itChild++) {
        parseNode(sceneToFill, *itChild, transf);
    }*/
}

void Scene::addPrimitive(CS123ScenePrimitive &scenePrimitive, const Matrix4x4 &matrix)
{
    /*Shapes *shape = new Shapes();
    shape->drawShape(scenePrimitive.type, 30, 30, 30, matrix, true);

    m_types->push_back(scenePrimitive.type);
    m_shapes->push_back(shape);

    // transformation
    m_matrices->push_back(matrix);

    m_materials->push_back(scenePrimitive.material);

    // save file maps
    CS123SceneFileMap *textureMap = scenePrimitive.material.textureMap;
    m_fileMaps->push_back(*textureMap);

    string filename = textureMap->filename;
    if (textureMap->isUsed && m_textMaps->count(filename) == 0) {
        (*m_textMaps)[filename] = QImage(filename.c_str());
    }
*/
}

void Scene::addLight(const CS123SceneLightData &sceneLight)
{
    m_lights->push_back(sceneLight);
}

void Scene::setGlobal(const CS123SceneGlobalData &global)
{
    m_global = global;
}

vector<int> *Scene::getTypes() {
    return m_types;
}

vector<Matrix4x4> *Scene::getMatrices() {
    return m_matrices;
}

vector<CS123SceneLightData> *Scene::getLights() {
    return m_lights;
}
CS123SceneGlobalData Scene::getGlobal() {
    return m_global;
}
