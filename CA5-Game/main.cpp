#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace sf;
using namespace std;

#define WIN_WIDTH 768
#define WIN_HEIGHT 576
#define VERT_CONST 30        
#define WIDTH_CONST 76          
#define LIFE_OF_TURTIX 3       
#define LIFE_OF_FIRST_ENEMY 2
#define LIFE_OF_SECOND_ENEMY 1
#define INITIAL_DIR_OF_ENEMY LEFT
#define STEP_SIZE 70                  
#define DIAMOND_SCORE 2
#define HEIGHT_OF_ROCKY_PART_IN_GROUND 30
#define NUM_OF_TURTLES 3
#define ELAPSED_TIME 200

enum Direction {LEFT, UP, RIGHT, DOWN};
const int delta_x[4] = {-1, 0, 1, 0};
const int delta_y[4] = {0, -1, 0, 1};

class Turtix {
public:
	Turtix() {
		if (!texture.loadFromFile("sprite/turtix_stand.png"))
			abort();
		sprite.setTexture(texture);
		life = LIFE_OF_TURTIX;
		num_of_removed_turtles = 0;
		score = 0;
		view = true;
	}

	void setPosition(Vector2f pos) {
		x = pos.x;
		y = pos.y;
		sprite.setPosition(x, y);
	}

	void setMapPos(int width, int height) {
		width_of_map = width;
		height_of_map = height;
	}

	void setView(bool mode) {
		view = mode;
	}

	void setScore(int score_) {
		score += score_;
	}

	Vector2f getPosition() {
		return sprite.getPosition();
	}

	Direction getDirection() {
		return direction;
	}

	int getNumOfRemovedTurtles() {
		return num_of_removed_turtles;
	}

	void addRemovedTurtles() {
		if (num_of_removed_turtles < NUM_OF_TURTLES)
			++num_of_removed_turtles;
	}

	void reduceLife() {
		--life;
	}

	void move(Direction dir) {
		if (dir == UP || dir == DOWN) {
			x += delta_x[dir] * STEP_SIZE;
			y += delta_y[dir] * STEP_SIZE;
		}
		else {
			x += delta_x[dir] * STEP_SIZE;
			y += delta_y[dir] * STEP_SIZE;
		}
		checkPosition(x, y);
		sprite.setPosition(x, y);
		direction = dir;

	}

	void movePartially(Direction dir_) {
		sprite.move(delta_x[dir_], delta_y[dir_]);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
	}

	void checkPosition(int& x, int& y) {
		if (x < 0)
			x = 0;
		if (y < 0)
			y = 0;
		if (x + getGlobalBounds().width > width_of_map)
			x = width_of_map - getGlobalBounds().width;
		if (y + getGlobalBounds().height > height_of_map)
			y = height_of_map - getGlobalBounds().height;
	}

	void draw(RenderWindow& window) {
		if (view)
			window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	int x, y;
	int life, num_of_removed_turtles, score;
	int width_of_map, height_of_map;
	bool view;
	Direction direction;
	Texture texture;
	Sprite sprite;
};

class FreeTurtle {
public:
	FreeTurtle() {
		if (!texture.loadFromFile("sprite/turtle_free.png"))
			abort();
		sprite.setTexture(texture);
		direction = LEFT;
	}

	void setPosition(int _x, int _y) {
		x = _x;
		y = _y;
		sprite.setPosition(x, y);
	}

	void setDirection(Direction dir) {
		direction = dir;
	}

	void setWidthOfMap(int width) {
		width_of_map = width;
	}

