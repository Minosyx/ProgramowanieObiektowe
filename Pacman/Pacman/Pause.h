#pragma once

#include <Godot.hpp>
#include <Control.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>

namespace godot {
	class Pause : public Control
	{
		GODOT_CLASS(Pause, Control);
	public:
		static void _register_methods();
		void _init();
		void _process(float delta);

		Pause();
		~Pause();

		void checkPause();
	};
}

