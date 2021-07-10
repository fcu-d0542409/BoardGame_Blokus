#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct Bricks{
	int id;		
	int entry;	
	int feature[4];
	char shape[25];
	int valid;
	};
	
struct Bricks player_1[21];		//���a 1 
struct Bricks player_2[21];		//���a 2 

char board[14][14];				//�ѽL 

char star = '*',pound = '#',zero = '0';

int round = 0;					//�^�X�� 

int pos_row[20] = {0};			//�Ѧ��I�}�C 
int pos_column[20] = {0};		//�Ѧ��I�}�C 

int array_best[21][4][20] = {0};		//�s��Ҧ��i��ҥͦ���vertex ,[21] = blicks�B [4] = ���স�� �B [x] = �ϤW�e x �ӰѦ��I 

void initial();
void print();


int array[9][4] = {{1,10,-1,90}, //1		����x�}�� 
				   {2,20,-2,180}, //2 
				   {3,30,-3,270}, //3
				   {4,40,-4,360}, //4
				   {11,-11,-91,91}, //5
				   {12,-21,-92,181}, //6
				   {13,-31,-93,271}, //7
				   {21,-12,-181,92}, //8
				   {22,-22,-182,182}}; //9


int type(struct Bricks *p, int (*array)[4],int k){			// ���ɰw���� 
	
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 4; j++){
				if(p->feature[k] == array[i][j]){
					if(j!=3)
						return array[i][j + 1];
					else
						return array[i][0];
				}
			}
		}
		return 0;
	}
	
int retype(struct Bricks *p, int (*array)[4],int k){		// �f�ɰw���� 
	
		for(int i = 0; i < 9; i++){
			for(int j = 0; j < 4; j++){
				if(p->feature[k] == array[i][j]){
					if(j!=0)
						return array[i][j - 1];
					else
						return array[i][3];
				}
			}
		}
		return 0;
	}
	
		
int legal_fun(char (*board)[14],int row, int column, int down[5], int right[5]){   //�P�_�O�_�X�k��m�j�� 
	
	int pos_row[20];
	int pos_column[20];
	int k = 0;

	pos_row[20] = {0};			//�s��{�Ϥ��Ҧ��Ѧ��I��row 
	pos_column[20] = {0};		//�s��{�Ϥ��Ҧ��Ѧ��I��column
	
	for(int i = 0; i < 14; i++){        //�N�{�ѽL�Ҧ��Ѧ��I�O���_�� 
		
		for(int j = 0; j < 14; j++){
			
			if(i == 0){
				
				if(board[i + 1][j - 1] == '*' || board[i + 1][j + 1] == '*'){
					
					if(board[i + 1][j] != '*'  && board[i][j + 1] != '*' && board[i][j - 1] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[k] = i;
							pos_column[k] = j;
							k++;
						}
					}
				}
			}
			
			else if(j == 0){
				
				if(board[i + 1][j + 1] == '*' || board[i - 1][j + 1] == '*'){
					
					if(board[i + 1][j] != '*'  && board[i][j + 1] != '*' && board[i - 1][j] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[k] = i;
							pos_column[k] = j;
							k++;
						}
					}
				}
			}
			
			else if(j == 13){				//�Y�a�� 
				
				if(board[i - 1][j - 1] == '*' || board[i + 1][j - 1] == '*'){
					
					if(board[i + 1][j] != '*'  && board[i][j - 1] != '*' && board[i - 1][j] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[k] = i;
							pos_column[k] = j;
							k++;		
						}	
					}
				}
			}
			
		
			else{						
							
				if(board[i + 1][j + 1] == '*' || board[i + 1][j - 1] == '*' || board[i - 1][j + 1] == '*' || board[i - 1][j - 1] == '*'){
					
					if(board[i + 1][j] != '*' && board[i - 1][j] != '*' && board[i][j + 1] != '*' && board[i][j - 1] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[k] = i;
							pos_column[k] = j;
							k++;		
						}
						
					}
				}
			}
		}
	}
	
		int illegal_1 = 0;
		int illegal_2 = 0;
		
		
		for(int i = 0; i < 14; i++){
			board[i][-1] = '0';
			board[-1][i] = '0';
		}
			
		
		for(int t = 0; t < k; t++){			// �̧ǱN���j�� 5�ӯS�x�Ȫ�{�X��(�@���㪺�j��)�� k�ӰѦ��I���A�óz�L�S�w�P�_�X�k�Τ��X�k					
			
			
			for(int u = 0; u < 5; u++){
				
					
				if(row + down[u] == pos_row[t] && column + right[u] == pos_column[t] ){		//�Y���I��m���j������Ĳ��Ѧ��I�����p�U 
					
									
					for(int r = 0; r < 5; r++){			// ���p�j���@�榳'*'�s�b �hcontract 
						
						if(board[row + down[r] + 1][column + right[r]] == '*' 
						|| board[row + down[r] - 1][column + right[r]] == '*' 
						|| board[row + down[r]][column + right[r] + 1] == '*' 
						|| board[row + down[r]][column + right[r] - 1] == '*'
						|| board[row + down[r]][column + right[r]] == '+'	){
		
							illegal_1 = 1;
							return 1;
						}	
						
						if(row + down[r] < 0 || column + right[r] < 0 || row + down[r] > 13 || column + right[r] > 13){		//�Ω�m���j���W�L�ѽL over board

							illegal_2 = 1;
							return 2;	
						}					
					}	
		
						if(illegal_1 == 0 && illegal_2 == 0){

							return 0;
						}
							
				}
			}
		}
		
		if(round != 0 || round != 1){			//�Y�S��Ĳ����I �hnot natch 
			return 3;	
		}			
}


