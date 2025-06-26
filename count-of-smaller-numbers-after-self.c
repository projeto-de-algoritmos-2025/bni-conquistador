/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

typedef struct Sol {
    int val,idx,inv;
} Sol;

void mergeAndCount(Sol *nums, int left, int mid, int right) {
    int i = left, j=mid+1, k=0;
    Sol temp[right-i+1];
    while ((i <= mid) && (j <= right)) {
        if (nums[i].val > nums[j].val) {
            nums[i].inv += right-j+1;
            temp[k++] = nums[i++];
        } else temp[k++] = nums[j++];

    }
    while (i <= mid) temp[k++] = nums[i++];
    while (j <= right) temp[k++] = nums[j++];
    for (i = left, k=0; i <= right; i++,k++) nums[i] = temp[k];
}

void mergeSortAndCount(Sol *nums, int left, int right) {
    if (right > left) {
        int mid = (right + left) / 2;
        mergeSortAndCount(nums, left, mid);
        mergeSortAndCount(nums, mid + 1, right);
        mergeAndCount(nums, left, mid, right);
    }
    return;
}

int* countSmaller(int* nums, int numsSize, int* returnSize) {
    Sol sol[numsSize];
    for (int i=0;i<numsSize;i++) {
        sol[i].val = nums[i];
        sol[i].idx = i;
        sol[i].inv = 0;
    }
    mergeSortAndCount(sol, 0, numsSize-1);
    *returnSize = numsSize;
    int* res = malloc(numsSize*sizeof(int));
    for (int i=0;i<numsSize;i++) res[sol[i].idx] = sol[i].inv;
    return res;
}
