/*
 * CS123 New Parser for XML
 */

#include "CS123XmlSceneParser.h"
#include "CS123SceneData.h"

#include <CS123Common.h>
#include <assert.h>
#include <string.h>
#include <string>

/*XML Parsing Headers */
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;

CS123XmlSceneParser::CS123XmlSceneParser(const std::string& name) 
{
   file_name = name;

   memset(&m_cameraData, 0, sizeof(CS123SceneCameraData));
   memset(&m_globalData, 0, sizeof(CS123SceneGlobalData));
   m_objects.clear();
   m_lights.clear();
   m_nodes.clear();
}

CS123XmlSceneParser::~CS123XmlSceneParser() 
{
   std::vector<CS123SceneLightData*>::iterator lights;
   for (lights = m_lights.begin(); lights != m_lights.end(); lights++) {
      delete *lights;
   }

   /* Delete all Scene Nodes */
   for (unsigned int node = 0; node < m_nodes.size(); node++) {           
      for (size_t i = 0; i < (m_nodes[node])->transformations.size(); i++) {
         delete (m_nodes[node])->transformations[i];
      }
      for (size_t i = 0; i < (m_nodes[node])->primitives.size(); i++) {
         delete (m_nodes[node])->primitives[i]->material.textureMap;
         delete (m_nodes[node])->primitives[i]->material.bumpMap;
         delete (m_nodes[node])->primitives[i];
      }
      (m_nodes[node])->transformations.clear();
      (m_nodes[node])->primitives.clear();
      (m_nodes[node])->children.clear();
      delete m_nodes[node];
   }

   m_nodes.clear();
   m_lights.clear();
   m_objects.clear(); 
}

bool CS123XmlSceneParser :: getGlobalData(CS123SceneGlobalData& data) const
{
   data = m_globalData;
   return true;
}

bool CS123XmlSceneParser :: getCameraData(CS123SceneCameraData& data) const
{
   data = m_cameraData;
   return true;
}

int CS123XmlSceneParser :: getNumLights() const
{
   return m_lights.size();
}

bool CS123XmlSceneParser :: getLightData(int i, CS123SceneLightData& data) const
{
   if (i < 0 || (unsigned int)i >= m_lights.size())
   {
      printf("Invalid light index %d.\n", i);
      return false;
   }
   data = *m_lights[i];
   return true;
}

CS123SceneNode* CS123XmlSceneParser :: getRootNode() const
{
   map<std::string, CS123SceneNode*>::iterator node = m_objects.find("root");
   if (node == m_objects.end())
      return NULL;
   return m_objects["root"];
}

/* this is where it all goes down... */
bool CS123XmlSceneParser::parse() 
{
   TiXmlDocument doc(file_name.c_str());
   bool loaded = doc.LoadFile();

   if(loaded)
      printf("Loaded file %s\n", file_name.c_str());
   else
   {
      printf("\nFailed to load file: %s\n", file_name.c_str());
      return false;
   }

   TiXmlElement* txn = doc.FirstChildElement();
   //should be scenefile element. has no siblings.
   if (txn == NULL)
   {
      printf("Invalid xml file.  Could not parse root.\n");
      return false;
   }


   if (!txn->ValueStr().compare("scenefile"))
   {
      printf("Begin parsing file...\n");

      const TiXmlElement* scene_elem = txn->FirstChildElement();

      /* Default Camera */
      m_cameraData.pos = Vector4(5, 5, 5, 1);
      m_cameraData.up = Vector4(0, 1, 0, 0);
      m_cameraData.look = Vector4(-1, -1, -1, 0);
      m_cameraData.heightAngle = 45;
      m_cameraData.aspectRatio = 1.0f;

      /* Default global data */
      m_globalData.ka = 0.5f;
      m_globalData.kd = 0.5f;
      m_globalData.ks = 0.5f;
      m_globalData.kt = 0.5f;

      while (scene_elem)
      {
         const string& elem = scene_elem->ValueStr();

         if (!elem.compare("globaldata")) 
         {
            if (!parseGlobalData(scene_elem))
               return false;
         }
         else if (!elem.compare("lightdata"))
         {
            if (!parseLightData(scene_elem))
               return false;
         }
         else if (!elem.compare("cameradata"))
         {
            if (!parseCameraData(scene_elem))
               return false;
         }
         else if (!elem.compare("object"))
         {
            if (!parseObjectData(scene_elem))
               return false;
         }
         else
         {
            printf("Unsupported element type %s\n", elem.c_str());
            return false;
         }

         /* advance to the next scene element */
         scene_elem = scene_elem->NextSiblingElement();
      }

      printf("Finished parsing file.\n");
      return true;
   }
   else {
      printf("Error parsing Scenefile Document.\n");
      return false;
   }


}

