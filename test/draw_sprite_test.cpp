#include <gtest/gtest.h>
#include <cpu_state.h>
#include <instructions/draw_sprite.h>
#include <video.h>
#include <constants.h>

class DrawSpriteTest : public ::testing::Test {
protected:
	Chip8::CPUState* cpu_state_;	
	Chip::Video* video_;
	Chip8::DrawSprite* instruction_;
	int* sprite_height_;
	int *sprite_data_address_;

	DrawSpriteTest() 
	{
		instruction_ = new Chip8::DrawSprite();
	}

	~DrawSpriteTest() 
	{
		delete instruction_;
	}

    void SetUp() override
    {
		cpu_state_ = new Chip8::CPUState();
		video_ = new Chip8::Video();
		
		video_->ClearBuffer();
		cpu_state_->v[0xF] = 0;

		sprite_height_ = new int(4);
		unsigned char* spriteData = new unsigned char[sprite_height_] {
			{
				0b00111100,
				0b00100100,
				0b00100100,
				0b00111100,
			}
		};

		sprite_data_address_ = 0x200;

		for (int i = 0; i < sprite_height_; ++i) {
			cpu_state_->memory[sprite_data_address_ + i];	
		}

		delete[] spriteData;		
    }

    void TearDown() override
    {
		delete cpu_state_;
		delete video_;
		delete sprite_height_;
    }

};

TEST_F(DrawSpriteTest, ShouldDrawSpriteAtCorrectCoords) {
	int spriteX = 60;
	int spriteY = 28;
	unsigned short opcode = 0xd014;	

	cpu_state_->i = sprite_data_address_;
	cpu_state_->v[0] = spriteX;
	cpu_state_->v[1] = spriteY;

	instruction_->Process(cpu_state_);

	for (int i = 0; i < sprite_height_; ++i) {
		unsigned char spriteLine = 0;

		for (int j = 0; j < 8; j++) {
			int y = (spriteY + i) % 32;
			int x = (spriteX + j) % 64;
			unsigned char pixel = cpu_state_->video->GetBuffer()[y * 64 + x];

			spriteLine = (spriteLine << 1) + pixel;
		}

		EXPECT_EQ(spriteLine, cpu_state_->memory[sprite_data_address_ + i * sprite_height_]);
	}
}


TEST_F(DrawSpriteTest, ShouldDrawSpriteWrappedAcrossScreen) {
	int spriteX = 10;
	int spriteY = 10;
	unsigned short opcode = 0xd014;	

	cpu_state_->i = sprite_data_address_;
	cpu_state_->v[0] = spriteX;
	cpu_state_->v[1] = spriteY;

	instruction_->Process(cpu_state_);

	for (int i = 0; i < sprite_height_; ++i) {
		unsigned char spriteLine = 0;

		for (int j = 0; j < 8; j++) {
			int y = (spriteY + i) % 32;
			int x = (spriteX + j) % 64;
			unsigned char pixel = cpu_state_->video->GetBuffer()[y * 64 + x];

			spriteLine = (spriteLine << 1) + pixel;
		}

		EXPECT_EQ(spriteLine, cpu_state_->memory[sprite_data_address_ + i * sprite_height_]);
	}
}

TEST_F(DrawSpriteTest, ShouldRegisterCollision) {
	int spriteX = 10;
	int spriteY = 10;
	unsigned short opcode = 0xd014;	

	cpu_state_->i = sprite_data_address_;
	cpu_state_->v[0] = spriteX;
	cpu_state_->v[1] = spriteY;

	instruction_->Process(cpu_state_);

	EXPECT_EQ(cpu_state_->v[0xF], 0);

	instruction_->Process(cpu_state_);

	EXPECT_EQ(cpu_state_->v[0xF], 1);
}
