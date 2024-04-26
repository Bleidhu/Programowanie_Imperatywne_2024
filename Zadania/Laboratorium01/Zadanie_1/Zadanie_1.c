#include <stdio.h>

void linspace(double v[], double start, double stop, int n)
{
    double dist = (stop - start)/(n- 1);
    double val = 0;
    for(int i=0; i<n; ++i)
    {
        v[i] = start + val;
        val+=dist;
    }

}

void add(double v1[], const double v2[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        v1[i] += v2[i];
    }
}

double dot_product(const double v1[], const double v2[], int n)
{
    double ans = 0;
    for(int i = 0; i < n; ++i)
    {
        ans+=v1[i]*v2[i];
    }
    return ans;
}

void multiply_by_scalar(double v[], int n, double s)
{
    for(int i=0; i < n; ++i)
    {
        v[i] *= s;
    }
}

void range(double v[], int n, double start, double step)
{
    for(int i=0; i<n;++i)
    {
        v[i] = start;
        start += step;
    }
}

void read_vector(double v[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        scanf("%lf", &v[i]);
    }
}

void print_vector(double v[], int n)
{
    for(int i = 0; i < n; ++i)
    {
        printf("%.2lf ", v[i]);
    }
}

int main()
{
    int command;

    scanf("%d", &command);
    

   
    if(command == 1)
    {
        int n;
        double start;
        double stop;
        scanf("%d %lf %lf", &n, &start, &stop);
        double v[n];
        linspace(v, start, stop, n);
        print_vector(v, n);
    
    }
    if(command == 2)
    {
        int n;
        scanf("%d", &n);
        double v1[n];
        double v2[n];
        read_vector(v1, n);
        read_vector(v2, n);
        add(v1, v2, n);
        print_vector(v1, n);
    
    }
    if(command == 3)
    {
        int n;
        scanf("%d", &n);
        double v1[n];
        double v2[n];
        read_vector(v1, n);
        read_vector(v2, n);
        double dotprod = dot_product(v1, v2, n);
        printf("%.2lf", dotprod);
    }
    if(command == 4)
    {
        int n;
        double s;
        scanf("%d %lf", &n, &s);
        double v[n];
        read_vector(v, n);
        multiply_by_scalar(v, n, s);
        print_vector(v, n);
    }
    if(command == 5)
    {
        int n;
        double start;
        double step;
        scanf("%d %lf %lf", &n, &start, &step);
        double v[n];
        range(v, n, start, step);
        print_vector(v, n);
    }
    return 0;
}