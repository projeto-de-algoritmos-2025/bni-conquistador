#define less(A,B) ((A) < (B))

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int k = 0, i = 0, ii = 0, nsize = nums1Size + nums2Size, m = (nsize-1)/2, v[nsize];
	while (i < nums1Size && ii < nums2Size)
		if (less(nums1[i], nums2[ii])) v[k++] = nums1[i++];
		else v[k++] = nums2[ii++];
	while (i < nums1Size) v[k++] = nums1[i++];
	while (ii < nums2Size) v[k++] = nums2[ii++];
	return nsize % 2 == 0 ? (v[m+1] + v[m]) / 2.0 : (double)v[m];
}