/** Helper function to parse a triple 
*/
bool parseTriple(const TiXmlElement* triple, float& x, float& y, float& z)
{
   const TiXmlAttribute* attr = triple->FirstAttribute();
   if (!attr)
      return false;

   x = attr->DoubleValue();
   attr = attr->Next();
   if (!attr)
      return false;

   y = attr->DoubleValue();
   attr = attr->Next();
   if (!attr)
      return false;

   z = attr->DoubleValue();

   return true;
}
bool parseMatrix(const TiXmlElement* e, double matrix[16]) {
   const TiXmlElement* r = e->FirstChildElement();
   
   for (int row = 0; row < 4; row++) {
      if (!r)
         goto end;
      const TiXmlAttribute* a = r->FirstAttribute();
      
      for (int col = 0; col < 4; col++) {
         if (!a)
            goto end;
         matrix[row*4 + col] = a->DoubleValue();
         a = a->Next();
      }
      r = r->NextSiblingElement();
   }
   return true;
end:
   printf("Could not parse matrix.\n");
   return false;
}

bool parseColor(const TiXmlElement* color, CS123SceneColor& c)
{
   memset(&c, 0, sizeof(CS123SceneColor));

   const TiXmlAttribute* attr = color->FirstAttribute();
   if (!attr)
      return false;

   c.r = attr->DoubleValue();
   attr = attr->Next();
   if (!attr)
      return false;

   c.g = attr->DoubleValue();
   attr = attr->Next();
   if (!attr)
      return false;

   c.b = attr->DoubleValue();

   attr = attr->Next();
   if (!attr)
      c.a = 1.0f;
   else
      c.a = attr->DoubleValue();

   return true;
}

bool parseFloat(const TiXmlElement* value, float& f)
{
   const TiXmlAttribute* attr = value->FirstAttribute();
   if (!attr)
      return false;
   f = attr->DoubleValue();
   return true;
}

bool parseMap(const TiXmlElement* e, CS123SceneFileMap* map)
{
   const TiXmlAttribute* attr = e->FirstAttribute();
   if (!attr)
      return false;

   map->filename = attr->ValueStr();

   attr = attr->Next();
   if (attr)
   {
      map->repeatU = attr->DoubleValue();
      attr = attr->Next();
      if (!attr)
         return false;
      map->repeatV = attr->DoubleValue();
   }
   else
      map->repeatU = map->repeatV = 1.0f;

   map->isUsed = true;

   return true;
}

/**
 *
 * The initial XML element passed in as an argument SHOULD be
 * the element for the data being parsed. In this case, it should
 * be the GlobalData element.
 *
 */
bool CS123XmlSceneParser::parseGlobalData(const TiXmlElement* scenefile) 
{

   const TiXmlElement* globaldata = scenefile->FirstChildElement();

   if (!globaldata) 
   {
      printf("Could not parse global data.\n");
      return false;
   }

   while (globaldata) 
   {
      const string& elem = globaldata->ValueStr();
      if (!elem.compare( "diffusecoeff"))
      {
         if (!parseFloat(globaldata, m_globalData.kd))
         {
            printf("Invalid diffuse coefficient.\n");
            return false;
         }
      }
      else if (!elem.compare("ambientcoeff"))
      {
         if (!parseFloat(globaldata, m_globalData.ka))
         {
            printf("Invalid ambient coefficient.\n");
            return false;
         }
      }
      else if (!elem.compare("transparentcoeff"))
      {
         if (!parseFloat(globaldata, m_globalData.kt))
         {
            printf("Invalid transparent coefficient.\n");
            return false;
         }
      }
      else if (!elem.compare("specularcoeff"))
      {
         if (!parseFloat(globaldata, m_globalData.ks))
         {
            printf("Invalid specular coefficient.\n");
            return false;
         }
      }
      else 
      {
         printf("Invalid global data type %s\n", elem.c_str());
         return false;
      }
      globaldata = globaldata->NextSiblingElement();
   }
   return true;
}



/**
 *
 * The initial XML element passed in as an argument SHOULD be
 * the element for the data being parsed. In this case, it should
 * be the LightData element.
 *
 */

