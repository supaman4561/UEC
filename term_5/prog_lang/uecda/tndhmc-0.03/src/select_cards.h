void select_change_cards(int out_cards[8][15],int my_cards[8][15],int num_of_change);
void select_publish_cards(int out_cards[8][15],int my_cards[8][15], state *field_status);
void operate_my_cards(int my_cards[8][15], state *field_status);
void operate_field_cards(int ba_cards[8][15], state *field_status);
void select_submit_cards(int out_cards[8][15],int my_cards[8][15], state *field_status);

void select_cards_free(int select_cards[8][15], int my_cards[8][15], state *field_status);
void select_cards_restrict(int select_cards[8][15], int my_cards[8][15], state *field_status);
void select_cards_free_rev(int select_cards[8][15], int my_cards[8][15], state *field_status);
void select_cards_restrict_rev(int select_cards[8][15], int my_cards[8][15], state *field_status);


