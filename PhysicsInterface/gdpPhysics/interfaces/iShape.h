#pragma once

#include "eShapeType.h"

namespace gdpPhysics
{
	class iShape
	{
	public:
		virtual ~iShape() {}

		eShapeType GetShapeType() const { return m_ShapeType; }

	protected:
		iShape(eShapeType shapeType)
			: m_ShapeType(shapeType) { }

	private:
		eShapeType m_ShapeType;

		iShape(const iShape&) {}
		iShape& operator=(const iShape&) { return *this; }
	};
}
