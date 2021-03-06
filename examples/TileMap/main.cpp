/*
* NessEngine TileMap demo. creates a tilemap and gives basic editing toolbar.
* PLEASE NOTE: this project relays on the folder examples/ness-engine to be one step above the project dir. so make sure you include it as well.
*				also, the vs project adds the libs dir to the PATH variable when running debug/release. so if you want to run the exectuables outside 
*				visual studio (by clicking on the exectuable), you'll need to copy the dll files to the same dir as the exe.
* Author: Ronen Ness
* Since: 07/2014
*/

#include <NessEngine.h>
#include <tchar.h>

int _tmain(int argc, _TCHAR* argv[])
{
	// init and create a renderer
	Ness::init();
	Ness::Renderer render("Tilemap demo!", Ness::Sizei(800, 600));

	// create a new scene
	Ness::ScenePtr scene = render.create_scene();

	// create the tilemap
	const int TileSize = 32;							// <-- 32 is the size of a single tile in the spritesheet
	const Ness::Pointi TilesInSpritesheet(6, 16);		// <-- 6 is how many tile types we got in the spritesheet on X axis, 16 is how many we got on Y axis
	Ness::TileMapPtr map = scene->create_tilemap("tilemap.jpg", Ness::Sizei(100, 100), Ness::Sizei(TileSize, TileSize));
	map->set_all_tiles_type(Ness::Pointi(0, 0), TilesInSpritesheet);

	// create the highlight of the currently selected tile
	Ness::RectangleShapePtr selectedTile = scene->create_rectangle();
	selectedTile->set_size(Ness::Sizei(TileSize, TileSize));
	selectedTile->set_color(Ness::Color::GREEN);
	selectedTile->set_anchor(Ness::Point(0.0f, 0.0f));
	selectedTile->set_filled(false);

	// create the tile selection box
	Ness::SpritePtr tilesToolbar = scene->create_sprite("tilemap.jpg");
	tilesToolbar->set_static(true);

	// create the tile selection red border
	Ness::RectangleShapePtr tilesToolbarBorder = scene->create_rectangle();
	tilesToolbarBorder->set_size(tilesToolbar->get_size());
	tilesToolbarBorder->set_color(Ness::Color::RED);
	tilesToolbarBorder->set_static(true);
	tilesToolbarBorder->set_filled(false);

	// create the highlight of the selected tile from the toolbar on the left
	Ness::RectangleShapePtr tilesToolbarSelectedType = scene->create_rectangle();
	tilesToolbarSelectedType->set_size(Ness::Sizei(TileSize, TileSize));
	tilesToolbarSelectedType->set_color(Ness::Color(1.0f, 0.0f, 0.0f, 0.45f));
	tilesToolbarSelectedType->set_static(true);
	tilesToolbarSelectedType->set_filled(true);
	tilesToolbarSelectedType->set_blend_mode(Ness::BLEND_MODE_BLEND);

	// the currently selected tile type to set
	Ness::Pointi SelectedTileType(0, 0);

	// create instructions text
	Ness::MultiTextPtr instructions = scene->create_multitext("../ness-engine/resources/fonts/courier.ttf", 
		"use arrows or wasd to move around the map.\npick tile type from the left bar & click anywhere to set.\nz to zoom-in, x to zoom-out, c to reset zoom.", 18);
	instructions->set_static(true);
	instructions->set_position(Ness::Point(0.0f, (float)render.get_screen_size().y - 50));
	instructions->set_anchor(Ness::Point(0.0f, 1.0f));

	// create a camera
	Ness::CameraPtr camera = render.create_camera();
	float CameraSpeed = 500.0f;

	// create the corner logo
	Ness::SpritePtr corner_logo = scene->create_sprite("../ness-engine/resources/gfx/Ness-Engine-Small.png");
	corner_logo->set_blend_mode(Ness::BLEND_MODE_BLEND);
	corner_logo->set_anchor(Ness::Point::ONE);
	corner_logo->set_opacity(0.5f);
	corner_logo->set_static(true);
	corner_logo->set_position(render.get_screen_size());

	// create the events handler
	Ness::Utils::EventsPoller EventsPoller;
	Ness::Utils::Mouse mouse;
	Ness::Utils::Keyboard keyboard;
	Ness::Utils::ApplicationEvents app;
	EventsPoller.add_handler(mouse);
	EventsPoller.add_handler(keyboard);
	EventsPoller.add_handler(app);

	// current zoomin
	float zoom = 1.0f;

	// show logo screen
	Ness::Utils::make_logo_screen(scene, "../ness-engine/resources/gfx/logo.png");

	// loop until exit button is pressed
	while( !app.got_quit() )
	{
		// handle events
		EventsPoller.poll_events();

		// render the scene
		render.start_frame();

		// do keyboard control
		if (keyboard.key_state(SDLK_DOWN) || keyboard.key_state(SDLK_s))
		{
			camera->position.y += render.time_factor() * CameraSpeed;
		}
		if (keyboard.key_state(SDLK_UP) || keyboard.key_state(SDLK_w))
		{
			camera->position.y -= render.time_factor() * CameraSpeed;
		}
		if (keyboard.key_state(SDLK_LEFT) || keyboard.key_state(SDLK_a))
		{
			camera->position.x -= render.time_factor() * CameraSpeed;
		}
		if (keyboard.key_state(SDLK_RIGHT) || keyboard.key_state(SDLK_d))
		{
			camera->position.x += render.time_factor() * CameraSpeed;
		}
		if (keyboard.key_state(SDLK_z))
		{
			zoom += 0.5f * render.time_factor();
			map->set_scale(zoom);
		}
		if (keyboard.key_state(SDLK_x))
		{
			zoom -= 0.5f * render.time_factor();
			map->set_scale(zoom);
		}
		if (keyboard.key_state(SDLK_c))
		{
			zoom = 1.0f;
			map->set_scale(zoom);
		}

		// pick the tile we currently point on with the mouse
		Ness::SpritePtr tile = map->get_sprite_by_position((Ness::Pointi)camera->position + mouse.position());

		// if a tile is picked set the visual on it
		if (tile)
		{
			selectedTile->set_position(tile->get_absolute_position());
			selectedTile->set_scale(zoom);
			selectedTile->set_visible(true);
		}
		else
		{
			selectedTile->set_visible(false);
		}
		

		// if left mouse click is down:
		if (mouse.is_down(Ness::MOUSE_LEFT))
		{
			// if mouse position is inside the tile selection, we pick a new tile type:
			if (mouse.position().x <= tilesToolbar->get_size().x && mouse.position().y <= tilesToolbar->get_size().y)
			{
				SelectedTileType.x = (int)(mouse.position().x / TileSize);
				SelectedTileType.y = (int)(mouse.position().y / TileSize);
				tilesToolbarSelectedType->set_position(SelectedTileType * TileSize);
			}

			// else, if we got selected tile, change its type
			else if (tile)
			{
				tile->set_source_from_sprite_sheet(SelectedTileType, TilesInSpritesheet);
			}
		}

		// render and end the scene
		scene->render(camera);
		render.end_frame();
	}

	// cleanup. 
	// note: the 'remove' lines are not mandatory, they are just to illustrate how to remove an entity from the scene.
	scene->remove(tilesToolbarBorder);
	scene->remove(tilesToolbar);
	scene->remove(map);
	return 0;
}