int put(struct Bricks *p,int row, int column, char (*board)[14], char sign,int rotation){
	
	int down[5] = {0};
	int right[5] = {0};
	int legal = 0;
	
	
	if(rotation == 90){
		for(int k = 1; k < 5; k++)
			p->feature[k-1] = type(p,array,k-1);
	}
	
	if(rotation == 180){
		for(int k = 1; k < 5; k++){
			p->feature[k-1] = type(p,array,k-1);
			p->feature[k-1] = type(p,array,k-1);
		}
	}
	
	if(rotation == 270){
		for(int k = 1; k < 5; k++){
			p->feature[k-1] = type(p,array,k-1);
			p->feature[k-1] = type(p,array,k-1);
			p->feature[k-1] = type(p,array,k-1);
		}
	}
	
	

	for(int k = 1; k < 5; k++){
		if(p->feature[k-1] < 0){
			if(p->feature[k-1] <= -90){
				down[k] = p->feature[k-1] / 90; 
				right[k] = p->feature[k-1] % 10;
			}
			else{
				down[k] = -(p->feature[k-1] / 10);
				right[k] = p->feature[k-1] % 10;
			}
		}
		else{
			if(p->feature[k-1] >= 90){
				down[k] = -(p->feature[k-1] / 90); 
				right[k] = p->feature[k-1] % 10;
			}
			else{
				down[k] = p->feature[k-1] / 10;
				right[k] = p->feature[k-1] % 10;
			}
		}
	}

	legal = legal_fun(board,row,column,down,right);
	
	if(round == 0 || round == 1){
		for(int i = 1; i < 5; i++){
			if(row + down[i] < 14 && column + right[i] < 14){
				board[row][column] = sign;
				board[row + down[i]][column + right[i]] = sign;
				p->valid = 0;
			}
		}
		print();
		return 1;	
	}
	
	else if(legal == 0 || legal == 3){	
		for(int i = 1; i < 5; i++){
			if(row + down[i] < 14 && column + right[i] < 14){
				board[row][column] = sign;
				board[row + down[i]][column + right[i]] = sign;
				p->valid = 0;
			}
		}
		print();		
		return 1;
	}
	
	else{
		if(round != 0 && round != 1)
			printf("PASS ! !\n");
			printf("illegal %d\n",legal);
			return 0;
	}
	
}

