/*sudo*
 * @file <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_box_model.cpp>
 *
 * @author Michael Allwright - <allsey87@gmail.com>
 */

#include "dynamics3d_box_model.h"

#include <argos3/plugins/simulator/physics_engines/dynamics3d/dynamics3d_engine.h>

namespace argos {

   /****************************************/
   /****************************************/

   CDynamics3DBoxModel::CDynamics3DBoxModel(CDynamics3DEngine& c_engine,
                                            CBoxEntity& c_box) :
      CDynamics3DModel(c_engine, c_box.GetEmbodiedEntity(), c_box.GetId()),
      m_cBoxEntity(c_box) {
      /* Get origin anchor and register its update method */
      const SAnchor& sOrigin = GetEmbodiedEntity().GetOriginAnchor();
      RegisterAnchorMethod<CDynamics3DBoxModel>(sOrigin,
                                                &CDynamics3DBoxModel::UpdateOriginAnchor);
      /* When defining size of objects we must manually swap the Z and Y components */
      m_pcBoxCollisionShape = m_cBoxShapeManager.RequestBoxShape(btVector3(c_box.GetSize().GetX() * 0.5f,
                                                                           c_box.GetSize().GetZ() * 0.5f, 
                                                                           c_box.GetSize().GetY() * 0.5f));
      btTransform cBoxGeometricOffset(
         btQuaternion(0.0f, 0.0f, 0.0f, 1.0f),
         btVector3(0.0f, -c_box.GetSize().GetZ() * 0.5f, 0.0f));
      Real fMass = c_box.GetEmbodiedEntity().IsMovable() ? c_box.GetMass() : 0.0f;
      m_vecLocalBodies.push_back(new CDynamics3DBody(this,
                                                     "box",
                                                     m_pcBoxCollisionShape,
                                                     btTransform::getIdentity(),
                                                     cBoxGeometricOffset,
                                                     fMass));
      /* move the model to the specified coordinates */
      SetModelCoordinates(btTransform(ARGoSToBullet(GetEmbodiedEntity().GetOriginAnchor().Orientation),
                                      ARGoSToBullet(GetEmbodiedEntity().GetOriginAnchor().Position)));
   }
   
   /****************************************/
   /****************************************/
   
   CDynamics3DBoxModel::~CDynamics3DBoxModel() {
      m_cBoxShapeManager.ReleaseBoxShape(m_pcBoxCollisionShape);
   }
   
   /****************************************/
   /****************************************/

   void CDynamics3DBoxModel::UpdateEntityStatus() {
      if(m_cBoxEntity.GetEmbodiedEntity().IsMovable()) {      
         CPhysicsModel::UpdateEntityStatus();
     }
   }

   /****************************************/
   /****************************************/

   btTransform CDynamics3DBoxModel::GetModelCoordinates() const {
      return m_vecLocalBodies[0]->GetMotionStateTransform();
   }

   /****************************************/
   /****************************************/

   void CDynamics3DBoxModel::UpdateOriginAnchor(SAnchor& s_anchor) {
      s_anchor.Position = BulletToARGoS(GetModelCoordinates().getOrigin());
      s_anchor.Orientation = BulletToARGoS(GetModelCoordinates().getRotation());
   }

   /****************************************/
   /****************************************/

   btBoxShape* CDynamics3DBoxModel::CBoxShapeManager::RequestBoxShape(const btVector3& c_half_extents) {
      std::vector<CResource>::iterator itResource;      
      for(itResource = m_vecResources.begin();
          itResource != m_vecResources.end();
          ++itResource) {
         if(itResource->m_cHalfExtents == c_half_extents) break;
      }      
      // if it doesn't exist, create a new one
      if(itResource == m_vecResources.end()) {
         itResource = m_vecResources.insert(itResource, 
                                            CResource(c_half_extents, new btBoxShape(c_half_extents)));
      }
      itResource->m_unInUseCount++;
      return itResource->m_cShape;
   }

   /****************************************/
   /****************************************/

   void CDynamics3DBoxModel::CBoxShapeManager::ReleaseBoxShape(const btBoxShape* pc_release) {
      std::vector<CResource>::iterator itResource;      
      for(itResource = m_vecResources.begin();
          itResource != m_vecResources.end();
          ++itResource) {
         if(itResource->m_cShape == pc_release) break;
      }
      // if it doesn't exist, throw an exception
      if(itResource == m_vecResources.end()) {
         THROW_ARGOSEXCEPTION("Attempt to release unknown btBoxShape from the box shape manager!");
      }
      itResource->m_unInUseCount--;
      if(itResource->m_unInUseCount == 0) {
         delete itResource->m_cShape;
         m_vecResources.erase(itResource);
      }
   }

   /****************************************/
   /****************************************/

   CDynamics3DBoxModel::CBoxShapeManager::CResource::CResource(const btVector3& c_half_extents,
                                                               btBoxShape* c_shape) : 
      m_cHalfExtents(c_half_extents),
      m_cShape(c_shape),
      m_unInUseCount(0) {}

   /****************************************/
   /****************************************/

   CDynamics3DBoxModel::CBoxShapeManager CDynamics3DBoxModel::m_cBoxShapeManager;

   /****************************************/
   /****************************************/

   REGISTER_STANDARD_DYNAMICS3D_OPERATIONS_ON_ENTITY(CBoxEntity, CDynamics3DBoxModel);

}
