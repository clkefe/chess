#include <SFML/Graphics.hpp>
#include <iostream>


// Constants
const sf::Color COLOR_GREEN = sf::Color(124, 148, 93);
const sf::Color COLOR_WHITE = sf::Color(238,238,213);


// Function declerations. TODO: Move these to the headers file!
sf::Color get_square_color(int row, int col);

int main()
{
    auto window = sf::RenderWindow{ { 800, 800 }, "Chess Game",  sf::Style::Close};
    window.setFramerateLimit(144);

    // We use 256 vertex because each quad needs 4 vertex, and there are 64 squares on a chess board (64*4=256).
    sf::VertexArray triangle(sf::Quads, 256);

    float square_x{0};
    float square_y{0};

    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            // Find the square's linear position in the 8x8 grid. Then, muliply by 4 because each quad has 4 vertex.
            int starting_index = (row * 8 + col) * 4;

            triangle[starting_index].position = sf::Vector2f(square_x, square_y + 100); // left-bottom
            triangle[starting_index + 1].position = sf::Vector2f(square_x, square_y); // left-top
            triangle[starting_index + 2].position = sf::Vector2f(square_x + 100, square_y); // right-top
            triangle[starting_index + 3].position = sf::Vector2f(square_x + 100, square_y + 100); // right-bottom

            // Set the color of each vertex of each quad/square (in SFML, each quad has 4 vertex).
            for(int j = 0; j < 4; j++) {
                triangle[starting_index + j].color = get_square_color(row, col);
            }

            square_x += 100.f;
        }

        square_y += 100.f;
        square_x = 0;
    }


    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();
        window.draw(triangle);
        window.display();
    }
}

sf::Color get_square_color(const int row, const int col) {
    if ((row + col) % 2 == 0) {
        return COLOR_WHITE;
    }

    return COLOR_GREEN;
}