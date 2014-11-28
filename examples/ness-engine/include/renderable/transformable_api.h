/* 
  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.

  Ronen Ness
  ronenness@gmail.com

*/

/**
* This entity is a middle layer - gives the logic of transformations (color, scale, blending, etc..)
* every object that inherit from this will support transformations, but will also require to implement some functions
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once
#include "transformations.h"

namespace Ness
{

	// a renderable object/node
	class Transformable
	{
	protected:
		SRenderTransformations	m_transformations;				// render transformations (opacity, size, position, ...)

	public:

		// setters/getters
		NESSENGINE_API virtual void set_transformations(const SRenderTransformations& newTrans) {m_transformations = newTrans; transformations_update();}
		NESSENGINE_API virtual const SRenderTransformations& get_transformation() const {return m_transformations;}
		NESSENGINE_API virtual void set_position(const Ness::Point& NewPos) {if (NewPos == m_transformations.position) return; m_transformations.position = NewPos; transformations_update();}
		NESSENGINE_API virtual void add_position(const Ness::Point& NewPos) {m_transformations.position += NewPos; transformations_update();}
		NESSENGINE_API virtual void multiply_position(const Ness::Point& NewPos) {m_transformations.position *= NewPos; transformations_update();}
		NESSENGINE_API virtual void set_scale(const Size& NewScale) {if (NewScale == m_transformations.scale) return; m_transformations.scale = NewScale; transformations_update();}
		NESSENGINE_API virtual void add_scale(const Size& NewScale) {m_transformations.scale += NewScale; transformations_update();}
		NESSENGINE_API virtual void multiply_scale(const Size& NewScale) {m_transformations.scale *= NewScale; transformations_update();}
		NESSENGINE_API virtual void set_scale(float NewScale) {set_scale(Point(NewScale, NewScale));}
		NESSENGINE_API virtual void add_scale(float NewScale) {m_transformations.scale += NewScale; transformations_update();}
		NESSENGINE_API virtual void multiply_scale(float NewScale) {m_transformations.scale *= NewScale; transformations_update();}
		NESSENGINE_API virtual void set_rotation(float NewRotation) {if (NewRotation == m_transformations.rotation) return; m_transformations.rotation = NewRotation; transformations_update();}
		NESSENGINE_API virtual void add_rotation(float NewRotation) {m_transformations.rotation += NewRotation; transformations_update();}
		NESSENGINE_API virtual void multiply_rotation(float NewRotation) {m_transformations.rotation *= NewRotation; transformations_update();}
		NESSENGINE_API virtual void set_color(const Color& NewColor) {if (NewColor == m_transformations.color) return; m_transformations.color = NewColor; transformations_update();}
		NESSENGINE_API virtual void add_color(const Color& NewColor) {set_color(get_color() + NewColor);}
		NESSENGINE_API virtual void multiply_color(const Color& NewColor) {set_color(get_color() * NewColor);}
		NESSENGINE_API virtual void set_opacity(float opacity) {if (opacity == m_transformations.color.a) return; m_transformations.color.a = opacity; transformations_update();}
		NESSENGINE_API virtual void add_opacity(float opacity) {set_opacity(get_opacity() + opacity);}
		NESSENGINE_API virtual void multiply_opacity(float opacity) {set_opacity(get_opacity() * opacity);}
		NESSENGINE_API virtual void set_blend_mode(EBlendModes NewMode) {if (m_transformations.blend == NewMode) return; m_transformations.blend = NewMode; transformations_update();}
		NESSENGINE_API virtual void set_zindex(float newZ) {if (m_transformations.zorder == newZ) return; m_transformations.zorder = newZ; transformations_update();}
		NESSENGINE_API virtual void flip_x() {m_transformations.scale.x *= -1; transformations_update();}
		NESSENGINE_API virtual void flip_y() {m_transformations.scale.y *= -1; transformations_update();}
		NESSENGINE_API virtual const Point& get_position() const {return m_transformations.position;}
		NESSENGINE_API virtual const Size& get_scale() const {return m_transformations.scale;}
		NESSENGINE_API virtual const float get_rotation() const {return m_transformations.rotation;}
		NESSENGINE_API virtual const Color& get_color() const {return m_transformations.color;}
		NESSENGINE_API virtual const float get_opacity() const {return get_color().a;}
		NESSENGINE_API virtual const EBlendModes get_blend_mode() const {return m_transformations.blend;}
		NESSENGINE_API virtual float get_zindex() const {return m_transformations.zorder;}
		NESSENGINE_API virtual Ness::Point get_direction_vector() const {return Ness::Point::from_angle(get_rotation());}

		// return absolute position
		NESSENGINE_API virtual Point get_absolute_position() {return get_absolute_transformations().position;}

		// return absolute z index
		NESSENGINE_API virtual float get_absolute_zindex() {return get_absolute_transformations().zorder;}

		// called whenever transformations are updated
		NESSENGINE_API virtual void transformations_update() {}
		NESSENGINE_API virtual bool need_transformations_update() = 0;

		// return the absolute transformations of this object, with its parents taken into consideration
		NESSENGINE_API virtual const SRenderTransformations& get_absolute_transformations() = 0;
	};

};