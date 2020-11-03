#include "header.hpp"

class Player{
	public:
		int Timer1,Timer2;
		float dx,dy;
		FloatRect rect;
		bool onGround, mode;
		Sprite sprite;
		float CurrentFrame;

	Player(Texture & image){
		Timer2 = 0;
		Timer1 = 0;
		mode = false;
		sprite.setTexture(image);
		sprite.setTextureRect(IntRect(80,144,16,16));
		rect = FloatRect(52,32,16,16);

		dx=dy=0;
		CurrentFrame = 0;
	}

	void update(float time){
		rect.left += dx * time;
		Collision(0);

		if (!onGround){ dy = dy + 0.0015*time; }
		rect.top += dy * time;
		onGround = false;
		Collision(1);

		CurrentFrame += 0.005*time; 
		if (CurrentFrame > 3){ CurrentFrame -=3; }
		if (dx<0){ sprite.setTextureRect(IntRect(80+31*int(CurrentFrame)+16,144,-16,16)); }
		if (dx>0){ sprite.setTextureRect(IntRect(80+31*int(CurrentFrame),144,16,16)); }
		
		sprite.setPosition(rect.left - offsetX,rect.top - offsetY);
		dx=0;
	}

	void Collision(int dir){
		for (int i=rect.top/16; i<(rect.top+rect.height)/16; i++)
			for (int j=rect.left/16; j<(rect.left+rect.width)/16; j++){
				if (TileMap[i][j] == 'P' || TileMap[i][j] == '0' || TileMap[i][j] == 'k' || TileMap[i][j] == 'r' || TileMap[i][j] == 't'){
					if ((dx>0) && (dir == 0)){ rect.left = j*16 - rect.width; }
					if ((dx<0) && (dir == 0)){ rect.left = j*16 + 16; }
					if ((dy>0) && (dir == 1)){ rect.top = i*16 - rect.height; dy=0; onGround = true; }
					if ((dy<0) && (dir == 1)){ rect.top = i*16 + 16; dy=0; }
				}
				if (TileMap[i][j] == 'c'){
					TileMap[i][j] = ' '; 
					sprite.setScale(2,2);
					sprite.setOrigin(8,8);
					mode = true;
				}
			}
	}
};

class Enemy{
	public:
		float dx,dy;
		FloatRect rect;
		Sprite sprite;
		float CurrentFrame;
		bool life;

	void set(Texture &image, int x, int y){
		sprite.setTexture(image);
		rect = FloatRect(x,y,16,16);

		dx=0.05;
		CurrentFrame = 0;
		life = true;
	}

	void update(float time){
		rect.left += dx * time;
		Collision();

		CurrentFrame += time * 0.005;
		if (CurrentFrame>2){ CurrentFrame -= 2; }

		sprite.setTextureRect(IntRect(18*int (CurrentFrame),0,16,16));
		if (!life){ sprite.setTextureRect(IntRect(58,0,16,16)); }

		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}

	void Collision(){
		for (int i = rect.top/16 ; i<(rect.top+rect.height)/16; i++)
			for (int j = rect.left/16; j<(rect.left+rect.width)/16; j++){
				if ((TileMap[i][j]=='P') || (TileMap[i][j]=='0')){ 
					if (dx>0){ rect.left =  j*16 - rect.width; dx*=-1; }
					else if (dx<0){ rect.left =  j*16 + 16;  dx*=-1; }				
				}
			}
	}
};

int main(){
	RenderWindow window(VideoMode(400,250),"SFML WINDOW");

	float CurrentFrame = 0;
	Clock clock;

	Texture tileset;
	tileset.loadFromFile("Images/Mario_tileset.png");

	Player p(tileset);
	Enemy enemy;
	enemy.set(tileset,48*16,208);

	Texture map;
	map.loadFromFile("Images/Mario_tileset.png");
	Sprite s_map;
	s_map.setTexture(map);

	SoundBuffer buffer;
	buffer.loadFromFile("Audio/Jump.ogg");
	Sound sound(buffer);
	sound.setVolume(10);

	Music music;
	music.openFromFile("Audio/Mario_Theme.ogg");
	music.play();
	music.setVolume(10);

	while (window.isOpen()){
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;

		if (p.mode){
		p.Timer1 += time;
			if (p.Timer1>5000){
			p.sprite.setScale(1,1);
			p.sprite.setOrigin(0,0);
			p.Timer1 = 0;
			p.mode = false;
			}
		}

		Event event;
		
		while (window.pollEvent(event)){
			if (event.type == Event::Closed) window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape)){ window.close(); }

		if (Keyboard::isKeyPressed(Keyboard::Left)){ p.dx = -0.1; }

		if (Keyboard::isKeyPressed(Keyboard::Right)){ p.dx = 0.1; }
		
		if (Keyboard::isKeyPressed(Keyboard::Up)){ 
			if (p.onGround){
				if (!p.mode){ p.dy = -0.5; p.onGround = false; sound.play(); } 
				if (p.mode){ p.dy = -0.7; p.onGround = false; sound.play(); }
			}
		}

		p.update(time);
		enemy.update(time);

		if (p.rect.intersects(enemy.rect)){
			if (enemy.life){
				if (p.dy>0) { enemy.dx=0; p.dy=-0.2; enemy.life = false; }
				else { p.sprite.setColor(Color::Red); }
			}
		}

		if (p.rect.left>200) { offsetX = p.rect.left - 200; }
		window.clear(Color(107,140,255));

		for (int i=0; i<H; i++)
			for (int j=0; j<W; j++){
				if (TileMap[i][j]=='P'){ s_map.setTextureRect( IntRect(143-16*3,112,16,16) ); }

				if (TileMap[i][j]=='k'){ s_map.setTextureRect( IntRect(143,112,16,16) ); }
												
				if (TileMap[i][j]=='c'){ s_map.setTextureRect( IntRect(143-16,112,16,16) ); }

				if (TileMap[i][j]=='t'){ s_map.setTextureRect( IntRect(0,47,32,95-47) ); }

				if (TileMap[i][j]=='g'){ s_map.setTextureRect( IntRect(0,16*9-5,3*16,16*2+5) ); }

				if (TileMap[i][j]=='G'){ s_map.setTextureRect( IntRect(145,222,222-145,255-222) ); }

				if (TileMap[i][j]=='d'){ s_map.setTextureRect( IntRect(0,106,74,127-106) ); }

				if (TileMap[i][j]=='w'){ s_map.setTextureRect( IntRect(99,224,140-99,255-224) ); }

				if (TileMap[i][j]=='r'){ s_map.setTextureRect( IntRect(143-32,112,16,16) ); }

				if (TileMap[i][j]== 'U'){ s_map.setTextureRect( IntRect(96,4,107,105) ); }

				if ((TileMap[i][j]==' ') || (TileMap[i][j]=='0')){ continue; }

				s_map.setPosition(j*16 - offsetX, i*16 - offsetY);
				window.draw(s_map);
			}

		window.draw(p.sprite);
		window.draw(enemy.sprite);
		window.display();
	}
	return 0;
}