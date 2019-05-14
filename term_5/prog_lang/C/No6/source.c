int search_low_pair(int dst_cards[8][15],int info_table[8][15],int my_cards[8][15])
{
  int i,j;
  
  clear_table(dst_cards);
  for(i=1;i<=13;i++){
    if(info_table[4][i]>=2) {
      break;
    }
  }

  if(i<=13){
    for(j=0;j<=3;j++) {
      dst_cards[j][i]=my_cards[j][i];
    }
    return 1;
  }
  else{
    return 0;
  }
}

int search_high_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15])
{
  int i, j;

  clear_table(dst_cards);
  for (i=13; i>=1; i--) {
    if (info_table[4][i]>=2) {
      break;
    }
  }  

  if (i >= 1) {
    for (j=0; j<=3; j++) {
      dst_cards[j][i]=my_cards[j][i];
    }
    return 1;
  } else {
    return 0;
  }
}

int search_max_quantity_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15])
{
  int max, max_i;
  int i, j;

  max = 1;
  max_i = 0;
  clear_table(dst_cards);
  for (i=1; i<=13; i++) {
    if (info_table[4][i] > max) {
      max = info_table[4][i];
      max_i = i;
    }
  }

  if (max_i != 0) {
    for (j=0; j<=3; j++) {
      dst_cards[j][max_i] = my_cards[j][max_i];
    }
    return 1;
  } else {
    return 0;
  }
}

int search_quantity_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int num)
{
  int i, j;

  clear_table(dst_cards);
  for (i=1; i<=13; i++) {
    if (info_table[4][i] >= num) {
      break;
    }
  }

  if (i <= 13) {
    for (j=0; j<=3; j++) {
      dst_cards[j][i] = my_cards[j][i];
    }
    return 1;
  } else {
    return 0;
  }
}


/**
 * 8*15のint型配列info_tableには現在所持しているカードの情報が格納されている
 *（図を提供したほうがやりやすい）.それを利用して5行目の配列に加算して2以上
 * だったら ペア的なこと書く
 */
