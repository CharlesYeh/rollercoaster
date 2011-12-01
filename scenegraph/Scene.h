/*!
   @file   Scene.h
   @author Ben Herila (ben@herila.net)
   @author Evan Wallace (evan.exe@gmail.com)
   @date   Fall 2010

   @brief  This is a great place to put common data structures that need to be used by
   all your scenes.
*/

#ifndef SCENE_H
#define SCENE_H

#include "math/CS123Algebra.h"
#include "lib/CS123SceneData.h"
#include "math/CS123Matrix.h"
#include <map>
#include <string>

class Camera;
class CS123ISceneParser;
class Shapes;

/**

 @class Scene

 @brief This is the base class for all scenes. Modify this class if you want to provide
 common functionality to all your scenes.

 @author  Evan Wallace (edwallac)
 @author  Ben Herila (bherila)
 @date    9/1/2010

**/
class Scene
{
public:
    Scene();
    virtual ~Scene();

    static void parse(Scene *sceneToFill, CS123ISceneParser *parser);

    ///*! @brief Returns this scene's local camera (a pointer to one of the cameras in SupportCanvas3D). */
    //Camera *getCamera() { return m_camera; }

    ///*! @brief Sets this scene's local camera(a pointer to one of the cameras in SupportCanvas3D). */
    //void setCamera(Camera *newCamera);
    static void parseNode(Scene *sceneToFill, CS123SceneNode *curr, Matrix4x4 transf);

    virtual void setLights(const Camera *follow) = 0;

    std::map<string, QImage>    *getTextureMaps() { return m_textMaps; }
    vector<int>                 *getTypes();
    vector<CS123SceneMaterial>  *getMaterials() { return m_materials; }
    vector<CS123SceneFileMap>   *getFileMaps() { return m_fileMaps; }
    vector<Matrix4x4>           *getMatrices();
    vector<CS123SceneLightData> *getLights();
    CS123SceneGlobalData        getGlobal();

protected:

    /*! Adds a primitive to the scene. */
    virtual void addPrimitive(CS123ScenePrimitive &scenePrimitive, const Matrix4x4 &matrix);

    /*! Adds a light to the scene. */
    virtual void addLight(const CS123SceneLightData &sceneLight);

    /*! Sets the global data for the scene. */
    virtual void setGlobal(const CS123SceneGlobalData &global);

    map<string, QImage> *m_textMaps;
    vector<int>         *m_types;
    vector<Shapes *>    *m_shapes;
    vector<CS123SceneMaterial> *m_materials;
    vector<CS123SceneFileMap> *m_fileMaps;
    vector<Matrix4x4>   *m_matrices;

    vector<CS123SceneLightData> *m_lights;
    CS123SceneGlobalData m_global;
};

#endif // SCENE_H
