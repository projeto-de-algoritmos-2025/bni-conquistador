int inv_count = 0;

void mergeAndCount(int *nums, int left, int mid, int right) {
    int i = left, j=mid+1, k=0;
    while(i<=mid && j<=right){
        long long t=2*(long)nums[j];
        while(i<=mid && nums[i]<=t)i++;
        inv_count+=(mid-i+1);
        j++;
    }
    i=left, j=mid+1;
    int temp[right-i+1];
    while ((i <= mid) && (j <= right)) {
        if (nums[i] <= nums[j]) temp[k++] = nums[i++];
        else temp[k++] = nums[j++];
    }
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= right) temp[k++] = nums[j++];
    for (i = left, k=0; i <= right; i++,k++) nums[i] = temp[k];
}

void mergeSortAndCount(int *nums, int left, int right) {
    if (right > left) {
        int mid = (right + left) / 2;
        mergeSortAndCount(nums, left, mid);
        mergeSortAndCount(nums, mid + 1, right);
        mergeAndCount(nums, left, mid, right);
    }
    return;
}

int reversePairs(int* nums, int numsSize) {
    inv_count = 0;
    mergeSortAndCount(nums, 0, numsSize-1);
    return inv_count;
}
