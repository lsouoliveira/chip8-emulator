#include <instructions/draw_sprite.h>

#include <constants.h>

namespace Chip8
{

DrawSprite::DrawSprite()
{
}

void DrawSprite::Process(CPUState* state)
{	
	unsigned char vx;
	unsigned char vy;
	unsigned char spriteHeight;
	int x;
	int y;

	vx = ((state->opcode) & 0x0F00) >> 8;
	vy = ((state->opcode) & 0x00F0) >> 4;
	spriteHeight = (state->opcode) & 0x000F;

	x = state->v[vx];
	y = state->v[vy];



	for (int i = 0; i < spriteHeight; ++i) {
		unsigned char spriteLine = state->memory[state->i + i];	
		
		for(int j = 0; j < 8; j++) {
			int videoX = (x + j) % 64;
			int videoY = (y + i) % 32;
			int pixelPos = 64 * (videoY) + videoX; 
			unsigned char pixelColor = ((spriteLine >> (7 - j)) & 1);
			unsigned char currPixelColor = state->video->GetBuffer()[pixelPos];
			unsigned char updatedColor = (currPixelColor + pixelColor) % 2;

			if(pixelColor == 1 && updatedColor == 0) {
				state->v[0xF] = 1;
			}

			state->video->GetBuffer()[pixelPos] = updatedColor;	
		}
	}
}

}
