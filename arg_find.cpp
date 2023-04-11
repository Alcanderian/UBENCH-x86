int binary_find_index_asc(int val, const int *val_arr, const int *index_arr, int length) {
    int left = 0;
    int right = length - 1;
    while(left <= right) {
        int mid = left + ((right - left) >> 1);
        int idx = index_arr[mid];
        if(val == val_arr[idx]) return idx;
        if(val < val_arr[idx]) right = mid - 1;
        else left = mid + 1;
    }
    return -1;
}

int linear_find_index_ooo(int val, const int *val_arr, int length) {
    auto find_beg = val_arr;
    auto find_end = val_arr + length;

    for(auto find = find_beg; find < find_end; ++find)
        if(*find == val)
            return find - find_beg;
    return -1;
}
