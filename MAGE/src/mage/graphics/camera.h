#pragma once
#include "pch.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "mage/event/event_handler_container.h"
#include "mage/layer/layer.h"
#include "mage/util/typed.h"

namespace mage::gfx
{
	template<typename T>
	class camera : 
		public event_handler,
		public typed<T>
	{
	public:
		typedef typed<T>::s_type s_type;
	public:
		MAGE_DCM(camera);
		virtual ~camera() {}
	public:
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
		virtual const s_type& get_rotation() const
		{
			return m_rotation;
		}
		virtual void set_pos(const glm::vec3& pos)
		{
			m_pos = pos;
			update();
		}
		virtual void set_rotation(const s_type& rotation)
		{
			m_rotation = rotation;
			update();
		}
	protected:
		glm::mat4 m_projection, m_view, m_view_projection;
		glm::vec3 m_pos;
		s_type m_rotation;
	protected:
		camera(event_handler_container& c, const glm::mat4& projection, const glm::mat4& view, const glm::vec3& pos, const s_type& rotation) :
			m_projection(projection),
			m_view(view),
			m_pos(pos),
			m_rotation(rotation)
		{
			c.add(this);
		}
	protected:
		virtual void update() = 0;
	};



	class orthographic_camera : public camera<float>, public dimensional<float>
	{
	public:
		typedef camera::s_type s_type;
	public:
		MAGE_DCM(orthographic_camera);
		virtual ~orthographic_camera() {}
	public:
		static orthographic_camera* create(event_handler_container& c, float width, float height, const glm::vec3& pos, s_type rotation, float zoom);
		bool on_window_resize(window_resize_event& e) override
		{
			m_projection = compute_projection(m_w = e.get_w<float>(), m_h = e.get_h<float>());
			return true;
		}
		float get_zoom() const
		{
			return 1.f / m_zoom;
		}
		void set_zoom(float zoom)
		{
			m_zoom = 1.f / zoom;
			m_projection = compute_projection(m_w, m_h);
		}
	protected:
		float m_zoom;
	protected:
		orthographic_camera(event_handler_container& c, float width, float height, const glm::vec3& pos, s_type rotation, float zoom) :
			camera<float>(c, compute_projection(width, height), glm::mat4(1.f), pos, rotation),
			dimensional<float>(width, height),
			m_zoom(zoom)
		{}
	protected:
		glm::mat4 compute_projection(float width, float height)
		{
			return glm::ortho(-m_zoom, m_zoom, -height / width * m_zoom, height / width * m_zoom);
		}
	};
}
