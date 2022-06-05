#include "Enemy.h"

#define RED_SPEED 200
#define ORANGE_SPEED 250
#define PINK_SPEED 300

using namespace godot;

void Enemy::_register_methods() {
	register_method("_process", &Enemy::_process);
	register_method("_ready", &Enemy::_ready);
	register_method("dir_change", &Enemy::dir_change);
	register_method("on_change_behaviour", &Enemy::on_change_behaviour);
	register_signal<Enemy>("death", "node", GODOT_VARIANT_TYPE_OBJECT);
}

void Enemy::set_default() {
	if (get_name() == "Red") {
		SPEED = RED_SPEED;
		motion.y -= SPEED;
	}
	else if (get_name() == "Orange") {
		SPEED = ORANGE_SPEED;
		motion.y -= SPEED;
	}
	else {
		SPEED = PINK_SPEED;
		motion.y -= SPEED;
	}
}

void Enemy::_init() {
	motion = Vector2(0, 0);
	set_default();
}

void Enemy::_ready() {
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	player = get_node("../../Player")->get_instance_id();
	Node* obj;
	Array bp = get_tree()->get_nodes_in_group("BigPoint");
	for (int i = 0; i < bp.size(); i++) {
		obj = bp.operator[](i);
		obj->connect("change_behaviour", this, "on_change_behaviour");
	}
}

Enemy::Enemy() {
	direction = 0;
	timer = 0.0;
	was_changed = false;
}
Enemy::~Enemy() {}

void Enemy::_process(float delta) {
	timer += delta;
	Ref<KinematicCollision2D> col = move_and_collide(delta * motion);
	if(!col.is_null())
		checkCollider(col->get_collider_id());
	if (was_changed && timer > 5) {
		set_default();
		was_changed = false;
	}
}

void Enemy::dir_change(Node *body) {
	prevM = motion;
	motion = Vector2(0, 0);
	String enemy_name = get_name();
	int breaker = 0;
	std::uniform_int_distribution<int> distribution(0, 3);
	while (enemy_name == body->get_name() && !breaker) {
		int i = distribution(generator);
		switch (i)
		{
		case 0:
			if (direction != 1) {
				motion.y -= SPEED;
				direction = 0;
				breaker = 1;
			}
			break;
		case 1:		
			if (direction != 0) {
				motion.y += SPEED;
				direction = 1;
				breaker = 1;
			}
			break;
		case 2:
			if (direction != 3) {
				motion.x -= SPEED;
				direction = 2;
				breaker = 1;
				apply_scale(Vector2(-1, 1));
			}
			break;
		case 3:
			if (direction != 2) {
				motion.x += SPEED;
				direction = 3;
				breaker = 1;
				apply_scale(Vector2(-1, 1));
			}
			break;
		default:
			break;
		}
	}
	if (enemy_name != body->get_name()) {
		motion = prevM;
	}
}

void Enemy::checkCollider(int col) {
	if (col == player) {
		emit_signal("death", this);
	}
	dir_change(this);
}

void Enemy::on_change_behaviour() {
	if (get_name() == "Pink") {
		SPEED = 100;
		timer = 0;
		was_changed = true;
	}
	else if (get_name() == "Orange") {
		SPEED = 50;
		timer = 0;
		was_changed = true;
	}
	else if (get_name() == "Red"){
		SPEED = 0;
		timer = 0;
		was_changed = true;
	}
}