#include <iostream>
#include <SDL2/SDL.h>
#include <set>


std::set<SDL_Joystick*> joysticks;

void addJoystickToSet(int id) {
	SDL_Joystick* joystick = SDL_JoystickOpen(id);
	if (joystick) {
		joysticks.insert(joystick);
	}
}

void removeJoystickFromSet(int id) {
	joysticks.erase(SDL_JoystickFromInstanceID(id));
	SDL_JoystickClose(SDL_JoystickFromInstanceID(id));
}

void addAllConnectedJoystickToSet() {
	int numJoysticks = SDL_NumJoysticks();
	for (int i = 0; i < numJoysticks; ++i) {
		addJoystickToSet(i);
	}
}

void removeAllConnectedJoystickToSet() {
	int numJoysticks = SDL_NumJoysticks();
	for (int i = 0; i < numJoysticks; ++i) {
		removeJoystickFromSet(i);
	}
}

int main(int argc, char* argv[]) {

	std::cout << "SDL2 Joystick Test" << std::endl;

    // Starting SDL 2
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0) {
        std::cerr << "Error on SDL start up: " << SDL_GetError() << std::endl;
        return 1;
    }

	addAllConnectedJoystickToSet();

    bool isStillRunning = true;

    while (isStillRunning) {
		SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
				case SDL_JOYDEVICEADDED:
					addJoystickToSet(event.jdevice.which);
					std::cout << "Joystick added: " << SDL_JoystickNameForIndex(event.jdevice.which) << std::endl;
					break;
				case SDL_JOYDEVICEREMOVED:
					std::cout << "Joystick removed: " << event.jdevice.which << std::endl;
					removeJoystickFromSet(event.jdevice.which);
					break;
				case SDL_JOYAXISMOTION:
					std::cout << "Joystick " << (int)event.jaxis.which
						<< ", axis " << (int)event.jaxis.axis
						<< " value: " << event.jaxis.value << std::endl;
					break;
				case SDL_JOYBUTTONDOWN:
				case SDL_JOYBUTTONUP:
					std::cout << "Joystick " << (int)event.jbutton.which
						<< ", button " << (int)event.jbutton.button
						<< (event.type == SDL_JOYBUTTONDOWN ? " pressed" : " released") << std::endl;
					break;
				case SDL_QUIT:
					isStillRunning = false;
					break;
				default:
					break;
			}
		}

		SDL_Delay(10);
	}

	removeAllConnectedJoystickToSet();
	SDL_Quit();

    return 0;
}