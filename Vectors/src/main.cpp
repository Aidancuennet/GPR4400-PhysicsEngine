#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>


#include "physic_mrua.h"

namespace gpr4400 {


	class PhysicMRUAViewer : public PhysicMRUA {
	public:
		PhysicMRUAViewer(int dx, int dy) : PhysicMRUA(dx, dy) {}
		void Init() {
			PhysicMRUA::Init();
		}
		void UpdateDrawData(double delta_time) {
			PhysicMRUA::UpdateDrawData(delta_time);
			circle_shapes_.clear();
			for (const auto& circle : circles_) {
				srand(time(NULL));
				sf::CircleShape circle_shape;
				circle_shape.setRadius(circle.radius);
				circle_shape.setOutlineColor(circle.color);
				circle_shape.setOutlineThickness(2);
				circle_shape.setPosition({ circle.get_printing_center().x - circle.radius,
					circle.get_printing_center().y - circle.radius });
				circle_shapes_.push_back(circle_shape);
			}
		}
		void Render(sf::RenderWindow& window) const {
			for (auto& circle : circle_shapes_)
				window.draw(circle);
		}


	protected:
		std::vector<sf::CircleShape> circle_shapes_;
	};

} // End namespace gpr4400.

int main(int ac, char** av) {
	auto videoMode = sf::VideoMode(1280, 720);
	sf::RenderWindow window(videoMode, "Physic simulator sphere Viewer");
	sf::Mouse mouse;
	window.setFramerateLimit(60);

	gpr4400::PhysicMRUAViewer physic_sym(1280, 720);
	physic_sym.Init();
	// Setup the timer.
	auto start = std::chrono::steady_clock::now();
	auto previous = start;
	double delta_time = 0.0;
	while (window.isOpen()) {
		sf::Event event;
		
		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				
				if (event.key.code == sf::Keyboard::Key::Q)
				{
					physic_sym.CreateCircle({ static_cast<float>(mouse.getPosition(window).x/100), static_cast<float>(mouse.getPosition(window).y/100) }, 20.f, { 4.f, 4.f }, 20.f);
				}
				if (event.key.code == sf::Keyboard::Key::W)
				{
					physic_sym.CreateCircle({ static_cast<float>(mouse.getPosition(window).x / 100), static_cast<float>(mouse.getPosition(window).y / 100) }, 30.f, { 4.f, 4.f }, 30.f);
				}
				
				if (event.key.code == sf::Keyboard::Key::Escape)
					window.close();
					
			//if (event.key.code == sf::Keyboard::Key::W)
				//	physic_sym.CreateCircle({ 0,0 }, 20.f, { 4.f,4.f }, 20.f);
				//if (event.key.code == sf::Keyboard::Key::E)
				//	physic_sym.CreateCircle({ 0,0 }, 30.f, { 4.f,4.f }, 30.f);
				//if (event.key.code == sf::Keyboard::Key::R)
				//	physic_sym.CreateCircle({ 0,0 }, 40.f, { 4.f,4.f }, 40.f);
				//if (event.key.code == sf::Keyboard::Key::T)
					
			}
		}
		// Compute the time.
		auto end = std::chrono::steady_clock::now();
		using second = std::chrono::duration<double>;
		delta_time = std::chrono::duration_cast<second>(end - previous).count();
		previous = end;
		physic_sym.UpdateDrawData(delta_time);
		window.clear(sf::Color::Black);
		physic_sym.Render(window);
		window.display();
	}
	return 0;
}