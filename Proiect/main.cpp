#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <fstream>

class Vector2D {
	float x;
	float y;
public:
	Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float a, float b) : x(a), y(b) {}
	Vector2D(const Vector2D& vec) { setX(vec.x); setY(vec.y); }
	~Vector2D() {}
	Vector2D& Add(const Vector2D& vec) {
		x += vec.x; y += vec.y;
		return *this;
	}
	Vector2D& Subtract(const Vector2D& vec) {
		x -= vec.x; y -= vec.y;
		return *this;
	}
	Vector2D& Multiply(const Vector2D& vec) {
		x *= vec.x; y *= vec.y;
		return *this;
	}
	Vector2D& Divide(const Vector2D& vec) {
		x /= vec.x; y /= vec.y;
		return *this;
	}
	Vector2D& operator+=(const Vector2D& vec) { return this->Add(vec); }
	Vector2D& operator-=(const Vector2D& vec) { return this->Subtract(vec); }
	Vector2D& operator*=(const Vector2D& vec) { return this->Multiply(vec); }
	Vector2D& operator/=(const Vector2D& vec) { return this->Divide(vec); }
	Vector2D& operator*(const int& i) { x *= i; y *= i; return *this; }
	Vector2D& operator=(Vector2D* vec) { x = vec->x; y = vec->y; return *this; }
	friend Vector2D operator+(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator-(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator*(Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator/(Vector2D& v1, const Vector2D& v2);

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& vec);
	int getX() const { return int(x); }
	int getY() const { return int(y); }
	void setX(float z) { x = z; }
	void setY(float z) { y = z; }
	void clear() { x = 0; y = 0; }
};

Vector2D operator+(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x + v2.x, v1.y + v2.y); }
Vector2D operator-(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x - v2.x, v1.y - v2.y); }
Vector2D operator*(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x * v2.x, v1.y * v2.y); }
Vector2D operator/(Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x / v2.x, v1.y / v2.y); }
std::ostream& operator<<(std::ostream& out, const Vector2D& vec) { out << "(" << vec.x << "," << vec.y << ")"; return out; }

class GameObject;

class Collider {
	SDL_Rect collider;
	SDL_Rect* destR;
	SDL_Rect prevState;
	Vector2D* position;
	Vector2D prevPos;
public:
	Collider(GameObject* player);
	~Collider() { delete position; delete destR; }
	void update() {
		collider = *destR;
	}
	static bool collision(const SDL_Rect& recA, const SDL_Rect& recB) {
		if (recA.x + recA.w > recB.x &&
			recB.x + recB.w > recA.x &&
			recA.y + recA.h > recB.y &&
			recB.y + recB.h > recA.y)
			return true;
		return false;
	}
	SDL_Rect getRect() const { return collider; }
	void setPrevPos() {
		prevState.x = destR->x;
		prevState.y = destR->y;
		prevState.w = destR->w;
		prevState.h = destR->h;
		prevPos = position;
	}
	void getPrevPos() const { *destR = prevState; *position = Vector2D(prevPos.getX(), prevPos.getY()); }
	//SDL_Rect getPrevState() const { return prevState; }
	friend std::ostream& operator<<(std::ostream& out, const Collider& col);
};
std::ostream& operator<<(std::ostream& out, const Collider& col) {
	out << col.collider.x << " ";
	out << col.collider.y << " ";
	out << col.collider.w << " ";
	out << col.collider.h << "\n";
	return out;
}

class StateManager {
	int isJumping;
	bool isCrouching;
	//int isHit;
	//int isAttacking;
public:
	StateManager() : isJumping(0), isCrouching(false) {}
	~StateManager() {}
	void update() {
		if (isJumping)
			isJumping--;
	}
	void jump() { isJumping = 20; }
	void crouch() { isCrouching = true; }
	void noCrouch() { isCrouching = false; }
	bool IsJumping() const { return bool(isJumping); }
	bool IsCrouching() const { return isCrouching; }
	friend std::ostream& operator<< (std::ostream & out, const StateManager & state);
};
std::ostream& operator<< (std::ostream& out, const StateManager& state) {
	out << state.isJumping << " ";
	out << state.isCrouching << "\n";
	return out;
}

