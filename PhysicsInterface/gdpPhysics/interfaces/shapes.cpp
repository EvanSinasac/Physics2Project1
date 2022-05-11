#include "shapes.h"

#include <glm/glm.hpp>

namespace gdpPhysics
{
	// SPHERE SHAPE
	SphereShape::SphereShape(float radius)
		: iShape(ShapeTypeSphere)
		, m_Radius(radius)
	{}

	SphereShape::~SphereShape() 
	{}

	float SphereShape::GetRadius() const
	{
		return m_Radius;
	}

	SphereShape* SphereShape::Cast(iShape* shape)
	{
		return dynamic_cast<SphereShape*>(shape);
	}

	// PLANE SHAPE
	PlaneShape::PlaneShape(float dotProduct, const glm::vec3& normal)
		: iShape(ShapeTypePlane)
		, m_DotProduct(dotProduct)
		, m_Normal(normal)
	{

	}


	PlaneShape* PlaneShape::Cast(iShape* shape)
	{
		return dynamic_cast<PlaneShape*>(shape);
	}
}