#include "Renderer.h"

void Renderer::draw(ofImage sprite, Rigidbody* body)
{
	//ofPushMatrix ~= glPushMatrix()
	//I may need to refresh my memory from CS355 to get this down that same way. I could do 3D that way but let's not get carried away just yet...
	ofPushMatrix();
	ofTranslate(body->position.x, body->position.y);
	ofRotateDeg(body->orientation);

	//The 'location' of the image is one of the corners. This offsets it so that the 'location' is the center of the boid image.
	//Height is divided by 1.5 since I want the center of the circle to roughly be the center of the boid
	//I'll probably eventually want to make a sprite class that can take in these properties and make sure it uses the right values for that sprite
	sprite.draw(-sprite.getWidth() / 2, -sprite.getHeight() / 1.5);

	ofPopMatrix();
}