bool CS123XmlSceneParser::parseLightData(const TiXmlElement* scenefile) 
{
   const TiXmlElement* lightelem = scenefile->FirstChildElement();

   if (!lightelem) 
   {
      printf("Invalid light data - no data provided.\n");
      return false;
   }

   CS123SceneLightData* light = new CS123SceneLightData();
   m_lights.push_back(light);    
   memset(light, 0, sizeof(CS123SceneLightData));
   light->pos = Vector4(3, 3, 3, 0);
   light->dir = Vector4(0, 0, 0, 0);
   light->color.r = light->color.g = light->color.b = 1.0f;
   light->function = Vector3(1, 0, 0);

   while(lightelem) 
   {
      const string& elem = lightelem->ValueStr();

      if (!elem.compare("id")) 
      {
         const TiXmlAttribute* attr = lightelem->FirstAttribute();
         if (!attr)
         {
            printf("Invalid light id.\n");
            return false;
         }
         light->id  = attr->IntValue();        
      }
      else if (!elem.compare("type"))
      {
         const TiXmlAttribute* attr = lightelem->FirstAttribute();
         if (!attr)
         {
            printf("Invalid light type.\n");
            return false;
         }
         if (!attr->ValueStr().compare("directional"))
            light->type = LIGHT_DIRECTIONAL;
         else if (!attr->ValueStr().compare("point"))
            light->type = LIGHT_POINT;
         else if (!attr->ValueStr().compare("spot"))
            light->type = LIGHT_SPOT;
         else if (!attr->ValueStr().compare("area"))
            light->type = LIGHT_AREA;
         else {
            printf("Unknown light type %s.\n", attr->ValueStr().c_str());
            return false;
         }

      }
      else if (!elem.compare("color"))
      {
         if (!parseColor(lightelem, light->color))
         {
            printf("Invalid light color.\n");
            return false;
         }
      }
      else if (!elem.compare("function"))
      {
         float x, y, z;
         if (parseTriple(lightelem, x, y, z))
            light->function = Vector3(x, y, z);
         else
         {
            printf("Invalid light function.\n");
            return false;
         }
      }
      else if (!elem.compare("position"))
      {
         if (light->type == LIGHT_DIRECTIONAL)
         {
            printf("Position is not applicable to directional lights.\n");
            return false;
         }
         float x, y, z;
         if (parseTriple(lightelem, x, y, z))
            light->pos = Vector4(x, y, z, 1);
         else
         {
            printf("Invalid light position.\n");
            return false;
         }
      }    
      else if (!elem.compare("direction"))
      {
         if (light->type == LIGHT_POINT)
         {
            printf("Direction is not applicable to point lights.\n");
            return false;
         }
         float x, y, z;
         if (parseTriple(lightelem, x, y, z))
            light->dir = Vector4(x, y, z, 0);
         else
         {
            printf("Invalid light direction.\n");
            return false;
         }
      }
      else if (!elem.compare("radius"))
      {
         if (light->type != LIGHT_SPOT)
         {
            printf("Radius is only applicable to spot lights.\n");
            return false;
         }
         if (!parseFloat(lightelem, light->radius))
         {
            printf("Invalid radius.\n");
            return false;
         }
      }
      else if (!elem.compare("penumbra"))
      {
         if (light->type != LIGHT_SPOT)
         {
            printf("Penumbra is only applicable to spot lights.\n");
            return false;
         }
         if (!parseFloat(lightelem, light->penumbra))
         {
            printf("Invalid penumbra.\n");
            return false;
         }
      }
      else if (!elem.compare("angle"))
      {
         if (light->type != LIGHT_SPOT)
         {
            printf("Angle is only applicable to spot lights.\n");
            return false;
         }
         if (!parseFloat(lightelem, light->angle))
         {
            printf("Invalid angle.\n");
            return false;
         }
      }
      else if (!elem.compare("width"))
      {
         if (light->type != LIGHT_AREA)
         {
            printf("Width is only applicable to area lights.\n");
            return false;
         }
         if (!parseFloat(lightelem, light->width))
         {
            printf("Invalid width.\n");
            return false;
         }
      }
      else if (!elem.compare("height"))
      {
         if (light->type != LIGHT_AREA)
         {
            printf("Height is only applicable to area lights.\n");
            return false;
         }
         if (!parseFloat(lightelem, light->height))
         {
            printf("Invalid height.\n");
            return false;
         }
      }
      else {
         printf("Invalid element type %s.\n", elem.c_str());
      }

      lightelem = lightelem->NextSiblingElement();
   }

   return true;
}


