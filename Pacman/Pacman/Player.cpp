#include "Player.h"

using namespace godot;

#define ADJUST 4

void Player::_register_methods() {
	register_method("_process", &Player::_process);
	register_method("_ready", &Player::_ready);
	register_method("on_body_entered", &Player::on_body_entered);
	register_method("die", &Player::die);
	register_signal<Player>("redraw", "node", GODOT_VARIANT_TYPE_OBJECT, "lives", GODOT_VARIANT_TYPE_INT);
	register_signal<Player>("change_position", "node", GODOT_VARIANT_TYPE_OBJECT, "nposition", GODOT_VARIANT_TYPE_VECTOR2);
}

void Player::_init() {}

Player::Player() {
	motion = Vector2(0, 0);
	rotation = 0.0;
	dir = 0;
}

Player::~Player() {}

void Player::_ready() {
	lives = get_node("/root/PlayerVariables")->get("Health");
	int enCount = get_tree()->get_nodes_in_group("Enemy").size();
	Array en = get_tree()->get_nodes_in_group("Enemy");
	for (int i = 0; i < enCount; i++) {
		Node* obj = en.operator[](i);
		obj->connect("death", this, "die");
	}
}

void Player::_process(float delta) {
	move_and_slide(motion);
	input();
	move();
	emit_signal("change_position", this, get_position());
}

void Player::move() {
	motion = Vector2(0, 0);
	if (dir == 1) {
		motion.y -= SPEED;
		rotation = -90.0;
		dir = 1;
	}
	if (dir == 2) {
		motion.y += SPEED;
		rotation = 90.0;
		dir = 2;
	}
	if (dir == 3) {
		motion.x -= SPEED;
		rotation = 180.0;
		dir = 3;
	}
	if (dir == 4) {
		motion.x += SPEED;
		rotation = 0.0;
		dir = 4;
	}
	set_rotation_degrees(rotation);
}

void Player::raycast() {
	auto* rf = cast_to<RayCast2D>(get_node("Forward"));
	auto* rb = cast_to<RayCast2D>(get_node("Backward"));
	auto* rl = cast_to<RayCast2D>(get_node("Left"));
	auto* rr = cast_to<RayCast2D>(get_node("Right"));
	auto* crl = cast_to<RayCast2D>(get_node("checkLeft"));
	auto* crr = cast_to<RayCast2D>(get_node("checkRight"));
	auto* frl = cast_to<RayCast2D>(get_node("frontLeft"));
	auto* frr = cast_to<RayCast2D>(get_node("frontRight"));

	if (rf->is_colliding()) {
		motion = Vector2(0, 0);
		dir = 0;
	}

	if (!nKey.empty()) {
		if (nKey.front() == 1) {
			if (rotation == 0 && !rl->is_colliding() && !crl->is_colliding() && !frl->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 180 && !rr->is_colliding() && !crr->is_colliding() && !frr->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == -90 && !rf->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 90 && !rb->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
		}
		else if (nKey.front() == 2) {
			if (rotation == 0 && !rr->is_colliding() && !crr->is_colliding() && !frr->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 180 && !rl->is_colliding() && !crl->is_colliding() && !frl->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == -90 && !rb->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 90 && !rf->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
		}
		else if (nKey.front() == 3) {
			if (rotation == 0 && !rb->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 180 && !rf->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == -90 && !rl->is_colliding() && !crl->is_colliding() && !frl->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 90 && !rr->is_colliding() && !crr->is_colliding() && !frr->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
		}
		else if (nKey.front() == 4) {
			if (rotation == 0 && !rf->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 180 && !rb->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == -90 && !rr->is_colliding() && !crr->is_colliding() && !frr->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
			else if (rotation == 90 && !rl->is_colliding() && !crl->is_colliding() && !frl->is_colliding()) {
				dir = nKey.front();
				nKey.pop();
			}
		}
	}
}

void Player::input() {
	Input* i = Input::get_singleton();
	if (!nKey.empty() && (i->is_action_just_pressed("ui_up") || i->is_action_just_pressed("ui_down") || i->is_action_just_pressed("ui_left") || i->is_action_just_pressed("ui_right")))
		nKey.pop();
	if (nKey.empty()) {
		if (i->is_action_just_pressed("ui_up"))
			nKey.push(1);
		else if (i->is_action_just_pressed("ui_down"))
			nKey.push(2);
		else if (i->is_action_just_pressed("ui_left"))
			nKey.push(3);
		else if (i->is_action_just_pressed("ui_right"))
			nKey.push(4);
	}
	raycast();
}

void Player::on_body_entered(Node *node, int src) {
	Vector2 pos;
	if (src == 2) {
		pos = Vector2(585, get_position().y);
		set_position(pos);
	}
	else {
		pos = Vector2(15, get_position().y);
		set_position(pos);
	}
}

void Player::die() {
	if (!nKey.empty())
		nKey.pop();
	get_node("/root/PlayerVariables")->set("Health", --lives);
	emit_signal("redraw", this, lives);
}