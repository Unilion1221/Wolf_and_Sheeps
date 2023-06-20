#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

using namespace std;
//using namespace sf;

//Class Board
class Board {
private:
	sf::RectangleShape tilesArr[5][5];
	sf::RectangleShape tile;
	float posX;
	float posY;
public:



	void createBoard() {
		this->initTiles();
		this->posX = 125.f;
		this->posY = 125.f;

		//Insert into array tiles
		for (int i = 0; i < 5; i++) {
			cout << "Y is: " << this->posY << endl;
			for (int j = 0; j < 5; j++)
			{
				cout << posX << endl;
				if (this->posX > 765) {
					posX = 125.f;
				}

				this->setTilePos(posX, posY);
				tilesArr[i][j] = this->tile;
				this->posX += 160.f; 
			}
			this->posY += 160.f;
		}
	}


	Board() {
		this->createBoard();
	}

	//Functions

	void initTiles()
	{
		//size of the tile
		this->tile.setSize(sf::Vector2f(100.f, 100.f));

		//tile color
		this->tile.setFillColor(sf::Color(205, 127, 50, 255));
		this->tile.setOutlineColor(sf::Color(205, 127, 50, 255));
		this->tile.setOutlineThickness(1.f);
	}


	//test setting tile position
	void setTilePos(float posRow, float posCol) {
		this->tile.setPosition(posRow, posCol);
	}

	//test get tile
	
	sf::RectangleShape getTile() {
		return this->tile;
	}

	//test function to print board

	void printBoard(sf::RenderWindow* win) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++)
			{
				win->draw(this->tilesArr[i][j]);
			}
		}
	}

};



class Pawn {
private:

	//need getter for wolf pawn positions from board class
	//set position fucntion and print functuon
	//create wolf and sheep subclass
	sf::CircleShape pawn;
	Board board;
public:
	

	void initPawn() 
	{
		this->pawn.setRadius(50);
		this->pawn.setOutlineColor(sf::Color(0, 0, 0, 255));
		this->pawn.setOutlineThickness(-3);
		this->pawn.setPosition(125, 125.f);
	}

	Pawn() {
		this->initPawn();
	}




	//Test render func
	void printPawn(sf::RenderWindow* win) {
		
		win->draw(this->pawn);

	}

};




//////////////

//Game Class
class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event eve;

	//Objects of the game
	Board board;
	Pawn pawn;

	//Functions

	void initializeVars() {
		this->window = nullptr;

	}

	void initializeWindow() {
		this->window = new sf::RenderWindow(sf::VideoMode(1000, 1000), "Game Window", sf::Style::Titlebar | sf::Style::Close);
	}

public:

	//test func
	Board getBoard() {
		return board;
	}

	//Constructor and Destructor
	Game() {
		this->initializeVars();
		this->initializeWindow();
	}

	~Game() {
		delete this->window;
	}

	//check if game is running
	bool gameRunState() {
		return this->window->isOpen();
	}

	//Initializing

	//Rendering Game
	void gameRender() {
		this->window->clear();
		
		this->board.printBoard(this->window);

		this->pawn.printPawn(this->window);

		this->window->display();
	}

	//Updating Game
	void gameUpdate() {
		this->getKeboardInp();

	}

	//To close window with input
	void getKeboardInp() {
		while (this->window->pollEvent(this->eve))
		{
			switch (this->eve.type)
			{
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				//if esc is pressed we close the window
				if (this->eve.key.code == sf::Keyboard::Escape) {
					this->window->close();
					break;
				}
			}
		}
	}

};

///////////

int main(){

	Game game;

	while (game.gameRunState())
	{
		//Updating the game
		game.gameUpdate();

		//Rendering the game
		game.gameRender();

	}

}