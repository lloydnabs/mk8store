#if defined(SWITCH)
#include <switch.h>
#endif

#if defined(__WIIU__)
#include <unistd.h>
#endif
#if OSGetTitleID==0000500101004A200
#define DEFAULT_REPO "http://host.ctgpu.tk/CTGPU/PAL"
#else OSGetTitleID = 0x000500101004A100
#define DEFAULT_REPO "http://host.ctgpu.tk/CTGPU/USA"
#endif
#include "libget/src/Get.hpp"
#include "libget/src/Utils.hpp"
#include "dynamic_libs/os_functions.h"
#include "dynamic_libs/sys_functions.h"
#if defined(NOGUI)
#include "console/Input.hpp"
#include "console/Menu.hpp"
#else
#include "gui/MainDisplay.hpp"
#endif

#if defined(__WIIU__)
	 
#else
#define DEFAULT_REPO "https://switch.apps.fortheusers.org"
#endif

int main(int argc, char* argv[])
{
//	consoleDebugInit(debugDevice_SVC);
//	stdout = stderr; // for yuzu

#if defined(__WIIU__)
#define HBAS_PATH ROOT_PATH "wiiu/apps/mk8store"
#define ELF_PATH HBAS_PATH "/hbas.elf"
#define RPX_PATH HBAS_PATH "/mk8store.rpx"
    mkdir(HBAS_PATH, 0700);
	chdir(HBAS_PATH);

	// "migrate" old elf users over to rpx (should've been done last version)
	struct stat sbuff;
	if (stat(ELF_PATH, &sbuff) == 0)
		std::rename(ELF_PATH, RPX_PATH);
#endif
	init_networking();

	// create main get object
	Get* get = new Get("./.get/", DEFAULT_REPO);

#if defined(NOGUI)
	// if NOGUI variable defined, use the console's main method
	int console_main(Get*);
	return console_main(get);
#else

	// initialize main title screen
	MainDisplay* display = new MainDisplay(get);

	// the main inuput handler
	InputEvents* events = new InputEvents();

	bool running = true;
	while (running)
	{
		bool atLeastOneNewEvent = false;
		bool viewChanged = false;

		int frameStart = SDL_GetTicks();

		// get any new input events
		while (events->update())
		{
			// process the inputs of the supplied event
			viewChanged |= display->process(events);
			atLeastOneNewEvent = true;
		}

		// one more event update if nothing changed or there were no previous events seen
		// needed to non-input related processing that might update the screen to take place
		if ((!atLeastOneNewEvent && !viewChanged) || display->showingSplash)
		{
			events->update();
			viewChanged |= display->process(events);
		}

		// draw the display if we processed an event or the view
		if (viewChanged)
			display->render(NULL);
		else
		{
			// delay for the remainder of the frame to keep up to 60fps
			// (we only do this if we didn't draw to not waste energy
			// if we did draw, then proceed immediately without waiting for smoother progress bars / scrolling)
			int delayTime = (SDL_GetTicks() - frameStart);
			if (delayTime < 0)
				delayTime = 0;
			if (delayTime < 16)
				SDL_Delay(16 - delayTime);
		}
	}

	quit();

	return 0;
#endif
}