class TextureManager {
	SDL_Texture* idle;
	SDL_Texture* crouch;
	SDL_Texture** objectTex;
	StateManager* state;
public:
	TextureManager(GameObject* player, SDL_Renderer* renderer, std::string folder);
	~TextureManager() { SDL_DestroyTexture(idle); SDL_DestroyTexture(crouch); }
	static SDL_Texture* LoadTexture(std::string fileName, SDL_Renderer* renderer) {
		SDL_Surface* tempSurface = IMG_Load(fileName.c_str());
		SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, tempSurface);
		SDL_FreeSurface(tempSurface);
		return tex;
	}
	void update() {
		if (state->IsCrouching()) {
			*objectTex = crouch;
		}
		else
			*objectTex = idle;
	}
};

class GameObject {
	Vector2D position;
	Vector2D velocity;
	Vector2D dimensions;// width/height
	static float speed;
	bool aDown, dDown;
	SDL_KeyCode Up, Down, Left, Right;
	TextureManager* texture;
	Collider* collider;
	StateManager* state;
	SDL_Texture* objectTex;
	SDL_Rect destR;
	SDL_Renderer* renderer;
	int windowW, windowH;
	/*void updateDestPos() {
		destR.x = position.getX();
		destR.y = position.getY();
	}*/
	void updateDestR() {
		destR.x = position.getX();
		destR.y = position.getY();
		destR.h = dimensions.getY();
		destR.w = dimensions.getX();
	}
	static void calculatePos(GameObject* player) { player->position += player->velocity * speed; }
public:
	GameObject(std::string folder, SDL_Renderer* ren, int x, int y, int w, int h, const SDL_KeyCode& up, const SDL_KeyCode& down, const SDL_KeyCode& left, const SDL_KeyCode& right) {
		renderer = ren;
		collider = new Collider(this);
		state = new StateManager();
		texture = new TextureManager(this, ren, folder);
		position = Vector2D(x, y);
		velocity = Vector2D();
		dimensions = Vector2D(w, h);
		SDL_GetRendererOutputSize(renderer, &windowW, &windowH);
		aDown = dDown = false;
		Up = up; Down = down; Left = left; Right = right;
	}
	~GameObject() { delete texture; delete state; delete collider; }
	void Update() {
		state->update();
		std::cout << *state;
		texture->update();
		std::cout << *collider;
	}
	void MoveX() {
		collider->setPrevPos();
		velocity.clear();
		velocity.setX(0 + dDown - aDown);
		calculatePos(this);
		if (position.getX() < 0)
			position.setX(0);
		if (position.getX() > windowW - dimensions.getX())
			position.setX(windowW - dimensions.getX());
		updateDestR();
		if (state->IsCrouching()) { destR.h /= 2; destR.y += destR.h; }//state : crouch
		collider->update();
	}
	void MoveY() {
		if (state->IsCrouching()) { destR.y -= destR.h; destR.h *= 2; }//state : crouch
		collider->setPrevPos();
		velocity.clear();
		if (state->IsJumping())//state : jump
			velocity.setY(-2.5);
		else
			velocity.setY(2.5);
		calculatePos(this);
		if (position.getY() > windowH - dimensions.getY())
			position.setY(windowH - dimensions.getY());
		if (state->IsCrouching()) { destR.h /= 2; destR.y += destR.h; }
		updateDestR();
		if (state->IsCrouching()) { destR.h /= 2; destR.y += destR.h; }//state : crouch
		collider->update();
	}
	void handleInput(const SDL_Event& event) {
		if (event.type == SDL_KEYDOWN) {
			if (event.key.keysym.sym == Up && position.getY() == windowH - dimensions.getY())
				state->jump();
			if (event.key.keysym.sym == Down && !state->IsJumping())
				state->crouch();
			if (event.key.keysym.sym == Left)
				aDown = true;
			if (event.key.keysym.sym == Right)
				dDown = true;
		}
		if (event.type == SDL_KEYUP) {
			if (event.key.keysym.sym == Down)
				state->noCrouch();
			if (event.key.keysym.sym == Left)
				aDown = false;
			if (event.key.keysym.sym == Right)
				dDown = false;
		}
	}
	void Render() {
		SDL_RenderCopy(renderer, objectTex, NULL, &destR);
	}
	void revertPos() {
		collider->getPrevPos();
		collider->update();
	}
	Vector2D getPos() const { return position; }
	Vector2D* getPosPointer()  { return &position; }
	SDL_Rect* getDestRPointer() { return &destR; }
	Collider* getCollider() const { return collider; }
	SDL_Texture** getTexturePointer() { return &objectTex; }
	StateManager* getState() const { return state; }
	friend std::istream& operator>>(std::istream& in, GameObject player);
};
std::istream& operator>>(std::istream& in, GameObject player) {
	int x, y;
	in >> x;
	player.dimensions.setX(x);
	in >> y;
	player.dimensions.setY(y);
	return in;
}

