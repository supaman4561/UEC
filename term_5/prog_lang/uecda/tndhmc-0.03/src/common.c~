#include<stdio.h>
#include<string.h>
#include<strings.h>
#include"common.h"

void copy_table(int dst_table[8][15], int src_table[8][15]){ 
  /*
   *  引数で渡されたカードテーブル src_table を
   *  カードテーブル dst_table にコピーする
  */
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<15;j++){
      dst_table[i][j]=src_table[i][j];
    }
  }
} 

void clear_table(int cards[8][15]){ 
  /*
   * 引数で渡されたカードテーブルcardsを全て0にする。
  */
  int i,j;
  
  for(i=0;i<8;i++){
    for(j=0;j<15;j++){
      cards[i][j]=0;
    }   
  }
}

void copy_cards(int dst_cards[8][15],int src_cards[8][15]){ 
  /*
   * 引数で渡されたカードテーブル src_cards のカード情報の部分を
   * カードテーブル dst_cards にコピーする
   */
  int i,j;
  for(i=0;i<5;i++){
    for(j=0;j<15;j++){
      dst_cards[i][j]=src_cards[i][j];
    }
  }
}

void clear_cards(int cards[8][15]){  
  /*
   * 引数で渡されたカードテーブルcardsのカード情報の部分を全て0にし、
   * カードを一枚も無い状態にする。
   */
  int i,j;
  
  for(i=0;i<5;i++){
    for(j=0;j<15;j++){
      cards[i][j]=0;
    }   
  }
}

void diff_cards(int cards1[8][15],int cards2[8][15]){ 
  /*
    cards1からcards2にあるカードを削除する
    */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards2[j][i]==1) cards1[j][i]=0;
}

void or_cards(int cards1[8][15],int cards2[8][15]){
  /*
    cards1にcards2にあるカードを加える
    */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards2[j][i]>0)cards1[j][i]=1; 
}

void and_cards(int cards1[8][15],int cards2[8][15]){ 
  /*
    cards1のカードのうち、cards2にあるものだけをcards1にのこす。
  */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards1[j][i]==1&&cards2[j][i]==1) cards1[j][i]=1;
      else cards1[j][i]=0;
}

void not_cards(int cards[8][15]){ 
  /*
    カードの有無を反転させる
    */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards[j][i]==1) 
        cards[j][i]=0;
      else 
        cards[j][i]=1;
}

void get_field_state_from_field_cards(int cards[8][15], state *field_status){
  /*
    場に出たカードの情報を得る。
    引数は場に出たカードのテーブル
    */
  int i,j,count=0;
  i=j=0;
  
  //カードのある位置を探す
      while(j<15&&cards[i][j]==0){
	field_status->suit[i]=0;
	i++;
	if(i==4){
	  j++;
	  i=0;
	}
      }
  //階段が否か
      if(j<14){
	if(cards[i][j+1]>0) field_status->is_sequence=1;
	else field_status->is_sequence=0;
      }
  //枚数を数える また強さを調べる
      if(field_status->is_sequence==0){
	//枚数組
	    for(;i<5;i++){
	      if(cards[i][j]>0){
		count++;
		field_status->suit[i]=1;
	      }else{
		field_status->suit[i]=0;
	      }
	    }
	if(j==0||j==14){
	  if(field_status->is_rev==0){
	    field_status->order=14;
	  }else{
	    field_status->order=0;
	  }
	}else{
	  field_status->order=j;
	}
      }else{
	//階段
	    while(j+count<15 && cards[i][j+count]>0){
	      count++;
	    }
	if((field_status->is_rev==0)||( field_status->is_rev==1 )){
	  field_status->order=j+count-1;
	}else{
	  field_status->order=j;
	}
	field_status->suit[i]=1;
      }
  //枚数を記憶
      field_status->quantity=count;
 
  if(field_status->quantity > 0){ //枚数が0より大きいとき 新しい場のフラグを0にする
				      field_status->is_no_card=0;
  }
}

void get_field_state_from_own_cards(int cards[8][15], state *field_status){
  /*
    カードテーブルから得られる情報を読み込む
    引数は手札のカードテーブル
    */
  int i;
  //状態
      if(cards[5][4]>0) field_status->is_no_card=1; //場にカードがないとき 1
							else              field_status->is_no_card=0;
  if(cards[5][6]>0) field_status->is_rev=1;   //革命状態の時 1 
						  else              field_status->is_rev=0;
  if(cards[5][7]>0) field_status->is_lock=1;  //しばり時 1
						  else              field_status->is_lock=0;

  if(field_status->is_no_card==1){   //新たな場のとき札の情報をリセット
					 field_status->quantity=0;
  field_status->order=0;
  field_status->is_lock=0;
  for(i=0;i<5;i++)field_status->suit[i]=0;
  }
  
  for(i=0;i<5;i++) field_status->player_quantity[i]=cards[6][i];   //手持ちのカード
								       for(i=0;i<5;i++) field_status->player_rank[i]=cards[6][5+i];//各プレーヤのランク
																       for(i=0;i<5;i++) field_status->seat[i]=cards[6][10+i];      //誰がどのシートに座っているか
																								       //シートiにプレーヤ STATE.SEAT[I]が座っている

																								       if(cards[4][1]==2) field_status->have_joker=1;     //Jokerがある時 1
																															      else               field_status->have_joker=0;

  
}

void remove_low_card(int cards[8][15], int num, int rev){
  /*
   * revが0の時，配列 cards の num 以下の部分を 0 にする
   * revが1の時，配列 cards の num 以下の部分を 0 にする
   * joker については考慮しない
  */
  int i,j;

  if(rev==0){
    for(i=0;i<=num;i++)
      for(j=0;j<=3;j++)
        cards[j][i]=0;
  }else{
    for(i=num;i<15;i++)
      for(j=0;j<=3;j++)
        cards[j][i]=0;
  }
}

void remove_suit(int cards[8][15], int suit[5], int flag){
  int i,j;

  for(i=0;i<=3;i++){
    if((suit[i]+flag)%2){
      for(j=0;j<15;j++)
        cards[i][j]=0;
    }
  }
}

int count_cards(int cards[8][15]){
  int i,j;
  int  quantity=0;

  for(i=0;i<5;i++)
      for(j=0;j<15;j++)
        quantity += (cards[i][j]!=0);

  return quantity;
}




