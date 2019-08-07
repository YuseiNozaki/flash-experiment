#include <stdio.h>
#include <math.h>


// read data into array
void data_read(char [], double [], double [], int *);

// log of array
void log_arr(double [], int);

// least squares method
void lsm(double [], double [], int, double *, double *);


int main(){

	int n;
	double time[1024], abs[1024], a, b;
	char fname[1024];

	printf("file name:");

	scanf("%s", fname);

	data_read(fname, time, abs, &n);

	log_arr(abs, n);

	lsm(time, abs, n, &a, &b);

	printf("a = %f\nb = %f\n", a, b);
	
	printf("expr = exp(%f) * exp(%f * x)\n", b, a);

	return 0;
}


// read date into array
void data_read(char fname[], double x[], double y[], int *n){

	FILE *fp;
	int ret, i=0;
	
	fp = fopen(fname, "r");

	if(fp == NULL){
		printf("File could not be opened.\n");
	}

	while((ret = fscanf(fp, "%lf, %lf", &x[i], &y[i])) != EOF){
		i++; 
	}	

	*n = i;
	
        fclose(fp);
}


// log of array
void log_arr(double arr[], int n){

	int i;

	for(i=0; i<n; i++){
		arr[i] = log(arr[i]);
	}
}


// least squares method
void lsm(double x[], double y[], int n, double *a, double *b){
    
    	int i, j;
    	double x_ave = 0, y_ave = 0, x_dis = 0, cov = 0;

    	// average of x,y
    	for(i=0; i<n; i++){
        	x_ave += x[i] / n;
        	y_ave += y[i] / n;
    	}

    	// dispersion of x
    	// covariance
    	for(j=0; j<n; j++){
        	x_dis += (x[j] - x_ave) * (x[j] - x_ave) / n;
        	cov += (x[j] - x_ave) * (y[j] - y_ave) / n;
    	}

	*a = cov / x_dis;

	*b = y_ave - *a * x_ave;
}
