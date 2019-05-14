#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "daihinmin.h"
#include "connection.h"

const int g_logging=0;                     //���O�������邩�ۂ��𔻒肷�邽�߂̕ϐ�

int main(int argc,char* argv[]){

  int my_playernum;              //�v���C���[�ԍ����L������
  int whole_gameend_flag=0;	 //�S�Q�[�����I���������ۂ��𔻕ʂ���ϐ�
  int one_gameend_flag=0;	 //1�Q�[�����I��������ۂ��𔻕ʂ���ϐ�
  int accept_flag=0;             //��o�����J�[�h���󗝂��ꂽ���𔻕ʂ���ϐ�
  int game_count=0;		 //�Q�[���̉񐔂��L������
  
  int own_cards_buf[8][15];      //��D�̃J�[�h�e�[�u���������߂�ϐ�
  int own_cards[8][15];	         //����p�̎�D�̃e�[�u��
  int ba_cards_buf[8][15];       //��ɏo���J�[�h�e�[�u����[�߂�
  int ba_cards[8][15];           //����p�̏�̎D�̃e�[�u��
  
  //�����̃`�F�b�N �����ɏ]���ăT�[�o�A�h���X�A�ڑ��|�[�g�A�N���C�A���g����ύX
  checkArg(argc,argv);

  //�Q�[���ɎQ��
  my_playernum=entryToGame();
  
  while(whole_gameend_flag==0){
    one_gameend_flag=0;                 //1�Q�[�����I��������������t���O��������
    
    game_count=startGame(own_cards_buf);//���E���h���n�߂� �ŏ��̃J�[�h���󂯎��B
    copyTable(own_cards,own_cards_buf); //��������e�[�u���𑀍삷�邽�߂̃e�[�u���ɃR�s�[
    ///�J�[�h����
    if(own_cards[5][0]== 0){ //�J�[�h�������t���O���`�F�b�N ==1�Ő���
      printf("not card-change turn?\n");
      exit (1);
    }
    else{ //�e�[�u���ɖ�肪������Ύ��ۂɌ�����
      if(own_cards[5][1] > 0 && own_cards[5][1]<100){
	int change_qty=own_cards[5][1];          //�J�[�h�̌�������
      	int select_cards[8][15]={{0}};           //�I�񂾃J�[�h���i�[
	
	//�������x���A��x���ł���Εs�v�ȃJ�[�h��I�яo��
	
	/////////////////////////////////////////////////////////////
	//�J�[�h�����̃A���S���Y���͂����ɏ���
	/////////////////////////////////////////////////////////////
	
	change(select_cards,own_cards,change_qty);
	
	/////////////////////////////////////////////////////////////
	//�J�[�h�����̃A���S���Y�� �����܂�
	/////////////////////////////////////////////////////////////
    
	//�I�񂾃J�[�h�𑗐M
	sendChangingCards(select_cards);
      }
      else{
	//�����������ȉ��Ȃ�A��������K�v�͂Ȃ�
	
      }
    } //�J�[�h���������܂�

    while(one_gameend_flag == 0){     //1�Q�[�����I���܂ł̌J��Ԃ�
      int select_cards[8][15]={{0}};      //��o�p�̃e�[�u��
      
      if(receiveCards(own_cards_buf)== 1){  //�J�[�h��own_cards_buf�Ɏ󂯎��
                                            //�����Ԃ̓ǂݏo��
	                                    //�����̃^�[���ł��邩���m�F����
	//�����̃^�[���ł���΂��̃u���b�N�����s�����B
	clearCards(select_cards);             //�I�񂾃J�[�h�̃N���A
        copyTable(own_cards,own_cards_buf);   //�J�[�h�e�[�u�����R�s�[
	/////////////////////////////////////////////////////////////
	//�A���S���Y����������
	//�ǂ̃J�[�h���o�����͂����ɂ���
	/////////////////////////////////////////////////////////////
	if(state.onset==1){                //��ɃJ�[�h�������Ƃ�
	  if(state.rev==0){
	    lead(select_cards,own_cards);    //�ʏ펞�̒�o�p
	  }else{
	    leadRev(select_cards,own_cards); //�v�����̒�o�p
	  }
	}else{                               //���łɏ�ɃJ�[�h������Ƃ�
	  if(state.rev==0){
	    follow(select_cards,own_cards);    //�ʏ펞�̒�o�p 
	  }else{
	    followRev(select_cards,own_cards); //�v�����̒�o�p
	  } 
	}
	/////////////////////////////////////////////////////////////
	//�A���S���Y���͂����܂�
	/////////////////////////////////////////////////////////////
	accept_flag=sendCards(select_cards);//cards���o
      }
      else{
	//�����̃^�[���ł͂Ȃ���
	//�K�v�Ȃ炱���ɏ������L�q����
      }
      
     
      
      //���̃^�[���ɒ�o���ꂽ���ʂ̃e�[�u���󂯎��,��ɏo���J�[�h�̏�����͂���
      lookField(ba_cards_buf);
      copyTable(ba_cards,ba_cards_buf);

      ///////////////////////////////////////////////////////////////
      //�J�[�h���o���ꂽ���� �N�����J�[�h���o���O�̏����͂����ɏ���
      ///////////////////////////////////////////////////////////////

            
      ///////////////////////////////////////////////////////////////
      //�����܂�
      ///////////////////////////////////////////////////////////////
      
      //���̃Q�[�����I��������ۂ��̒ʒm���T�[�o���炤����B
      switch (beGameEnd()){
      case 0: //0�̂Ƃ��Q�[���𑱂���
	one_gameend_flag=0;
	whole_gameend_flag=0;
	break;
      case 1: //1�̂Ƃ� 1�Q�[���̏I��
	one_gameend_flag=1;
	whole_gameend_flag=0;
	if(g_logging == 1){
	  printf("game #%d was finished.\n",game_count);
	}
	break;
      default: //���̑��̏ꍇ �S�Q�[���̏I��
	one_gameend_flag=1;
	whole_gameend_flag=1;
	if(g_logging == 1){
	  printf("All game was finished(Total %d games.)\n",game_count);
	}
	break;
      }
    }//1�Q�[�����I���܂ł̌J��Ԃ������܂�
  }//�S�Q�[�����I���܂ł̌J��Ԃ������܂�
  //�\�P�b�g����ďI��
  if(closeSocket()!=0){
    printf("failed to close socket\n");
    exit(1);
  }
  exit(0);
}
