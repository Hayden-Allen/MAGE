#pragma once
#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace mage::gfx
{
	template<typename T>
	class camera
	{
	public:
		MAGE_DCM(camera);
		virtual ~camera() {}


		virtual const glm::mat4& get_projection() const
		{
			return m_projection;
		}
		virtual const glm::mat4& get_view() const
		{
			return m_view;
		}
		virtual const glm::mat4& get_view_projection() const
		{
			return m_view_projection;
		}
		virtual const glm::vec3& get_pos() const
		{
			return m_pos;
		}
		virtual const T& get_rotation() const
		{
			return m_rotation;
		}
		virtual void set_pos(const glm::vec3& pos)
		{
			m_pos = pos;
			update();
		}
		virtual void set_rotation(const T& rotation)
		{
			m_rotation = rotation;
			update();
		}
	protected:
		glm::mat4 m_projection, m_view, m_view_projection;
		glm::vec3 m_pos;
		T m_rotation;


		camera(const glm::mat4& projection, const glm::mat4& view, const glm::vec3& pos, const T& rotation) :
			m_projection(projection),
			m_view(view),
			m_pos(pos),
			m_rotation(rotation)
		{}


		virtual void update() = 0;
	};



	class orthographic_camera : public camera<float>
	{
	public:
		MAGE_DCM(orthographic_camera);
		virtual ~orthographic_camera() {}


		static orthographic_camera* create(float left, float right, float bottom, float top, const glm::vec3& pos, float rotation);
	protected:
		orthographic_camera(float left, float right, float bottom, float top, const glm::vec3& pos, float rotation) :
			camera<float>(glm::ortho(left, right, bottom, top), glm::mat4(1.f), pos, rotation)
		{}
	};
}
