/*daifugo*/ 
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>

#include "daihinmin.h"

extern const int g_logging;

void getState(int cards[8][15]){
  /*
    �J�[�h�e�[�u�����瓾�������ǂݍ���
    �����͎�D�̃J�[�h�e�[�u��
    ���͍L��ϐ�state�Ɋi�[�����
  */
  int i;
  //���
  if(cards[5][4]>0) state.onset=1; //��ɃJ�[�h���Ȃ��Ƃ� 1
  else              state.onset=0;
  if(cards[5][6]>0) state.rev=1;   //�v����Ԃ̎� 1 
  else              state.rev=0;
  if(cards[5][5]>0) state.b11=1;   //11�o�b�N�� 1 ���g�p
  else              state.b11=0;
  if(cards[5][7]>0) state.lock=1;  //���΂莞 1
  else              state.lock=0;

  if(state.onset==1){   //�V���ȏ�̂Ƃ��D�̏������Z�b�g
    state.qty=0;
    state.ord=0;
    state.lock=0;
    for(i=0;i<5;i++)state.suit[i]=0;
  }
  
  for(i=0;i<5;i++) state.player_qty[i]=cards[6][i];   //�莝���̃J�[�h
  for(i=0;i<5;i++) state.player_rank[i]=cards[6][5+i];//�e�v���[���̃����N
  for(i=0;i<5;i++) state.seat[i]=cards[6][10+i];      //�N���ǂ̃V�[�g�ɍ����Ă��邩
                                                      //�V�[�gi�Ƀv���[�� STATE.SEAT[I]�������Ă���

  if(cards[4][1]==2) state.joker=1;     //Joker�����鎞 1
  else               state.joker=0;

  
}

void getField(int cards[8][15]){
  /*
    ��ɏo���J�[�h�̏��𓾂�B
    �����͏�ɏo���J�[�h�̃e�[�u��
    ���͍L��ϐ�state�Ɋi�[�����
  */
  int i,j,count=0;
  int found_joker = 0;
  i=j=0;
  
  //�J�[�h�̂���ʒu��T��
  while(j<15&&cards[i][j]==0){
    state.suit[i]=0;
    i++;
    if(i==4){
      j++;
      i=0;
    }
  }

  //�������J�[�h���W���[�J�[�Ȃ�΁Afound_joker=1�B
  if (cards[i][j] == 2){
    found_joker = 1;
  }

  //�K�i���ۂ�
  if(j<14){
    if(cards[i][j+1]>0) state.sequence=1;
    else state.sequence=0;
  }
  //�����𐔂��� �܂������𒲂ׂ�
  if(state.sequence==0){
    //�����g
    for(;i<5;i++){
      if(cards[i][j]>0){
	count++;
	state.suit[i]=1;
      }else{
	state.suit[i]=0;
      }
    }
    
    //�W���[�J�[�P�R����ɏo�Ă���Ȃ�΁Astate.ord���ő�̋������������̂ɐݒ�
    //�m�[�}���J�[�h�̏ꍇ�́A���̋��������̂܂�state.ord�֊i�[
    if ((found_joker == 1) && (count == 1)){
      if (state.rev == 0){
	state.ord = 14;
      }else{
	state.ord = 0;
      }
    }else{
      state.ord=j;
    }
 
  }else{
    //�K�i
    while(j+count<15 && cards[i][j+count]>0){
      count++;
    }
    if((state.rev==0 && state.b11==0 )||( state.rev==1 && state.b11==1 )){
      state.ord=j+count-1;
    }else{
      state.ord=j;
    }
    state.suit[i]=1;
  }
  //�������L��
  state.qty=count;
 
  if(state.qty>0){ //������0���傫���Ƃ� �V������̃t���O��0�ɂ���
    state.onset=0;
  }
}


void showState(struct state_type *state){
  /*�����œn���ꂽ���state�̓��e��\������*/
  int i;
  printf("state rev   : %d\n",state->rev);
  printf("state lock  : %d\n",state->lock);
  printf("state joker : %d\n",state->joker);
  
  printf("state qty   : %d\n",state->qty);
  printf("state ord   : %d\n",state->ord);
  printf("state seq   : %d\n",state->sequence);
  printf("state onset : %d\n",state->onset);
  printf("state suit :");
  for(i=0;i<4;i++)printf("%d ",state->suit[i]);
  printf("\n"); printf("state player qty :");
  for(i=0;i<5;i++)printf("%d ",state->player_qty[i]);
  printf("\n"); printf("state player rank :");
  for(i=0;i<5;i++)printf("%d ",state->player_rank[i]);
  printf("\n"); printf("state player_num on seat :");
  for(i=0;i<5;i++)printf("%d ",state->seat[i]);
  printf("\n");
}

//���ꂼ��J�[�h�̘a ���� ���� �t�] ���Ƃ�
void cardsOr(int cards1[8][15],int cards2[8][15]){
  /*
    cards1��cards2�ɂ���J�[�h��������
  */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards2[j][i]>0)cards1[j][i]=1; 
}

void cardsAnd(int cards1[8][15],int cards2[8][15]){ 
  /*
    cards1�̃J�[�h�̂����Acards2�ɂ�����̂�����cards1�ɂ̂����B
  */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards1[j][i]==1&&cards2[j][i]==1) cards1[j][i]=1;
      else cards1[j][i]=0;
}

