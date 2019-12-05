#include<stdio.h>
#include<stdlib.h>
#include "functions.h"
#include<math.h>

//数组冒泡排序
void sort(float* arr,int num){
	for(int x = 0;x < num - 1;x++){
		for(int i = 0;i < num - 1 - x;i++){
			float p;arr[i] > arr[i+1]?(p = arr[i],arr[i]=arr[i+1],arr[i+1]=p):1;
		}
	}
}

//平均数
float mean(float* arr,int num){float sum = 0; for(int i = 0;i < num;i++) sum += arr[i]; return sum/num;}

//众数*****可用 待改进
struct mode_retrn mode(float* arr,int num){
	struct mode_retrn indicate;
	indicate.num = 1;
	int store[num]; for(int i = 0;i < num;i++) store[i] = 1;
	int p = 0; for(int i = 0;i < num;i++) arr[i] == arr[i+1]?store[p]++:p++;
	int q = 0; for(int i = 0;i < num - 1;i++) store[q] > store[i+1]? :(q = i + 1);
	if(store[q] != 1){
		indicate.num = arr[q];
		indicate.ch = 'Y';
		return indicate;
	}
	else{
		indicate.ch = 'N';
		return indicate;
	}
	
}

//方差
float variance(float* arr,int num,float mean){
	float sum = 0; 
	for(int i = 0;i < num;i++) sum += (arr[i]-mean)*(arr[i]-mean);
	return sum/(num - 1);
}

//四分位数
float qtl(float* arr,int num,int where){
	float dot = where*(num + 1.0)/4.0;
	float pst = (float)dot - (int)dot;
	return arr[(int)dot - 1]*(1-pst) + arr[(int)dot]*pst;
}

//偏态系数
float skew(float* arr,int num,float mean,float std_dvt){
	float sum = 0;
	for(int i = 0;i < num;i++){
		float p = (arr[i] - mean);
		sum += p*p*p;
	}
	return num*sum/((num - 1)*(num - 2)*std_dvt*std_dvt);
}

//峰态系数
float kurtosis(float* arr,int num,float mean,float std_dvt){
	float sum1,sum2 = 0;
	float std4 = std_dvt*std_dvt*std_dvt*std_dvt*std_dvt;
	for(int i = 0;i < num;i++){
		float p = arr[i] - mean;
		p = p*p;
		sum1 += p*p; sum2 += p;
	}
	return (num*(num + 1)*sum1 - 3*sum2*sum2*(num - 1)) / ((num - 1)*(num - 2)*(num - 3)*std4);
}

struct information gnrl_statistics(float *arr,int num){										
	sort(arr,num);												//从小到大排序
	struct information store;
	struct mode_retrn new = mode(arr,num);						//众数判断后直接输出

	store.mean_ = mean(arr,num);  								//均值
	store.mid_ = qtl(arr,num,2);								//中位数
	store.variance_ = variance(arr,num,store.mean_);  				//方差
	store.std_variance_ = sqrt(store.variance_);						//标准差
	store.qtl_up_ = qtl(arr,num,3);								//上四分位数
	store.qtl_low_ = qtl(arr,num,1);							//下四分位数
	store.qtl_rg_ = store.qtl_up_ - store.qtl_low_;							//四分位差
	store.cv_ = store.std_variance_/store.mean_;								//离散系数
	store.skew_ = skew(arr,num,store.mean_,store.std_variance_);				//偏态系数
	store.kurtosis_ = kurtosis(arr,num,store.mean_,store.std_variance_); 	//峰态系数
	store.range_ = arr[num - 1] - arr[0];						//全距

	return store;
}