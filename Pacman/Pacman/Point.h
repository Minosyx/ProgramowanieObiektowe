#pragma once

#include <Godot.hpp>
#include <Area2D.hpp>

namespace godot {
	class Point : public Area2D
	{
		GODOT_CLASS(Point, Area2D);
	public:
		static void _register_methods();
		void _init();

		void _ready();
		Point();
		~Point();

		void on_move(Node*, Vector2);
	};
}
