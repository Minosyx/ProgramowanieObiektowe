#include "Game.h"

using namespace godot;

#define SCR_LEN 8

void Game::_register_methods() {
	register_method("_ready", &Game::_ready);
	register_method("force_draw", &Game::force_draw);
	register_method("on_got_point", &Game::on_got_point);
	register_method("quitGame", &Game::quitGame);
}

void Game::_init() {}

void Game::_ready() {
	int lives = get_node("/root/PlayerVariables")->get("Health");
	int max = get_node("/root/PlayerVariables")->get("MaxHealth");
	for (int i = lives + 1; i <= max && i > 0; i++) {
		String name = "L" + String::num_int64(i);
		get_node(NodePath("Lives/" + name))->queue_free();
	}
	points_to_go = get_tree()->get_nodes_in_group("Point").size();
	Array a = get_tree()->get_nodes_in_group("Point");
	for (int i = 0; i < points_to_go; i++) {
		Node* obj = a.operator[](i);
		obj->connect("got_point", this, "on_got_point");
	}
	get_node("Player")->connect("redraw", this, "force_draw");
	RichTextLabel* text = cast_to<RichTextLabel>(get_node("Score/Value"));
	String svalue = "0";
	svalue = svalue.pad_zeros(SCR_LEN);
	text->set_text(svalue);
}

Game::Game() {
	score = 0;
}
Game::~Game() {}

void Game::force_draw(Node *node, int lives) {
	AudioStreamPlayer2D* audioplayer = cast_to<AudioStreamPlayer2D>(get_node("/root/GDeath"));
	audioplayer->play();	
	if (lives == 0)
		gameEnd(false);
	else {
		get_tree()->reload_current_scene();
	}
}

void Game::on_got_point(Node *node) {
	if (node->is_in_group("BigPoint")) {
		score += 2500;
	}
	else {
		score += 500;
	}
	updateScore(score);
	AudioStreamPlayer2D *audioplayer = cast_to<AudioStreamPlayer2D>(get_node("Player/Munch"));
	audioplayer->play();
	points_to_go--;
	if (points_to_go == 0) {
		gameEnd(true);
	}
}

void Game::updateScore(int score) {
	RichTextLabel *svalue = cast_to<RichTextLabel>(get_node("Score/Value"));
	String value = String::num_int64(score);
	value = value.pad_zeros(SCR_LEN);
	svalue->set_text(value);
}

void Game::gameEnd(bool status) {
	AcceptDialog *dialBox;
	AudioStreamPlayer2D *audioplayer;
	NodePath path;
	get_node("Control/Pause")->set_pause_mode(1);
	if (status) {
		path = "Control/PopUp/Win";
		dialBox = cast_to<AcceptDialog>(get_node(path));
		audioplayer = cast_to<AudioStreamPlayer2D>(get_node(NodePath(String(String(path) + "/GameWin"))));
	}
	else {
		path = "Control/PopUp/Lose";
		dialBox = cast_to<AcceptDialog>(get_node(path));
		audioplayer = cast_to<AudioStreamPlayer2D>(get_node(NodePath(String(String(path) + "/GameOver"))));
	}
	audioplayer->play();
	get_tree()->set_pause(1);
	dialBox->popup_centered();
}

void Game::quitGame() {
	get_tree()->quit();
}
