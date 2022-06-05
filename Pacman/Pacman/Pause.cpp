#include "Pause.h"

using namespace godot;

void Pause::_register_methods(){
	register_method("_process", &Pause::_process);
}

void Pause::_init() {};

void Pause::_process(float delta) {
	checkPause();
};

Pause::Pause() {};
Pause::~Pause() {};

void Pause::checkPause() {
	Input* i = Input::get_singleton();
	if (i->is_action_just_pressed("ui_select")) {
		if (get_tree()->is_paused()) {
			get_tree()->set_pause(0);
			set_visible(false);
		}
		else {
			get_tree()->set_pause(1);
			set_visible(true);
		}
	}
}