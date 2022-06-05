#include "Point.h"

using namespace godot;

void Point::_register_methods() {
	register_method("_ready", &Point::_ready);
	register_method("on_move", &Point::on_move);
	register_signal<Point>("got_point", "node", GODOT_VARIANT_TYPE_OBJECT);
	register_signal<Point>("change_behaviour", "node", GODOT_VARIANT_TYPE_OBJECT);
}

void Point::_init() {}

Point::Point() {}
Point::~Point() {}

void Point::_ready() {
	get_node("../../Player")->connect("change_position", this, "on_move");
}

void Point::on_move(Node *node, Vector2 nposition) {
	float px = nposition.x;
	float py = nposition.y;
	float x = get_position().x;
	float y = get_position().y;

	if (is_visible()) {
		if (px - 10 < x && px + 10 > x && py - 10 < y && py + 10 > y) {
			set_visible(false);
			emit_signal("got_point", this);
			if (is_in_group("BigPoint"))
				emit_signal("change_behaviour", this);
			queue_free();
		}
	}
}