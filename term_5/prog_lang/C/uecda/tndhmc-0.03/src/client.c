#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include "connection.h"
#include "common.h"
#include "select_cards.h"

int main(int argc,char* argv[]){

  int my_playernum;              //プレイヤー番号を記憶する
  int whole_gameend_flag=0;	 //全ゲームが終了したか否かを判別する変数
  int one_gameend_flag=0;	 //1ゲームが終わったか否かを判別する変数
  int accept_flag=0;             //提出したカードが受理されたかを判別する変数
  int game_count=0;		 //ゲームの回数を記憶する
  
  int own_cards_buf[8][15];      //手札のカードテーブルをおさめる変数
  int own_cards[8][15];	         //操作用の手札のテーブル
  int field_cards_buf[8][15];       //場に出たカードテーブルを納める
  int field_cards[8][15];           //操作用の場の札のテーブル
  state field_status;         
  
  int change_quantity;                //カードの交換枚数
  int select_cards[8][15];       //選んだカードを格納
  int is_my_turn=0;                //カードの交換枚数

  clear_table(field_status.cards);

  //引数のチェック 引数に従ってサーバアドレス、接続ポート、クライアント名を変更
  check_arg(argc,argv);

  //ゲームに参加
  my_playernum=entry_to_game();
  
  while(whole_gameend_flag==0){
    one_gameend_flag=0;                 //1ゲームが終わった事を示すフラグを初期化
    
    game_count=start_game(own_cards_buf);//ラウンドを始める 最初のカードを受け取る。
    copy_table(own_cards,own_cards_buf); //もらったテーブルを操作するためのテーブルにコピー
    ///カード交換
    if(own_cards[5][0]== 0){ //カード交換時フラグをチェック ==1で正常
      printf("not card-change turn?\n");
      exit (1);
    }else{ //テーブルに問題が無ければ実際に交換へ
      if(own_cards[5][1] > 0 && own_cards[5][1]<100){
	change_quantity=own_cards[5][1];                              //カードの交換枚数
      	clear_table(select_cards);                //選んだカードを格納
	select_change_cards(select_cards,own_cards,change_quantity);  //自分が富豪、大富豪であれば不要なカードを選び出す
	send_changing_cards(select_cards);                       //選んだカードを送信
      }else{
     	                                                         //自分が平民以下なら、何かする必要はない
      }
    } //カード交換ここまで

    while(one_gameend_flag == 0){     //1ゲームが終わるまでの繰り返し
      is_my_turn=receive_cards(own_cards_buf); //カードをown_cards_bufに受け取り 場を状態の読み出し
      if(is_my_turn){  //自分のターンであるかを確認する 自分のターンであればこのブロックが実行される。
        copy_table(own_cards,own_cards_buf);   //カードテーブルをコピー
	clear_cards(select_cards);             //選んだカードのクリア
        get_field_state_from_own_cards(own_cards,&field_status); //場に出ているカードの情報を読み出す
        select_submit_cards(select_cards,own_cards,&field_status);
	accept_flag=send_cards(select_cards);//cardsを提出
      }
      else{ //自分のターンではない時
        operate_my_cards(own_cards, &field_status);
      }
      
      //そのターンに提出された結果のテーブル受け取り,場に出たカードの情報を解析する
      look_field(field_cards_buf);
      copy_table(field_cards,field_cards_buf);
      copy_table(field_status.cards,field_cards_buf);
      get_field_state_from_field_cards(field_cards,&field_status); //場に出ているカードの情報を読み出す
      operate_field_cards(field_cards,&field_status); //カードが出されたあとの処理

      //一回のゲームが終わったか否かの通知をサーバからうける。
      switch (be_game_end()){
      case 0: //0のときゲームを続ける
	one_gameend_flag=0;
	whole_gameend_flag=0;
	break;
      case 1: //1のとき 1ゲームの終了
	one_gameend_flag=1;
	whole_gameend_flag=0;
	break;
      default: //その他の場合 全ゲームの終了
	one_gameend_flag=1;
	whole_gameend_flag=1;
	break;
      }
    }//1ゲームが終わるまでの繰り返しここまで
  }//全ゲームが終わるまでの繰り返しここまで
  //ソケットを閉じて終了
  if(close_socket()!=0){
    printf("failed to close socket\n");
    exit(1);
  }
  exit(0);
}
