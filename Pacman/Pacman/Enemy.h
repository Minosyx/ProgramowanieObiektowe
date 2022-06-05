#pragma once

#include <Godot.hpp>
#include <KinematicBody2D.hpp>
#include <KinematicCollision2D.hpp>
#include <SceneTree.hpp>
#include <Node2D.hpp>
#include <chrono>
#include <random>


namespace godot {

	class Enemy : public KinematicBody2D
	{
		GODOT_CLASS(Enemy, KinematicBody2D);
	private:
		Vector2 motion;
		Vector2 prevM;
		int player;
		int direction;
		std::default_random_engine generator;
		int SPEED;
		float timer;
		bool was_changed;
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		void _ready();
		Enemy();
		~Enemy();

		void on_change_behaviour();
		void dir_change(Node *);
		void checkCollider(int);
		void set_default();
	};

}