int ai_fun(struct Bricks *p, char (*board)[14], int bricks, int rotation){
	
	int k = 0;
	int down[5] = {0};
	int right[5] = {0};
	int legal = 0;
	int total = 0;
	
	pos_row[20] = {0};
	pos_column[20] = {0};
	
	for(int i = 0; i < 14; i++){        //�N�{�ѽL�Ҧ��Ѧ��I�O���_�� 
		
		for(int j = 0; j < 14; j++){
			
			if(i == 0){
				
				if(board[i + 1][j - 1] == '*' || board[i + 1][j + 1] == '*'){
					
					if(board[i + 1][j] != '*'  && board[i][j + 1] != '*' && board[i][j - 1] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[total] = i;
							pos_column[total] = j;
							total++;
						}
					}
				}
			}
			
			else if(j == 0){
				
				if(board[i + 1][j + 1] == '*' || board[i - 1][j + 1] == '*'){
					
					if(board[i + 1][j] != '*'  && board[i][j + 1] != '*' && board[i - 1][j] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[total] = i;
							pos_column[total] = j;
							total++;
						}
					}
				}
			}
			
			else if(j == 13){				//�Y�a�� 
				
				if(board[i - 1][j - 1] == '*' || board[i + 1][j - 1] == '*'){
					
					if(board[i + 1][j] != '*'  && board[i][j - 1] != '*' && board[i - 1][j] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[total] = i;
							pos_column[total] = j;
							total++;		
						}	
					}
				}
			}
			
		
			else{						
							
				if(board[i + 1][j + 1] == '*' || board[i + 1][j - 1] == '*' || board[i - 1][j + 1] == '*' || board[i - 1][j - 1] == '*'){
					
					if(board[i + 1][j] != '*' && board[i - 1][j] != '*' && board[i][j + 1] != '*' && board[i][j - 1] != '*'){
						
						if(board[i][j] != '+'){
							pos_row[total] = i;
							pos_column[total] = j;
							total++;		
						}
						
					}
				}
			}
		}
	}
				
				if(rotation == 90){							//���ɰw����
					for(int k = 1; k < 5; k++)
						p->feature[k-1] = type(p,array,k-1);
				}
		
				if(rotation == 180){
					for(int k = 1; k < 5; k++){
						p->feature[k-1] = type(p,array,k-1);
						p->feature[k-1] = type(p,array,k-1);
					}
				}
		
				if(rotation == 270){
					for(int k = 1; k < 5; k++){
						p->feature[k-1] = type(p,array,k-1);
						p->feature[k-1] = type(p,array,k-1);
						p->feature[k-1] = type(p,array,k-1);
					}
				}
				
				for(int k = 1; k < 5; k++){					//�S�x�Ȳq�� 
					if(p->feature[k-1] < 0){
						if(p->feature[k-1] <= -90){
							down[k] = p->feature[k-1] / 90; 
							right[k] = (p->feature[k-1] % 10);
						}
						else{
							down[k] = -(p->feature[k-1] / 10);
							right[k] = p->feature[k-1] % 10;
						}
					}
					else{
						if(p->feature[k-1] >= 90){
							down[k] = -(p->feature[k-1] / 90); 
							right[k] = p->feature[k-1] % 10;
						}
						else{
							down[k] = p->feature[k-1] / 10;
							right[k] = p->feature[k-1] % 10;
						}
					}
				}
				
				if(rotation == 90){							//�f�ɰw���� (�_��) 
					for(int k = 1; k < 5; k++)
						p->feature[k-1] = retype(p,array,k-1);
				}
	
				if(rotation == 180){
					for(int k = 1; k < 5; k++){
						p->feature[k-1] = retype(p,array,k-1);
						p->feature[k-1] = retype(p,array,k-1);
					}
				}
	
				if(rotation == 270){
					for(int k = 1; k < 5; k++){
						p->feature[k-1] = retype(p,array,k-1);
						p->feature[k-1] = retype(p,array,k-1);
						p->feature[k-1] = retype(p,array,k-1);
					}
				}
				
				
			for(int n = 0; n < total; n++){						//���Nint main�̥����j�骺�j����W�h�p�� 
				
				legal = legal_fun(board,pos_row[n],pos_column[n],down,right);
		
				if(legal == 0){	
					for(int j = 1; j < 5; j++){
						if(pos_row[n] + down[j] < 14 && pos_column[n] + right[j] < 14 && pos_row[n] + down[j] >= 0 && pos_column[n] + right[j] >= 0){
							board[pos_row[n]][pos_column[n]] = star;
							board[pos_row[n] + down[j]][pos_column[n] + right[j]] = star;
						}
					}
					
					for(int i = 0; i < 14; i++){				//�����j��j����m�� �w��total�ӰѦ��I�� �B���P���স�ƤU �ҧΦ���h(�h��)�Ѧ��I 
			
						for(int j = 0; j < 14; j++){
							
							if(board[i][j] != '*'){
						
								if(board[i + 1][j + 1] == '*' || board[i + 1][j - 1] == '*' || board[i - 1][j + 1] == '*' || board[i - 1][j - 1] == '*'){
									
									if(board[i + 1][j] != '*' && board[i - 1][j] != '*' && board[i][j + 1] != '*' && board[i][j - 1] != '*'){
										
										if(rotation == 0){
											array_best[p->id][0][n]++;
										}
								
												
										 if(rotation == 90){
										 	array_best[p->id][1][n]++; 
										 }
										 
										 if(rotation == 180){
										 	array_best[p->id][2][n]++;
										 }
										 	
										 if(rotation == 270){
										 	array_best[p->id][3][n]++;
										 }			 
											
										}
									}
								}
							}
						}
									
			
					for(int j = 1; j < 5; j++){					//�_�� ��j���ޱ� 
						if(pos_row[n] + down[j] < 14 && pos_column[n] + right[j] < 14){
							board[pos_row[n]][pos_column[n]] = zero;
							board[pos_row[n] + down[j]][pos_column[n] + right[j]] = zero;
							
						}
					}		
				}
		}

}

