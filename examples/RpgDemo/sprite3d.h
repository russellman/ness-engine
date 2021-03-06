#include <NessEngine.h>

// our customized sprite with 3d lightings effect
class Sprite3d : public Ness::Sprite
{
private:
	Ness::ManagedResources::ManagedTexturePtr		m_light_front;
	Ness::ManagedResources::ManagedTexturePtr		m_light_left;
	Ness::ManagedResources::ManagedTexturePtr		m_light_right;
	Ness::LightNodePtr								m_light_node;
	Ness::CameraApiPtr								m_last_camera;
	bool											m_render_diffuse;

public:

	Sprite3d(Ness::LightNodePtr lightNode, const Ness::String& TextureFile);

	// enable/disable diffuse layer
	inline void render_diffuse(bool enabled) {m_render_diffuse = enabled;}

	// override the render function just to store the camera before do_render (we need it inside)
	virtual void render(const Ness::CameraApiPtr& camera);

	// do the 3d-like rendering
	virtual void Sprite3d::do_render(const Ness::Rectangle& target, const Ness::SRenderTransformations& transformations);
};