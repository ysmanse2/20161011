#include <iostream>
#include <string>
#include <vector>
#include <GLFW/glfw3.h>
#include <stdlib.h>		  
#include <math.h>

const int width = 640;
const int height = 480;
int i_center = 300, j_center = 400;
int thickness = 50;

float *pixels = new float[width * height * 3];

void drawPixel(const int& i, const int& j, const float& red, const float& green, const float& blue)
{
	pixels[(i + width* j) * 3 + 0] = red;
	pixels[(i + width* j) * 3 + 1] = green;
	pixels[(i + width* j) * 3 + 2] = blue;
}


class Background
{
public:
	// some variables
	void draw()
	{
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				pixels[(i + width* j) * 3 + 0] = 1.0f;
				pixels[(i + width* j) * 3 + 1] = 1.0f;
				pixels[(i + width* j) * 3 + 2] = 1.0f;
			}
		}
	}
};


class Box // NO PARENT (2pts)
{
public:
	// some variables
	void draw()
	{
		//»ç°¢Çü
		int i_center = 500;
		int j_center = 400;

		for (int j = j_center - thickness; j < j_center + thickness; j++) {
			for (int i = i_center - thickness; i < i_center + thickness; i++) {
				drawPixel(i, j, 1.0f, 0.0f, 0.0f);
			}
		}
	}
};
class Circle // NO PARENT (2pts)
{
public:
	// some variables
	void draw()
	{
		double radius = 0;

		for (int j = 1; j <= 60; j++)
		{
			radius = j;
			for (double i = 0.0; i < 360.0; i += 0.1)
			{
				double angle = i * 3.1415926535897932384626433832795 / 180;

				int x = (int)(300 + radius * cos(angle));
				int y = (int)(100 + radius * sin(angle));

				drawPixel(x, y, 1.0f, 0.0f, 0.0f);
			}
		}
	}
};

class GeometricobjectInterface
{
public:
	virtual void draw() = 0;
};


template<class T_OPERATION>
class GeometricObject : public GeometricobjectInterface
{
public:

	void draw()
	{
		T_OPERATION operation;
		operation.draw();
	}

};

// And implement an templatized GeometricObject class. (3pts)
int main()
{

	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(width, height, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		glClear(GL_COLOR_BUFFER_BIT);

		std::vector<GeometricobjectInterface*> obj_list;
		obj_list.push_back(new GeometricObject<Background>);
		obj_list.push_back(new GeometricObject<Box>);
		obj_list.push_back(new GeometricObject<Circle>);

		for (auto itr : obj_list)
			itr->draw();

		glDrawPixels(width, height, GL_RGB, GL_FLOAT, pixels);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();

	delete[] pixels;
	// free(pixels);

	return 0;
}