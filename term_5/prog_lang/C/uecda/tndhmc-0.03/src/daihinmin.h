void search_low_card(int out_cards[8][15],int my_cards[8][15],int use_joker_flag);
void search_low_card_wosp(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int use_joker_flag);
void make_info_table(int info_table[8][15], int info_j_table[8][15], int my_cards[8][15]);
int search_low_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_low_pair_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15]);
int search_max_quantity_pair_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15]);
int search_low_pair_restrict(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int quantity);
int search_high_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_max_quantity_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_quantity_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int num);
int search_low_sequence(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]);
int search_low_sequence_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15]);
int search_low_sequence_restrict(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int quantity);