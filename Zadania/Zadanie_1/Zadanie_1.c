#include <cstdin>

void linspace(double v[], double start, double stop, int n)
{
    int dist = (stop - start)/n;

    for(int i=0; i<n; ++i)
    {
        v[i] = start + n;
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
    
}

int main()
{
    int v1[] = {25, 50, 75, 100};

    multiply_by_scalar(v1, 4, 2);
    for(int i = 0; i < 4; ++i)
    {
        printf("%d", v1[i])
    }
    return 0;
}