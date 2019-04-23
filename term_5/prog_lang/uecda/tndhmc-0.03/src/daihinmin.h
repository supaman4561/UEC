void search_low_card(int out_cards[8][15],int my_cards[8][15],int joker_flag);
void make_info_table(int info_table[8][15], int my_cards[8][15]);
int search_low_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_high_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_max_quantity_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_quantity_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
