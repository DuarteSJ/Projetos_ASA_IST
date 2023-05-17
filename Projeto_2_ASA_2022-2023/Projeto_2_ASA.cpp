/*grupo 93*/
#include <iostream>
#include <vector>
#include <string.h>
#include <unordered_map>


int n=0, m=0, maxsquaresize = 0;
std::unordered_map<uint64_t, unsigned long long int> memo;

uint64_t convertArrToStr(std::vector<int> const &v){

    uint64_t code = 0;
    for (int i=0; i<n; i++){
        code = code*100 +v[i];
    }
    return code;
}

std::vector<int> readFile(){

    scanf("%d %d", &n, &m);
    std::vector<int> v(n);
    for (int i=0; i<n; i++){
        scanf("%d", &v[i]);
    }

    return v;
}

int maxElement(std::vector<int> const &v){
    if (v.empty())
        return -1;

    int max = v[0];

    for(int i=1;i<n;i++){
        if (v[i]>max)
            max = v[i];
    }
    return max;
}

void findLargestSquare(std::vector<int> const &v){
    int line = 0,col = 0;
    line = n-1;
    col = 1;
    while (line>=0 && v[line]>=col){
        line-=1;
        col+=1;
    }
    maxsquaresize = col-1;
}

int min3(int num1,int num2, int num3){
    if(num1 <= num2 && num1 <= num3)
	{
		return num1;
	}
	else if(num2 <= num3)
	{
        return num2;
	}
	else
	{
		return num3;
	}	
}

bool isGridFull(std::vector<int> &v){
    int c = maxElement(v);
    if (c==1 || c==0)
        return true;
    return false;
}

unsigned long long int countWaysRecursive(std::vector<int> &v){
    uint64_t vect = convertArrToStr(v);
    if (memo.find(vect) != memo.end())
        return memo[vect];
        

    if (isGridFull(v))
        return 0;

    int max_col=0,linha=0;
    unsigned long long int sol=0;
    max_col = maxElement(v)-1;

    for (int i=0;i<n;i++){
        if(v[i] == max_col+1){
            linha = i;
            break;
        }
    }

    int flag=0;
    unsigned long long int sum = 0;
    std::vector<int> lst(v);

    for (int j= min3(maxsquaresize, max_col, n-linha-1); j>=0;j--){
        flag = 0;
        lst = v;

        if ( (linha+j>=n) || (v[linha+j] < v[linha]) || (v[linha]-j<=0))
            continue;
        
        for (int k=j; k>=0; k--){
            if ((v[linha+k] < v[linha])){
                flag = 1;
                break;
            }
            else
                lst[linha+k]-=j+1;
        }

        if (flag==1)
            continue;
        sum = 0;
        if (j)
            sum=1;

        sol += sum + countWaysRecursive(lst);
    }

    memo.insert({vect,sol});
    return sol;
}

int main(){
    unsigned long long int has_solutions=0;
    std::vector<int> v = readFile();
    findLargestSquare(v);

    for(int i=n-1; i>=0; i--){
        if (v[i] != 0){
            has_solutions = 1;
            break;
        }
    }
    printf("%lld\n", countWaysRecursive(v) + has_solutions);
}