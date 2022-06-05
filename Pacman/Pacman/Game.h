#pragma once
#include <Godot.hpp>
#include <Node2D.hpp>
#include <SceneTree.hpp>
#include <AudioStreamPlayer2D.hpp>
#include <RichTextLabel.hpp>
#include <AcceptDialog.hpp>

namespace godot {
	class Game : public Node2D {
		GODOT_CLASS(Game, Node2D);
		int points_to_go;
		int score;
	public:
		static void _register_methods();
		void _init();

		void _ready();
		Game();
		~Game();

		void on_got_point(Node *);
		void force_draw(Node *, int);
		void updateScore(int);
		void gameEnd(bool);
		void quitGame();
	};
}