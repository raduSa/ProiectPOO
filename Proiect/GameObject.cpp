#include "GameObject.h"

float GameObject::speed = 5;

void GameObject::updateDestR() {
	destR.x = position.getX();
	destR.y = position.getY();
	destR.h = dimensions.getY();
	destR.w = dimensions.getX();
}

GameObject::GameObject(std::string folder, int x, int y, int w, int h, bool isTurned,
	const SDL_KeyCode& up, const SDL_KeyCode& down, const SDL_KeyCode& left, const SDL_KeyCode& right,
	const SDL_KeyCode& punch, const SDL_KeyCode& kick) {
	collider = new Collider(this);
	state = new StateManager(isTurned);
	texture = new TextureManager(this, folder);
	position = Vector2D(x, y);
	velocity = Vector2D();
	dimensions = Vector2D(w, h);
	SDL_GetRendererOutputSize(Game::getRenderer(), &windowW, &windowH);
	aDown = dDown = punchDown = kickDown = false;
	Up = up; Down = down; Left = left; Right = right; PUNCH = punch; KICK = kick;
}

void GameObject::Update() {
	state->update();
	texture->update();
	//std::cout << *collider;
	//collider->update() - for changes in hitbox based on state
	// check for airborne player
	if (position.getY() < windowH - dimensions.getY())
		state->airborne();
	std::cout << *state;
	std::cout << "HP: " << HP << "\n";
}

void GameObject::MoveX() {
	// save previous pos in case of collision
	collider->setPrevPos();
	// get new velocity and pos
	velocity.clear();
	if (state->CanAct())
		velocity.setX(0 + dDown - aDown);
	if (state->IsHit())
		if (state->IsTurned())
			velocity.setX(0.5);
		else
			velocity.setX(-0.5);
	calculatePos(this);
	// check collisions with screen edges
	if (position.getX() < 0)
		position.setX(0);
	if (position.getX() > windowW - dimensions.getX())
		position.setX(windowW - dimensions.getX());
	// update the collision box
	updateDestR();
	if (state->IsCrouching()) { destR.h /= 2; destR.y += destR.h; }//state : crouch
}

void GameObject::MoveY() {
	//if (state->IsCrouching()) { destR.y -= destR.h; destR.h *= 2; }//uncrouch - idk if this is needed
	collider->setPrevPos();
	// get new velocity and pos, considering jumping
	velocity.clear();
	if (state->IsJumping())//state : jump
		velocity.setY(-2.5);
	else
		velocity.setY(2.5);
	calculatePos(this);
	// check collision with the bottom of the screen
	if (position.getY() > windowH - dimensions.getY())
		position.setY(windowH - dimensions.getY());
	if (state->IsCrouching()) { destR.h /= 2; destR.y += destR.h; }
	// update collision box
	updateDestR();
	if (state->IsCrouching()) { destR.h /= 2; destR.y += destR.h; }
}

void GameObject::handleInput(const SDL_Event& event) {
	if (event.type == SDL_KEYDOWN && state->CanAct()) {
		if (event.key.keysym.sym == Up && !state->IsAirborne())
			state->jump();
		if (event.key.keysym.sym == Down && !state->IsJumping())
			state->crouch();
		if (event.key.keysym.sym == Left)
			aDown = true;
		if (event.key.keysym.sym == Right)
			dDown = true;
		if (event.key.keysym.sym == PUNCH && !state->IsAirborne()) {
			if (!punchDown) {
				state->punch();
				state->flipCanAct();
			}
			punchDown = true;
		}
		if (event.key.keysym.sym == KICK && !state->IsAirborne()) {
			if (!kickDown) {
				state->kick();
				state->flipCanAct();
			}
			kickDown = true;
		}
	}
	if (event.type == SDL_KEYUP) {
		if (event.key.keysym.sym == Down)
			state->noCrouch();
		if (event.key.keysym.sym == Left)
			aDown = false;
		if (event.key.keysym.sym == Right)
			dDown = false;
		if (event.key.keysym.sym == PUNCH)
			punchDown = false;
		if (event.key.keysym.sym == KICK)
			kickDown = false;
	}
}

void GameObject::Render() {
	// if player is attacking, draw the model wider (doesnt affect the hitbox)
	collider->setPrevPos();
	if (state->IsAttacking()) {
		if (state->IsTurned()) {
			destR.x -= 0.4 * destR.w;
			destR.w *= 1.4;
		}
		else 
			destR.w *= 1.4;
		if (state->IsKicking())
			destR.w *= 1.3;
		Attack* temp = nullptr;
		if (state->IsPunching())
			temp = new Punch(this, other); // upcasting
		else if (state->IsKicking())
			temp = new Kick(this, other);
		temp->drawHitbox();
	}
	SDL_RenderCopy(Game::getRenderer(), objectTex, NULL, &destR);
	collider->getPrevPos();
}

void GameObject::revertPos() {
	collider->getPrevPos();
}

void GameObject::drainHP(const int& x) {
	/*if (state->IsBlocking())
		x /= 4;*/
	HP -= x;
}

std::istream& operator>>(std::istream& in, GameObject player) {
	int x, y;
	in >> x;
	player.dimensions.setX(x);
	in >> y;
	player.dimensions.setY(y);
	return in;
}