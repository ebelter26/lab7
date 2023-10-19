#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>
using namespace std;
using namespace sf;
using namespace sfp;
int main()
{
	// Create our window and world with gravity 0,1
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	// Create the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(150,250));
	ball.setRadius(20);
	world.AddPhysicsBody(ball);
	ball.applyImpulse(Vector2f(0.5,0.4));



	// Create the square
	PhysicsRectangle square;
	square.setSize(Vector2f(80, 80));
	square.setCenter(Vector2f(400,300));
	square.setStatic(true);
	world.AddPhysicsBody(square);
	int bangCount(1);
	square.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++;
		if (bangCount == 3) {
			exit(0);
		}
		};

	// Create the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);
	int thudCount(1);
	//adds to count "thud" if ball strikes floor
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};
	// Create the left wall
	PhysicsRectangle wallLeft;
	wallLeft.setSize(Vector2f(20, 600));
	wallLeft.setCenter(Vector2f(10, 300));
	wallLeft.setStatic(true);
	world.AddPhysicsBody(wallLeft);
	//adds to count "thud" if ball strikes wall
	wallLeft.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Create the right wall
	PhysicsRectangle wallRight;
	wallRight.setSize(Vector2f(20, 600));
	wallRight.setCenter(Vector2f(790, 300));
	wallRight.setStatic(true);
	world.AddPhysicsBody(wallRight);
	//adds to count "thud" if ball strikes wall
	wallRight.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	// Create the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(800, 20));
	ceiling.setCenter(Vector2f(400, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);
	//adds to count "thud" if ball strikes ceiling
	ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++;
		};

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(square);
		window.draw(floor);
		window.draw(wallLeft);
		window.draw(wallRight);
		window.draw(ceiling);
		window.display();
	}
}
