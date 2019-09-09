#include <stdio.h>
#include <stdlib.h>

#define n 4

int tree[2*n - 1];
int array[n];

void build(int i, int l, int r){
    if(l == r)
        tree[i] = array[l];
    else{
        int m = (l + r) / 2;

        build(2*i, l, m);
        build(2*i + 1, m + 1, r);

        tree[i] = tree[2*i] + tree[2*i + 1];
    }
}


void update(int pos, int value, int idx, int l, int r)
{    
    tree[idx] += ( value - array[pos] ); 
    if (r - l < 2) 
    {
        array[pos] = value;
        return;
    }
    int mid = (l+r) / 2;
    
    if (pos < mid) 
    {
        update(pos, value, idx*2, l, mid);
    }
    else
    {
        update(pos, value, idx*2+1, mid, r);
    }
}

int search(int x, int y, int idx, int l, int r)
{    
    if (x >= r || y <= l) 
    {
        return 0;
    }
    if (x <= l && y >= r)
    {        
        return tree[idx];
    }
    int m = (l + r) / 2;    
    return search(x, y, idx * 2, l, m) + search(x, y, idx * 2 + 1, m, r);
}



int main(){
    return 0;
}