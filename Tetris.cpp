#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;
ifstream fin("Tetris.data");
ofstream fout("Tetris.final");
class Shape{
	public:
		Shape(char t,int id):type(t),index(id){};	
		char gettype(){
			return type;
		}
		int getindex(){
			return index;
		}
		int getposition(){
			return pos;
		}
		void setposition(int p){
			pos = p;
		}
	private:
		char type; 
		int index; 
		int pos;
};
int** Build(int r,int c){
	int** Tetris = new int*[r+4];
    for(int i=0;i<r+4;i++){
    	Tetris[i] = new int[c];
    	for(int j=0;j<c;j++){
    		Tetris[i][j] = 0;   //init with 0
		}
	}return Tetris;
}
int Checklines(int **T,int r,int c){
    int k=(r+4)-1;
	int i, j,count;
    int suc=1;
    for(i=r+4-1;i>=0 ;i--){
		count=0;
		for(j=0;j<c;j++){
			if(T[i][j]==1 && k>=4) count++;
			T[k][j] = T[i][j];
		}
		if(count<c) k--;
	}
    for (k=3; k >= 0;k--){
        for (j = 0; j < c;j++){
            if(T[k][j]==1){
                suc = -1;
                break;
                }
            }
        if(suc==-1)   break;
        } 
    return suc;
}
void ShapeT(int**T,Shape b,int r,int c){
	int count=0,p=b.getposition()-1;
	int k,j;
	switch(b.getindex()){
		case(1):
			for(k=0;k<r+4;k++){
			    if(count>=1 && T[k][p+1]==0 && T[k-1][p]==0 && T[k-1][p+2]==0){
					T[k][p+1]=1; T[k-1][p]=1; T[k-1][p+2]=1; count++;
					if(count>2){
						T[k-2][p]=0; T[k-2][p+1]=0; T[k-2][p+2]=0;
					}	
				}else if(count==0 && T[k][p+1]==0){
					T[k][p+1]=1; count++;	 				
				}
				else break;
			}break;
		case(2):
		    for(k=0;k<r+4;k++){
		        if(count>=1 && T[k][p+1]==0 && T[k-1][p]==0){
					T[k][p+1]=1; T[k-1][p]=1; count++;
					if(count==3){
					 	T[k-2][p]=0; //clear	
					}else if(count>3){
						T[k-2][p]=0; T[k-3][p+1]=0;
					}
				}else if(count==0 && T[k][p+1]==0){
		    		T[k][p+1]=1; count++;
		        }else break;
			}break;	
		case(3):
		    for(k=0;k<r+4;k++){
		    	if(T[k][p]==0 && T[k][p+1]==0 && T[k][p+2]==0){
		    		T[k][p]=1; T[k][p+1]=1; T[k][p+2]=1; count++;
		    		if(count==2){
		    		   T[k-1][p]=0; T[k-1][p+2]=0;
					}else if(count>2){
					   T[k-1][p]=0; T[k-1][p+2]=0; T[k-2][p+1]=0;
					}	
				}else break;
			}break;
		case(4):
		    for(k=0;k<r+4;k++){
		        if(count>=1 && T[k][p]==0 && T[k-1][p+1]==0){
					T[k][p]=1; T[k-1][p+1]=1; count++;
					if(count==3){
						T[k-2][p+1]=0; //clear
					}else if(count>3){
						T[k-2][p+1]=0; T[k-3][p]=0;
					}
				}else if(count==0 && T[k][p]==0){
		            T[k][p]=1; count++;
				}else break;
			}break;
		default:
		    break;			
	}
}
void ShapeL(int**T,Shape b,int r,int c){
	int count=0,p=b.getposition()-1;
	int k;
	switch(b.getindex()){
		case(1):
		    for(k=0;k<r+4;k++){
				if(T[k][p]==0 && T[k][p+1]==0){
					T[k][p]=1; T[k][p+1]=1; count++;
					if(count==2 ||count ==3)
						T[k-1][p+1]=0;
					else if(count>3){
						T[k-1][p+1]=0; T[k-3][p]=0;
					} 
				}else break;
			}break;
        case(2):
		    for(k=0;k<r+4;k++){
				if(count>=1 && T[k][p]==0 && T[k-1][p+1]==0 && T[k-1][p+2]==0){
					T[k][p]=1; T[k-1][p+1]=1; T[k-1][p+2]=1; count++;
					if(count>2){
						T[k-2][p]=0; T[k-2][p+1]=0; T[k-2][p+2]=0;
					}
				}else if(count==0 && T[k][p]==0){
					T[k][p]=1; count++;
				}else break;	
			}break;
		case(3):
		    for(k=0;k<r+4;k++){
				if(count>=2 && T[k][p+1]==0 && T[k-2][p]==0){
					T[k][p+1]=1; T[k-2][p]=1; count++;
					if(count>3){
						T[k-3][p+1]=0; T[k-3][p]=0;
					}
				}else if(count<2 && T[k][p+1]==0){
					T[k][p+1]=1; count++;
				}else break;
			}break;	
		case(4):
		    for(k=0;k<r+4;k++){
			    if(T[k][p]==0 && T[k][p+1]==0 && T[k][p+2]==0){
					T[k][p]=1; T[k][p+1]=1; T[k][p+2]=1; count++;
					if(count>2){
						T[k-1][p]=0; T[k-1][p+1]=0; T[k-2][p+2]=0;
					}else if(count==2){
						T[k-1][p]=0; T[k-1][p+1]=0;
					}
				}else break;
			}break;	
		default:
		    break;	
	}
}
void ShapeJ(int**T,Shape b,int r,int c){
	int count=0,p=b.getposition()-1;
	int k;
	switch(b.getindex()){
		case(1):
		    for(k=0;k<r+4;k++){
				if(T[k][p]==0 && T[k][p+1]==0){
					T[k][p]=1; T[k][p+1]=1; count++;
					if(count>3){
						T[k-1][p]=0; T[k-3][p+1]=0;
					}else if(count==2 || count==3)
					    T[k-1][p]=0;
			    }else break;
			}break;
		case(2):
		    for(k=0;k<r+4;k++){
				if(T[k][p]==0 && T[k][p+1]==0 && T[k][p+2]==0){
					T[k][p]=1; T[k][p+1]=1; T[k][p+2]=1; count++;
					if(count>2){
						T[k-1][p+1]=0; T[k-1][p+2]=0; T[k-2][p]=0;
					}else if(count==2){
						T[k-1][p+1]=0; T[k-1][p+2]=0;
					}
				}else break;
			}break;
		case(3):
		    for(k=0;k<r+4;k++){
				if(count>=2 && T[k][p]==0 && T[k-2][p+1]==0){
					T[k][p]=1; T[k-2][p+1]=1; count++;
					if(count>3){
						T[k-3][p]=0; T[k-3][p+1]=0;
					}
				}else if(count<2 && T[k][p]==0){
					T[k][p]=1; count++;
				}else break;
			}break;
		case(4):
		    for(k=0;k<r+4;k++){
				if(count>=1 && T[k][p+2]==0 && T[k-1][p]==0 && T[k-1][p+1]==0){
					T[k][p+2]=1; T[k-1][p]=1; T[k-1][p+1]=1; count++;
					if(count>2){
						T[k-2][p]=0; T[k-2][p+1]=0; T[k-2][p+2]=0;
					}
				}else if(count==0 && T[k][p+2]==0){
					T[k][p+2]=1; count++;
				}else break;
			}break;	
		default:
		    break;		
	}
}
void ShapeS(int**T,Shape b,int r,int c){
	int count=0,p=b.getposition()-1;
	int k;
	switch(b.getindex()){
		case(1):
			for(k=0;k<r+4;k++){
				if(count>=1 && T[k][p]==0 && T[k][p+1]==0 && T[k-1][p+2]==0){
					T[k][p]=1; T[k][p+1]=1; T[k-1][p+2]=1; count++;
					if(count==2) T[k-1][p]=0;
					else if(count>2){
						T[k-1][p]=0; T[k-2][p+1]=0; T[k-2][p+2]=0;
					}
				}else if(count==0 && T[k][p]==0 && T[k][p+1]==0){
					T[k][p]=1; T[k][p+1]=1; count++;
				}else break;
			}break;
		case(2):
		    for(k=0;k<r+4;k++){
		        if(count>=1 && T[k][p+1]==0 && T[k-1][p]==0){
					T[k][p+1]=1; T[k-1][p]=1; count++;
					if(count==3) T[k-2][p+1]=0;
					else if(count>3){
					    T[k-2][p+1]=0; T[k-3][p]=0; 
					}
				}else if(count==0 && T[k][p+1]==0){
		    		T[k][p+1]=1; count++;
				}else break;
			}break;	
		default:
		    break;	
	}
}
void ShapeZ(int**T,Shape b,int r,int c){
	int count = 0, p = b.getposition() - 1;
	int k;
	switch(b.getindex()){
		case(1):
		    for(k=0;k<r+4;k++){
				if(count>=1 && T[k][p+1]==0 && T[k][p+2]==0 && T[k-1][p]==0){
					T[k][p+1]=1; T[k][p+2]=1; T[k-1][p]=1; count++;
					if(count==2) T[k-1][p+2]=0;
					else{
						T[k-2][p]=0; T[k-2][p+1]=0; T[k-1][p+2]=0;
					}
				}else if(count==0 && T[k][p+1]==0 && T[k][p+2]==0){
					T[k][p+1]=1; T[k][p+2]=1; count++;
				}else break;
			}break;
		case(2):
		    for(k=0;k<r+4;k++){
				if(count>=1 && T[k][p]==0 && T[k-1][p+1]==0){
					T[k][p]=1; T[k-1][p+1]=1; count++;
					if(count==3) T[k-2][p]=0;
					else if(count>3){
						T[k-2][p]=0; T[k-3][p+1]=0;
					}
				}else if(count==0 && T[k][p]==0){
					T[k][p]=1; count++;
				}else break;
			}break;
		default:
		    break;	
	}
}
void ShapeI(int**T,Shape b,int r,int c){ 
	int count=0,p=b.getposition()-1;
	int k,j;
	switch(b.getindex()){
		case(1):
			for(k=0;k<r+4;k++){
			    if(T[k][p]==0){
				   if(count < 4){
					  T[k][p]=1;  count++;     
				}else{              
					T[k][p] = 1;
					T[k-count][p]= 0; }
			    }else break;
		    }break;
		case(2):
		     for(k=0;k<r+4;k++){
			     if(T[k][p]==0 && T[k][p+1]==0 && T[k][p+2]==0 && T[k][p+3]==0){
				    count =1;
				    for(j=p;j<p+4;j++){
					    T[k][j]=1;
					    if(k>0) T[k-1][j]=0;
				    }
			      }else break;
		     }break;
	    default:
		    break;	
	}
}
void ShapeO(int**T,Shape b,int r,int c){
	int count=0,p=b.getposition()-1;
	for(int k=0;k<r+4;k++){
	    if(T[k][p]==0 && T[k][p+1]==0 ){
	    	if(count<2){
	    	    T[k][p]=1; T[k][p+1]=1;
			    count++;
			}else{
	        	T[k][p]=1; T[k][p+1]=1;
	        	T[k-2][p]=0; T[k-2][p+1]=0;
			}
		}else break;
	}
}
void ShowT(int **T,int r,int c){
	for(int i=4;i<r+4;i++){
		for(int j=0;j<c;j++){
			fout << T[i][j] ;
		}
		fout << endl;
	}
	fout.close();
}
int Move(int **T,Shape b,int r,int c){
	int p,success=-1;
	fin >> p ; b.setposition(p);
	switch(b.gettype()){
		case('T'):
			ShapeT(T,b,r,c); break;
		case('L'):
		    ShapeL(T,b,r,c); break;
		case('J'):
		    ShapeJ(T,b,r,c); break;		
		case('S'):
			ShapeS(T,b,r,c); break;
		case('Z'):
		    ShapeZ(T,b,r,c); break;
		case('I'):
		    ShapeI(T,b,r,c); break;
	    case('O'):
	    	ShapeO(T,b,r,c); break;	
		default: break;		
	}
	success = Checklines(T,r,c);
	return success;	
}
int main(){
	if(!fin){ //check file
		cout << "Filein error!";
		exit(1);
	}
	if(!fout){
		cout << "Fileout error!";
		exit(1);
	}
	int m,n,success=-1;
	fin >> m >> n ;     //row,column
    int **T = Build(m,n);
    char t; int id;
	while(fin >> t && t!='E'){
		if(t!='O')
		   fin >> id;
        else if(t=='O')
           id=0;
		Shape b(t,id);      //set shape
		success = Move(T,b,m,n);  
		if(success==-1)
		  break;    
	} ShowT(T,m,n);
} 




