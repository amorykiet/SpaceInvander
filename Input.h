#ifndef INPUT_H
#define INPUT_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>


class Input {
public:
	static bool Keys[1024];

	static bool IsPressed(int key) {
		return Keys[key];
	}

private:
	Input();
};

#endif // !INPUT_H