typedef struct state_type
{
  int cards[8][15]; // カード
  int order;          // カードの強さ
  int quantity;     // カードの枚数
  int suit[5];      // 場に出ているカードのスート

  int is_sequence;  // 階段か否か
  int is_rev;       // 革命中か否か
  int is_lock;      // 縛り状態か否か
  int is_no_card;   // 場にカードが無い状態か否か

  int player_quantity[5];  // 各プレイヤの持つカード枚s数
  int player_rank[5];      // 各プレイヤの身分
  int seat[5];             // 席順

  int have_joker;          // 自分が joker を持っているか否か
}state;

void copy_table(int dst_table[8][15], int src_table[8][15]);
void clear_table(int cards[8][15]);

void copy_cards(int dest_cards[8][15],int org_cards[8][15]); 
void clear_cards(int cards[8][15]);  

void diff_cards(int cards1[8][15],int cards2[8][15]); 
void or_cards(int cards1[8][15],int cards2[8][15]);
void and_cards(int cards1[8][15],int cards2[8][15]); 
void not_cards(int cards[8][15]); 
void remove_low_card(int cards[8][15], int num, int rev);
void remove_suit(int cards[8][15], int suit[5], int flag);

void get_field_state_from_own_cards(int own_cards[8][15], state *field_status);
void get_field_state_from_field_cards(int ba_cards[8][15], state *field_status);

int count_cards(int cards[8][15]);