/**
 *
 * The initial XML element passed in as an argument SHOULD be
 * the element for the data being parsed. In this case, it should
 * be the CameraData element.
 *
 */
bool CS123XmlSceneParser::parseCameraData(const TiXmlElement* scenefile)
{
   const TiXmlElement* cam_element = scenefile->FirstChildElement();
   if (!cam_element)
   {
      printf("Invalid camera data.\n");
      return false;
   }

   bool focusFound = false;
   bool lookFound = false;

   while(cam_element)
   {
      const string& elem = cam_element->ValueStr();
      if (!elem.compare("pos"))
      {
         float x, y, z;
         if (!parseTriple(cam_element, x, y, z))
         {
            printf("Invalid camera position.\n");
            return false;
         }
         m_cameraData.pos = Vector4(x, y, z, 1);
      }
      else if (!elem.compare("look"))
      {
         float x, y, z;
         if (!parseTriple(cam_element, x, y, z))
         {
            printf("Invalid camera look.\n");
            return false;
         }
         lookFound = true;
         m_cameraData.look = Vector4(x, y, z, 0);
      }
      else if (!elem.compare("focus"))
      {
         float x, y, z;
         if (!parseTriple(cam_element, x, y, z))
         {
            printf("Invalid camera focus.\n");
            return false;
         }
         focusFound = true;
         m_cameraData.look = Vector4(x, y, z, 0);
      }
      else if (!elem.compare("up"))
      {
         float x, y, z;
         if (!parseTriple(cam_element, x, y, z))
         {
            printf("Invalid camera up.\n");
            return false;
         }
         m_cameraData.up = Vector4(x, y, z, 0);
      }
      else if (!elem.compare("heightangle"))
      {
         if (!parseFloat(cam_element, m_cameraData.heightAngle))
         {
            printf("Invalid camera field of view.\n");
            return false;
         }    
      }
      else if (!elem.compare("aspectratio"))
      {
         if (!parseFloat(cam_element, m_cameraData.aspectRatio))
         {
            printf("Invalid camera aspect ratio.\n");
            return false;
         }
      }        
      else if (!elem.compare("aperture"))
      {
         if (!parseFloat(cam_element, m_cameraData.aperture))
         {
            printf("Invalid camera aperture.\n");
            return false;
         }
      }        
      else if (!elem.compare("focallength"))
      {
         if (!parseFloat(cam_element, m_cameraData.focalLength))
         {
            printf("Invalid camera focal length.\n");
            return false;
         }
      }        
      else 
      {
         printf("Invalid camera element %s.\n", elem.c_str());
         return false;
      }
      cam_element = cam_element->NextSiblingElement();
   }

   if (focusFound && lookFound)
   {
      printf("Camera can not have both look and focus.\n");
      return false;
   }
   if (focusFound)
   {
      m_cameraData.look.data[0] = m_cameraData.look.data[0] - m_cameraData.pos.data[0];
      m_cameraData.look.data[1] = m_cameraData.look.data[1] - m_cameraData.pos.data[1];
      m_cameraData.look.data[2] = m_cameraData.look.data[2] - m_cameraData.pos.data[2];
      m_cameraData.look.data[3] = 0.0f;
   }

   return true;
}

/*
 * This method expects that the element passed in was an object
 * Further, it is almost certainly a tree object, since the only caller
 * of this method will be the element loop in the parse method.
 *
 */
bool CS123XmlSceneParser::parseObjectData(const TiXmlElement* scenefile){

   const TiXmlAttribute* attr = scenefile->FirstAttribute();

   if (attr == NULL || attr->ValueStr().compare("tree"))
   {
      printf("Invalid object data.\n");
      return false;\
   }

   const TiXmlAttribute* name = scenefile->FirstAttribute()->Next();
   const string& nameStr = name->ValueStr();

   /* now we iterate over its child elements, which MUST be trans blocks.
    * master objects contain no object blocks within themselves.
    */
   const TiXmlElement* obj_element = scenefile->FirstChildElement();
   if (!obj_element)
   {
      printf("Object has no data.\n");
      return false;
   }

   /* Check that this object does not exist */
   if (m_objects[nameStr] != NULL)
   {
      printf("Two objects with the same name: %s.\n", nameStr.c_str());
      return false;
   }

   /* Create the object and add to the map */
   CS123SceneNode* node = new CS123SceneNode;
   m_nodes.push_back(node);

   m_objects[nameStr] = node;

   /* now iterate over all of the transblocks in this master object */
   while (obj_element)
   {
      CS123SceneNode* child = new CS123SceneNode;
      m_nodes.push_back(child);

      if (!parseTransBlock(obj_element, child))
      {
         printf("Could not parse transblock.\n");
         return false;
      }
      node->children.push_back(child);
      /* advance the element pointer */
      obj_element = obj_element->NextSiblingElement();
   }

   return true;
}

