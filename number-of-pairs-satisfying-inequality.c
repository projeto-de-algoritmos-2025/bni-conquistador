//nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff
long long int inv_count;
void mergeAndCount(int *nums, int left, int mid, int right, int diff) {
    int i = left, j=mid+1, k=0;
    while(i<=mid && j<=right){
        while(j<=right && nums[i] > nums[j] + diff)j++;
        inv_count+=(right-j+1);
        i++;
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

void mergeSortAndCount(int *nums, int left, int right, int diff) {
    if (right > left) {
        int mid = (right + left) / 2;
        mergeSortAndCount(nums, left, mid, diff);
        mergeSortAndCount(nums, mid + 1, right, diff);
        mergeAndCount(nums, left, mid, right, diff);
    }
    return;
}

long long numberOfPairs(int* nums1, int nums1Size, int* nums2, int nums2Size, int diff) {
    int nums[nums1Size];
    inv_count = 0;
    for (int i=0;i<nums1Size;i++) nums[i] = nums1[i]-nums2[i];
    mergeSortAndCount(nums,0,nums1Size-1, diff);
    return inv_count;
}
