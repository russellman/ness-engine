/**
* Define the loaded Font class
* Author: Ronen Ness
* Since: 07/1014
*/

#pragma once
#include "../exports.h"
#include <SDL_ttf.h>
#include <string>
#include "../primitives/primitives.h"

namespace Ness
{
	namespace Resources
	{
		/**
		* represent a loadable font data
		*/
		class LoadedFont
		{
		private:
			TTF_Font* m_font;

		public:
			// create the font from file
			NESSENGINE_API LoadedFont(const std::string& fileName, int fontSize = 12);

			// destroy the font
			NESSENGINE_API ~LoadedFont();

			// return the font
			inline NESSENGINE_API TTF_Font* font() const {return m_font;}

		};
	};
};