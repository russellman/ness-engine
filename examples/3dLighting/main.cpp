/*
* NessEngine hello world application. does nothing but rendering "hello world" on the screen.
* PLEASE NOTE: this project relays on the folder examples/ness-engine to be one step above the project dir. so make sure you include it as well.
*				also, the vs project adds the libs dir to the PATH variable when running debug/release. so if you want to run the exectuables outside 
*				visual studio (by clicking on the exectuable), you'll need to copy the dll files to the same dir as the exe.
* Author: Ronen Ness
* Since: 07/2014
*/

#include <NessEngine.h>

// is the program still running
bool g_running = true;

// our customized sprite with 3d lightings effect
class Sprite3d : public Ness::Sprite
{

};

// callback to handle exit events
void HandleEvents(const SDL_Event& event)
{
	if (event.type == SDL_QUIT)
		g_running = false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// init and create a renderer
	Ness::init();
	Ness::Renderer renderer("Hello World!", Ness::Sizei(512, 512));

	// create a new scene
	Ness::ScenePtr scene = renderer.create_scene();

	// add the hello-world sprite to it
	Ness::SpritePtr sprite = scene->create_sprite("hello_world.png");

	// create the events handler
	Ness::Utils::EventsPoller EventsPoller;

	// loop until exit button is pressed
	while( g_running )
	{
		// handle events
		EventsPoller.poll_events(HandleEvents, false);

		// render the scene
		renderer.start_frame();
		scene->render();
		renderer.end_frame();
	}

	// cleanup
	scene->remove(sprite);
	renderer.remove_scene(scene);
	return 0;
}