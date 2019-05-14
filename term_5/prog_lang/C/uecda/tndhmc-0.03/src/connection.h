/*connection*/ 

void check_arg(int argc,char* argv[]);
int  start_game(int table[8][15]);
int  entry_to_game(void);
void send_changing_cards(int cards[8][15]);
int  receive_cards(int cards[8][15]);
int  send_cards(int cards[8][15]);
void look_field(int cards[8][15]);
int  be_game_end(void);
int  close_socket();

