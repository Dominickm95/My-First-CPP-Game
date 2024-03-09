#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)


float player_1p, player_1dp, player_2p, player_2dp;
float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2.5, player_half_size_y = 12;
float ball_p_x, ball_p_y, ball_dp_x = 100, ball_dp_y, ball_half_size = 1;

internal void
simulate_game(Input* input, float dt) {
	clear_screen(800080);
	draw_rect(0, 0, arena_half_size_x, arena_half_size_y, 0xffaa33);

	float player_1ddp = 0.f;
	if (is_down(BUTTON_UP)) player_1ddp += 2000;
	if (is_down(BUTTON_DOWN)) player_1ddp -= 2000;

	float player_2ddp = 0.f;
	if (is_down(BUTTON_W)) player_2ddp += 2000;
	if (is_down(BUTTON_S)) player_2ddp -= 2000;
	
	//Player 1 Animation
	player_1ddp -= player_1dp * 10.f;
	
	player_1p = player_1p + player_1dp * dt + player_1ddp * dt * dt * .5f;
	player_1dp = player_1dp + player_1ddp * dt;

	if (player_1p + player_half_size_y > arena_half_size_y) {
		player_1p = arena_half_size_y - player_half_size_y;
		player_1p = 0;
	}
	else if (player_1p - player_half_size_y < -arena_half_size_y) {
		player_1p = -arena_half_size_y + player_half_size_y;
		player_1p = 0;
	}

	//Player 2 Animation 
	player_2ddp -= player_2dp * 10.f;

	player_2p = player_2p + player_2dp * dt + player_2ddp * dt * dt * .5f;
	player_2dp = player_2dp + player_2ddp * dt;

	if (player_2p + player_half_size_y > arena_half_size_y) {
		player_2p = arena_half_size_y - player_half_size_y;
		player_2p = 0;
	}
	else if (player_2p - player_half_size_y < -arena_half_size_y) {
		player_2p = -arena_half_size_y + player_half_size_y;
		player_2p = 0;
	}	

	//Ball Physics 
	ball_p_x += ball_dp_x * dt;
	ball_p_y += ball_dp_y * dt;

	
	if (ball_p_x + ball_half_size > 80 - player_half_size_x &&
		ball_p_x - ball_half_size < 80 + player_half_size_x &&
		ball_p_y + ball_half_size > player_1p - player_half_size_y &&
		ball_p_y + ball_half_size < player_1p + player_half_size_y) {
		ball_p_x = 80 - player_half_size_x - ball_half_size;
		ball_dp_x *= -1;
		ball_dp_y = (ball_dp_y - player_1p)* 2 + player_1dp * .75f; 
	} else if (ball_p_x + ball_half_size > -80 - player_half_size_x &&
		ball_p_x - ball_half_size < -80 + player_half_size_x &&
		ball_p_y + ball_half_size > player_2p - player_half_size_y &&
		ball_p_y + ball_half_size < player_2p + player_half_size_y) {
		ball_p_x = -80 + player_half_size_x + ball_half_size;
		ball_dp_x *= -1;
		ball_dp_y = (ball_dp_y - player_2p) * 2 + player_2dp * .75f;
	}

	if (ball_p_y + ball_half_size > arena_half_size_y) {
		ball_p_y = arena_half_size_y - ball_half_size;
		ball_dp_y *= -1;
	}
	else if (ball_p_y - ball_half_size < -arena_half_size_y) {
		ball_p_y = -arena_half_size_y + ball_half_size;
		ball_dp_y *= -1;
	}
	
	//Player and ball render 
	draw_rect(ball_p_x, ball_p_y, ball_half_size, ball_half_size, 0xffffff);

	draw_rect(80, player_1p, player_half_size_x, player_half_size_y, 0x880999);
	draw_rect(-80, player_2p, player_half_size_x, player_half_size_y, 0x880999);
}
