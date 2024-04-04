#include "GameObject.h"

float GameObject::speed = 5;

void GameObject::updateDestR() {
	destR.x = position.getX();
	destR.y = position.getY();
	destR.h = dimensions.getY();
	destR.w = dimensions.getX();
}

GameObject::GameObject(std::string folder, SDL_Renderer* ren, int x, int y, int w, int h, const SDL_KeyCode& up, const SDL_KeyCode& down, const SDL_KeyCode& left, const SDL_KeyCode& right) {
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

void GameObject::Update() {
	state->update();
	std::cout << *state;
	texture->update();
	std::cout << *collider;
}

void GameObject::MoveX() {
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

void GameObject::MoveY() {
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

void GameObject::handleInput(const SDL_Event& event) {
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

void GameObject::revertPos() {
	collider->getPrevPos();
	collider->update();
}

std::istream& operator>>(std::istream& in, GameObject player) {
	int x, y;
	in >> x;
	player.dimensions.setX(x);
	in >> y;
	player.dimensions.setY(y);
	return in;
}