#pragma once

#include "iShape.h"
#include <glm/vec3.hpp>

namespace gdpPhysics
{
	class SphereShape : public iShape
	{
	public:
		SphereShape(float radius);
		virtual ~SphereShape();

		float GetRadius() const;
		static SphereShape* Cast(iShape* shape);

	protected:
		SphereShape(eShapeType shapeType)
			: iShape(shapeType) {}

	private:
		float m_Radius;
		SphereShape(const SphereShape&) : iShape(ShapeTypeSphere) {}
		SphereShape& operator=(const SphereShape&) { return *this; }
	};

	class PlaneShape : public iShape
	{
	public:
		PlaneShape(float dotProduct, const glm::vec3& normal);
		virtual ~PlaneShape() {}

		float GetDotProduct() const { return m_DotProduct; }
		const glm::vec3& GetNormal() { return m_Normal; }

		static PlaneShape* Cast(iShape* shape);

	private:
		glm::vec3 m_Normal;
		float m_DotProduct;

		PlaneShape(const PlaneShape&) : iShape(ShapeTypePlane) {}
		PlaneShape& operator=(const PlaneShape&) { return *this; }
	};
}