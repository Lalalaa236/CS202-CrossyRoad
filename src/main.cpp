#include <bits/stdc++.h>
#include "raylib.h"
// #include "Player.h"

using namespace std;

#define MAX_OBSTACLES 10

class Player {
public:
	Vector3 position;
	float speed;
	float size;
	Color color;

	Player(Vector3 position, float speed, float size, Color color) {
		this->position = position;
		this->speed = speed;
		this->size = size;
		this->color = color;
	}

	void move(Vector3 direction) {
		position.x += direction.x * speed;
		position.z += direction.z * speed;
	}

	void draw() {
		DrawCube(position, size, size, size, color);
	}
};

class Obstacle {
public:
	Vector3 position;
	float speed;
	float size;
	Color color;

	Obstacle(Vector3 position, float speed, float size, Color color) {
		this->position = position;
		this->speed = speed;
		this->size = size;
		this->color = color;
	}

	void move() {
		position.z += speed;
	}

	void draw() {
		DrawCube(position, size, size, size, color);
	}
};

int main() {
	const int screenWidth = 800;
	const int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Crossing Road");

	Camera camera = { 0 };
	camera.position = { 20.0f, 20.0f, 20.0f };
	camera.target = { 0.0f, 0.0f, 0.0f };
	camera.up = { 0.0f, 1.0f, 0.0f };
	camera.fovy = 45.0f;
	camera.type = CAMERA_PERSPECTIVE;

	SetCameraMode(camera, CAMERA_FREE);

	Player player({ 0.0f, 0.5f, 0.0f }, 0.2f, 1.0f, RED);

	std::vector<Obstacle> obstacles;

	for (int i = 0; i < MAX_OBSTACLES; i++) {
		obstacles.push_back(Obstacle({ GetRandomValue(-10, 10), 0.5f, GetRandomValue(-50, -10) }, GetRandomValue(1, 5) / 10.0f, 1.0f, BLUE));
	}

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		UpdateCamera(&camera);

		Vector3 direction = { 0.0f, 0.0f, 0.0f };

		if (IsKeyDown(KEY_UP)) {
			direction.z = -1.0f;
		}
		if (IsKeyDown(KEY_DOWN)) {
			direction.z = 1.0f;
		}
		if (IsKeyDown(KEY_LEFT)) {
			direction.x = -1.0f;
		}
		if (IsKeyDown(KEY_RIGHT)) {
			direction.x = 1.0f;
		}

		player.move(direction);

		for (auto& obstacle : obstacles) {
			obstacle.move();

			if (CheckCollisionBoxes({ obstacle.position.x - obstacle.size / 2, obstacle.position.y - obstacle.size / 2, obstacle.position.z - obstacle.size / 2, obstacle.size, obstacle.size, obstacle.size },
				{ player.position.x - player.size / 2, player.position.y - player.size / 2, player.position.z - player.size / 2, player.size, player.size, player.size })) {
				player.color = BLACK;
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		BeginMode3D(camera);

		player.draw();

		for (auto& obstacle : obstacles) {
			obstacle.draw();
		}

		EndMode3D();

		EndDrawing();
	}

	CloseWindow();

	return 0;
}