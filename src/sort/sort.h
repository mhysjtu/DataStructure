//insert
template< class T >
void insert_sort(T a[], int size){
    int j;
    T tmp;
    for (int i = 1; i < size; ++i){
        tmp = a[i];
        for (j = i-1; j >=0&& a[j]>tmp; --j){
            a[j+1]=a[j];
        }
        a[j+1]=tmp;
    }
}

//shell 
template< class T >
void shell_sort(T a[], int size){
    int i, j, step;
    T tmp;
    for(step=size/2;step>0;step/=2){
        for(i = step; i<size; ++i){//必须是++i，交替对子数组进行插入排序
            tmp = a[i];
            for(j = i-step;j>=0&&a[j]>tmp;j-=step){
                a[j+step]=a[j];
            }
            a[j+step]=tmp;
        }
    }
}

//select
template< class T >
void select_sort(T a[], int size){
    int tmp_min;
    T tmp;
    for(int i=0;i<size-1;++i){
        tmp_min = i;
        for(int j=i+1;j<size;++j){
            if(a[j]<a[tmp_min]) 
                tmp_min = j;
        }
        tmp = a[i];
        a[i] = a[tmp_min];
        a[tmp_min] = tmp;
    }
}

//heap
template< class T >
void percolateDown(T a[], int hole, int size){
    T tmp = a[hole];

    for(int child=0;hole*2+1<size;hole = child){
        child = hole*2+1;
        if(child!=size-1 && a[child+1]>a[child])
            ++child;
        if(a[child]>tmp)
            a[hole] = a[child];
        else
            break;
    }
    a[hole] = tmp;
}

template< class T >
void heap_sort(T a[], int size){
    T tmp;
    //构造最大堆
    //从后面开始过滤，这样对前面过滤时后面大部分都已经有序了
    for(int i=size/2-1;i>=0;--i)
        percolateDown(a, i, size);
    
    //出堆
    for(int i = size-1;i>0;--i){
        //删除根节点（最大值），和堆中最后一个交换
        //然后对根节点执行向下过滤，使堆重新有序
        tmp = a[0];
        a[0] = a[i];
        a[i]=tmp;
        //向下过滤
        percolateDown(a, 0, i);
    }
}

//bubble
template< class T >
void bubble_sort(T a[], int size){
    T tmp;
    for(int i=0;i<size-1;++i){
        bool swapped = false;
        for(int j = 0; j<size-i-1;++j){
            if(a[j]>a[j+1]){
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1]=tmp;
                swapped = true;
            }
        }
        if(!swapped)
            break;
    }
}