/**
 *
 * This method expects a transblock as its element, so we need
 * to iterate over all of its child elements, which could be 
 * translate, rotate, etc etc elements.  The information will be stripped
 * from the element, and then we'll tackle the next one. If it's an object
 * in here, it's either a master reference, a subtree, or a primitive.
 * if it's a master reference, we handle it here. if it's one of the other
 * two, then we call other methods.
 *
 */

bool CS123XmlSceneParser::parseTransBlock(const TiXmlElement* transblock, 
                                          CS123SceneNode* node)
{
   /* could have any number of translates, rotates, scale, matrix */
   /* and then one final object block */
   const TiXmlElement* trans_elem = transblock->FirstChildElement();
   if (!trans_elem)
   {
      printf("No transformation data.\n");
      return false;
   }

   while(trans_elem)
   {
      const string& elem = trans_elem->ValueStr();

      if (!elem.compare("translate"))
      {
         CS123SceneTransformation* t = new CS123SceneTransformation();
         node->transformations.push_back(t);
         t->type = TRANSFORMATION_TRANSLATE;
         float x, y, z;

         if (!parseTriple(trans_elem, x, y, z))
         {
            printf("Could not parse translate type.\n");
            return false;
         }

         t->translate = Vector4(x, y, z, 0);
      }
      else if (!elem.compare("rotate"))
      {
         CS123SceneTransformation* t = new CS123SceneTransformation();
         t->type = TRANSFORMATION_ROTATE;
         float x, y, z, angle = 0;

         const TiXmlAttribute* attr = trans_elem->FirstAttribute();
         if (!attr)
            return false;

         x = attr->DoubleValue();
         attr = attr->Next();
         if (!attr)
            return false;

         y = attr->DoubleValue();
         attr = attr->Next();
         if (!attr)
            return false;

         z = attr->DoubleValue();
         attr = attr->Next();
         if (attr)
         {
            angle = attr->DoubleValue();
         }

         t->rotate = Vector4(x, y, z, 0);
         /* Convert to radians */
         t->angle = angle * M_PI / 180.f;

         node->transformations.push_back(t);   
      }
      else if (!elem.compare("scale"))
      {
         CS123SceneTransformation* t = new CS123SceneTransformation();
         t->type = TRANSFORMATION_SCALE;
         float x, y, z;

         if (!parseTriple(trans_elem, x, y, z))
         {
            printf("Could not parse scale type.\n");
            return false;
         }

         t->scale = Vector4(x, y, z, 0);
         node->transformations.push_back(t);
      }
      else if (!elem.compare("matrix"))
      {
         CS123SceneTransformation* t = new CS123SceneTransformation();
         t->type = TRANSFORMATION_MATRIX;

         REAL matrix[16];
         if (!parseMatrix(trans_elem, matrix)) {
            printf("Could not parse matrix.\n");
            return false;
         }
         
         t->matrix = Matrix4x4(matrix);
         node->transformations.push_back(t);
      }

      else if (!elem.compare("object"))
      {
         const TiXmlAttribute* attr = trans_elem->FirstAttribute();
         if (!attr->ValueStr().compare("master"))
         {
            attr = attr->Next();
            if (!attr)
            {
               printf("Invalid master object reference.\n");
               return false;
            }
            if (!m_objects[attr->ValueStr()])
            {
               printf("Invalid master object reference %s\n", 
                      attr->ValueStr().c_str());
               return false;
            }
            node->children.push_back(m_objects[attr->ValueStr()]);
         }
         else if (!attr->ValueStr().compare("tree"))
         {
            const TiXmlElement* subblock = trans_elem->FirstChildElement();
            while (subblock)
            {
               CS123SceneNode* n = new CS123SceneNode;
               m_nodes.push_back(n);
               if (!parseTransBlock(subblock, n))
                  return false;
               node->children.push_back(n);
               subblock = subblock->NextSiblingElement();
            }
         }
         else if (!attr->ValueStr().compare("primitive"))
         {
            if (!parsePrimitive(trans_elem, node))
            {
               printf("Could not parse primitive.\n");
               return false;
            }
         }
         else {
            printf("Unknown object type!.\n");
            return false;
         }
      }
      else 
      {
         printf("Invalid transblock element type %s\n", elem.c_str());
         return false;
      }
      trans_elem = trans_elem->NextSiblingElement();
   }

   return true;
}

