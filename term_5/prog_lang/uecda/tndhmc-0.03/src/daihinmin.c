#include<stdio.h>
#include<string.h>
#include<strings.h>
#include"common.h"

void search_low_card(int out_cards[8][15],int my_cards[8][15],int use_joker_flag){
  /*
    低い方から探して,最初に見つけたカードを一枚out_cardsにのせる。
    use_joker_flagが1のとき,カードが見つからなければ,jokerを一枚out_cardsにのせる。
  */
  int i,j,find_flag=0;

  clear_table(out_cards);                  //テーブルをクリア
  for(j=1;j<14&&find_flag==0;j++){        //低い方からさがし
    for(i=0;i<4&&find_flag==0;i++){
      if(my_cards[i][j]==1){              //カードを見つけたら               
        find_flag=1;                      //フラグを立て
        out_cards[i][j]=my_cards[i][j];   //out_cardsにのせ,ループを抜ける。
      }
    }
  }
  if(find_flag==0&&use_joker_flag==1){       //見つからなかったとき
    out_cards[0][14]=2;                  //ジョーカーをのせる
  }
}

void search_low_card_wosp(int dst_cards[8][15],int info_table[8][15], int my_cards[8][15],int use_joker_flag){
  int i,j,k,find_flag=0;

  clear_table(dst_cards);

  // シークエンスとして出せる札をmy_cardsから削除
  for (i=0; i<4; i++) {
    for (j=1; j<=13; j++) {
      if (info_table[i][j] >= 3) {
	for (k=0; k<info_table[i][j]; k++) {
	  info_table[i][j+k] = 0;
	}
      }
    }
  }
  
  for(j=1;j<14&&find_flag==0;j++){        
    for(i=0;i<4&&find_flag==0;i++){
      if(my_cards[i][j]==1){
	if(info_table[4][j]==1){   // ペアが存在しない
	  find_flag=1;
	  dst_cards[i][j]=my_cards[i][j];
	}
      }
    }
  }

  // push joker
  if(find_flag==0&&use_joker_flag==1){       
    dst_cards[0][14]=2;                  
  }
}

void make_info_table(int info_table[8][15], int info_j_table[8][15], int my_cards[8][15])
{
  int cnt, i, j, zero_mark;
  clear_table(info_table);
  clear_table(info_j_table);

  // for sequence
  for(i=0;i<4;i++){
    cnt=0;
    for(j=13;j>=1;j--){
      if (info_table[i][j]==0) {
        cnt = 0;
      }
      cnt += my_cards[i][j];
      info_table[i][j] = cnt;
      if (info_table[i][j] == 2) {
        info_table[i][j] = 1;
      }
    }
  }
  
  // for pair 
  for(i=1;i<=13;i++){
    for(j=0;j<4;j++){
      info_table[4][i]+=(my_cards[j][i]>0);
    }
  }

  // make joker table
  if (my_cards[4][1] == 2) {
    // pair
    for (i=1; i<=13; i++) {
      info_j_table[4][i] = info_table[4][i] + 1;
    }

    // sequence
    for (i=0; i<=3; i++) {
      zero_mark = 14;
      for (j=13; j>=1; j--) {
        if (info_table[i][j] == 0) {
          info_j_table[i][j] = info_j_table[i][j+1] - info_j_table[i][zero_mark] + 1;
          zero_mark = j;
        } else {
          info_j_table[i][j] = info_j_table[i][j+1] + 1;
        }
      } 
    }
  }

}

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

int search_low_pair_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15])
{
  int i, j, joker_used;

  joker_used = 0;

  for (i=1; i<=13; i++) {
    if (info_j_table[4][i] >= 2) {
      for (j=0; j<=3; j++) {
        if (my_cards[j][i] == 0 && joker_used == 0) {
          dst_cards[j][i] = 2;
          joker_used = 1;
        }
        else {
          dst_cards[j][i] = my_cards[j][i];
        }
      }
      return 1;
    }
  }

  return 0;
}

int search_max_quantity_pair_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15])
{
  int i, j, joker_used, max, max_i;

  joker_used = 0;
  max = 2;
  max_i = 0;
  for (i=1; i<=13; i++) {
    if (info_j_table[4][i] > max) {
      max_i = i;
      max = info_j_table[4][i];      
    }
  }

  if (max_i == 0) {
    return 0;
  } else {
    for (i=0; i<=3; i++) {
      if (my_cards[i][max_i] == 0 && joker_used == 0) {
        dst_cards[i][max_i] = 2;
        joker_used = 1;
      } else {
        dst_cards[i][max_i] = my_cards[i][max_i];
      }
    }

    return 1;
  }
}

int search_low_pair_restrict(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int quantity)
{
  int i,j;
  clear_table(dst_cards);
  for (i=1; i<=13; i++) {
    if (info_table[4][i]>=quantity) {
      if ((my_cards[0][i]+my_cards[1][i]+my_cards[2][i]+my_cards[3][i])>=quantity) {
	break;
      }
    }
  }

  if (i<=13) {
    for (j=0; j<=3; j++) {
      dst_cards[j][i] = my_cards[j][i];
    }
    return 1;
  } else {
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

int search_low_sequence(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15])
{
  int i,j,k;

  for (i=1; i<=13; i++) {
    for (j=0; j<4; j++) {
      if (info_table[j][i] >= 3) {
	      for (k=0;k<info_table[j][i];k++) {
	        dst_cards[j][i+k] = 1;
	      }
	      return 1;
      }
    }
  }

  return 0;
}

int search_low_sequence_wj(int dst_cards[8][15], int info_j_table[8][15], int my_cards[8][15])
{
  int i,j,k;

  for (i=1; i<=13; i++) {
    for (j=0; j<=3; j++) {
      if (info_j_table[j][i] >= 3) {
        for (k=0; k<info_j_table[j][i]; k++) {
          if (my_cards[j][i+k] == 0) {
            dst_cards[j][i+k] = 2;
          } else {
            dst_cards[j][i+k] = 1;
          }
        }

        return 1;
      }
    }
  }

  return 0;
}

int search_low_sequence_restrict(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15], int quantity)
{
  int i,j,k;

  for (i=1; i<=13; i++) {
    for (j=0; j<4; j++) {
      if (info_table[j][i] >= quantity) {
	if (my_cards[j][i] == 1) {
	  for (k=0;k<info_table[j][i];k++) {
	    dst_cards[j][i+k] = 1;
	  }
	  return 1;
	}
      }
    }
  }

  return 0;
}