	Direction getDirection() {
		return direction;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	void move() {
		x += delta_x[direction] * STEP_SIZE / 2;
		y += delta_y[direction] * STEP_SIZE / 2;
		checkPosition(x, y);
		sprite.setPosition(x, y);
	}

	void movePartially(Direction dir_) {
		sprite.move(delta_x[dir_], delta_y[dir_]);
		x = sprite.getPosition().x;
		y = sprite.getPosition().y;
	}

	void checkPosition(int& x, int& y) {
		if (x < 0) {
			x = 0;
			changeDirection();
		}
		if (x + getGlobalBounds().width > width_of_map) {
			x = width_of_map - getGlobalBounds().width;
			changeDirection();
		}
	}

	void changeDirection() {
		switch (direction) {
		case LEFT :
			direction = RIGHT;
			break;
		case RIGHT :
			direction = LEFT;
			break;
		case DOWN :
			direction = LEFT;
		}
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	int x, y;
	int width_of_map;
	Direction direction;
	Texture texture;
	Sprite sprite;
};

class Ground {
public:
	Ground() {
		if (!texture.loadFromFile("sprite/ground.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	bool intersects(Turtix& turtix) {
		return getGlobalBounds().intersects(turtix.getGlobalBounds());
	}

	bool intersectsWithTurtle(FreeTurtle& turtle) {
		return getGlobalBounds().intersects(turtle.getGlobalBounds());
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Soil {
public:
	Soil() {
		if (!texture.loadFromFile("sprite/soil.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	bool intersects(Turtix& turtix) {
		bool result = getGlobalBounds().intersects(turtix.getGlobalBounds());
		while (getGlobalBounds().intersects(turtix.getGlobalBounds())) {
			if (turtix.getDirection() == LEFT)
				turtix.movePartially(RIGHT);
			else if (turtix.getDirection() == RIGHT)
				turtix.movePartially(LEFT);
			else
				return false;
		}
		return result;
	}

	bool intersectsWithTurtle(FreeTurtle& turtle) {
		bool result = getGlobalBounds().intersects(turtle.getGlobalBounds());
		while (getGlobalBounds().intersects(turtle.getGlobalBounds())) {
			if (turtle.getDirection() == LEFT)
				turtle.movePartially(RIGHT);
			else if (turtle.getDirection() == RIGHT)
				turtle.movePartially(LEFT);
			else
				return false;
		}
		if (result)
			turtle.changeDirection();
		return result;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Barrier {
public:
	Barrier() {
		if (!texture.loadFromFile("sprite/barrier_active.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Rope {
public:
	Rope() {
		if (!texture.loadFromFile("sprite/rope.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Ladder {
public:
	Ladder() {
		if (!texture.loadFromFile("sprite/ladder_appendix.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	Vector2f getPosition() {
		return sprite.getPosition();
	}

	bool intersects(Turtix& turtix) {
		if (getGlobalBounds().intersects(turtix.getGlobalBounds())) {
			turtix.setPosition(sprite.getPosition());
			return true;
		}
		return false;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Thorn {
public:
	Thorn() {
		if (!texture.loadFromFile("sprite/thorn.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Block {
public:
	Block() {
		if (!texture.loadFromFile("sprite/block.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Star {
public:
	Star() {
		if (!texture.loadFromFile("sprite/star.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	bool intersects(Turtix& turtix) {
		if (getGlobalBounds().intersects(turtix.getGlobalBounds())) {
			turtix.setScore(DIAMOND_SCORE / 2);
			return true;
		}
		return false;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};
	
class Diamond {
public:
	Diamond() {
		if (!texture.loadFromFile("sprite/diamond.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	bool intersects(Turtix& turtix) {
		if (getGlobalBounds().intersects(turtix.getGlobalBounds())) {
			turtix.setScore(DIAMOND_SCORE);
			return true;
		}
		return false;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class CageTurtle {
public:
	CageTurtle() {
		if (!texture.loadFromFile("sprite/turtle_cage.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	Vector2f getPosition() {
		return sprite.getPosition();
	}

	bool intersects(Turtix& turtix) {
		return getGlobalBounds().intersects(turtix.getGlobalBounds());
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class SecondEnemy {
public:
	SecondEnemy() {
		setDestructible();
		life = LIFE_OF_SECOND_ENEMY;
		direction = INITIAL_DIR_OF_ENEMY;
	}

	void setPosition(int _x, int _y) {
		x = _x;
		y = _y;
		sprite.setPosition(x, y);
	}

	void setDestructible() {
		if (!texture.loadFromFile("sprite/enemy_02_stand.png"))
			abort();
		sprite.setTexture(texture);
		indestructible = false;
	}

	void setIndestructible() {
		if (!texture.loadFromFile("sprite/enemy_02_indestructible.png"))
			abort();
		sprite.setTexture(texture);
		indestructible = true;
	}

	void reduceLife() {
		if (!indestructible)
			--life;
	}

	void move() {
		x += delta_x[direction] * STEP_SIZE;
		if (x < 0) {
			x = -x;
			direction = RIGHT;
		}
		if (x >= WIN_WIDTH) {
			x = 2 * WIN_WIDTH - x;
			direction = LEFT;
		}
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	int x, y;
	int life;
	bool indestructible;
	Direction direction;
	Texture texture;
	Sprite sprite;
};

class FirstEnemy {
public:
	FirstEnemy() {
		if (!texture.loadFromFile("sprite/enemy_01_stand.png"))
			abort();
		sprite.setTexture(texture);
		life = LIFE_OF_FIRST_ENEMY;
		direction = INITIAL_DIR_OF_ENEMY;
	}

	void setPosition(int _x, int _y) {
		x = _x;
		y = _y;
		sprite.setPosition(x, y);
	}

	void reduceLife() {
		--life;
	}

	void move() {
		x += delta_x[direction] * STEP_SIZE;
		if (x < 0) {
			x = -x;
			direction = RIGHT;
		}
		if (x >= WIN_WIDTH) {
			x = 2 * WIN_WIDTH - x;
			direction = LEFT;
		}
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	int x, y;
	int life;
	Direction direction;
	Texture texture;
	Sprite sprite;
};

class Portal {
public:
	Portal() {
		if (!texture.loadFromFile("sprite/portal.png"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(int x, int y) {
		sprite.setPosition(x, y);
	}

	Vector2f getPosition() {
		return sprite.getPosition();
	}

	void intersects(Turtix& turtix) {
		if (getGlobalBounds().intersects(turtix.getGlobalBounds()))
			if (turtix.getNumOfRemovedTurtles() == NUM_OF_TURTLES)
				turtix.setView(false);
	}

	bool intersectsWithTurtle(FreeTurtle& turtle) {
		if (getGlobalBounds().intersects(turtle.getGlobalBounds()))
			return true;
		return false;
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}

	FloatRect getGlobalBounds() {
		return sprite.getGlobalBounds();
	}
private:
	Texture texture;
	Sprite sprite;
};

class Background {
public:
	Background() {
		if (!texture.loadFromFile("sprite/background.jpg"))
			abort();
		sprite.setTexture(texture);
	}

	void setPosition(Vector2f view_center) {
		sprite.setPosition(view_center - Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2));
	}

	void draw(RenderWindow& window) {
		window.draw(sprite);
	}
private:
	Texture texture;
	Sprite sprite;
};

class Map {
public:
	Map() {
		ifstream map_file;
		string line;
		map_file.open("map.txt");
		while (getline(map_file, line))
			map_vec.push_back(line);
		map_file.close();
	}

	vector<string> getVec() {
		return map_vec;
	}
private:
	vector<string> map_vec;
};

class Game {
public:
	Game() : background(), 
			 map(), 
			 turtix(), 
			 portal(),
			 first_enemy(),
			 second_enemy(),
			 cage_turtle(),
			 free_turtle(),
			 diamond(),
			 star(),
			 block(),
			 thorn(),
			 ladder(),
			 rope(),
			 barrier(),
			 ground(),
			 soil() {                              
		vector<string> map_vec = map.getVec();
		int horiz_pos, max_height_in_the_area;
		int vert_pos = VERT_CONST;
		for (int i = 0; i < map_vec.size(); i++)
		{
			horiz_pos = 0;
			int vert_pos_in_the_area = vert_pos;
			max_height_in_the_area = 0;
			int flag = 0;
			for (int j = 0; j < map_vec[i].size(); j++)
			{
				FloatRect bounding_box;
				if (map_vec[i][j] == '.' || map_vec[i][j] == ',')
					if (i + 1 < map_vec.size() && map_vec[i + 1][j] == '.') {
						if (!flag) {
							vert_pos -= VERT_CONST + HEIGHT_OF_ROCKY_PART_IN_GROUND;
							flag = 1;
						}
						map_vec[i + 1][j] = ',';
					}
				bounding_box = to_sprite(map_vec[i][j], horiz_pos, vert_pos_in_the_area);
				horiz_pos += bounding_box.width;
				if (bounding_box.height > max_height_in_the_area)
					max_height_in_the_area = bounding_box.height;
			}
			vert_pos += max_height_in_the_area + VERT_CONST;
		}
		width_of_map = horiz_pos - WIDTH_CONST;
		height_of_map = vert_pos - VERT_CONST;
		turtix.setPosition(portal.getPosition());
		turtix.setMapPos(width_of_map, height_of_map);
	}

	void setBackground(Vector2f view_center) {
		background.setPosition(view_center);
	}

	Vector2f getTurtixPosition() {
		return turtix.getPosition();
	}

	Vector2f checkViewCenter(Vector2f pos) {
		if (pos.x < WIN_WIDTH / 2)
			pos.x = WIN_WIDTH / 2;
		if (pos.y < WIN_HEIGHT / 2)
			pos.y = WIN_HEIGHT / 2;
		if (width_of_map - pos.x < WIN_WIDTH / 2)
			pos.x = width_of_map - WIN_WIDTH / 2;
		if (height_of_map - pos.y < WIN_HEIGHT / 2)
			pos.y = height_of_map - WIN_HEIGHT / 2;
		return pos;
	}

	void moveTurtix(Direction direction) {
		turtix.move(direction);
	}

	void moveFreeTurtles() {
		for (int i = 0; i < free_turtles.size(); i++) {
			free_turtles[i].move();
			if (intersectsTurtleWithPortal(free_turtles[i])){
				free_turtles.erase(free_turtles.begin() + i);
				turtix.addRemovedTurtles();
				continue;
			}
			intersectsTurtleWithSoil(free_turtles[i]);
			if (free_turtles[i].getDirection() == DOWN)
				free_turtles[i].changeDirection();
			if (!intersectsTurtleWithGround(free_turtles[i]))
				free_turtles[i].setDirection(DOWN);
		}
	}

	void intersectsTurtix() {
		portal.intersects(turtix);
		for (int i = 0; i < cage_turtles.size(); i++)
			if (cage_turtles[i].intersects(turtix)) {
				int horiz_pos = cage_turtles[i].getPosition().x;
				int vert_pos = cage_turtles[i].getPosition().y;
				to_sprite('F', horiz_pos, vert_pos);
				cage_turtles.erase(cage_turtles.begin() + i);
				break;
			}
		for (int i = 0; i < diamonds.size(); i++)
			if (diamonds[i].intersects(turtix)) {
				diamonds.erase(diamonds.begin() + i);
				break;
			}
		for (int i = 0; i < stars.size(); i++)
			if (stars[i].intersects(turtix)) {
				stars.erase(stars.begin() + i);
				break;
			}
		for (Soil temp : soils)
			if (temp.intersects(turtix))
				break;
	}

	bool intersectsWithGround() {
		for (Ground temp : grounds)
			if (temp.intersects(turtix))
				return true;
		return false;
	}
	bool intersectsWithLadder() {
		for (Ladder temp : ladders)
			if (temp.intersects(turtix))
				return true;
		return false;
	}
	bool intersectsTurtleWithPortal(FreeTurtle& turtle) {
		if (portal.intersectsWithTurtle(turtle))
			return true;
		return false;
	}
	void intersectsTurtleWithSoil(FreeTurtle& turtle) {
		for (Soil temp : soils)
			if (temp.intersectsWithTurtle(turtle))
				break;
	}
	bool intersectsTurtleWithGround(FreeTurtle& turtle) {
		for (Ground temp : grounds)
			if (temp.intersectsWithTurtle(turtle))
				return true;
		return false;
	}

	void draw(RenderWindow& window) {
		window.clear();
		background.draw(window);
		portal.draw(window);
		for (Ground temp : grounds)
			temp.draw(window);
		for (Soil temp : soils)
			temp.draw(window);
		for (CageTurtle temp : cage_turtles)
			temp.draw(window);
		for (FreeTurtle temp : free_turtles)
			temp.draw(window);
		for (Diamond temp : diamonds)
			temp.draw(window);
		for (Star temp : stars)
			temp.draw(window);
		for (Block temp : blocks)
			temp.draw(window);
		for (Thorn temp : thorns)
			temp.draw(window);
		for (Ladder temp : ladders)
			temp.draw(window);
		for (Rope temp : ropes)
			temp.draw(window);
		for (Barrier temp : barriers)
			temp.draw(window);
		for (FirstEnemy temp : first_enemies)
			temp.draw(window);
		for (SecondEnemy temp : second_enemies)
			temp.draw(window);
		turtix.draw(window);
	}

private:
	FloatRect to_sprite(char elmt, int horiz_pos, int vert_pos) {
		if (elmt == '$') {
			portal.setPosition(horiz_pos, vert_pos);
			return portal.getGlobalBounds();
		}
		else if (elmt == 'E') {
			first_enemy.setPosition(horiz_pos, vert_pos + VERT_CONST);
			first_enemies.push_back(first_enemy);
			return first_enemy.getGlobalBounds();
		}
		else if (elmt == 'M') {
			second_enemy.setPosition(horiz_pos, vert_pos + 2 * VERT_CONST);
			second_enemies.push_back(second_enemy);
			return second_enemy.getGlobalBounds();
		}
		else if (elmt == 'O') {
			cage_turtle.setPosition(horiz_pos, vert_pos + VERT_CONST);
			cage_turtles.push_back(cage_turtle);
			return cage_turtle.getGlobalBounds();
		}
		else if (elmt == 'F') {
			free_turtle.setPosition(horiz_pos, vert_pos);
			free_turtle.setWidthOfMap(width_of_map);
			free_turtles.push_back(free_turtle);
			return free_turtle.getGlobalBounds();
		}
		else if (elmt == '^') {
			diamond.setPosition(horiz_pos, vert_pos);
			diamonds.push_back(diamond);
			return diamond.getGlobalBounds();
		}
		else if (elmt =='*') {
			star.setPosition(horiz_pos, vert_pos);
			stars.push_back(star);
			return star.getGlobalBounds();
		}
		else if (elmt == 'H') {
			block.setPosition(horiz_pos, vert_pos + 2 * VERT_CONST);
			blocks.push_back(block);
			return block.getGlobalBounds();
		}
		else if (elmt == '|') {
			thorn.setPosition(horiz_pos, vert_pos);
			thorns.push_back(thorn);
			return thorn.getGlobalBounds();
		}
		else if (elmt == '#') {
			if (ladders.size() == 0)
				ladder.setPosition(horiz_pos, vert_pos - 2 * VERT_CONST);
			else {
				int height = ladders[ladders.size() - 1].getGlobalBounds().height;
				Vector2f pos = ladders[ladders.size() - 1].getPosition() + Vector2f(0, height);
				ladder.setPosition(pos.x, pos.y);
			}
			ladders.push_back(ladder);
			return ladder.getGlobalBounds();
		}
		else if (elmt == '-') {
			rope.setPosition(horiz_pos, vert_pos);
			ropes.push_back(rope);
			return rope.getGlobalBounds();
		}
		else if (elmt == 'B') {
			barrier.setPosition(horiz_pos, vert_pos + 2 * VERT_CONST);
			barriers.push_back(barrier);
			return barrier.getGlobalBounds();
		}
		else if (elmt == '.') {
			ground.setPosition(horiz_pos, vert_pos);
			grounds.push_back(ground);
			return ground.getGlobalBounds();
		}
		else if (elmt == ',') {
			soil.setPosition(horiz_pos, vert_pos);
			soils.push_back(soil);
			return soil.getGlobalBounds();
		}
		else
			return FloatRect(0.f, 0.f, WIDTH_CONST, 0.f);
	}

	int width_of_map, height_of_map;
	Background background;
	Map map;
	Turtix turtix;
	Portal portal;
	CageTurtle cage_turtle;
	FreeTurtle free_turtle;
	Diamond diamond;
	Star star;
	Block block;
	Thorn thorn;
	Ladder ladder;
	Rope rope;
	Barrier barrier;
	Ground ground;
	Soil soil;
	FirstEnemy first_enemy;
	SecondEnemy second_enemy;
	vector<CageTurtle> cage_turtles;
	vector<FreeTurtle> free_turtles;
	vector<Diamond> diamonds;
	vector<Star> stars;
	vector<Block> blocks;
	vector<Thorn> thorns;
	vector<Ladder> ladders;
	vector<Rope> ropes;
	vector<Barrier> barriers;
	vector<Ground> grounds;
	vector<Soil> soils;
	vector<FirstEnemy> first_enemies;
	vector<SecondEnemy> second_enemies;
};

int main()
{
	RenderWindow window(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Turtix", Style::Close);
	Game game;
	View view;
	view.setSize(Vector2f(WIN_WIDTH, WIN_HEIGHT));
	view.setCenter(game.checkViewCenter(game.getTurtixPosition()));	
	   
	Clock clock, clock_turtle, clock_dir;	
	int flag = 0;
	while (window.isOpen())
	{
		Event event;
		Direction direction;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case Event::Closed :
				window.close();
				break;
			case Event::KeyPressed :
				switch (event.key.code){
				case Keyboard::Left :
					direction = LEFT;
					flag = 1;
					break;
				case Keyboard::Up :
					if (direction == UP)
						break;
					direction = UP;
					clock.restart();
					flag = 1;
					break;
				case Keyboard::Right :
					direction = RIGHT;
					flag = 1;
					break;
				}
				break;
			}

		}
		if (direction == UP)
			if (clock.getElapsedTime() >= milliseconds(ELAPSED_TIME)) {
				direction = DOWN;
				clock_dir.restart();
				flag = 1;
			}
		if (flag) {
			game.moveTurtix(direction);
			game.intersectsTurtix();
			view.setCenter(game.checkViewCenter(game.getTurtixPosition()));
			flag = 0;
		}
		if (clock_turtle.getElapsedTime() >= milliseconds(ELAPSED_TIME)) {
			game.moveFreeTurtles();
			clock_turtle.restart();
		}
		if (direction == RIGHT || direction == LEFT)
			if (!game.intersectsWithGround()) {
				direction = DOWN;
				clock_dir.restart();
				flag = 1;
			}
		window.setView(view);
		game.setBackground(view.getCenter());
		game.draw(window);
		window.display();
	}
}