#pragma once
#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <RayCast2D.hpp>
#include <string.h>
#include <thread>
#include <queue>

namespace godot {
	class Player : public KinematicBody2D {
		GODOT_CLASS(Player, KinematicBody2D);
	private:
		Vector2 motion;
		float rotation;
		int dir;
		int lives;
		std::queue<int> nKey;
	public:
		const int SPEED = 200;
		static void _register_methods();
		void _init();
		void _process(float delta);

		void _ready();
		Player();
		~Player();

		void on_body_entered(Node*, int);
		void die();
		void raycast();
		void move();
		void input();
	};
}