/**
 * Parse primitive data 
 */
bool CS123XmlSceneParser::parsePrimitive(const TiXmlElement* prim, 
                                         CS123SceneNode* node)
{
   const TiXmlAttribute* attr = prim->FirstAttribute();
   attr = attr->Next();
   if (!prim)
   {
      printf("Could not parse primitive type.\n");
      return false;
   }

   CS123ScenePrimitive* primitive = new CS123ScenePrimitive();
   CS123SceneMaterial& mat = primitive->material;
   memset(&mat, 0, sizeof(CS123SceneMaterial));
   mat.textureMap = new CS123SceneFileMap;
   mat.bumpMap = new CS123SceneFileMap;

   /* Initialize primitive values */
   primitive->type = PRIMITIVE_CUBE;
   mat.textureMap->isUsed = false;
   mat.bumpMap->isUsed = false;
   mat.cDiffuse.r = mat.cDiffuse.g = mat.cDiffuse.b = 1.0;

   node->primitives.push_back(primitive);

   const string& primType = attr->ValueStr();

   if (!primType.compare("sphere"))
      primitive->type = PRIMITIVE_SPHERE;
   else if (!primType.compare("cube"))
      primitive->type = PRIMITIVE_CUBE;
   else if (!primType.compare("cylinder"))
      primitive->type = PRIMITIVE_CYLINDER;
   else if (!primType.compare("cone"))
      primitive->type = PRIMITIVE_CONE;
   else if (!primType.compare("torus"))
      primitive->type = PRIMITIVE_TORUS;
   else if (!primType.compare("mesh"))
   {
      primitive->type = PRIMITIVE_MESH;
      attr = attr->Next();
      if (!attr)
      {
         printf("Mesh type must specify mesh file.\n");
         return false;
      }
      primitive->meshfile = attr->ValueStr();
   }
   const TiXmlElement* primdata = prim->FirstChildElement();

   while(primdata)
   {
      const string& elem = primdata->ValueStr();

      if (!elem.compare("diffuse"))
      {
         if (!parseColor(primdata, mat.cDiffuse))
         {
            printf("Could not parse diffuse color.\n");
            return false;
         }
      }
      else if (!elem.compare("ambient"))
      {
         if (!parseColor(primdata, mat.cAmbient))
         {
            printf("Could not parse ambient color.\n");
            return false;
         }
      }
      else if (!elem.compare("reflective"))
      {
         if (!parseColor(primdata, mat.cReflective))
         {
            printf("Could not parse reflective color.\n");
            return false;
         }
      }
      else if (!elem.compare("specular"))
      {
         if (!parseColor(primdata, mat.cSpecular))
         {
            printf("Could not parse specular color.\n");
            return false;
         }
      }
      else if (!elem.compare("emissive"))
      {
         if (!parseColor(primdata, mat.cEmissive))
         {
            printf("Could not parse emissive color.\n");
            return false;
         }
      }
      else if (!elem.compare("transparent"))
      {
         if (!parseColor(primdata, mat.cTransparent))
         {
            printf("Could not parse transparent color.\n");
            return false;
         }
      }
      else if (!elem.compare("shininess"))
      {
         if (!parseFloat(primdata, mat.shininess))
         {
            printf("Could not parse shininess.\n");
            return false;
         }
      }
      else if (!elem.compare("ior"))
      {
         if (!parseFloat(primdata, mat.ior))
         {
            printf("Could not parse ior.\n");
            return false;
         }
      }
      else if (!elem.compare("texture"))
      {
         if (!parseMap(primdata, mat.textureMap))
         {
            printf("Could not parse texture map.\n");
            return false;
         }
      }
      else if (!elem.compare("bumpmap"))
      {
         if (!parseMap(primdata, mat.bumpMap))
         {
            printf("Could not parse bump map.\n");
            return false;
         }
      }
      else if (!elem.compare("blend"))
      {
         if (!parseFloat(primdata, mat.blend))
         {
            printf("Could not parse blend.\n");
            return false;
         }
      }
      else 
      {
         printf("Invalid primitive data %s\n", elem.c_str());
         return false;
      }
      primdata = primdata->NextSiblingElement();
   }

   return true;
}