float GameObject::speed = 5;

inline Collider::Collider(GameObject* player) : destR(player->getDestRPointer()), position(player->getPosPointer()) {
	setPrevPos();
}

inline TextureManager::TextureManager(GameObject* player, SDL_Renderer* renderer, std::string folder) :
	objectTex(player->getTexturePointer()), state(player->getState()) {
	idle = TextureManager::LoadTexture("assets/" + folder + "/idle.png", renderer);
	crouch = TextureManager::LoadTexture("assets/" + folder + "/crouch.png", renderer);
}

class Game {
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* backgroundTex;
	GameObject* player;
	GameObject* enemy;
	int width, height;

public:
	Game() { width = 0; height = 0; }
	void init(const char* title, int xpos, int ypos, bool fullscreen) {
		int flags = 0;
		std::cout << width << " " << height;
		if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }

		if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
			window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
			renderer = SDL_CreateRenderer(window, -1, 0);
			backgroundTex = TextureManager::LoadTexture("assets/background.png", renderer);
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			isRunning = true;
		}
		else { isRunning = false; }
		player = new GameObject("player", renderer, 0, height - 256, 200, 450, SDLK_w, SDLK_s, SDLK_a, SDLK_d);
		enemy = new GameObject("enemy", renderer, width - 128, height - 256, 200, 450, SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT);

	}
	void handleEvents() {
		SDL_Event event;
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			isRunning = false;
			return;
		}
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			isRunning = false;
			return;
		}
		player->handleInput(event);
		enemy->handleInput(event);
	}
	void update() {
		player->Update();
		player->MoveX();
		if (Collider::collision(player->getCollider()->getRect(), enemy->getCollider()->getRect()))
			player->revertPos();
		player->MoveY();
		if (Collider::collision(player->getCollider()->getRect(), enemy->getCollider()->getRect()))
			player->revertPos();
		enemy->Update();
		enemy->MoveX();
		if (Collider::collision(enemy->getCollider()->getRect(), player->getCollider()->getRect()))
			enemy->revertPos();
		enemy->MoveY();
		if (Collider::collision(enemy->getCollider()->getRect(), player->getCollider()->getRect()))
			enemy->revertPos();
	}
	void render() {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, backgroundTex, NULL, NULL);
		player->Render();
		enemy->Render();
		SDL_RenderPresent(renderer);
	}
	void clean() {
		SDL_DestroyWindow(window);
		SDL_DestroyTexture(backgroundTex);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		std::cout << "Game cleaned\n";
	}
	bool running() { return isRunning; }
	friend std::istream& operator>>(std::istream& in, Game* game);
};
std::istream& operator>>(std::istream& in, Game* game) {
	in >> game->width;
	in >> game->height;
	return in;
}

int main(int argc, char* argv[]) {

	std::ifstream input("input.txt");
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	Game* game = new Game();
	input >> game;
	game->init("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);

	while (game->running()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		// Delay if too many frames
		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}
	game->clean();
	return 0;
}