void change(char (*board)[14]){
	
	for(int i = 0; i < 14; i++){        
		
		for(int j = 0; j < 14; j++){
			
			if(board[i][j] == '*'){
				board[i][j] = '+';
			}
				
			else if(board[i][j] == '+'){
				board[i][j] = '*';
			}	
				
		}		
	}
	print();
}




int main(){
	
		player_1[0] = {0,1,{0,0,0,0},
				{'*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[1] = {1,2,{1,0,0,0},
				{'*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[2] = {2,3,{1,11,0,0},
				{'*','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[3] = {3,3,{1,2,0,0},
				{'*','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[4] = {4,4,{1,10,11,0},
				{'*','*','\0','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[5] = {5,4,{1,2,10,0},
				{'*','*','*','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[6] = {6,4,{1,2,11,0},
				{'*','*','*','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[7] = {7,4,{1,11,12,0},
				{'*','*','\0','\0','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[8] = {8,4,{1,2,3,0},
				{'*','*','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[9] = {9,5,{1,2,10,11},
				{'*','*','*','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[10] = {10,5,{1,2,10,12},
			 	 {'*','*','*','\0','\0','*','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[11] = {11,5,{1,2,11,21},
				 {'*','*','*','\0','\0','\0','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[12] = {12,5,{1,2,10,20},
				 {'*','*','*','\0','\0','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[13] = {13,5,{1,11,12,22},
				 {'*','*','\0','\0','\0','\0','*','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[14] = {14,5,{10,11,12,22},
				 {'*','\0','\0','\0','\0','*','*','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[15] = {15,5,{10,11,12,21},
				 {'*','\0','\0','\0','\0','*','*','*','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[16] = {16,5,{91,1,11,2},
				 {'\0','*','\0','\0','\0','*','*','*','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[17] = {17,5,{1,2,3,10},
				 {'*','*','*','*','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[18] = {18,5,{1,2,12,13},
				 {'*','*','*','\0','\0','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[19] = {19,5,{1,2,3,11},
				 {'*','*','*','*','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_1[20] = {20,5,{1,2,3,4},
				 {'*','*','*','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
			 
			 
		player_2[0] = {0,1,{0,0,0,0},
				{'*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[1] = {1,2,{1,0,0,0},
				{'*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[2] = {2,3,{1,11,0,0},
				{'*','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[3] = {3,3,{1,2,0,0},
				{'*','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[4] = {4,4,{1,10,11,0},
				{'*','*','\0','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[5] = {5,4,{1,2,10,0},
				{'*','*','*','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[6] = {6,4,{1,2,11,0},
				{'*','*','*','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[7] = {7,4,{1,11,12,0},
				{'*','*','\0','\0','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[8] = {8,4,{1,2,3,0},
				{'*','*','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[9] = {9,5,{1,2,10,11},
				{'*','*','*','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[10] = {10,5,{1,2,10,12},
			 	 {'*','*','*','\0','\0','*','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[11] = {11,5,{1,2,11,21},
				 {'*','*','*','\0','\0','\0','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[12] = {12,5,{1,2,10,20},
				 {'*','*','*','\0','\0','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[13] = {13,5,{1,11,12,22},
				 {'*','*','\0','\0','\0','\0','*','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[14] = {14,5,{10,11,12,22},
				 {'*','\0','\0','\0','\0','*','*','*','\0','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[15] = {15,5,{10,11,12,21},
				 {'*','\0','\0','\0','\0','*','*','*','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[16] = {16,5,{91,1,11,2},
				 {'\0','*','\0','\0','\0','*','*','*','\0','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[17] = {17,5,{1,2,3,10},
				 {'*','*','*','*','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[18] = {18,5,{1,2,12,13},
				 {'*','*','*','\0','\0','\0','\0','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[19] = {19,5,{1,2,3,11},
				 {'*','*','*','*','\0','\0','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
		player_2[20] = {20,5,{1,2,3,4},
				 {'*','*','*','*','*','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0','\0'},1};
			 	 
			 
	int row = 0,column = 0;
	int pivot = 0;
	int choice = 0;
	int rotation = 0;
	
	
	initial();
	int big = 0;
	int method = 0;
	
	for(int k = 0; k < 42; k++){
		
		printf("Which method would you like\n");
		printf("(1)algo(1p) (2)algo(2p) (3)by hand(1p) (4)by hand(2p)\n");
		scanf(" %d",&method);
		
		switch(method){
			
			case 1:	{					//�۰ʤU�� 
				
				double start,end;
					start = clock();
					
				change(board);
				
				if(round == 0 || round == 1){
					struct Bricks *p = &player_1[16];
					printf("\n==========================================================\n\n");
					printf("\n ROUND = %d    P 1 turn\n\n",round+1);
					printf("Bricks %d is placed on vertex (%d,%d) with rotation %d\n\n",16,4,4,0);
					put(p,4,4,board,star,rotation);
					printf("\n\n");
					round++;
					p->valid = 0;
				}
				
				else{		
				
						for(int i = 0; i < 21; i++){
								
								for(int j = 0; j < 4; j++){
									
									for(int k = 0; k < 20; k++){
										
										array_best[i][j][k] = 0;
									}
								}
							}
				
						for(int bricks = 21; bricks > 0; bricks--){
							
							struct Bricks *p = &player_1[bricks - 1];
							
								if(p->valid == 1){
							
									for(int angle = 0; angle <=270; angle += 90){
									
										ai_fun(p,board,bricks,angle);			//�P�_�{�ϩҦ��Ѧ��I �j���B���� �ñN�Ҧ����G���array_best�O�s 
									
									}
								}	
						}

				int max_count = 0;		
				int max_blick = 0;
				int max_rotation = 0;
				int max_vertex = 0;
				int count = 0;
				
				int sec_count = 0;
				int sec_blick = 0;
				int sec_rotation = 0;
				int sec_vertex = 0;
				
				
					max_count = array_best[20][0][0];
					sec_count = array_best[20][0][0];	
						
					for(int i = 20; i >= 0; i--){
						
						if(player_1[i].valid == 0)		
							continue;
									
						for(int j = 0; j < 4; j++){
							
							for(int k = 0; k < 20; k++){
										
								if(array_best[i][j][k] > max_count){	
									sec_count = max_count;
									sec_blick = max_blick;
									sec_rotation = max_rotation;
									sec_vertex = max_vertex;	
								
									max_count = array_best[i][j][k];     	////�Darray_best���̤j�� 
									max_blick = i;
									max_rotation = j;
									max_vertex = k;
								}		
							}	
						}	
					}
					
					if(max_count == 0){
						printf("\n==========================================================\n\n");
						printf("\n ROUND = %d    P 1 turn\n\n",round+1);
						printf("\n-------- P 1  ->  P A S S ----------\n\n");
						round++;
					}
					
					else{

						printf("max count = %d\n",max_count);
						printf("max blick = %d\n",max_blick);
						printf("max rotation = %d\n",max_rotation);
						printf("max vertex = %d\n",max_vertex);
		
						max_rotation *= 90;	
						struct Bricks *p = &player_1[max_blick];
						printf("%d\n",max_vertex);
						
						if(p->valid == 1){					//�N array_best�̤j�ȵ��G��put�N�j����W�h 
							printf("\n==========================================================\n\n");
							printf("\n ROUND = %d    P 1 turn\n\n",round+1);
							printf("Bricks %d is placed on vertex (%d,%d) with rotation %d\n\n",max_blick,pos_row[max_vertex],pos_column[max_vertex],max_rotation);
							
							if(put(p,pos_row[max_vertex],pos_column[max_vertex],board,star,max_rotation) ==	0){
								
								sec_rotation *= 90;
								struct Bricks *p = &player_1[sec_blick];
								printf("%d\n",sec_vertex);
								if(p->valid == 1){					//�N array_best�̤j�ȵ��G��put�N�j����W�h 
									printf("\n==========================================================\n\n");
									printf("\n ROUND = %d\n\n",round+1);
									printf("Bricks %d is placed on vertex (%d,%d) with rotation %d\n\n",sec_blick,pos_row[sec_vertex],pos_column[sec_vertex],sec_rotation);
									put(p,pos_row[sec_vertex],pos_column[sec_vertex],board,star,sec_rotation);
									printf("\n\n");
									round++;
									p->valid = 0;	
								}
							}	
								
							else{
								printf("\n\n");
								round++;
								p->valid = 0;
							}	
								
						}
					}
				}
				
				end = clock();
				
				printf("Start time: %f s     End time: %f s\n",start/1000,end/1000);
				printf("Cost time: %f s\n",(end - start) / 1000);
				printf("\n");
				printf("\n==========================================================\n");
						
				break;
			}
			
			case 2:	{					//�۰ʤU�� 
				
				double start,end;
					start = clock();
					
				change(board);
				
				if(round == 0 || round == 1){
					struct Bricks *q = &player_2[16];
					printf("\n==========================================================\n\n");
					printf("\n ROUND = %d    P 2 turn\n\n",round+1);
					printf("Bricks %d is placed on vertex (%d,%d) with rotation %d\n\n",16,9,9,0);
					put(q,9,9,board,star,rotation);
					printf("\n\n");
					round++;
					q->valid = 0;
				}
				
				else{	
				
						for(int i = 0; i < 21; i++){
							
								for(int j = 0; j < 4; j++){
									
									for(int k = 0; k < 20; k++){
										
										array_best[i][j][k] = 0;
									}
								}
							}	
				 				
						for(int bricks = 21; bricks > 0; bricks--){
					
							struct Bricks *q = &player_2[bricks - 1];
							
								if(q->valid == 1){
							
									for(int angle = 0; angle <=270; angle += 90){
									
										ai_fun(q,board,bricks,angle);			//�P�_�{�ϩҦ��Ѧ��I �j���B���� �ñN�Ҧ����G���array_best�O�s 
									
									}
								}	
						}

				int max_count = 0;		
				int max_blick = 0;
				int max_rotation = 0;
				int max_vertex = 0;
				int count = 0;
				
				int sec_count = 0;
				int sec_blick = 0;
				int sec_rotation = 0;
				int sec_vertex = 0;
				
					max_count = array_best[20][0][0];	
						
					for(int i = 20; i >= 0; i--){
						
						if(player_2[i].valid == 0)		
							continue;
									
						for(int j = 0; j < 4; j++){
									
							for(int k = 0; k < 20; k++){
										
								if(array_best[i][j][k] > max_count){			////�Darray_best���̤j�� 
									max_count = array_best[i][j][k];
									max_blick = i;
									max_rotation = j;
									max_vertex = k;
								}		
							}	
						}	
					}
					
					if(max_count == 0){
						printf("\n==========================================================\n\n");
						printf("\n ROUND = %d    P 2 turn\n\n",round+1);
						printf("\n-------- P 2  ->  P A S S ----------\n\n");
						round++;
					}
					
					else{
					
						printf("max count = %d\n",max_count);
						printf("max blick = %d\n",max_blick);
						printf("max rotation = %d\n",max_rotation);
						printf("max vertex = %d\n",max_vertex);
		
						max_rotation *= 90;	
						struct Bricks *q = &player_2[max_blick];
						printf("%d\n",max_vertex);
						
						if(q->valid == 1){					//�N array_best�̤j�ȵ��G��put�N�j����W�h 
							printf("\n==========================================================\n\n");
							printf("\n ROUND = %d    P 2 turn\n\n",round+1);
							printf("Bricks %d is placed on vertex (%d,%d) with rotation %d\n\n",max_blick,pos_row[max_vertex],pos_column[max_vertex],max_rotation);
							
							if(put(q,pos_row[max_vertex],pos_column[max_vertex],board,star,max_rotation) ==	0){
								
								sec_rotation *= 90;
								struct Bricks *q = &player_2[sec_blick];
								printf("%d\n",sec_vertex);
								if(q->valid == 1){					//�N array_best�̤j�ȵ��G��put�N�j����W�h 
									printf("\n==========================================================\n\n");
									printf("\n ROUND = %d\n\n",round+1);
									printf("Bricks %d is placed on vertex (%d,%d) with rotation %d\n\n",sec_blick,pos_row[sec_vertex],pos_column[sec_vertex],sec_rotation);
									put(q,pos_row[sec_vertex],pos_column[sec_vertex],board,star,sec_rotation);
									printf("\n\n");
									round++;
									q->valid = 0;	
								}
							}	
								
							else{
								printf("\n\n");
								round++;
								q->valid = 0;
							}	
								
						}
					
					}
				}
				
				end = clock();
				
				printf("Start time: %f s     End time: %f s\n",start/1000,end/1000);
				printf("Cost time: %f s\n",(end - start) / 1000);
				printf("\n");
				printf("\n==========================================================\n");
						
				break;
			}
				
			case 3:	{
				
				change(board);
			
				printf("Please choose the vertex :");
				scanf(" %d %d",&row,&column);
				
				printf("\nWhich brick would you choose ? ");
				scanf(" %d", &choice);
			
				for(int j = 0; j < 25; j++){
					printf(" %c",player_1[choice-1].shape[j]);
					if((j + 1) % 5 == 0)
						printf("\n");
				}
				
				printf("\nNeed to rotate ? ( 0 / 90 / 180 / 270 ) ");
				scanf(" %d", &rotation);
				
				struct Bricks *p = &player_1[choice - 1];
				
				printf("\n=======================================\n");
				printf("\n");
				
				if(p->valid == 1){
					printf("Bricks %d is placed on vertex : (%d,%d) \n",choice,row,column);
					printf("\n");
			
					put(p,row,column,board,star,rotation);
					round++;
					p->valid = 0;
			
					printf("\n");
				}
				
				else
					printf("Already used, please choose another one !\n");
				
				printf("=======================================\n");
				
				break;
			
			}
					
				
			case 4:	{
				
				change(board);
				
				printf("Please choose the vertex :");
				scanf(" %d %d",&row,&column);
				
				printf("\nWhich brick would you choose ? ");
				scanf(" %d", &choice);
				
				for(int j = 0; j < 25; j++){
					printf(" %c",player_2[choice-1].shape[j]);
					if((j + 1) % 5 == 0)
						printf("\n");
				}
				
				printf("\nNeed to rotate ? ( 0 / 90 / 180 / 270 ) ");
				scanf(" %d", &rotation);
				
				struct Bricks *q = &player_2[choice - 1];
				
				printf("\n=======================================\n");
				printf("\n");
				
				if(q->valid == 1){
					printf("Bricks %d is placed on vertex : (%d,%d) \n",choice,row,column);
					printf("\n");
			
					put(q,row,column,board,star,rotation);
					round++;
					q->valid = 0;
			
					printf("\n");
				}
				
				else
					printf("Already used, please choose another one !\n");
				
				printf("=======================================\n");
				
				break;
				
			}			
		}
	}
	
	system("pause");
	return 0;
	
} 


void initial(){
	
	for(int i = 0; i < 14; i++){
		for(int j = 0; j < 14; j++){
			board[i][j] = '0';
		}
	}
}

void print(){
	
	for(int i = 0; i < 14; i++){
		for(int j =0; j < 14; j++){
			printf(" %c",board[i][j]);
		}
		printf("\n");
	}
}


