#include <instructions/draw_sprite.h>

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

	state->v[0xF] = 0;

	for (int i = 0; i < spriteHeight; ++i) {
		unsigned char spriteLine = state->memory[state->i + i];	

		for(int j = 0; j < 8; j++) {
			int videoX = (x + j) % 64;
			int videoY = (y + i) % 32;
			int pixelPos = 64 * (videoY) + videoX; 
			unsigned char pixelColor = (spriteLine & 1);
			spriteLine = spriteLine >> 1;

			if(pixelColor == 1 && state->video->GetBuffer()[pixelPos] == pixelColor) {
				state->v[0xF] = 1;
			}
			
			state->video->GetBuffer()[pixelPos] = pixelColor;
		}
	}

	/*
	for (int i = 0; i < 32; ++i) {
		for (int j = 0; j < 64; ++j) {
			std::cout << (int)state->video->GetBuffer()[64 * i + j];
		}	
		std::cout << std::endl;
	}
	*/;
}

}