void cardsDiff(int cards1[8][15],int cards2[8][15]){ 
  /*
    cards1����cards2�ɂ���J�[�h���폜����
  */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards2[j][i]==1) cards1[j][i]=0;
}
void cardsNot(int cards[8][15]){ 
  /*
    �J�[�h�̗L���𔽓]������
  */
  int i,j;
  
  for(i=0;i<15;i++)
    for(j=0;j<5;j++)
      if(cards[j][i]==1) cards[j][i]=0;
      else cards[j][i]=1;
}


void outputTable(int table[8][15]){ 
  /*
    �����œn���ꂽ�J�[�h�e�[�u�����o�͂���
  */
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<15;j++){
      printf("%i ",table[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void copyTable(int dest_table[8][15], int org_table[8][15]){ 
  /*
    �����œn���ꂽ�J�[�h�e�[�u��org_table��
    �J�[�h�e�[�u��dest_table�ɃR�s�[����
  */
  int i,j;
  for(i=0;i<8;i++){
    for(j=0;j<15;j++){
      dest_table[i][j]=org_table[i][j];
    }
  }
} 

void copyCards(int dest_cards[8][15],int org_cards[8][15]){ 
  /*
    �����œn���ꂽ�J�[�h�e�[�u��org_cards�̃J�[�h���̕�����
    �J�[�h�e�[�u��dest_cards�ɃR�s�[����
  */
  int i,j;
  for(i=0;i<5;i++){
    for(j=0;j<15;j++){
      dest_cards[i][j]=org_cards[i][j];
    }
  }
}


void clearCards(int cards[8][15]){  
  /*
    �����œn���ꂽ�J�[�h�e�[�u��cards�̃J�[�h���̕�����S��0�ɂ��A�J�[�h���ꖇ��������Ԃɂ���B
  */
  int s,t;
  
  for(s=0;s<5;s++){
    for(t=0;t<15;t++){
      cards[s][t]=0;
    }   
  }
}

void clearTable(int cards[8][15]){ 
  /*
    �����œn���ꂽ�J�[�h�e�[�u��cards��S��0�ɂ���B
  */
  int s,t;
  
  for(s=0;s<8;s++){
    for(t=0;t<15;t++){
      cards[s][t]=0;
    }   
  }
}

int beEmptyCards(int cards[8][15]){  
  /*
    �����œn���ꂽ�J�[�h�e�[�u��cards�̊܂ރJ�[�h�̖�����0�̂Ƃ�1���A
    ����ȊO�̂Ƃ�0��Ԃ�
  */
  int i,j,f=1;
  
  for(i=0;i<5;i++){
    for(j=0;j<15;j++){
      if(cards[i][j]>0)f=0;
    }
  }
  return f;
}

int qtyOfCards(int cards[8][15]){  
  /*
    �����œn���ꂽ�J�[�h�e�[�u��cards�̊܂ރJ�[�h�̖�����Ԃ�
  */
  int i,j,count=0;
  
  for(i=0;i<5;i++)
    for(j=0;j<15;j++)
      if(cards[i][j]>0)count++;
  
  return count;
}



void makeJKaidanTable(int tgt_cards[][15], int my_cards[][15]){
  /*
    �n���ꂽ�J�[�h�e�[�u��my_cards����A�W���[�J�[���l�����K�i�ŏo���邩�ǂ�������͂��A
    ���ʂ��e�[�u��tgt_cards�Ɋi�[����B
  */
  int i,j;
  int count,noJcount;    //�W���[�J�[���g�p�����ꍇ�̃J�[�h�̖���,�g�p���Ȃ�����
  
  clearTable(tgt_cards);         //�e�[�u���̃N���A
  if(state.joker==1){            //joker������Ƃ�
    for(i=0;i<4;i++){            //�e�X�[�g���ɑ�����
      count=1;
      noJcount=0; 
      for(j=13;j>=0;j--){        //���Ԃɂ݂�
	if(my_cards[i][j]==1){   //�J�[�h������Ƃ�
	  count++;               //2�̃J�E���^��i�߂�
	  noJcount++;
	}
	else{                    //�J�[�h���Ȃ��Ƃ�
	  count=noJcount+1;      //�W���[�J�[����̊K�i�̖����ɃW���[�J�[���𑫂� 
	  noJcount=0;            //�W���[�J�[�Ȃ��̊K�i�̖��������Z�b�g����
	}
	
	if(count>2){              //3���ȏ�̂Ƃ�
	  tgt_cards[i][j]=count;  //���̖������e�[�u���Ɋi�[
	}
	else{
	  tgt_cards[i][j]=0;      //���̑���0�ɂ���
	}
      }
    }
  }

  if(g_logging==1){
    printf("make Joker kaidan \n");
    outputTable(tgt_cards);
  }
}

void makeKaidanTable(int tgt_cards[][15], int my_cards[][15]){
  /*
    �n���ꂽ�J�[�h�e�[�u��my_cards����A�K�i�ŏo���邩�ǂ�������͂��A
    ���ʂ��e�[�u��tgt_cards�Ɋi�[����B
  */
  int i,j;
  int count;
  
  clearTable(tgt_cards);
  for(i=0;i<4;i++){             //�e�X�[�g���ɑ�����
    for(j=13,count=0;j>0;j--){  //���Ԃɂ݂�
      if(my_cards[i][j]==1){    //�J�[�h������Ƃ�
	count++;                //�J�E���^��i��
      }
      else{
	count=0;                //�J�[�h���Ȃ��Ƃ����Z�b�g����
      }
      
      if(count>2){              //3���ȏ�̂Ƃ����̖������e�[�u���Ɋi�[
	tgt_cards[i][j]=count;   
      }
      else{
	tgt_cards[i][j]=0;     //���̑���0�ɂ���
      }
    }
  }
  if(g_logging==1){
    printf("make kaidan \n");
    outputTable(tgt_cards);
  }
}

void makeGroupTable(int tgt_cards[][15], int my_cards[][15]){
  /*
    �n���ꂽ�J�[�h�e�[�u��my_cards����A2���ȏ�̖����g�ŏo���邩�ǂ�������͂��A
    ���ʂ��e�[�u��tgt_cards�Ɋi�[����B
  */
  int i,j;
  int count;
  
  
  clearTable(tgt_cards);
  for(i=0;i<15;i++){  //���ꂻ��̋����̃J�[�h�̖����𐔂�
    count=my_cards[0][i]+my_cards[1][i]+my_cards[2][i]+my_cards[3][i];
    if(count>1){      //������2���ȏ�̂Ƃ�
      for(j=0;j<4;j++){
	if(my_cards[j][i]==1){    //�J�[�h�������Ă��镔����
	  tgt_cards[j][i]=count; //���̖������i�[
	}
      }
    }
  }
  if(g_logging==1){
    printf("make group \n");
    outputTable(tgt_cards);
  }
}

void makeJGroupTable(int tgt_cards[][15], int my_cards[][15]){
  /*
    �n���ꂽ�J�[�h�e�[�u��my_cards����A
    �W���[�J�[���l����2���ȏ�̖����g�ŏo���邩�ǂ�������͂��A
    ���ʂ��e�[�u��tgt_cards�Ɋi�[����B
  */
  int i,j;
  int count;
 
  clearTable(tgt_cards);
  if(state.joker!=0){ 
    for(i=0;i<14;i++){ //���ꂻ��̋����̃J�[�h�̖����𐔂� �W���[�J�[�̕���������
      count=my_cards[0][i]+my_cards[1][i]+my_cards[2][i]+my_cards[3][i]+1;
      if(count>1){     //������2���ȏ�̂Ƃ�
	for(j=0;j<4;j++){
	  if(my_cards[j][i]==1){   //�J�[�h�������Ă��镔����
	    tgt_cards[j][i]=count; //���̖������i�[
	  }
	}
      }
    }
  }
  if(g_logging==1){
    printf("make Joker group \n");
    outputTable(tgt_cards);
  }
}


void lowCards(int out_cards[8][15],int my_cards[8][15],int threshold){
  /*
    �n���ꂽ�J�[�h�e�[�u��my_cards�̃J�[�h������
    threshold�ȏ�̕�����0�ł���,threshold���Ⴂ�������̂����A
    �J�[�h�e�[�u��out_cards�Ɋi�[����B
  */
  int i;
  copyTable(out_cards,my_cards); //my_cards���R�s�[����
  for(i=threshold;i<15;i++){    //threshold����15�܂�
    out_cards[0][i]=0;          //0�ł��߂�
    out_cards[1][i]=0;
    out_cards[2][i]=0;
    out_cards[3][i]=0;
  }
}


void highCards(int out_cards[8][15],int my_cards[8][15],int threshold){
  /*
    �n���ꂽ�J�[�h�e�[�u��my_cards�̃J�[�h������
    threshold�ȉ��̕�����0�ł���,threshold��荂���������̂���
    �J�[�h�e�[�u��out_cards�Ɋi�[����
  */
  int i;
  copyTable(out_cards,my_cards); //my_cards���R�s�[����
  for(i=0;i<=threshold;i++){    //0����threshold�܂�
    out_cards[0][i]=0;          //0�ł��߂�
    out_cards[1][i]=0;
    out_cards[2][i]=0;
    out_cards[3][i]=0;
  } 
}
int nCards(int n_cards[8][15],int target[8][15],int n){
  /*
    n���̃y�A���邢�͊K�i�݂̂�n_cards �ɂ̂����B���̂Ƃ��e�[�u���ɂ̂鐔����n�̂݁B
    �J�[�h�������Ƃ���0,����Ƃ���1���������B
  */
  int i,j,flag=0;         
  clearTable(n_cards);          //�e�[�u�����N���A
  for(i=0;i<4;i++)           
    for(j=0;j<15;j++)           //�e�[�u���S�̂𑖍���
      if(target[i][j]==(int)n){ //n�ƂȂ���̂��݂����Ƃ�
      	n_cards[i][j]=n;
	flag=1;                 //�t���O������
      }else{                    //n�ȊO�̏ꏊ��
	n_cards[i][j]=0;        //0�Ŗ��߂�B
      }
  return flag;
}

void lockCards(int target_cards[8][15],int suit[5]){
  /*
    ���ϐ�state.suit�̂P�������Ă���X�[�g�̂݃J�[�h�e�[�u��target_cards�Ɏc���B
  */
  int i,j;
  for(i=0;i<4;i++)
    for(j=0;j<15;j++)
      target_cards[i][j]*=suit[i]; //suit[i]==1 �̂Ƃ��͂��̂܂�,==0�̂Ƃ�0�ł���B
}

void lowGroup(int out_cards[8][15],int my_cards[8][15],int group[8][15]) {
  /*
    �n���ꂽ�����g�ŏo����J�[�h�̏����̂���group�ƃJ�[�h�e�[�u��my_cards����
    �ł��Ⴂ�����g��T���A��������J�[�h�e�[�u��out_cards�ɂ��̃J�[�h���ڂ���B
  */
  int i, j;					//�J�E���^
  int count = 0,qty=0;				//�J�[�h�̖���,����
  
  clearTable(out_cards);
  for(j=1; j<14; j++) {	                        //�����N���Ⴂ���ɒT������ 
    for(i=0; i<4; i++) {
      if(group[i][j] >1 ) {	        	//group�e�[�u����2�ȏ�̐����𔭌�������
	out_cards[i][j] = 1;			//out_cards�Ƀt���O�𗧂Ă�
	count++;
	qty=group[i][j];
      }
    }
    if(count >0) break;			//���[�v�E�o�p�t���O�������Ă�����
  }
  
  for(i=0; count<qty; i++) {
    if(my_cards[i][j] == 0 && (state.lock==0||state.suit[i]==1)){	
      out_cards[i][j] = 2;		//�W���[�J�[�p�t���O�𗧂Ă� 
      count++;
    }
  }
}

void highGroup(int out_cards[8][15],int my_cards[8][15],int group[8][15]) {
  /*
    �n���ꂽ�����g�ŏo����J�[�h�̏����̂���group�ƃJ�[�h�e�[�u��my_cards����
    �ł����������g��T���A��������J�[�h�e�[�u��out_cards�ɂ��̃J�[�h���ڂ���B
  */
  int i, j;					//�J�E���^
  int count = 0,qty=0;				//�J�[�h�̖���,����
  
  clearTable(out_cards);
  for(j=13; j>0; j--) {	                        //�����N���Ⴂ���ɒT������ 
    for(i=0; i<4; i++) {
      if(group[i][j] > 1) {	        	//group�e�[�u����2�ȏ�̐����𔭌�������
	out_cards[i][j] = 1;			//out_cards�Ƀt���O�𗧂Ă�
	count++;
	qty=group[i][j];
      }
    }
    if(count >0) break;			//���[�v�E�o�p�t���O�������Ă�����
  }
  
  for(i=0; count<qty; i++) {
    if(my_cards[i][j] == 0 && (state.lock==0||state.suit[i]==1)){
      out_cards[i][j] = 2;		//�W���[�J�[�p�t���O�𗧂Ă� 
      count++;
    }
  }
}


void lowSequence(int out_cards[8][15],int my_cards[8][15],int sequence[8][15]){
  /*
    �n���ꂽ�K�i�ŏo����J�[�h�̏����̂���group�ƃJ�[�h�e�[�u��my_cards����
    �ł��Ⴂ�K�i��T���A��������J�[�h�e�[�u��out_cards�ɂ��̃J�[�h���ڂ���B
  */
  int i,j,lowvalue,lowline=0,lowcolumn=0;
  
  lowvalue = 0;
  
  clearTable(out_cards);
  i = 0;
  
  //lowsequence�̔���
  while((i < 15) && (lowvalue == 0)){ //�K�i�e�[�u�����ɊK�i��������܂ŌJ��Ԃ�
    j = 0;
    while(j < 4){
      if(sequence[j][i] != 0){      //�Ⴂ�������璲��,�K�i�e�[�u����0�ȊO�������番��
	if(sequence[j][i] > lowvalue){ //�����������N�_�Ƃ��č����K�i�̒��ōŒ����ۂ�
	  lowvalue = sequence[j][i];   //�Œ���������l�Əꏊ��ۑ�
	  lowline = j;
	  lowcolumn = i;
	}
      }
      j++;
    }
    if(lowvalue == 0){
      i++;
    }
  }
  
  //out_cards�ւ̏��o��
  if(lowvalue != 0){              //�K�i��������Ȃ�������out_cards�ɂ͏��o���Ȃ�
    for(i = lowcolumn; i < (lowcolumn+lowvalue); i++){
      if(my_cards[lowline][i] == 1){
	out_cards[lowline][i] = 1;   //���ʂ̎�D�Ƃ��Ď����Ă�����1�𗧂Ă�
      }
      else{
	out_cards[lowline][i] = 2;        //�����Ă��Ȃ�������W���[�J�[�Ȃ̂�2�𗧂Ă�
      }
    }
  }
}

void highSequence (int out_cards[8][15],int my_cards[8][15],int sequence[8][15]){
  /*
    �n���ꂽ�K�i�ŏo����J�[�h�̏����̂���group�ƃJ�[�h�e�[�u��my_cards����
    �ł������K�i��T���A��������J�[�h�e�[�u��out_cards�ɂ��̃J�[�h���ڂ���B
  */
  int i,j,k,highvalue,highline=0,highcolumn=0,prevalue;
  highvalue = 0;

  clearTable(out_cards);
  i = 14;
  
  //highsequence�̔���
  while((i > 0) && (highvalue == 0)){  //�K�i�e�[�u�����ɊK�i��������܂ŌJ��Ԃ�
    j = 0;
    while(j < 4){
      k = -1;
      if((sequence[j][i] != 0) && (my_cards[j][i] != 0)){//�����������璲��,�K�i�e�[�u����0�ȊO�������番��
	do{                       //�������K�i�̍ō��l����,�Œ��̊K�i��T��
	  if(sequence[j][i-k] >= highvalue){ //�����ō��l�����K�i�̒��ōŒ����ۂ�
	    highvalue = sequence[j][i-k];  //�Œ���������L�^
	    highline = j;
	    highcolumn = i-k;
	  }
	  prevalue = sequence[j][i-k];
	  k++;
	}while((i-k >= 0) && (prevalue <= sequence[j][i-k]));
	
      }	
      j++;	
    }
    if(highvalue == 0){
      i--;
    }
  }

  //out_cards�ւ̏��o��
  for(i = highcolumn; i < (highcolumn+highvalue); i++){
    if(my_cards[highline][i] == 1){
      out_cards[highline][i] = 1; //���ʂ̎�D�Ƃ��Ď����Ă�����1�𗧂Ă�
    }
    else{
      out_cards[highline][i] = 2;     //�����Ă��Ȃ�������W���[�J�[�Ȃ̂�2�𗧂Ă�
    }
  } 
}

//my_cards(��D)����y�A,�K�i���̖��̃J�[�h�������������̂�out_card�Ɋi�[���� 
void removeGroup(int out_cards[8][15],int my_cards[8][15],int group[8][15]){
  /*
    �n���ꂽ�����g�ŏo����J�[�h�̏����̂���group�ƃJ�[�h�e�[�u��my_cards����
    �����g�ȊO�̃J�[�h��T���A�J�[�h�e�[�u��out_cards�ɂ��̃J�[�h���ڂ���B
  */
  int i,j;
  
  for (i = 0; i < 15; i++){
    for(j = 0; j < 4; j++){
      if((my_cards[j][i] == 1) && (group[j][i] == 0)){
	out_cards[j][i] = 1;         //mycards�ɑ��݂�,�����e�[�u���ɂȂ��ꍇ1
      }
      else{
	out_cards[j][i] = 0;             //����ȊO(mycards�ɂȂ���,���e�[�u���ɂ���)�̏ꍇ0
      }
    }
  }
}

void removeSequence(int out_cards[8][15],int my_cards[8][15],int sequence[8][15]){
  /*
    �n���ꂽ�K�i�ŏo����J�[�h�̏����̂���group�ƃJ�[�h�e�[�u��my_cards����
    �K�i�ȊO�̃J�[�h��T���A�J�[�h�e�[�u��out_cards�ɂ��̃J�[�h���ڂ���B
  */
  int i,j,k;
  
  for(j = 0; j < 4; j++){
    for (i = 0; i < 15; i++){
      if((my_cards[j][i] == 1) && (sequence[j][i] == 0)){
	out_cards[j][i] = 1;           //mycards�ɑ��݂�,�����e�[�u���ɂȂ��ꍇ1
      }else if(sequence[j][i] > 2){
      	for(k=0;k < sequence[j][i];k++){
      	  out_cards[j][i+k] = 0;
      	}
      	i += k-1;
      } 
      else {
	out_cards[j][i] = 0;      //����ȊO(mycards�ɂȂ���,���e�[�u���ɂ���)�̏ꍇ0
      }
    }
  }
}


void lowSolo(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    �Ⴂ������T����,�ŏ��Ɍ������J�[�h���ꖇout_cards�ɂ̂���B
    joker_flag��1�̂Ƃ�,�J�[�h��������Ȃ����,joker���ꖇout_cards�ɂ̂���B
  */
  int i,j,find_flag=0;

  clearTable(out_cards);                  //�e�[�u�����N���A
  for(j=1;j<14&&find_flag==0;j++){        //�Ⴂ�����炳����
    for(i=0;i<4&&find_flag==0;i++){
      if(my_cards[i][j]==1){              //�J�[�h����������               
	find_flag=1;                      //�t���O�𗧂�
	out_cards[i][j]=my_cards[i][j];   //out_cards�ɂ̂�,���[�v�𔲂���B
      }
    }
  }
  if(find_flag==0&&joker_flag==1){       //������Ȃ������Ƃ�
    out_cards[0][14]=2;                  //�W���[�J�[���̂���
  }
}

void highSolo(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    ����������T����,�ŏ��Ɍ������J�[�h���ꖇout_cards�ɂ̂���B
    joker_flag������Ƃ�,�J�[�h��������Ȃ����,joker���ꖇout_cards�ɂ̂���B
  */
  int i,j,find_flag=0;
  
  clearTable(out_cards);                 //�e�[�u�����N���A
  for(j=13;j>0&&find_flag==0;j--){       //���������炳����
    for(i=0;i<4&&find_flag==0;i++){
      if(my_cards[i][j]==1){              //�J�[�h����������
	find_flag=1;                      //�t���O�𗧂�
	out_cards[i][j]=my_cards[i][j];   //out_cards�ɂ̂�,���[�v�𔲂���B
      }
    }
  }
  if(find_flag==0&&joker_flag==1){       //������Ȃ������Ƃ�
    out_cards[0][0]=2;                   //�W���[�J�[���̂���
  }
}

void change(int out_cards[8][15],int my_cards[8][15],int num_of_change){
  /*
    �J�[�h�������̃A���S���Y��
    ��x�����邢�͕x�����A��n�����邢�͕n���ɃJ�[�h��n�����̃J�[�h��
    �J�[�h�e�[�u��my_cards�ƌ�������num_of_change�ɉ����āA
    �Ⴂ�ق�����I�уJ�[�h�e�[�u��out_cards�ɂ̂���
  */
  int count=0;
  int one_card[8][15];
  
  clearTable(out_cards);
  while(count<num_of_change){
    lowSolo(one_card,my_cards,0);
    cardsDiff(my_cards,one_card);
    cardsOr(out_cards,one_card);
    count++;
  }
}

void lead(int out_cards[8][15],int my_cards[8][15]){
  /*
    �V�����J�[�h���o����Ƃ��̑I�����[�`��
    �J�[�h�e�[�u��my_cards����K�i=>�y�A=>�ꖇ�̏��Ŗ����̑����ق����瑖����,
    �Ⴂ�J�[�h����݂āA�͂��߂Č��������̂� out_cards�ɂ̂���B
  */
  int group[8][15];           //�����g�𒲂ׂ邽�߂̃e�[�u��
  int sequence[8][15];        //�K�i�𒲂ׂ邽�߂̃e�[�u��
  int temp[8][15];            //�ꎞ�g�p�p�̃e�[�u��
  int i,find_flag=0;          //��D�������������ۂ��̃t���O

  clearTable(group);
  clearTable(sequence);
  clearTable(temp);
  if(state.joker==1){                      //�W���[�J�[������Ƃ�,�W���[�J�[���l����,
    makeJGroupTable(group,my_cards);       //�K�i�Ɩ����g�����邩�𒲂�,
    makeJKaidanTable(sequence,my_cards);   //�e�[�u���Ɋi�[����
  }else{
    makeGroupTable(group,my_cards);        //�W���[�J�[���Ȃ��Ƃ��̊K�i�Ɩ����g��
    makeKaidanTable(sequence,my_cards);    //�󋵂��e�[�u���Ɋi�[����
  }

  for(i=15;i>=3&&find_flag==0;i--){         //�����̑傫��������,������܂�
    find_flag=nCards(temp,sequence,i);      //�K�i�����邩�������,
    
    if(find_flag==1){                       //���������Ƃ�
      lowSequence(out_cards,my_cards,temp); //���̂Ȃ��ōł��Ⴂ���̂�out_cards
    }                                       //�ɂ̂���         
  }
  for(i=5;i>=2&&find_flag==0;i--){          //�����̑傫��������,������܂�
    find_flag=nCards(temp,group,i);         //�����g�����邩�𒲂�,
    if(find_flag==1){                       //���������Ƃ�
      lowGroup(out_cards,my_cards,temp);    //���̂Ȃ��ōł��Ⴂ���̂�out_cards
    }                                       //�̂���
  }
  if(find_flag==0){                          //�܂�������Ȃ��Ƃ�
    lowSolo(out_cards,my_cards,state.joker); //�ł��Ⴂ�J�[�h��out_cards�ɂ̂���B
  }
}

void leadRev(int out_cards[8][15],int my_cards[8][15]){
  /*
    �v�����p�̐V�����J�[�h���o����Ƃ��̑I�����[�`��
    �J�[�h�e�[�u��my_cards����K�i=>�y�A=>�ꖇ�̏��Ŗ����̑����ق����瑖����,
    �����J�[�h����݂āA�͂��߂Č��������̂� out_cards�ɂ̂���B
  */
  int group[8][15];           //�����g�𒲂ׂ邽�߂̃e�[�u��
  int sequence[8][15];        //�K�i�𒲂ׂ邽�߂̃e�[�u��
  int temp[8][15];            //�ꎞ�g�p�p�̃e�[�u��
  int i,find_flag=0;          //��D�������������ۂ��̃t���O
  //clearTable(group);
  //clearTable(sequence);
  //clearTable(temp);
  if(state.joker==1){                        //�W���[�J�[������Ƃ�,�W���[�J�[���l����,
    makeJGroupTable(group,my_cards);         //�K�i�Ɩ����g�����邩�𒲂�,
    makeJKaidanTable(sequence,my_cards);     //�e�[�u���Ɋi�[����
  }else{
    makeGroupTable(group,my_cards);          //�W���[�J�[���Ȃ��Ƃ��̊K�i�Ɩ����g��
    makeKaidanTable(sequence,my_cards);      //�󋵂��e�[�u���Ɋi�[����
  }		
  for(i=15;i>=3&&find_flag==0;i--){          //�����̑傫��������,������܂�
    
    find_flag=nCards(temp,sequence,i);       //�K�i�����邩�������,
    
    if(find_flag==1){                        //���������Ƃ�
      highSequence(out_cards,my_cards,temp); //���̂Ȃ��ōł��������̂�out_cards
    }                                        //�ɂ̂���
  }
  for(i=5;i>=2&&find_flag==0;i--){           //�����̑傫��������,������܂�
    find_flag=nCards(temp,group,i);          //�����g�����邩�𒲂�,
    if(find_flag==1){                        //���������Ƃ�
      highGroup(out_cards,my_cards,temp);    //���̂Ȃ��ōł��������̂�out_cards
    }                                        //�ɂ̂���       
  }
  if(find_flag==0){                          //�܂�������Ȃ��Ƃ�
    highSolo(out_cards,my_cards,state.joker);//�ł������J�[�h��out_cards�ɂ̂���
  }
}
 
void followSolo(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    ���̃v���[���[�ɑ����ăJ�[�h���ꖇ�ŏo���Ƃ��̃��[�`��
    joker_flag��1�̎��W���[�J�[���g�����Ƃ���
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  int group[8][15];       //�����g�𒲂ׂ邽�߂̃e�[�u��
  int sequence[8][15];    //�K�i�𒲂ׂ邽�߂̃e�[�u��
  int temp[8][15];        //�ꎞ�g�p�p�̃e�[�u��
  
  makeGroupTable(group,my_cards);           //�����g�������o��
  makeKaidanTable(sequence,my_cards);       //�K�i�������o��
  
  removeSequence(temp,my_cards,sequence);   // �K�i������
  removeGroup(out_cards,temp,group);        // �����g������
  
  highCards(temp,out_cards,state.ord);      // ��̃J�[�h���ア�J�[�h������

  if(state.lock==1){               
    lockCards(temp,state.suit);             //���b�N����Ă���Ƃ��o���Ȃ��J�[�h������
  }
  lowSolo(out_cards,temp,state.joker);      //�c�����J�[�h����ア�J�[�h�𔲂��o��
}

void followGroup(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*  
    ���̃v���[���[�ɑ����ăJ�[�h�𖇐��g�ŏo���Ƃ��̃��[�`��
    joker_flag��1�̎��W���[�J�[���g�����Ƃ���
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  int group[8][15];
  int ngroup[8][15];
  int temp[8][15];
  
  highCards(temp,my_cards,state.ord);          //���苭���J�[�h���c�� 
  if(state.lock==1){                           //���b�N����Ă���Ƃ�
    lockCards(temp,state.suit);                //�o���Ȃ��J�[�h������
  }
  makeGroupTable(group,temp);                  //�c�������̂��疇���g�������o��
  if(nCards(ngroup,group,state.qty)==0&&state.joker==1){
    //��Ɠ��������̑g�������Ƃ��W���[�J�[���g���ĒT��
    makeJGroupTable(group,temp);               
    nCards(ngroup,group,state.qty);     //��Ɠ��������̑g�݂̂̂����B 
  }
  lowGroup(out_cards,my_cards,ngroup);  //��Ԏア�g�𔲂��o��
}

void followSequence(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    ���̃v���[���[�ɑ����ăJ�[�h���K�i�ŏo���Ƃ��̃��[�`��
    joker_flag��1�̎��W���[�J�[���g�����Ƃ���
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  int seq[8][15];
  int nseq[8][15];
  int temp[8][15];
  
  highCards(temp,my_cards,state.ord);          //���苭���J�[�h���c��
  if(state.lock==1){                           //���b�N����Ă���Ƃ�
    lockCards(temp,state.suit);                //�o���Ȃ��J�[�h������
  }
  makeKaidanTable(seq,temp);                   //�K�i�������o��
  if(nCards(nseq,seq,state.qty)==0&&state.joker==1){
    //��Ɠ��������̊K�i�������Ƃ��W���[�J�[���g���ĒT��
    makeJKaidanTable(seq,temp);
    nCards(nseq,seq,state.qty);          //��Ɠ��������̑g�݂̂̂����B
  }
  lowSequence(out_cards,my_cards,nseq);  //��Ԏア�K�i��
}

void followSoloRev(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    �v����Ԃ̂Ƃ��ɑ��̃v���[���[�ɑ����ăJ�[�h���ꖇ�ŏo���Ƃ��̃��[�`��
    joker_flag��1�̎��W���[�J�[���g�����Ƃ���
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  int group[8][15];
  int sequence[8][15];
  int temp[8][15];
  
  makeGroupTable(group,my_cards);            //�����g�������o��
  makeKaidanTable(sequence,my_cards);        //�K�i�������o��
  
  removeSequence(temp,my_cards,sequence);    // �K�i������
  removeGroup(out_cards,temp,group);         // �����g������
  lowCards(temp,out_cards,state.ord);        // ��̃J�[�h��苭���J�[�h������
  if(state.lock==1){
    lockCards(temp,state.suit);          //���b�N����Ă���Ƃ��o���Ȃ��J�[�h������
  }
  highSolo(out_cards,temp,state.joker);  //�c�����J�[�h���狭���J�[�h�𔲂��o��
}

void followGroupRev(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    �v����Ԃ̂Ƃ��ɑ��̃v���[���[�ɑ����ăJ�[�h�𖇐��g�ŏo���Ƃ��̃��[�`��
    joker_flag��1�̎��W���[�J�[���g�����Ƃ���
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  int group[8][15];
  int ngroup[8][15];
  int temp[8][15];
  
  lowCards(temp,my_cards,state.ord);          //����ア�J�[�h���c��
  if(state.lock==1){                          //���b�N����Ă���Ƃ�
    lockCards(temp,state.suit);               //�o���Ȃ��J�[�h������
  }
  makeGroupTable(group,temp);                 //�����g�������o��
  if(nCards(ngroup,group,state.qty)==0&&state.joker==1){
    //��Ɠ��������̑g�������Ƃ��W���[�J�[���g���ĒT��
    makeJGroupTable(group,temp);
    nCards(ngroup,group,state.qty);      //��Ɠ��������̑g�݂̂̂����B
  }
  highGroup(out_cards,my_cards,ngroup);  //�c�������̂����ԋ����g�𔲂��o��
}

void followSequenceRev(int out_cards[8][15],int my_cards[8][15],int joker_flag){
  /*
    �v����Ԃ̂Ƃ��ɑ��̃v���[���[�ɑ����ăJ�[�h���K�i�ŏo���Ƃ��̃��[�`��
    joker_flag��1�̎��W���[�J�[���g�����Ƃ���
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  int seq[8][15];
  int nseq[8][15];
  int temp[8][15];
  
  lowCards(temp,my_cards,state.ord);          //����ア�J�[�h���c��
  if(state.lock==1){                          //���b�N����Ă���Ƃ�
    lockCards(temp,state.suit);               //�o���Ȃ��J�[�h������
  }
  makeKaidanTable(seq,temp);                  //�K�i�������o��
  if(nCards(nseq,seq,state.qty)==0&&state.joker==1){
    //��Ɠ��������̊K�i�������Ƃ��W���[�J�[���g���ĒT��
    makeJKaidanTable(seq,temp);
    nCards(nseq,seq,state.qty);          //��Ɠ��������̊K�i�݂̂̂����B
  } 
  highSequence(out_cards,my_cards,nseq); //�c�������̂����ԋ����g�𔲂��o��
}

void follow(int out_cards[8][15],int my_cards[8][15]){
  /*
    ���̃v���[���[�ɑ����ăJ�[�h���o���Ƃ��̃��[�`��
    ��̏��state�ɉ����Ĉꖇ�A�����g�A�K�i�̏ꍇ�ɕ�����
    �Ή������֐����Ăяo��
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  clearTable(out_cards);
  if(state.qty==1){
    followSolo(out_cards,my_cards,state.joker);    //�ꖇ�̂Ƃ�
  }else{
    if(state.sequence==0){
      followGroup(out_cards,my_cards,state.joker);  //�����g�̂Ƃ�
    }else{
      followSequence(out_cards,my_cards,state.joker); //�K�i�̂Ƃ�
    }
  }
}

void followRev(int out_cards[8][15],int my_cards[8][15]){
  /*
    ���̃v���[���[�ɑ����ăJ�[�h���o���Ƃ��̃��[�`��
    ��̏��state�ɉ����Ĉꖇ�A�����g�A�K�i�̏ꍇ�ɕ�����
    �Ή������֐����Ăяo��
    ��o����J�[�h�̓J�[�h�e�[�u��out_cards�Ɋi�[�����
  */
  clearTable(out_cards);
  if(state.qty==1){
    followSoloRev(out_cards,my_cards,state.joker);    //�ꖇ�̂Ƃ�
  }else{
    if(state.sequence==0){
      followGroupRev(out_cards,my_cards,state.joker);  //�����g�̂Ƃ�
    }else{
      followSequenceRev(out_cards,my_cards,state.joker); //�K�i�̂Ƃ�
    }
  }
}

int cmpCards(int cards1[8][15],int  cards2[8][15]){
  /*
    �J�[�h�e�[�u��cards1�Acards2�̃J�[�h�������r���A
    �قȂ��Ă����1�A��v���Ă����0��Ԃ�
  */
  int i,j,flag=0;
  
  for(i=0;i<5;i++)
    for(j=0;j<15;j++)
      if(cards1[i][j]!=cards2[i][j])
	flag=1;
  
  return flag;
}

int cmpState(struct state_type* state1,struct state_type* state2){
  /*
    ��Ԃ��i�[����state1��state2���r���A��v�����0���A
    �قȂ��Ă���΂���ȊO��Ԃ�
  */
  int i,flag=0;
  if(state1->ord != state2->ord) flag+=1;
  if(state1->qty != state2->qty) flag+=2;
  if(state1->sequence != state2->sequence) flag+=4;
  for(i=0;i<5;i++)
    if(state1->suit[i]!=state2->suit[i]) flag+=8;
  if(state1->onset != state2->onset) flag+=16;
  return flag;
}

int getLastPlayerNum(int ba_cards[8][15]){
  /*
    �Ō�p�X�ȊO�̃J�[�h��o�������v���[���[�̔ԍ���Ԃ��B
    ���̊֐��𐳏�ɓ��삳���邽�߂ɂ́A
    �T�[�o�����ɏo���J�[�h�����炤�x��
    ���̊֐����Ăяo���K�v������B
  */
  static struct state_type last_state;
  static int last_player_num=-1;
  
  if(g_logging==1){  //���O�̕\��
    printf("Now state \n");
    showState(&state);
    printf(" Last state \n");
    showState(&last_state);
  }
  
  if(cmpState(&last_state,&state)!=0){ //��̏�Ԃɕω����N������
    last_player_num =ba_cards[5][3];   //�Ō�̃v���[����
    last_state=state;                  //�ŐV�̏�Ԃ��X�V����
  }
  
  if(g_logging==1){ //���O�̕\��
    printf("last player num : %d\n",last_player_num);
  }
  
  return last_player_num;
}
