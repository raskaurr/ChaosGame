// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Make code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
    // Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

    srand(time(0));
    vector<Vector2f> vertices;
    vector<Vector2f> points;
	int numVertex;
    int recentChoice = -1;
	bool toDisplayText = true;
    long unsigned int randPolygon = rand() % 2 + 3; // generate a 3 or a 4 randomly
    string prompt = "";

    if (randPolygon == 4)
    {
        prompt = "Make five clicks!";
    }
    else
    {
        prompt = "Make four clicks!";
    }

	sf::Text text;
	sf::Font font;
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	text.setFont(font);
	text.setString(prompt);
	text.setCharacterSize(85);
	text.setPosition(1920/4.0f, 1080/4.0f);
	text.setFillColor(sf::Color::Blue);
	text.setStyle(sf::Text::Bold);

	while (window.isOpen())
	{
        /*
		****************************************
		Handle the players input
		****************************************
		*/
        Event event;
		while (window.pollEvent(event))
		{
            if (event.type == Event::Closed)
            {
				// Quit the game when the window is closed
				window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                    std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                    if(vertices.size() < randPolygon) // depends if triangle or quadrilateral
                    {
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if(points.size() == 0)
                    {
                        ///fourth click
                        ///push back to points vector
			//window.clear();
                        toDisplayText = false;
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
        /*
		****************************************
		Update
		****************************************
		*/

        if(points.size() > 0)
        {
            ///generate more point(s)
            ///select random vertex
            ///calculate midpoint between random vertex and the last point in the vector
            ///push back the newly generated coord.
			if (randPolygon == 4) // block repeats for quadrilateral
            {
			    numVertex = rand() % 4;
                while (numVertex == recentChoice)
                {
                    numVertex = rand() % 4; // keep generating until different from previous
                }
                recentChoice = numVertex;
                points.push_back(Vector2f((vertices.at(numVertex).x + points.at(points.size()-1).x) / 2, 
                    (vertices.at(numVertex).y + points.at(points.size()-1).y) / 2));
            }
            else // normal triangle
            {
                numVertex = rand() % 3;
                points.push_back(Vector2f((vertices.at(numVertex).x + points.at(points.size()-1).x) / 2, 
                    (vertices.at(numVertex).y + points.at(points.size()-1).y) / 2));
            }
        }

        /*
		****************************************
		Draw
		****************************************
		*/
        //if (points.size() % 100 == 0)
	//{
		window.clear();
	//}

		if (toDisplayText)
		{	
            window.draw(text);
		}

        for(long unsigned int i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
	    for(long unsigned int i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(10,10));
            rect.setPosition(Vector2f(points[i].x, points[i].y));
            rect.setFillColor(Color::Blue);
            window.draw(rect);
        }
        window.display();
    }
}
