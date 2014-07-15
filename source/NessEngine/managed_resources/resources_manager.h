/**
* A class that manage all the loaded resources
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once
#include "../exports.h"
#include <string>
#include <unordered_map>
#include "managed_texture.h"
#include "managed_font.h"

namespace Ness
{
	namespace ManagedResources
	{

		// Texture as it stored in the resources manager
		struct __STextureInManager
		{
			unsigned int	ref_count;
			ManagedTexture* texture;
		};

		// Font as it stored in the resources manager
		struct __SFontInManager
		{
			unsigned int	ref_count;
			ManagedFont*	font;
		};

		/**
		* the resources manager
		*/
		class ResourcesManager
		{
		private:
			std::unordered_map<std::string, __STextureInManager>	m_textures;			// map that holds all loaded textures
			std::unordered_map<std::string, __SFontInManager>		m_fonts;			// map that holds all loaded fonts
			std::string												m_base_path;		// basic path to search resources under
			Colorb													m_color_key;		// transparency color key
			bool													m_use_color_key;	// enable/disable color key
			SDL_Renderer*											m_renderer;			// our sdl renderer

		public:

			// create the resource manager and set defaults
			NESSENGINE_API ResourcesManager();

			// set the renderer for this resources manager
			NESSENGINE_API inline void set_renderer(SDL_Renderer* renderer) {m_renderer = renderer;}

			// get/load a texture
			NESSENGINE_API ManagedTexturePtr get_texture(const std::string& textureName);

			// get/load a font
			NESSENGINE_API ManagedFontPtr get_font(const std::string& fontName, int fontSize = 12);

			// create an empty texture you can render on (use as rendering target). 
			// this texture will be added to the resource manager and you can later get it with get_texture()
			// if size is ZERO, will use entire screen size
			NESSENGINE_API ManagedTexturePtr create_blank_texture(const std::string& textureName, const Sizei& size = Sizei::ZERO);

			// set the colorkey for this renderer
			// every texture loaded after this set will turn all pixels in the color key to transparent
			NESSENGINE_API void set_color_key(const Colorb& color) {m_color_key = color; m_use_color_key = true;}
			NESSENGINE_API void disable_color_key() {m_use_color_key = false;}

			// destroy the resources manager and clear all resources
			NESSENGINE_API ~ResourcesManager();

			// set basic path to search for resources under
			NESSENGINE_API inline void set_resources_path(const std::string& path) {m_base_path = path;}

			// when a texture is removed (no longer referenced and deleted), it calls this function to be removed from the textures map as well
			// DONT USE THIS ON YOUR OWN, it supposed to happen automatically when texture has no more references.
			void __delete_texture(const std::string& textureName);

			// when a font is removed (no longer referenced and deleted), it calls this function to be removed from the fonts map as well
			// DONT USE THIS ON YOUR OWN, it supposed to happen automatically when a font has no more references.
			void __delete_font(const std::string& fontName);

		};
	};
};